// ============================================================================
//
// Copyright (c) 1999,2000,2001,2002,2003 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : include/CGAL/Triangulation_ds_cell_base_3.h
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//
// coordinator   : INRIA Sophia Antipolis
//
// ============================================================================

// cell of a triangulation data structure of any dimension <=3

#ifndef CGAL_TRIANGULATION_DS_CELL_BASE_3_H
#define CGAL_TRIANGULATION_DS_CELL_BASE_3_H

#include <CGAL/basic.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_3.h>
#include <CGAL/Dummy_tds_3.h>

CGAL_BEGIN_NAMESPACE

template < typename TDS = void >
class Triangulation_ds_cell_base_3
{
public:
  typedef TDS                          Triangulation_data_structure;
  typedef typename TDS::Vertex_handle  Vertex_handle;
  typedef typename TDS::Cell_handle    Cell_handle;

  template <typename TDS2>
  struct Rebind_TDS { typedef Triangulation_ds_cell_base_3<TDS2> Other; };

  Triangulation_ds_cell_base_3()
  {
    set_vertices();
    set_neighbors();
  }

  Triangulation_ds_cell_base_3(Vertex_handle v0, Vertex_handle v1,
                               Vertex_handle v2, Vertex_handle v3)
  {
    set_vertices(v0, v1, v2, v3);
    set_neighbors();
  }

  Triangulation_ds_cell_base_3(Vertex_handle v0, Vertex_handle v1,
                               Vertex_handle v2, Vertex_handle v3,
                               Cell_handle   n0, Cell_handle   n1,
                               Cell_handle   n2, Cell_handle   n3)
  {
    set_vertices(v0, v1, v2, v3);
    set_neighbors(n0, n1, n2, n3);
  }

  // ACCESS FUNCTIONS

  const Vertex_handle vertex(int i) const
  {
    CGAL_triangulation_precondition( i >= 0 && i <= 3 );
    return V[i];
  } 

  bool has_vertex(const Vertex_handle v) const
  {
    return (V[0] == v) || (V[1] == v) || (V[2]== v) || (V[3]== v);
  }
    
  bool has_vertex(const Vertex_handle v, int & i) const
    {
      if (v == V[0]) { i = 0; return true; }
      if (v == V[1]) { i = 1; return true; }
      if (v == V[2]) { i = 2; return true; }
      if (v == V[3]) { i = 3; return true; }
      return false;
    }
    
  int index(const Vertex_handle v) const
  {
    if (v == V[0]) { return 0; }
    if (v == V[1]) { return 1; }
    if (v == V[2]) { return 2; }
    CGAL_triangulation_assertion( v == V[3] );
    return 3;
  }

  Cell_handle neighbor(int i) const
  {
    CGAL_triangulation_precondition( i >= 0 && i <= 3);
    return N[i];
  }
    
  bool has_neighbor(const Cell_handle n) const
  {
    return (N[0] == n) || (N[1] == n) || (N[2] == n) || (N[3] == n);
  }
    
  bool has_neighbor(const Cell_handle n, int & i) const
  {
    if(n == N[0]){ i = 0; return true; }
    if(n == N[1]){ i = 1; return true; }
    if(n == N[2]){ i = 2; return true; }
    if(n == N[3]){ i = 3; return true; }
    return false;
  }
    
  int index(const Cell_handle n) const
  {
    if (n == N[0]) return 0;
    if (n == N[1]) return 1;
    if (n == N[2]) return 2;
    CGAL_triangulation_assertion( n == N[3] );
    return 3;
  }
 
  // SETTING

  void set_vertex(int i, Vertex_handle v)
  {
    CGAL_triangulation_precondition( i >= 0 && i <= 3);
    V[i] = v;
  }
    
  void set_neighbor(int i, Cell_handle n)
  {
    CGAL_triangulation_precondition( i >= 0 && i <= 3);
    N[i] = n;
  }

  void set_vertices()
  {
    V[0] = V[1] = V[2] = V[3] = NULL;
  }
    
  void set_vertices(Vertex_handle v0, Vertex_handle v1,
                    Vertex_handle v2, Vertex_handle v3)
  {
    V[0] = v0;
    V[1] = v1;
    V[2] = v2;
    V[3] = v3;
  }
    
  void set_neighbors()
  {
    N[0] = NULL;
    N[1] = NULL;
    N[2] = NULL;
    N[3] = NULL;
  }
    
  void set_neighbors(Cell_handle n0, Cell_handle n1,
                     Cell_handle n2, Cell_handle n3)
  {
    N[0] = n0;
    N[1] = n1;
    N[2] = n2;
    N[3] = n3;
  }

  // CHECKING

  // the following trivial is_valid allows
  // the user of derived cell base classes 
  // to add their own purpose checking
  bool is_valid(bool, int ) const
    {return true;}

  // Obsolete : it's redundant with the default constructor.
  void init() const
  {}

private:
  Cell_handle   N[4];
  Vertex_handle V[4];
};

template < class TDS >
inline
std::istream&
operator>>(std::istream &is, Triangulation_ds_cell_base_3<TDS> &)
  // non combinatorial information. Default = nothing
{
  return is;
}

template < class TDS >
inline
std::ostream&
operator<<(std::ostream &os, const Triangulation_ds_cell_base_3<TDS> &)
  // non combinatorial information. Default = nothing
{
  return os;
}

// Specialisation for void.
template <>
class Triangulation_ds_cell_base_3<void>
{
public:
  typedef Dummy_tds_3                   Triangulation_data_structure;
  typedef Triangulation_data_structure::Vertex_handle   Vertex_handle;
  typedef Triangulation_data_structure::Cell_handle     Cell_handle;
  template <typename TDS2>
  struct Rebind_TDS { typedef Triangulation_ds_cell_base_3<TDS2> Other; };
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_DS_CELL_BASE_3_H
