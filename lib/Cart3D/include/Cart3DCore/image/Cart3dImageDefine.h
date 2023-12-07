#ifndef CART3D_IMAGE_DEFINE_H
#define CART3D_IMAGE_DEFINE_H


#ifdef _WIN32
#ifdef CART3D_IMAGE_EXPORTS
#define CART3D_IMAGE_API __declspec(dllexport)
#define CART3D_IMAGE_CLASS __declspec(dllexport)
#else
#define CART3D_IMAGE_API __declspec(dllimport)
#define CART3D_IMAGE_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_IMAGE_API
#define CART3D_IMAGE_CLASS
#endif


#endif