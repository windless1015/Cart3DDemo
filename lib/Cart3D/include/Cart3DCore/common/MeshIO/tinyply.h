/*
 * tinyply 2.3.4 (https://github.com/ddiakopoulos/tinyply)
 *
 * A single-header, zero-dependency (except the C++ STL) public domain implementation
 * of the PLY mesh file format. Requires C++11; errors are handled through exceptions.
 *
 * This software is in the public domain. Where that dedication is not
 * recognized, you are granted a perpetual, irrevocable license to copy,
 * distribute, and modify this file as you see fit.
 *
 * Authored by Dimitri Diakopoulos (http://www.dimitridiakopoulos.com)
 *
 * tinyply.h may be included in many files, however in a single compiled file,
 * the implementation must be created with the following defined prior to header inclusion
 * #define TINYPLY_IMPLEMENTATION
 *
 */

 ////////////////////////
 //   tinyply header   //
 ////////////////////////

#ifndef CART3D_tinyply_h
#define CART3D_tinyply_h

#include <Cart3DCommonDefine.h>
#include <vector>
#include <string>
#include <stdint.h>
#include <cstddef>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <functional>

namespace tinyply
{

	enum class Type : uint8_t
	{
		INVALID,
		INT8,
		UINT8,
		INT16,
		UINT16,
		INT32,
		UINT32,
		FLOAT32,
		FLOAT64
	};

	struct CART3D_COMMON_CLASS PropertyInfo
	{
		PropertyInfo() {};
		PropertyInfo(int stride, std::string str)
			: stride(stride), str(str) {}
		int stride{ 0 };
		std::string str;
	};

    extern std::map<Type, PropertyInfo> PropertyTable;
	class CART3D_COMMON_CLASS Buffer
	{
		uint8_t * alias{ nullptr };
		struct delete_array { void operator()(uint8_t * p) { delete[] p; } };
		std::unique_ptr<uint8_t, decltype(Buffer::delete_array())> data;
		size_t size{ 0 };
	public:
		Buffer() {};
		Buffer(const size_t size) : data(new uint8_t[size], delete_array()), size(size) { alias = data.get(); } // allocating
		Buffer(const uint8_t * ptr) : alias(const_cast<uint8_t*>(ptr)) { } // non-allocating, todo: set size?
		uint8_t * get() { return alias; }
		const uint8_t * get_const() const { return alias; }
		size_t size_bytes() const { return size; }
	};

	struct CART3D_COMMON_CLASS PlyData
	{
		Type t;
		Buffer buffer;
		size_t count{ 0 };
		bool isList{ false };
	};

	struct CART3D_COMMON_CLASS PlyProperty
	{
		PlyProperty(std::istream & is);
		PlyProperty(Type type, std::string & _name);
		PlyProperty(Type list_type, Type prop_type, std::string & _name, size_t list_count);
		std::string name;
		Type propertyType{ Type::INVALID };
		bool isList{ false };
		Type listType{ Type::INVALID };
		size_t listCount{ 0 };
	};

	struct CART3D_COMMON_CLASS PlyElement
	{
		PlyElement(std::istream & istream);
		PlyElement(const std::string & _name, size_t count);
		std::string name;
		size_t size{ 0 };
		std::vector<PlyProperty> properties;
	};

	struct CART3D_COMMON_CLASS PlyFile
	{
		struct PlyFileImpl;
		std::unique_ptr<PlyFileImpl> impl;

		PlyFile();
		~PlyFile();

		/*
		 * The ply format requires an ascii header. This can be used to determine at
		 * runtime which properties or elements exist in the file. Limited validation of the
		 * header is performed; it is assumed the header correctly reflects the contents of the
		 * payload. This function may throw. Returns true on success, false on failure.
		 */
		bool parse_header(std::istream & is);

		/*
		 * Execute a read operation. Data must be requested via `request_properties_from_element(...)`
		 * prior to calling this function.
		 */
		void read(std::istream & is);

		/*
		 * `write` performs no validation and assumes that the data passed into
		 * `add_properties_to_element` is well-formed.
		 */
		void write(std::ostream & os, bool isBinary);

		/*
		 * These functions are valid after a call to `parse_header(...)`. In the case of
		 * writing, get_comments() reference may also be used to add new comments to the ply header.
		 */
		std::vector<PlyElement> get_elements() const;
		std::vector<std::string> get_info() const;
		std::vector<std::string> & get_comments();
		bool is_binary_file() const;

		/*
		 * In the general case where |list_size_hint| is zero, `read` performs a two-pass
		 * parse to support variable length lists. The most general use of the
		 * ply format is storing triangle meshes. When this fact is known a-priori, we can pass
		 * an expected list length that will apply to this element. Doing so results in an up-front
		 * memory allocation and a single-pass import, a 2x performance optimization.
		 */
		std::shared_ptr<PlyData> request_properties_from_element(const std::string & elementKey,
			const std::vector<std::string> propertyKeys, const uint32_t list_size_hint = 0);

		void add_properties_to_element(const std::string & elementKey,
			const std::vector<std::string> propertyKeys,
			const Type type,
			const size_t count,
			const uint8_t * data,
			const Type listType,
			const size_t listCount);
	};


	
	struct CART3D_COMMON_CLASS PlyFile::PlyFileImpl
	{
		struct PlyDataCursor
		{
			size_t byteOffset{ 0 };
			size_t totalSizeBytes{ 0 };
		};

		struct ParsingHelper
		{
			std::shared_ptr<PlyData> data;
			std::shared_ptr<PlyDataCursor> cursor;
			uint32_t list_size_hint;
		};

		struct PropertyLookup
		{
			ParsingHelper * helper{ nullptr };
			bool skip{ false };
			size_t prop_stride{ 0 }; // precomputed
			size_t list_stride{ 0 }; // precomputed
		};

		std::unordered_map<uint32_t, ParsingHelper> userData;

		bool isBinary = false;
		bool isBigEndian = false;
		std::vector<PlyElement> elements;
		std::vector<std::string> comments;
		std::vector<std::string> objInfo;
		uint8_t scratch[64]; // large enough for max list size

		void read(std::istream & is);
		void write(std::ostream & os, bool isBinary);

		std::shared_ptr<PlyData> request_properties_from_element(const std::string & elementKey,
			const std::vector<std::string> propertyKeys,
			const uint32_t list_size_hint);

		void add_properties_to_element(const std::string & elementKey,
			const std::vector<std::string> propertyKeys,
			const Type type, const size_t count, const uint8_t * data, const Type listType, const size_t listCount);

		size_t read_property_binary(const size_t & stride, void * dest, size_t & destOffset, size_t destSize, std::istream & is);
		size_t read_property_ascii(const Type & t, const size_t & stride, void * dest, size_t & destOffset, size_t destSize, std::istream & is);

		std::vector<std::vector<PropertyLookup>> make_property_lookup_table();

		bool parse_header(std::istream & is);
		void parse_data(std::istream & is, bool firstPass);
		void read_header_format(std::istream & is);
		void read_header_element(std::istream & is);
		void read_header_property(std::istream & is);
		void read_header_text(std::string line, std::vector<std::string> & place, int erase = 0);

		void write_header(std::ostream & os) noexcept;
		void write_ascii_internal(std::ostream & os) noexcept;
		void write_binary_internal(std::ostream & os) noexcept;
		void write_property_ascii(Type t, std::ostream & os, const uint8_t * src, size_t & srcOffset);
		void write_property_binary(std::ostream & os, const uint8_t * src, size_t & srcOffset, const size_t & stride) noexcept;
	};


} // end namespace tinyply


#endif // end tinyply_h