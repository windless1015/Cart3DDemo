#ifndef CART3D_DEBUG_UTIL_HPP
#define CART3D_DEBUG_UTIL_HPP

namespace Cart3D
{

#define CART3D_USING_DEBUG 1

#if CART3D_USING_DEBUG
#define CART3D_DEBUG(expr) expr
#define CDBG(expr) expr
#else
#define CART3D_DEBUG(expr)
#define CDBG(expr)
#endif // USING_DEBUG


}




#endif

