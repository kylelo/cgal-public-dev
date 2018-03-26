// Copyright (c) 2017 CNRS and LIRIS' Establishments (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Guillaume Damiand <guillaume.damiand@liris.cnrs.fr>
//
#ifndef CGAL_PATH_ON_SURFACE_H
#define CGAL_PATH_ON_SURFACE_H 1

#include <stack>
#include <CGAL/Union_find.h>
#include <CGAL/Path_generators.h>
#include <boost/unordered_map.hpp>

namespace CGAL {

template<typename Map_>
class Path_on_surface
{
public:
  typedef Map_ Map;
  typedef typename Map::Dart_handle Dart_handle;
  typedef typename Map::Dart_const_handle Dart_const_handle;

  typedef Path_on_surface<Map> Self;

  Path_on_surface(const Map& amap) : m_map(amap), m_is_closed(false)
  {}

  void swap(Self& p2)
  {
    assert(&m_map==&(p2.m_map));
    m_path.swap(p2.m_path);
    std::swap(m_is_closed, p2.m_is_closed);
  }

  // @return true iff the path is empty
  bool is_empty() const
  { return m_path.empty(); }

  std::size_t length() const
  { return m_path.size(); }

  // @return true iff the path is closed (update after each path modification).
  bool is_closed() const
  { return m_is_closed; }

  const Map& get_map() const
  { return m_map; }

  void clear()
  { m_path.clear(); }
  
  std::size_t next_index(std::size_t i) const
  { return (is_closed() && i==m_path.size()-1?0:i+1); }

  std::size_t prev_index(std::size_t i) const
  { return (is_closed() && i==0?m_path.size()-1:i-1); }

  Dart_const_handle get_ith_dart(std::size_t i) const
  {
    assert(i<=m_path.size());
    return m_path[(i==m_path.size()?0:i)];
  }
  
  Dart_const_handle operator[] (std::size_t i) const
  {
    assert(i<=m_path.size());
    return m_path[((is_closed() && i==m_path.size())?0:i)];
  }

  Dart_const_handle back() const
  {
    assert(!is_empty());
    return m_path.back();
  }
  
  void push_back(Dart_const_handle dh)
  {
    assert(dh!=NULL && dh!=m_map.null_dart_handle);
    assert((is_empty() ||
           CGAL::template belong_to_same_cell<Map, 0>
           (m_map, m_map.other_extremity(back()), dh)));

    m_path.push_back(dh);
    update_is_closed();
  }

  // @return true iff the path is valid; i.e. a sequence of edges two by
  //              two adjacent.
  bool is_valid() const
  {
    for (unsigned int i=1; i<m_path.size(); ++i)
    {
      if (m_path[i]==NULL || m_path[i]==m_map.null_dart_handle)
      { return false; }

      Dart_const_handle pend=m_map.other_extremity(m_path[i-1]);
      if (pend==Map::null_handle) { return false; }

      if (!CGAL::template belong_to_same_cell<Map,0>(m_map, m_path[i], pend))
      { return false; }
    }
    if (is_closed())
    {
      Dart_const_handle pend=m_map.other_extremity(m_path[m_path.size()-1]);
      if (pend==Map::null_handle) { return false; }
      if (!CGAL::template belong_to_same_cell<Map,0>(m_map, pend, m_path[0]))
      { return false; }
    }

    return true;
  }

  // Update m_is_closed to true iff the path is closed (i.e. the second
  //   extremity of the last dart of the path is the same vertex than the one
  //   of the first dart of the path).
  void update_is_closed()
  {
    if (is_empty()) { m_is_closed=false; } // or true by vacuity ?
    if (!is_valid()) { m_is_closed=false; } // Interest ??

    Dart_const_handle pend=m_map.other_extremity(back());
    if (pend==Map::null_handle) { m_is_closed=false; }

    m_is_closed=CGAL::belong_to_same_cell<Map,0>(m_map, m_path[0], pend);
  }

