#ifndef CART3D_SLAM_DEFINE_H
#define CART3D_SLAM_DEFINE_H


#ifdef _WIN32
#ifdef CART3D_SLAM_EXPORTS
#define CART3D_SLAM_API __declspec(dllexport)
#define CART3D_SLAM_CLASS __declspec(dllexport)
#else
#define CART3D_SLAM_API __declspec(dllimport)
#define CART3D_SLAM_CLASS __declspec(dllimport)
#endif
#else
#define CART3D_SLAM_API
#define CART3D_SLAM_CLASS
#endif


#endif