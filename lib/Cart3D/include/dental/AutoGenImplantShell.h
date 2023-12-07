#ifndef CART3D_AUTO_GEN_IMPLANT_SHELL_H
#define CART3D_AUTO_GEN_IMPLANT_SHELL_H

#include <csgmesh/CSGMesh.h>
#include <CoordSystem/CoordSystem.h>
namespace Cart3D
{
    class AutoGenImplantShell
    {
    public:
        AutoGenImplantShell(const CSGMesh& msh, CoordSystem sys);
    public:
        void gen_convex(CSGMesh& mesh);
    private:
        const CSGMesh& btm;
        CoordSystem csys;
    };
}


#endif