  // @return true iff the path does not pass twice through a same edge
  //              or a same vertex.
  bool is_simple() const
  {
    typename Map::size_type markvertex=m_map.get_new_mark();
    typename Map::size_type markedge=m_map.get_new_mark();

    bool res=true;
    unsigned int i=0;
    for (i=0; res && i<m_path.size(); ++i)
    {
      if (m_map.is_marked(m_path[i], markvertex)) res=false;
      if (m_map.is_marked(m_path[i], markedge)) res=false;

      CGAL::mark_cell<Map, 0>(m_path[i], markvertex);
      CGAL::mark_cell<Map, 1>(m_path[i], markedge);
    }

    i=0;
    while(m_map.number_of_marked_darts(markedge)>0)
    {
      assert(i<m_path.size());
      CGAL::unmark_cell<Map, 0>(m_path[i], markvertex);
      CGAL::unmark_cell<Map, 1>(m_path[i], markedge);
      ++i;
    }

    m_map.free_mark(markvertex);
    m_map.free_mark(markedge);

    return res;
  }

  /// @return the turn between dart number i and dart number i+1.
  ///         (turn is position of the second edge in the cyclic ordering of
  ///          edges starting from the first edge around the second extremity
  ///          of the first dart)
  std::size_t next_turn(std::size_t i) const
  {
    assert(is_valid());
    assert(i<m_path.size());

    if (!is_closed() && i==length()-1)
    { return 0; }

    Dart_const_handle d1=m_path[i];
    Dart_const_handle d2=get_ith_dart(i+1); // Work also for the last dart for cycles
    assert(d1!=d2);

    std::size_t res=1;
    while (m_map.template beta<1>(d1)!=d2)
    {
      ++res;
      d1=m_map.template beta<1, 2>(d1);
    }
    // std::cout<<"next_turn="<<res<<std::endl;
    return res;
  }

  /// Same than next_turn but turning in reverse orientation around vertex.
  std::size_t next_negative_turn(std::size_t i) const
  {
    assert(is_valid());
    assert(i<m_path.size());

    if (!is_closed() && i==length()-1)
    { return 0; }

    Dart_const_handle d1=m_map.template beta<2>(m_path[i]);
    Dart_const_handle d2=m_map.template beta<2>(get_ith_dart(i+1)); // Work also for the last dart for cycles
    assert(d1!=d2);

    std::size_t res=1;
    while (m_map.template beta<0>(d1)!=d2)
    {
      ++res;
      d1=m_map.template beta<0, 2>(d1);
    }
    // std::cout<<"next_negative_turn="<<res<<std::endl;
    return res;
  }

  std::size_t find_end_of_braket(std::size_t begin, bool positive) const
  {
    assert((positive && next_turn(begin)==1) ||
           (!positive && next_negative_turn(begin)==1));
    std::size_t end=begin+1;
    if (!is_closed() && end==m_path.size()-1)
    { return begin; } // begin is the before last dart

    while ((positive && next_turn(end)==2) ||
           (!positive && next_negative_turn(end)==2))
    { end=next_index(end); }
    
    if ((positive && next_turn(end)==1) ||
        (!positive && next_negative_turn(end)==1)) // We are on the end of a bracket
    { end=next_index(end); }
    else
    { end=begin; }
    
    return end;
  }

  void transform_positive_bracket(std::size_t begin, std::size_t end,
                                  Self& new_path)
  {
    // There is a special case for (1 2^r). In this case, we need to ignore
    // the two darts begin and end
    Dart_const_handle d1=(next_index(begin)!=end?
          m_map.template beta<0>(get_ith_dart(begin)):
          m_map.template beta<1,2,0>(get_ith_dart(end)));
    Dart_const_handle d2=(next_index(begin)!=end?
          m_map.template beta<2,0,2>(get_ith_dart(end)):
          m_map.template beta<0,0,2>(get_ith_dart(begin)));

    new_path.push_back(m_map.template beta<2>(d1));
    CGAL::extend_straight_negative_until(new_path, d2);
  }

