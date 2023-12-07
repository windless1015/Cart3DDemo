#pragma once
#ifndef OPENMESH_ATTRIBUTE_H
#define OPENMESH_ATTRIBUTE_H

#include "Cart3dMeshDefine.h"
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{
	template<class type>
	struct vattribute_guard
	{
	public:
		vattribute_guard(OpenTriMesh& _mesh, OpenMesh::VPropHandleT<type>& _prop):
			mesh(_mesh),prop(_prop) {
			mesh.add_property(prop);
		}
		~vattribute_guard() {
			mesh.remove_property(prop);
		}
		vattribute_guard(const vattribute_guard&) = delete;
		vattribute_guard(const vattribute_guard&&) = delete;
		vattribute_guard& operator=(const vattribute_guard&) = delete;
	private:
		OpenTriMesh& mesh;
		OpenMesh::VPropHandleT<type>& prop;
	};

	template<class type>
	struct eattribute_guard
	{
	public:
		eattribute_guard(OpenTriMesh& _mesh, OpenMesh::EPropHandleT<type>& _prop) :
			mesh(_mesh), prop(_prop) {
			mesh.add_property(prop);
		}
		~eattribute_guard() {
			mesh.remove_property(prop);
		}
		eattribute_guard(const eattribute_guard&) = delete;
		eattribute_guard(const eattribute_guard&&) = delete;
		eattribute_guard& operator=(const eattribute_guard&) = delete;
	private:
		OpenTriMesh& mesh;
		OpenMesh::EPropHandleT<type>& prop;
	};


	template<class type>
	struct fattribute_guard
	{
	public:
		fattribute_guard(OpenTriMesh& _mesh, OpenMesh::FPropHandleT<type>& _prop) :
			mesh(_mesh), prop(_prop) {
			mesh.add_property(prop);
		}
		~fattribute_guard() {
			mesh.remove_property(prop);
		}
		fattribute_guard(const fattribute_guard&) = delete;
		fattribute_guard(const fattribute_guard&&) = delete;
		fattribute_guard& operator=(const fattribute_guard&) = delete;
	private:
		OpenTriMesh& mesh;
		OpenMesh::FPropHandleT<type>& prop;
	};

	struct CART3D_MESH_CLASS property_guard
	{
	public:
		property_guard(OpenTriMesh& mesh);
		property_guard(property_guard& rhs);
		property_guard(property_guard&& rhs) = delete;
		property_guard& operator=(property_guard& rhs);
		~property_guard();
	public:
		virtual void malloc_status() {};
		virtual void free_status() {};
	private:
		void remove();
	protected:
		OpenTriMesh& mesh;
	private:
		std::shared_ptr<size_t> ref_count;
	};
	struct CART3D_MESH_CLASS vstatus_guard :public property_guard
	{
	public:
		using property_guard::property_guard;
	public:
		void malloc_status()override;
		void free_status()override;
	};
	struct CART3D_MESH_CLASS estatus_guard :public property_guard
	{
	public:
		using property_guard::property_guard;
	public:
		void malloc_status()override;
		void free_status()override;
	};
	struct CART3D_MESH_CLASS fstatus_guard :public property_guard
	{
	public:
		using property_guard::property_guard;
	public:
		void malloc_status()override;
		void free_status()override;
	};


	struct CART3D_MESH_CLASS facenorml_gurad :public property_guard
	{
	public:
		using property_guard::property_guard;
	public:
		void malloc_status()override;
		void free_status()override;
	};
}


#endif