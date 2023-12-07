#ifndef CART3D_MESHGEN_TRIANGLEUTIL_H
#define CART3D_MESHGEN_TRIANGLEUTIL_H

#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>
#include <memory>

namespace Cart3D
{
	struct triangulateio;
	class CART3D_GENERATION_CLASS TriangleUitl
	{
	public:
	public:
		using Index = int;
	public:
		enum class Algorithm {
			idDefault, // Default algorithm.
			idSweepline, // Steven Fortune's sweepline algorithm (-F option)
			idIncremental // Incremental algorithm (-i options).
		};
		struct CART3D_GENERATION_CLASS Config
		{
			Config();
			cfloat min_angle;
			cfloat max_area;
			int max_num_steiner;//steiner点
			int verbose_level;
			Algorithm algorithm;
			bool convex_hull;
			bool conforming;
			bool exact;
			bool split_boundary;
			bool split_segments;
			bool auto_hole_detection;
		};
	public:
		TriangleUitl();
		virtual ~TriangleUitl();
	public:
		//设置点坐标
		void set_in_points(const cfloat* points, int num_points);
		void set_in_points(const cvector2d* points, int num_points);
		void unset_in_points();
		//设置线段约束
		void set_in_segments(const int* segments, int num_segments);
		void unset_in_segments();
		//设置三角形约束（局部细化三角形）
		void set_in_triangles(const int* triangles, int num_triangles);
		void unset_in_triangles();
		//设置洞约束
		void set_in_holes(const cfloat* holes, int num_holes);
		void set_in_holes(const cvector2d* holes, int num_holes);
		void unset_in_holes();
	public:
		void set_in_areas(const cfloat* areas, int num_areas);
		void unset_in_areas();
		void set_in_point_markers(const int* markers, int num_markers);
		void unset_in_point_markers();
		void set_in_segment_markers(const int* markers, int num_markers);
		void unset_in_segment_markers();
	public:
		void run(const Config& config);
	public:
		std::vector<cvector2d>get_in_points();
		std::vector<int> get_in_segments();
		const std::vector<cvector2d> get_out_points() const;
		const std::vector<int> get_out_triangles() const;
		const std::vector<int> get_out_segments() const;
		const std::vector<int> get_out_edges() const;
	protected:
		std::shared_ptr<triangulateio> m_in;
		std::shared_ptr<triangulateio> m_out;
		std::shared_ptr<triangulateio> m_vorout;
	private:
		std::shared_ptr<std::vector<cfloat>> points_cfloat;
	};
}

#endif