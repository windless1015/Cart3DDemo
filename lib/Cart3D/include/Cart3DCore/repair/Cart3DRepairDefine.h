#ifndef CART3D_REPAIR_DEFINE_H
#define CART3D_REPAIR_DEFINE_H

#ifdef _WIN32
#ifdef CART3D_REPAIR_EXPORTS
#define CART3D_REPAIR_API __declspec(dllexport)
#define CART3D_REPAIR_CLASS __declspec(dllexport)
#else
#define CART3D_REPAIR_API __declspec(dllimport)
#define CART3D_REPAIR_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_REPAIR_API
#define CART3D_REPAIR_CLASS
#endif


#endif