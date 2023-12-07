#ifndef CART3D_PARALLELCORK_QUANTIZATION_H
#define CART3D_PARALLELCORK_QUANTIZATION_H

#include <Util/EigenUtil.h>

namespace Cart3D
{
	class Quantizer
	{
	public:
		bool calibrate(cfloat maxMagnitude, cfloat minEdgeLength);
	public:
		int bits_purturbation_range() const;
		cfloat purturbation_quantum() const;
		int quantize_to_int(cfloat number) const;
		cfloat quantizedInt_to_cfloat(int number) const;
		cfloat quantize(cfloat number) const;
		cfloat quantize(float number) const;
		cfloat reshrink(cfloat number) const;
	public:
		cvector3i quantize_to_int(const cvector3d& vec) const;
		cvector3d quantize(const cvector3d& vec) const;
	private:
		cfloat m_magnify;
		cfloat m_reshrink;
		int m_bits;
	};
}



#endif