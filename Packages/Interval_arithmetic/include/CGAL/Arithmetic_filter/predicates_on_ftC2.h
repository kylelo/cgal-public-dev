// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : include/CGAL/Arithmetic_filter/predicates_on_ftC2.h
// package       : Interval_arithmetic
// source        : include/CGAL/predicates_on_ftC2.h
// revision      : $Revision$
// revision_date :
// author(s)     : Sylvain.Pion@sophia.inria.fr
//                 Sylvain Pion     (Sylvain.Pion@sophia.inria.fr)
//
// coordinator   : INRIA Sophia-Antipolis (Herve.Bronnimann@sophia.inria.fr)
//
// ======================================================================


#ifndef CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#define CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H

// This file is automatically generated with the script for filtering
// predicates, using Interval arithmetic.

#include <CGAL/Interval_arithmetic.h>

#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H

#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC2_H
#include <CGAL/basic_constructions_ftC2.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	            const Filtered_exact<CT,ET> &l1a,
	const Filtered_exact<CT,ET> &l1b,
	const Filtered_exact<CT,ET> &l1c,
	            const Filtered_exact<CT,ET> &l2a,
	const Filtered_exact<CT,ET> &l2b,
	const Filtered_exact<CT,ET> &l2c)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_xC2(
		px.interval(),
		py.interval(),
		l1a.interval(),
		l1b.interval(),
		l1c.interval(),
		l2a.interval(),
		l2b.interval(),
		l2c.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_xC2(
		px.exact(),
		py.exact(),
		l1a.exact(),
		l1b.exact(),
		l1c.exact(),
		l2a.exact(),
		l2b.exact(),
		l2c.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xC2(const Filtered_exact<CT,ET> &l1a,
	const Filtered_exact<CT,ET> &l1b,
	const Filtered_exact<CT,ET> &l1c,
	                 const Filtered_exact<CT,ET> &l2a,
	const Filtered_exact<CT,ET> &l2b,
	const Filtered_exact<CT,ET> &l2c,
	                 const Filtered_exact<CT,ET> &h1a,
	const Filtered_exact<CT,ET> &h1b,
	const Filtered_exact<CT,ET> &h1c,
	                 const Filtered_exact<CT,ET> &h2a,
	const Filtered_exact<CT,ET> &h2b,
	const Filtered_exact<CT,ET> &h2c)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_xC2(
		l1a.interval(),
		l1b.interval(),
		l1c.interval(),
		l2a.interval(),
		l2b.interval(),
		l2c.interval(),
		h1a.interval(),
		h1b.interval(),
		h1c.interval(),
		h2a.interval(),
		h2b.interval(),
		h2c.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_xC2(
		l1a.exact(),
		l1b.exact(),
		l1c.exact(),
		l2a.exact(),
		l2b.exact(),
		l2c.exact(),
		h1a.exact(),
		h1b.exact(),
		h1c.exact(),
		h2a.exact(),
		h2b.exact(),
		h2c.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_xC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                 const Filtered_exact<CT,ET> &la,
	const Filtered_exact<CT,ET> &lb,
	const Filtered_exact<CT,ET> &lc)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_y_at_xC2(
		px.interval(),
		py.interval(),
		la.interval(),
		lb.interval(),
		lc.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_y_at_xC2(
		px.exact(),
		py.exact(),
		la.exact(),
		lb.exact(),
		lc.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_xC2(const Filtered_exact<CT,ET> &px,
	                 const Filtered_exact<CT,ET> &l1a,
	const Filtered_exact<CT,ET> &l1b,
	const Filtered_exact<CT,ET> &l1c,
	                 const Filtered_exact<CT,ET> &l2a,
	const Filtered_exact<CT,ET> &l2b,
	const Filtered_exact<CT,ET> &l2c)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_y_at_xC2(
		px.interval(),
		l1a.interval(),
		l1b.interval(),
		l1c.interval(),
		l2a.interval(),
		l2b.interval(),
		l2c.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_y_at_xC2(
		px.exact(),
		l1a.exact(),
		l1b.exact(),
		l1c.exact(),
		l2a.exact(),
		l2b.exact(),
		l2c.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_y_at_xC2(const Filtered_exact<CT,ET> &l1a,
	const Filtered_exact<CT,ET> &l1b,
	const Filtered_exact<CT,ET> &l1c,
	                 const Filtered_exact<CT,ET> &l2a,
	const Filtered_exact<CT,ET> &l2b,
	const Filtered_exact<CT,ET> &l2c,
	                 const Filtered_exact<CT,ET> &ha,
	const Filtered_exact<CT,ET> &hb,
	const Filtered_exact<CT,ET> &hc)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_y_at_xC2(
		l1a.interval(),
		l1b.interval(),
		l1c.interval(),
		l2a.interval(),
		l2b.interval(),
		l2c.interval(),
		ha.interval(),
		hb.interval(),
		hc.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_y_at_xC2(
		l1a.exact(),
		l1b.exact(),
		l1c.exact(),
		l2a.exact(),
		l2b.exact(),
		l2c.exact(),
		ha.exact(),
		hb.exact(),
		hc.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_y_at_xC2(const Filtered_exact<CT,ET> &l1a,
	const Filtered_exact<CT,ET> &l1b,
	const Filtered_exact<CT,ET> &l1c,
	                 const Filtered_exact<CT,ET> &l2a,
	const Filtered_exact<CT,ET> &l2b,
	const Filtered_exact<CT,ET> &l2c,
	                 const Filtered_exact<CT,ET> &h1a,
	const Filtered_exact<CT,ET> &h1b,
	const Filtered_exact<CT,ET> &h1c,
	                 const Filtered_exact<CT,ET> &h2a,
	const Filtered_exact<CT,ET> &h2b,
	const Filtered_exact<CT,ET> &h2c)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_y_at_xC2(
		l1a.interval(),
		l1b.interval(),
		l1c.interval(),
		l2a.interval(),
		l2b.interval(),
		l2c.interval(),
		h1a.interval(),
		h1b.interval(),
		h1c.interval(),
		h2a.interval(),
		h2b.interval(),
		h2c.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_y_at_xC2(
		l1a.exact(),
		l1b.exact(),
		l1c.exact(),
		l2a.exact(),
		l2b.exact(),
		l2c.exact(),
		h1a.exact(),
		h1b.exact(),
		h1c.exact(),
		h2a.exact(),
		h2b.exact(),
		h2c.exact());
  }
  return result;
}

template < class CT, class ET >
// inline
Comparison_result
compare_deltax_deltayC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &qx,
	                             const Filtered_exact<CT,ET> &ry,
	const Filtered_exact<CT,ET> &sy)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_deltax_deltayC2(
		px.interval(),
		qx.interval(),
		ry.interval(),
		sy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_deltax_deltayC2(
		px.exact(),
		qx.exact(),
		ry.exact(),
		sy.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_lexicographically_xyC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                               const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = compare_lexicographically_xyC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = compare_lexicographically_xyC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Orientation
orientationC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	              const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	              const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry)
{
  Orientation result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = orientationC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = orientationC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_ordered_along_lineC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                                   const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                                   const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = collinear_are_ordered_along_lineC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = collinear_are_ordered_along_lineC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_strictly_ordered_along_lineC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                                            const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                                            const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = collinear_are_strictly_ordered_along_lineC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = collinear_are_strictly_ordered_along_lineC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_LARGE_INLINE
Oriented_side
side_of_oriented_circleC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                               const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                               const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry,
	                               const Filtered_exact<CT,ET> &tx,
	const Filtered_exact<CT,ET> &ty)
{
  Oriented_side result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = side_of_oriented_circleC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval(),
		tx.interval(),
		ty.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = side_of_oriented_circleC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact(),
		tx.exact(),
		ty.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_LARGE_INLINE
Bounded_side
side_of_bounded_circleC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                         const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                         const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry,
	                         const Filtered_exact<CT,ET> &tx,
	const Filtered_exact<CT,ET> &ty)
{
  Bounded_side result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = side_of_bounded_circleC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval(),
		tx.interval(),
		ty.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = side_of_bounded_circleC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact(),
		tx.exact(),
		ty.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
cmp_dist_to_pointC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                    const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                    const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = cmp_dist_to_pointC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = cmp_dist_to_pointC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_dist_to_pointC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                           const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                           const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = has_larger_dist_to_pointC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = has_larger_dist_to_pointC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_dist_to_pointC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                            const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                            const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = has_smaller_dist_to_pointC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = has_smaller_dist_to_pointC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
cmp_signed_dist_to_lineC2(const Filtered_exact<CT,ET> &la,
	const Filtered_exact<CT,ET> &lb,
	const Filtered_exact<CT,ET> &lc,
	                          const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                          const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = cmp_signed_dist_to_lineC2(
		la.interval(),
		lb.interval(),
		lc.interval(),
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = cmp_signed_dist_to_lineC2(
		la.exact(),
		lb.exact(),
		lc.exact(),
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_signed_dist_to_lineC2(const Filtered_exact<CT,ET> &la,
	const Filtered_exact<CT,ET> &lb,
	const Filtered_exact<CT,ET> &lc,
	                                 const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                                 const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = has_larger_signed_dist_to_lineC2(
		la.interval(),
		lb.interval(),
		lc.interval(),
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = has_larger_signed_dist_to_lineC2(
		la.exact(),
		lb.exact(),
		lc.exact(),
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_signed_dist_to_lineC2(const Filtered_exact<CT,ET> &la,
	const Filtered_exact<CT,ET> &lb,
	const Filtered_exact<CT,ET> &lc,
	                                  const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                                  const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = has_smaller_signed_dist_to_lineC2(
		la.interval(),
		lb.interval(),
		lc.interval(),
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = has_smaller_signed_dist_to_lineC2(
		la.exact(),
		lb.exact(),
		lc.exact(),
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact());
  }
  return result;
}
template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
cmp_signed_dist_to_lineC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                          const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                          const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry,
	                          const Filtered_exact<CT,ET> &sx,
	const Filtered_exact<CT,ET> &sy)
{
  Comparison_result result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = cmp_signed_dist_to_lineC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval(),
		sx.interval(),
		sy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = cmp_signed_dist_to_lineC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact(),
		sx.exact(),
		sy.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_signed_dist_to_lineC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                                 const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                                 const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry,
	                                 const Filtered_exact<CT,ET> &sx,
	const Filtered_exact<CT,ET> &sy)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = has_larger_signed_dist_to_lineC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval(),
		sx.interval(),
		sy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = has_larger_signed_dist_to_lineC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact(),
		sx.exact(),
		sy.exact());
  }
  return result;
}

template < class CT, class ET >
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_signed_dist_to_lineC2(const Filtered_exact<CT,ET> &px,
	const Filtered_exact<CT,ET> &py,
	                                  const Filtered_exact<CT,ET> &qx,
	const Filtered_exact<CT,ET> &qy,
	                                  const Filtered_exact<CT,ET> &rx,
	const Filtered_exact<CT,ET> &ry,
	                                  const Filtered_exact<CT,ET> &sx,
	const Filtered_exact<CT,ET> &sy)
{
  bool result;
  FPU_set_rounding_to_infinity();
  try
  {
    result = has_smaller_signed_dist_to_lineC2(
		px.interval(),
		py.interval(),
		qx.interval(),
		qy.interval(),
		rx.interval(),
		ry.interval(),
		sx.interval(),
		sy.interval());
    FPU_set_rounding_to_nearest();
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_rounding_to_nearest();
    result = has_smaller_signed_dist_to_lineC2(
		px.exact(),
		py.exact(),
		qx.exact(),
		qy.exact(),
		rx.exact(),
		ry.exact(),
		sx.exact(),
		sy.exact());
  }
  return result;
}

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#include <CGAL/Arithmetic_filter/predicates_on_ftC2.h>
#endif // CGAL_ARITHMETIC_FILTER_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#endif


CGAL_END_NAMESPACE

#endif  // CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
