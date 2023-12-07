#ifndef CART3D_MEMORY_POOL_H
#define CART3D_MEMORY_POOL_H
#include <Cart3DCommonDefine.h>
#include <Util/BoostUtil.h>
#include <atomic>
#include <mutex>
namespace Cart3D
{
	template<class BlockType>
	class MemoryPool
	{
	public:
		using BlockTypePtr = BlockType * ;
	public:
		MemoryPool::MemoryPool(int pagesize=1024) :
			m_pagesize(pagesize),
			m_reserved(0),
			m_num_pages(0),
			m_current_block(0)
		{}
		~MemoryPool() {
			for (auto&& i : m_pages) {
				mi_free(i);
			}
		}
	public:
		size_t size() const { return m_current_block; };
		BlockTypePtr operator[](const std::uint32_t i) const {
			const int page_idx = i / m_pagesize;
			const int ptr_idx = i % m_pagesize;
			return m_pages[page_idx] + (ptr_idx);
		}
		void reserve(const std::uint32_t n) {
			bool requires_realloc = (m_current_block + n) > m_reserved;
			if (requires_realloc)
				expand(n);
		}
		BlockTypePtr acquire_block() {
			std::uint32_t current = m_current_block.fetch_add(1);
			const std::uint32_t page_idx = current / m_pagesize;
			const std::uint32_t ptr_idx = current % m_pagesize;
			BlockTypePtr ptr = m_pages[page_idx] + (ptr_idx);
			return ptr;
		}
	private:
		const std::uint32_t m_pagesize;
		std::uint64_t m_reserved;	
		std::uint32_t m_num_pages;
		std::atomic<std::uint32_t> m_current_block;
		ct_vector<BlockTypePtr> m_pages;
	private:
		void expand(const size_t n) {
			static std::mutex mutex;
			std::lock_guard<std::mutex> guard(mutex);
			const std::uint32_t new_pages = std::ceil(n / m_pagesize);
			for (std::uint32_t p = 0; p <= new_pages; ++p) {
				m_pages.push_back((BlockTypePtr)mi_malloc(sizeof(BlockType)*m_pagesize));
				++m_num_pages;
				m_reserved += m_pagesize;
			}
		}
	private:
		MemoryPool(const MemoryPool& m);
	};

}

#endif