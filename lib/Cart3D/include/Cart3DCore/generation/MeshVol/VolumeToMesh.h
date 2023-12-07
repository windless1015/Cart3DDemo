#ifndef CART3D_GEN_VOL_TO_MESH_TOOLS_H
#define CART3D_GEN_VOL_TO_MESH_TOOLS_H


#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>
#include <Grid/Volume.h>
#include <Util/OpenMeshUtil.h>
namespace Cart3D
{

    class CART3D_GENERATION_CLASS VolumeToMesh
    {
    public:
        //效果比较差
        static bool qex_mc(
            const cvector3d& ori, const cvector3d& dscale,
            const std::vector<cvector3d>& snors,
            const std::vector<cfloat>& sdfs,
            int udim, int vdim, int wdim,
            cfloat feature_angle, cfloat iso,
            OpenTriMesh& mesh);
    public:
        static void volume_to_mesh(
            const std::shared_ptr<Volume>& grid,
            const std::vector<cfloat>& sdfs,
            const std::vector<cvector3d>& snors,
            std::vector<cvector3d>& points,
            std::vector<cvector4i>& quads,
            cfloat isovalue = 0.0);
        static void volume_to_mesh(
                const std::shared_ptr<Volume>& grid,
                const std::vector<cfloat>& sdfs,
                const std::vector<cvector3d>& snors,
                std::vector<cvector3d>& points,
                std::vector<cvector3i>& triangles,
                std::vector<cvector4i>& quads,
                cfloat isovalue = 0.0,
                cfloat adaptivity = 0.0,
                bool relaxDisorientedTriangles = true);
    public:
        static void flip_edges(OpenTriMesh& mesh);
        static VH find_feature(OpenTriMesh& mesh, const std::vector<VH>& vhs, cfloat cosangle);
        static bool is_feature_point(
            const std::vector<cvector3d>& points,
            const std::vector<cvector3d>& normals,
            cfloat cosangle);
    public:
        static cvector3d find_feature_point(
            const std::vector<cvector3d>& points,
            const std::vector<cvector3d>& normals);
        static bool is_planar_quad(
            const cvector3d& p0, const cvector3d& p1,
            const cvector3d& p2, const cvector3d& p3,
            const cfloat epsilon = 0.001);
    };


}


#endif