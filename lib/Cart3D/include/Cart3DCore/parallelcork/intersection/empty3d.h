#ifndef CART3D_PARLLEL_CORK_EMPTY3D_H
#define CART3D_PARLLEL_CORK_EMPTY3D_H

#include <atomic>
#include <Util/EigenUtil.h>
#include <math/ext4.hpp>
#include <math/fixext4.hpp>
#include <math/gmpext4.hpp>
#include <string>
namespace Cart3D
{
    class ExactArithmeticContext
    {
    public:
        ExactArithmeticContext() : degeneracy_count_(0), exact_count_(0), call_count_(0) {}
        ExactArithmeticContext(const ExactArithmeticContext&) = delete;
        ExactArithmeticContext(ExactArithmeticContext&&) = delete;
        ExactArithmeticContext& operator=(const ExactArithmeticContext&) = delete;
        ExactArithmeticContext& operator=(ExactArithmeticContext&&) = delete;
        ~ExactArithmeticContext() = default;
    public:
        void        reset_degeneracy_count();
        bool        has_degeneracies() const;
        void        found_degeneracy();
        uint32_t    exact_count() const;
        void        add_exact_computation();
        uint32_t    call_count() const;
        void        add_call_count();
    private:
        std::atomic<uint32_t> degeneracy_count_ = 0;
        std::atomic<uint32_t> exact_count_ = 0;
        std::atomic<uint32_t> call_count_ = 0;
    };
	class IntersectingTriangle
	{
	public:
		IntersectingTriangle() = delete;
		IntersectingTriangle(
			const cvector3d& tri0,
			const cvector3d& tri1,
			const cvector3d& tri2);
		const Ext4_1& p0() const;
		const Ext4_1& p1() const;
		const Ext4_1& p2() const;
	private:
		const Ext4_1 p0_;
		const Ext4_1 p1_;
		const Ext4_1 p2_;
	};
	class IntersectingEdge
	{
	public:
		IntersectingEdge() = delete;
		IntersectingEdge(const cvector3d& edge0,const cvector3d& edge1);
		const Ext4_1& p0() const;
		const Ext4_1& p1() const;
	private:
		const Ext4_1 p0_;
		const Ext4_1 p1_;
	};
	enum class HasIntersection
	{
		NO = -1,
		MAYBE = 0,
		YES = 1
	};
	extern std::string info(HasIntersection& has);
	class TriangleEdgeIntersection
	{
	public:
		TriangleEdgeIntersection(
			const IntersectingTriangle& triangle, 
			const IntersectingEdge& edge) : 
			tri_(triangle), 
			edge_(edge)
		{}
		HasIntersection isEmpty(ExactArithmeticContext& context) const;
		HasIntersection emptyExact(
			const Quantizer& quantizer, 
			ExactArithmeticContext& context) const;
		cvector3d coords() const;
		cvector3d coordsExact(const Quantizer& quantizer) const;
	private:
		IntersectingTriangle tri_;
		IntersectingEdge edge_;
		HasIntersection emptyFilter() const;
		HasIntersection exactFallback(const Quantizer& quantizer, ExactArithmeticContext& context) const;
	};
	cvector3d coordsExact(
		const GMPExt4_2& edge,
		const GMPExt4_3& triangle,
		const Quantizer& quantizer);
	class TriangleTriangleTriangleIntersection
	{
	public:
		TriangleTriangleTriangleIntersection(
			const IntersectingTriangle& triangle0, 
			const IntersectingTriangle& triangle1,
			const IntersectingTriangle& triangle2)
			: m_tri{triangle0, triangle1, triangle2 }
		{
		}
		~TriangleTriangleTriangleIntersection() {}
		const std::array<IntersectingTriangle, 3>& triangle() const { 
			return std::array<IntersectingTriangle, 3>{tri0, tri1, tri2};
		}
		HasIntersection isEmpty(ExactArithmeticContext& context) const;
		HasIntersection emptyExact(const Quantizer& quantizer, ExactArithmeticContext& context) const;
		cvector3d coords() const;
		cvector3d coordsExact(const Quantizer& quantizer) const;
	private:
		union {
			struct {
				IntersectingTriangle tri0, tri1, tri2;
			};
			struct {
				IntersectingTriangle m_tri[3];
			};
		};
		HasIntersection emptyFilter() const;
		HasIntersection exactFallback(const Quantizer& quantizer, ExactArithmeticContext& context) const;
	};
	cvector3d coordsExact(
		const GMPExt4_3& triangle0, 
		const GMPExt4_3& triangle1, 
		const GMPExt4_3& triangle2,
		const Quantizer& quantizer);

	class EdgeEdgeIntersection
	{
	public:
		EdgeEdgeIntersection(
			const IntersectingEdge& e0,
			const IntersectingEdge& e1);
		~EdgeEdgeIntersection(){}
	public:
		HasIntersection isEmpty(ExactArithmeticContext& context) const;
		HasIntersection emptyExact(const Quantizer& quantizer, ExactArithmeticContext& context) const;
		cvector3d coords() const;
		cvector3d coordsExact(const Quantizer& quantizer) const;
	private:
		union {
			struct { IntersectingEdge edge0, edge1; };
			struct { IntersectingEdge edge[2]; };
		};
	private:
		std::shared_ptr<IntersectingTriangle> virtual_triangle0;
		std::shared_ptr<IntersectingTriangle> virtual_triangle1;
	};




}


#endif