  void transform_negative_bracket(std::size_t begin, std::size_t end,
                                  Self& new_path)
  {
    // There is a special case for (-1 -2^r). In this case, we need to ignore
    // the two darts begin and end
    Dart_const_handle d1=(next_index(begin)!=end?
          m_map.template beta<2,1>(get_ith_dart(begin)):
          m_map.template beta<2,0,2,1>(get_ith_dart(end)));
    Dart_const_handle d2=(next_index(begin)!=end?
          m_map.template beta<1>(get_ith_dart(end)):
          m_map.template beta<2,1,1>(get_ith_dart(begin)));

    new_path.push_back(d1);
    CGAL::extend_straight_positive_until(new_path, d2);
  }

  void transform_bracket(std::size_t begin, std::size_t end,
                         Self& new_path,
                         bool positive)
  {
    if (positive)
    { transform_positive_bracket(begin, end, new_path); }
    else
    { transform_negative_bracket(begin, end, new_path); }
  }

  // copy all darts starting from begin and going to the dart before end
  // from this path to new_path.
  void copy_rest_of_path(std::size_t begin, std::size_t end,
                         Self& new_path)
  {
    assert(end<=length());
    assert(begin<=end);
    while(begin!=end)
    {
      new_path.push_back(get_ith_dart(begin));
      ++begin;
    }
  }

  bool bracket_flattening_one_step()
  {
    if (is_empty()) return false;

    Self new_path(m_map);
    bool positive=false;
    std::size_t begin, end;

    for (begin=0; begin<m_path.size()-1; ++begin)
    {
      positive=(next_turn(begin)==1);
      if (positive || next_negative_turn(begin)==1)
      {
        // we test if begin is the beginning of a bracket
        end=find_end_of_braket(begin, positive);
        if (begin!=end)
        {
          /* std::cout<<"Bracket: ["<<begin<<"; "<<end<<"] "
                   <<(positive?"+":"-")<<std::endl; */
          if (end<begin)
          {
            if (!is_closed())
            { return false; }

            copy_rest_of_path(end+1, begin, new_path);
          }
          else if (next_index(begin)!=end) // Special case of (1 2^r)
          { copy_rest_of_path(0, begin, new_path); }

          transform_bracket(begin, end, new_path, positive);

          if (begin<end && next_index(begin)!=end && end<length()-1)
          { copy_rest_of_path(end+1, length(), new_path); }

          swap(new_path);
          return true;
        }
      }
    }

    return false;
  }

  // Simplify the path by removing all brackets
  bool bracket_flattening()
  {
    bool res=false;
    while(bracket_flattening_one_step())
    { res=true; }
    return res;
  }
  
  bool remove_spurs_one_step()
  {
    if (is_empty()) return false;

    bool res=false;
    std::size_t i;
    Self new_path(m_map);
    for (i=0; i<m_path.size()-1; )
    {
      if (m_path[i]==m_map.template beta<2>(m_path[i+1]))
      {
        i+=2;
        res=true;
      }
      else
      {
        new_path.push_back(m_path[i]); // We copy this dart
        ++i;
      }
    }
    if (i==m_path.size()-1)
    { new_path.push_back(m_path[m_path.size()-1]); }

    swap(new_path);
    return res;
  }

  // Simplify the path by removing all spurs
  bool remove_spurs()
  {
    bool res=false;
    while(remove_spurs_one_step())
    { res=true; }
    return res;
  }

  // Simplify the path by removing all possible brackets and spurs

  void simplify()
  {
    bool modified=false;
    do
    {
      modified=bracket_flattening_one_step();
      if (!modified)
      { modified=remove_spurs_one_step(); }
    }
    while(modified);
  }

  bool find_l_shape(std::size_t begin,
                    std::size_t& middle,
                    std::size_t& end) const
  {
    assert(next_negative_turn(begin)==1 || next_negative_turn(begin)==2);
    end=begin+1;
    if (end==m_path.size()-1 && !is_closed())
    { return false; } // begin is the before last dart

    while (next_negative_turn(end)==2 && end!=begin)
    { end=next_index(end); }

    if (begin==end)
    { // Case of a path having only 2 turns
      return true;
    }

    if (next_negative_turn(end)==1)
    {
      middle=end;
      end=next_index(end);
    }
    else
    { return false; }

    while (next_negative_turn(end)==2 && end!=begin)
    { end=next_index(end); }

    return true;
  }

