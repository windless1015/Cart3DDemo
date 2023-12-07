#ifndef CART3D_COLLIDER_DEFINE_H
#define CART3D_COLLIDER_DEFINE_H


#ifdef _WIN32
#ifdef CART3D_COLLIDER_EXPORTS
#define CART3D_COLLIDER_API __declspec(dllexport)
#define CART3D_COLLIDER_CLASS __declspec(dllexport)
#else
#define CART3D_COLLIDER_API __declspec(dllimport)
#define CART3D_COLLIDER_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_COLLIDER_API
#define CART3D_COLLIDER_CLASS
#endif


#endif