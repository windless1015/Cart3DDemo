#ifndef CART3D_OFFSET_DEFINE_H
#define CART3D_OFFSET_DEFINE_H

#ifdef _WIN32
#ifdef CART3D_OFFSET_EXPORTS
#define CART3D_OFFSET_API __declspec(dllexport)
#define CART3D_OFFSET_CLASS __declspec(dllexport)
#else
#define CART3D_OFFSET_API __declspec(dllimport)
#define CART3D_OFFSET_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_OFFSET_API
#define CART3D_OFFSET_CLASS
#endif


#endif