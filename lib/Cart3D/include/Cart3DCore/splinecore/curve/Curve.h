#ifndef CART3D_SPLINECORE_CURVE_H
#define CART3D_SPLINECORE_CURVE_H

#include <Cart3DSplineCore.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{
	class CART3D_SPLINECORE_CLASS CubeicCurve
	{
	public:
		static void quadratic(
			const cvector3d& A,
			const cvector3d& B,
			const cvector3d& C,
			std::vector<cvector3d>& curve,
			int bezier_steps = 4,
			bool include_end = false,
			bool is_clear = false);

		static void cubic(
			const cvector3d& A, const cvector3d& B,
			const cvector3d& C, const cvector3d& D,
			std::vector<cvector3d>& curve,
			int bezier_steps = 4,
			bool include_end = false,
			bool is_clear = false);


		static void quadratic2d(
			const cvector2d& A,
			const cvector2d& B,
			const cvector2d& C,
			std::vector<cvector2d>& curve,
			int bezier_steps = 4,
			bool include_end = false,
			bool is_clear = false);

		static void cubic2d(
			const cvector2d& A, const cvector2d& B,
			const cvector2d& C, const cvector2d& D,
			std::vector<cvector2d>& curve,
			int bezier_steps = 4,
			bool include_end = false,
			bool is_clear = false);
	};


    class CART3D_SPLINECORE_CLASS Curve {
    public:
        Curve();
        virtual ~Curve();
    public:
        void set_steps(int steps);
        void add_way_point(const cvector3d& point);
        int node_count() const;
        const cvector3d& node(int i) const;
        cfloat length_from_start_point(int i) const;
        cfloat total_length() const;
        void clear();
    protected:
		void add_node(const cvector3d& node);
        virtual void on_way_point_added() = 0;
        virtual cvector3d
            interpolate(cfloat u,
                const cvector3d& P0,
                const cvector3d& P1, 
                const cvector3d& P2,
                const cvector3d& P3) const = 0;
    protected:
        int m_steps;
        std::vector<cvector3d> m_way_points;
        std::vector<cvector3d> m_nodes;
        std::vector<cfloat> m_distances;
    };

    class CART3D_SPLINECORE_CLASS Bezier : public Curve {
    public:
        Bezier() = default;
    protected:
        using Curve::m_way_points;
        using Curve::m_steps;
        using Curve::add_node;
        void on_way_point_added() override;
        cvector3d interpolate(cfloat u, const cvector3d& P0, const cvector3d& P1, const cvector3d& P2,
            const cvector3d& P3) const override;
    };

    class CART3D_SPLINECORE_CLASS BSpline : public Curve {
    public:
        BSpline() = default;
    protected:
        using Curve::m_way_points;
        using Curve::m_steps;
        using Curve::add_node;
        void on_way_point_added() override;
        cvector3d interpolate(cfloat u, const cvector3d& P0, const cvector3d& P1, const cvector3d& P2,
            const cvector3d& P3) const override;
    };

    class CART3D_SPLINECORE_CLASS CatmullRom : public Curve {
    public:
        CatmullRom() = default;
    protected:
        using Curve::m_way_points;
        using Curve::m_steps;
        using Curve::add_node;

        void on_way_point_added() override;

        cvector3d interpolate(cfloat u, const cvector3d& P0, const cvector3d& P1, const cvector3d& P2,
            const cvector3d& P3) const override;

    };
}



#endif