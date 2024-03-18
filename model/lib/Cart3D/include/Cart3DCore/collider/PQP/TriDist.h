/*************************************************************************\

  Copyright 1999 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             E. Larsen
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:               geom@cs.unc.edu


\**************************************************************************/
#pragma once
#ifndef PQP_TRIDIST_H
#define PQP_TRIDIST_H

#include "PQP_Compile.h"
#include "Tri.h"
// TriDist()
//
// computes the closest points on two triangles, and returns the 
// distance between them.
// 
// s and t are the triangles, stored tri[point][dimension].
//
// If the triangles are disjoint, p and q give the closest points of 
// s and t respectively. However, if the triangles overlap, p and q 
// are basically a random pair of points from the triangles, not 
// coincident points on the intersection of the triangles, as might 
// be expected.

PQP_REAL
TriDist(PQP_REAL p[3], PQP_REAL q[3],
    const PQP_REAL s[3][3], const PQP_REAL t[3][3]);

//------------------------------------------------------------------
//注意不能处理退化三角形情况，这里需要特殊考虑，建议使用
PQP_REAL
PointTriDist(int* posFlag, PQP_REAL q[3], const PQP_REAL p[3], const PQP_REAL t[3][3]);




int
project6(PQP_REAL* ax,
    PQP_REAL* p1, PQP_REAL* p2, PQP_REAL* p3,
    PQP_REAL* q1, PQP_REAL* q2, PQP_REAL* q3);
// very robust triangle intersection test
// uses no divisions
// works on coplanar triangles
int
TriContact(PQP_REAL* P1, PQP_REAL* P2, PQP_REAL* P3,
    PQP_REAL* Q1, PQP_REAL* Q2, PQP_REAL* Q3);

//------------------------------------------------------------------------------

PQP_REAL find_closet_point_triangle(
    PQP_REAL x[3],
    PQP_REAL pa[3],
    PQP_REAL pb[3],
    PQP_REAL pc[3],
    PQP_REAL pt[3],
    PQP_REAL t[2], int& posflag);

PQP_REAL find_closet_point_triangle(
    PQP_REAL x[3],
    PQP_REAL pa[3],
    PQP_REAL pb[3],
    PQP_REAL pc[3],
    PQP_REAL pt[3],
    PQP_REAL t[2]);

PQP_REAL find_closet_point_triangle(
    PQP_REAL x[3],
    PQP_REAL pa[3],
    PQP_REAL pb[3],
    PQP_REAL pc[3],
    PQP_REAL pt[3]);

//------------------------------------------------------------------------------

PQP_REAL
PointTriDistance(int* posFlag, PQP_REAL p[3], Tri* t, PQP_REAL q[3]);
//------------------------------------------------------------------------------


PQP_REAL
TriDistance(PQP_REAL R[3][3], PQP_REAL T[3], Tri* t1, Tri* t2,
    PQP_REAL p[3], PQP_REAL q[3]);



#endif
