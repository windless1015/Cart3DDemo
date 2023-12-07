#ifndef CART3D_PARALLELCORK_UNIONFIND_H
#define CART3D_PARALLELCORK_UNIONFIND_H

#include <Cart3dMathDefine.h>
#include <Util/BoostUtil.h>
#include <atomic>
namespace Cart3D
{
	class CART3D_MATH_CLASS IUnionFind
	{
	public:
		virtual ~IUnionFind();
	public:
		virtual  int size() const = 0;
		virtual  int find(int i) = 0;
		virtual void unite(int i, int j) = 0;
	public:
		ct_vector<int> dump();
	};
	class CART3D_MATH_CLASS RankWeightedSerialUnionFind : public IUnionFind
	{
	public:
		RankWeightedSerialUnionFind(int   N);
		int	size() const;
		int find(int	i);
		void unite(int i, int j);
	private:
		ct_vector<int>		ids_;
		ct_vector<int>		rank_;
	};

	class CART3D_MATH_CLASS RandomWeightedSerialUnionFind : public IUnionFind
	{
	public:
		RandomWeightedSerialUnionFind(int   N);
		~RandomWeightedSerialUnionFind();
		int	size() const;
		int find(int	i);
		void unite(int i, int j);
	private:
		int	size_;
		int* parents_;
		int* rank_;
	};

	class CART3D_MATH_CLASS RandomWeightedParallelUnionFind : public IUnionFind
	{
	public:
		RandomWeightedParallelUnionFind(int   N);
		~RandomWeightedParallelUnionFind();
		int	size() const;
		int find(int	i);
		void unite(int i, int j);
	private:
		int	size_;
		std::atomic<int>* parents_;
		int* rank_;
	};


	class CART3D_MATH_CLASS RandomWeightedParallelUnionFind1 : public IUnionFind
	{
	public:
		RandomWeightedParallelUnionFind1(int   N);
		~RandomWeightedParallelUnionFind1();
		int	size() const;
		int find(int	i);
		void unite(int i, int j);
	private:
		int	size_;
		std::atomic<int>* parents_;
		int* rank_;
		std::pair<int, int> findUnoptimized(int	i);
	};


}

#endif