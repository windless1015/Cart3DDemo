#ifndef CART3D_PARALLEL_CORK_DEFINE_H
#define CART3D_PARALLEL_CORK_DEFINE_H

#ifdef _WIN32
#ifdef CART3D_PARALLEL_CORK_EXPORTS
#define CART3D_PARALLEL_CORK_API __declspec(dllexport)
#define CART3D_PARALLEL_CORK_CLASS __declspec(dllexport)
#else
#define CART3D_PARALLEL_CORK_API __declspec(dllimport)
#define CART3D_PARALLEL_CORK_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_PARALLEL_CORK_API
#define CART3D_PARALLEL_CORK_CLASS
#endif


#endif