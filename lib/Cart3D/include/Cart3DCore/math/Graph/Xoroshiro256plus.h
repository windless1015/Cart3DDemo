#ifndef CART3D_NECSIM_XOROSHIRO256PLUS_H
#define CART3D_NECSIM_XOROSHIRO256PLUS_H

#include <Util/EigenUtil.h>
namespace Cart3D
{
    class Xoroshiro256Plus
    {
    protected:
        cvectort<uint64_t,4> shuffle_table;
    public:
        Xoroshiro256Plus();
        ~Xoroshiro256Plus();
        explicit Xoroshiro256Plus(uint64_t seed);
        void setSeed(uint64_t seed);
        uint64_t next();
        double d01();
        void jump();
    };
}
#endif //CART3D_NECSIM_XOROSHIRO256PLUS_H