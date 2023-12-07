#ifndef CART3D_AIF_CELL_MESH_H
#define CART3D_AIF_CELL_MESH_H

#include <Cart3dMeshDefine.h>
#include <Util/EigenUtil.h>
#include <Util/TreeUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{
    template<class T>
    class AIFCell
    {
    public:
        using iterator = typename ct_vector< T >::iterator;
        using const_iterator = typename ct_vector< T >::const_iterator;
    public:
        void add(T c) {
            c->set_index(static_cast<int>(container.size()));
            container.emplace_back(c);
        }
        int remove(int i)
        {
            int size = static_cast<int>(container.size());
            int lastId = size - 1;
            if (size == 0 || i > lastId)
                throw std::runtime_error("In CellContainer::remove(): index out of range.");
            int tmp = container[i]->get_index();
            bool ascending_order = (tmp == i) && (container[lastId]->get_index() == lastId);
            if (ascending_order) {
                container[i] = container[lastId];
                container[i]->set_index(i);
            }
            else {
                if (tmp == lastId)
                    container[i] = container[lastId];
                else
                {
                    int index_max = 0;
                    for (int n = 1; n <= lastId; ++n)
                        if (container[n]->get_index() > container[index_max]->get_index())
                            index_max = n;
                    container[i] = container[lastId];
                    container[index_max]->set_index(tmp);
                }
            }
            container.pop_back();
            return lastId;
        }
    public:
        T& operator[](int idx) { return container[idx]; }
        const T& operator[](int idx) const { return container.at(idx); }
        T& at(int idx) { return container[idx]; }
        const T& at(int idx) const { return container.at(idx); }
    public:
        iterator begin(void) { return container.begin(); }
        iterator end(void) { return container.end(); }
        const_iterator begin(void) const { return container.begin(); }
        const_iterator end(void) const { return container.end(); }
        const_iterator cbegin(void) const { return container.cbegin(); }
        const_iterator cend(void) const { return container.cend(); }
    public:
        int size(void) const { return container.size(); }
        void reserve(int n) { container.reserve(n); }
        iterator erase(const iterator iter) { return container.erase(iter); }
    private:
        ct_vector< T > container;
    };

    template< typename ContainerType, typename ContainedType >
    void insert(ContainerType& container, const ContainedType& element){
        container.insert(container.end(), element);
    }
    template< typename ContainerType, typename ContainedType >
    void erase(ContainerType& container, const ContainedType& element)
    {
        typename ContainerType::iterator it;
        if ((it = std::find(container.begin(), container.end(), element)) !=
            container.end())
            container.erase(it);
        else
            throw std::invalid_argument("Helpers::erase element in container -> given element not found.");
    }
    template<class T>
    using AIFProperty = tree_map<std::string, ct_vector<T>>;

}

#endif