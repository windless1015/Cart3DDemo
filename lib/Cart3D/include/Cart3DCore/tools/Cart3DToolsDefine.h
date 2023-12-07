#ifndef CART3D_TOOLS_DEFINE_H
#define CART3D_TOOLS_DEFINE_H


#ifdef _WIN32
#ifdef CART3D_TOOLS_EXPORTS
#define CART3D_TOOLS_API __declspec(dllexport)
#define CART3D_TOOLS_CLASS __declspec(dllexport)
#else
#define CART3D_TOOLS_API __declspec(dllimport)
#define CART3D_TOOLS_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_TOOLS_API
#define CART3D_TOOLS_CLASS
#endif


#endif