#ifndef CART3D_CUDA_MARCHINGCUBE_H
#define CART3D_CUDA_MARCHINGCUBE_H

#include <Cart3DGPUDefine.h>
#ifdef CUDA_CXX
#include <cuda.h>
#include <cuda_runtime.h>

namespace Cart3D
{
	/*
	 * @class CUDAMarchingCubes
	 * @brief cuda�汾��marching cube�㷨������֧��CPU�ڴ棬GPU�ڴ����ݵ���
	 * @detail �������Ҫrgb����ֱ�ӵ���nullptr����
	 * @see also:a parallel dual marching cubes approach to quad only surface reconstruction
	 * @see also: Real-time Marching Cubes using CUDA and HisToPyramids
	 * @see also: Performance Comparison of the marching cubes algorithm:CPU vs.GPU
	 * @see also: CUDA Samples
	 * @see also: CUDA-based triangulations of convolution molecular surfaces
	 * @see also: Real-time 3D Rendering of Water using CUDA-uBibliorum
	 * @see also: Real-time Marching Cubes On the Vertex Shader
	 */
	class CART3D_GPU_CLASS CUDAMarchingCubes {
	public:
		enum VolTexFormat { RGB3F, RGB4U };
	public:
		CUDAMarchingCubes(); 
		~CUDAMarchingCubes();
	public:
		bool initialize(uint3 maxgridsize);
	public:
		static size_t mem_usage_mc(unsigned int gx, unsigned int gy, unsigned int gz);
		size_t mem_usage_area_calc(unsigned int triaCount) const;
	public:
		/**
		 * @brief  ���û��߸�����������
		 * @detail ������Դ���device�ڴ棬Ҳ���Դ���host�ڴ�����
		 *
		 * @param[in] volume ������
		 * @param[in] colors rgb���ݣ����û��ֱ�Ӵ���NULL��
		 * @param[in] texformat rgb��ʽ
		 * @param[in] gridsize ����ߴ�
		 * @param[in] gridOrigin ����ԭ��
		 * @param[in] boundingBox ��Χ��
		 * @param[in] cudaArray true--��Ӧ��device�ڴ棬false--��Ӧ��host�ڴ�
		 * @return 'true' ����������óɹ�
		 */
		bool set_volume_data(float *volume, float3 *colors,
			uint3 gridsize, float3 gridOrigin,
			float3 boundingBox, bool cudaArray);
		bool set_volume_data(float *volume, uchar4 *colors,
			uint3 gridsize, float3 gridOrigin,
			float3 boundingBox, bool cudaArray);
		bool set_volume_data(float *volume, void *colors, VolTexFormat texformat,
			uint3 gridsize, float3 gridOrigin,
			float3 boundingBox, bool cudaArray);
		void set_sub_volume(uint3 start, uint3 end);
	public:
		uint3 get_max_gridsize()const;
		void set_isovalue(float isoval);
		void set_calc_norms(bool norms);
		float get_isovalue();
		unsigned int get_vertex_count();
		unsigned int get_active_voxel_count();
		unsigned int get_voxel_count();
		bool use_color();
	public:

		int compute_maxverts()const;

	public:
		/**
	     * @brief ʹ��cuda�����ֵ��
	     * @param[out] vertOut  �������±� (device memory, output)
	     * @param[out] normOut  Triangle vertex normals (device memory, output)
	     * @param[out] colOut   Triangle vertex colors (device memory, output)
	     * @param[in]  maxverts ������Ķ��㣨�����ڴ�Խ�磩����������ƿ�������INT_MAX��
	     */
		void compute_isosurface(float3* vertOut, float3* normOut, float3* colOut, unsigned int maxverts);
		void compute_isosurface(float3* vertOut, float3* normOut, uchar4* colOut, unsigned int maxverts);
		void compute_isosurface(float3* vertOut, char3* normOut, uchar4* colOut, unsigned int maxverts);
		bool compute_isosurface(float *volume, void *colors, VolTexFormat texformat,
			uint3 gridsize, float3 gridOrigin,
			float3 boundingBox, bool cudaArray,
			float3* vertOut, float3* normOut, float3* colOut,
			unsigned int maxverts);
	public:
		float compute_surface_area(float3 *verts, unsigned int triaCount);
	public:	
		void cleanup();
	private:
		void _compute_isosur_face_verts(float3* vertOut, unsigned int maxverts,dim3 & grid3);
		int cudadevice;              
		int cudacomputemajor;        
		uint3 maxGridSize;           
		size_t maxNumVoxels;         
		uint3 gridSize;             
		size_t numVoxels;           
		float3 origin;              
		float3 bBox;                
		float3 voxelSize;           
		uint3 subGridStart;         
		uint3 subGridEnd;           
		bool useSubGrid;   
		bool calcNorms;
		float isoValue;              
		unsigned int activeVoxels;   
		unsigned int totalVerts;   
		float *d_volume;          
		void *d_colors;              
		VolTexFormat texformat;     
		float ownCudaDataArrays;    
		cudaArray *d_volumeArray;    
		uint2 *d_voxelVerts;        
		unsigned int *d_compVoxelArray; 
		int* d_triTable;          
		unsigned int* d_numVertsTable;    
		bool useColor;             
		bool initialized;          
		bool setdata;              
		cudaTextureObject_t triTexObj;       
		cudaTextureObject_t numVertsTexObj;
		cudaTextureObject_t volTexObj;     
		void _allocate_textures(int **d_triTab, unsigned int **d_numVertsTab);
	};
}
#endif

#endif