
#pragma once
#include <vector>
#include <utility>
#include "topofwd.h"
template<class T>
class IterPool
{
private:
    struct Block {
        T       datum;
        Block* next;
        Block* prev;
    };
    Block* block_list;
    Block* block_list_end;
    uint numAlloced;
public:
    IterPool(int minInitBlocks=10) :
        numAlloced(0),
        block_list(nullptr)
    {}
    IterPool(IterPool &&src)
        : numAlloced(src.numAlloced),
          block_list(src.block_list)
    {
        src.block_list = nullptr;
    }
    ~IterPool() {
        // run through and destruct all remaining elements
        for_each([](T* obj) {
            obj->~T();
        });
		for (auto ptr : blocks) {
			mi_free(ptr);
		}
		blocks.clear();
    }
    
    void clear() {
        for_each([](T* obj) {
            obj->~T();
        });
        numAlloced = 0;
        block_list = nullptr;
		for (auto ptr : blocks) {
			mi_free(ptr);
		}
		blocks.clear();
    }
    
    void operator=(IterPool &&src)
    {
        for_each([](T* obj) {
            obj->~T();
        });
        block_list = src.block_list;
        src.block_list = nullptr;
    }
    
    

    
public: // allocation/deallocation support
    T* alloc() {
        Block *new_block = (Block*)mi_malloc(sizeof(Block));
		blocks.push_back(new_block);
        if(block_list) block_list->prev = new_block;
        new_block->next = block_list;
        new_block->prev = NULL;
        block_list = new_block;
        
        T* obj = (T*)new_block;
        new (obj) T(); // invoke default constructor when allocating
        
        numAlloced++;
        
		if (new_block->next==NULL)
			block_list_end = new_block;

        return obj;
    }
    void free(T* item) {
        if(item == NULL)   return;
        item->~T(); // invoke destructor before releasing
        
        numAlloced--;
        
        Block *ptr = (Block*)(item);
        if(ptr->next)   ptr->next->prev = ptr->prev;
        if(ptr->prev)   ptr->prev->next = ptr->next;
        if(ptr == block_list)   block_list = ptr->next;
    }

	void add(T* backItem, T* _block_list)
	{
		if (backItem == NULL || block_list == NULL)   return;
		Block *backPtr = (Block*)(backItem);
		Block *firstPtr = (Block*)(block_list);
		if (backPtr->next)  return;
		if (firstPtr->prev) return;
		backPtr->next = firstPtr;
		firstPtr->prev = backPtr;
		block_list = (Block*)(_block_list);
	}

	Block *getEnd()
	{
		return block_list_end;
	}

	Block *getfirst()
	{
		return block_list;
	}

	void glue(T* fistItem, T* backItem)
	{
		((Block*)(backItem))->next = ((Block*)(fistItem));
		((Block*)(fistItem))->prev = ((Block*)(backItem));
	}

	void glue_null(T* fistItem)
	{
		((Block*)(fistItem))->prev =NULL;
	}
    
public:
    inline void for_each(std::function<void(T*)> func) const {
        for(Block *block = block_list;
          block != NULL;
          block = block->next) {
			func((T*)(block));
        }
    }

	inline void back_for_each(std::function<void(T*)> func) const {
		for (Block *block = block_list_end;
			block != NULL;
			block = block->prev) {
			func((T*)(block));
		}
	}

	inline void for_each_stop(std::function<bool(T*)> func) const {
		for (Block *block = block_list;
			block != NULL;
			block = block->next) {
			if (func((T*)(block)))
				break;
		}
	}

	inline void for_each_contiune(std::function<bool(T*)> func) const {
		for (Block *block = block_list;
			block != NULL;
			block = block->next) {
			if (func((T*)(block)))
				continue;
		}
	}


    inline bool contains(T* tptr) const {
        for(Block *block = block_list;
          block != NULL;
          block = block->next) {
            if(tptr == (T*)(block))
                return true;
        }
        return false;
    }
    inline uint size() const {
        return numAlloced;
    }
public: // iteration support
    class iterator {
    public:
        iterator() : ptr(NULL) {}
        iterator(Block *init) : ptr(init) {}
        iterator(const iterator &cp) : ptr(cp.ptr) {}
        
        iterator& operator++() { // prefix version
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int) {
            iterator it(ptr);
            ptr = ptr->next;
            return it;
        } // postfix version
        T& operator*() {
            return ptr->datum;
        }
        T* operator->() {
            return (T*)(ptr);
        }
        bool operator==(const iterator &rhs) {
            return ptr == rhs.ptr;
        }
        bool operator!=(const iterator &rhs) {
            return ptr != rhs.ptr;
        }
    private:
        Block *ptr;
    };
    
    iterator begin() {
        return iterator(block_list);
    }
    iterator end() {
        return iterator(NULL);
    }
    
private:
	cork_vector<Block*> blocks;
};