  void push_l_shape(std::size_t begin,
                    std::size_t middle,
                    std::size_t end,
                    Self& new_path)
  {
    assert(begin!=middle);
    assert(middle!=end);

    Dart_const_handle d1=
        m_map.template beta<2,1>(get_ith_dart(begin));
    new_path.push_back(d1);

    CGAL::extend_uturn_positive(new_path, 1);

    d1=m_map.template beta<2,1,1>(get_ith_dart(middle));
    CGAL::extend_straight_positive_until(new_path, d1);

    CGAL::extend_uturn_positive(new_path, 3);

    d1=m_map.template beta<2,0,2,1>(get_ith_dart(end));
    CGAL::extend_straight_positive_until(new_path, d1);

    CGAL::extend_uturn_positive(new_path, 1);
  }

  bool right_push_one_step()
  {
    std::size_t begin, middle, end;
    std::size_t next_turn;
    for (begin=0; begin<m_path.size()-1; ++begin)
    {
      next_turn=next_negative_turn(begin);
      if (next_turn!=2)
      {
        if (find_l_shape(begin, middle, end))
        {
          Self new_path(m_map);
          if (begin==end)
          { // Special case of (-2^l)
            // TODO
            assert(false);
            return true;
          }

          if (end<begin)
          {
            if (!is_closed())
            { return false; }

            copy_rest_of_path(end+1, begin, new_path);
          }
          else // TODO SPECIAL CASES ??
          { copy_rest_of_path(0, begin, new_path); }

          push_l_shape(begin, middle, end, new_path);

          if (begin<end /* && XXX (TODO SPECIAL CASES ??)*/)
          { copy_rest_of_path(end+1, length(), new_path); }

          swap(new_path);
          return true;
        }
      }
    }
    return false;
  }

  bool right_push()
  {
    bool res=false;
    while(right_push_one_step())
    { res=true; }
    return res;
  }

  void display_positive_turns() const
  {
    std::cout<<"(";
    if (!is_empty())
    {
      std::size_t i;
      for (i=0; i<m_path.size()-1; ++i)
      {
        if (m_path[i]==m_map.template beta<2>(m_path[i+1]))
        { std::cout<<"0 "; }
        else { std::cout<<next_turn(i)<<" "; }
      }
      if (is_closed())
      {
        if (m_path[i]==m_map.template beta<2>(m_path[0]))
        { std::cout<<"0 "; }
        else { std::cout<<next_turn(i)<<" "; }
      }
    }
    std::cout<<")";
  }

  void display_negative_turns() const
  {
    std::cout<<"(";
    if (!is_empty())
    {
      std::size_t i;
      for (i=0; i<m_path.size()-1; ++i)
      {
        if (m_path[i]==m_map.template beta<2>(m_path[i+1]))
        { std::cout<<"0 "; }
        else { std::cout<<"-"<<next_negative_turn(i)<<" "; }
      }
      if (is_closed())
      {
        if (m_path[i]==m_map.template beta<2>(m_path[0]))
        { std::cout<<"0 "; }
        else { std::cout<<"-"<<next_negative_turn(i)<<" "; }
      }
    }
    std::cout<<")";
  }

  void reverse()
  {
    std::vector<Dart_const_handle> new_path(m_path.size());
    for (std::size_t i=0; i<m_path.size(); ++i)
    {
      new_path[m_path.size()-1-i]=m_map.template beta<2>(m_path[i]);
    }
    new_path.swap(m_path);
  }

protected:
  const Map& m_map; // The underlying map
  std::vector<Dart_const_handle> m_path; // The sequence of darts
  bool m_is_closed; // True iff the path is a cycle
};

} // namespace CGAL

#endif // CGAL_PATH_ON_SURFACE_H //
// EOF //
