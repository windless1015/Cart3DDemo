#pragma once
#ifndef CART3D_TRIBVH_IMPL_H
#define CART3D_TRIBVH_IMPL_H

#include "Bvh.h"

namespace Cart3D
{

	class CART3D_MATH_CLASS TriBvhOptim
	{
	public:
		TriBvhOptim();
	public:
		void start_bvh(int nface=0);
		void subdiv_triangle(
			int id,
			const cvector3d& t0,
			const cvector3d& t1,
			const cvector3d& t2,
			cfloat avglen);
		void end_bvh();	
	public:
		int get_map_id(int id)const;
		std::shared_ptr<Cart3DBvh> get_pbvh();
	private:
		std::shared_ptr<Cart3DBvh> m_pBvh;
		std::vector<GeomBlob> m_boxs;
		std::vector<int> m_id_tris;
	};

	class CART3D_MATH_CLASS TriBvhOptimParallel
	{
	public:
		TriBvhOptimParallel();
	public:
		void start_bvh(int nface = 0);
		void subdiv_triangle(
			int id,
			const cvector3d& t0,
			const cvector3d& t1,
			const cvector3d& t2,
			cfloat avglen);
		void end_bvh();
	public:
		int get_map_id(int id)const;
		std::shared_ptr<Cart3DBvh> get_pbvh();
	private:
		std::shared_ptr<Cart3DBvh> m_pBvh;
		std::vector<GeomBlob> m_boxs;
		std::vector<int> m_id_tris;

	private:
		std::vector<std::vector<GeomBlob>> m_all_boxs;
	};

}




#endif