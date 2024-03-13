#pragma once


#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;





#define M_PI_ 3.14159265359

static bool isLoading = false;