#ifndef __BINARYHEAP_H__
#define __BINARYHEAP_H__ 1

#include <functional>
#include <algorithm>
#include <vector>

//泛型参数：元素类型、元素的序关系、容器
template <
        typename _Type,
        typename _Compare = std::less<_Type>,
        typename _Container = std::vector<_Type>>
class BinaryHeap
{
protected:
    _Container container;
    _Compare compare;

public:
    //建堆函数
    template <typename _RandomAccessIterator, typename _Cmp>
    static void MakeHeap(_RandomAccessIterator begin, _RandomAccessIterator end, _Cmp comp = _Compare())
    {
        _RandomAccessIterator flag;
        size_t i;
        size_t len = end - begin;
        for (i = len / 2, flag = begin + i; flag != begin - 1; --flag, --i)
        {
            sink_down(begin, end, i, comp);
        }
    }

    //构造函数：支持通过容器、连续序列的头尾来构造
    BinaryHeap(const _Container &c = _Container(),
               const _Compare &cp = _Compare())
            : container(c), compare(cp)
    {
        MakeHeap(container.begin(), container.end(), compare);
    }

    template <typename _RandomAccessIterator>
    BinaryHeap(_RandomAccessIterator begin,
               _RandomAccessIterator end,
               const _Container &c = _Container(),
               const _Compare &cp = _Compare())
            : container(c), compare(cp)
    {
        container.assign(begin, end);
        MakeHeap(container.begin(), container.end(), compare);
    }

    //检查是否为空：调用容器的相关函数
    bool empty() const
    {
        return container.empty();
    }

    //返回元素个数
    size_t size() const
    {
        return container.size();
    }

    //返回顶部元素
    const _Type &top() const
    {
        return container.front();
    }

    //删除顶部元素
    void pop()
    {
        //头尾交换，删除尾部，然后下沉
        auto head = container.begin(), tail = container.end() - 1;
        auto temp = *head;
        *head = *tail;
        *tail = temp;
        container.pop_back();

        sink_down(container.begin(), container.end(), 0, compare);
    }

    //插入元素：插入尾部，然后上浮
    void push(_Type &t)
    {
        container.push_back(t);
        size_t sz = container.size();
        swim_up(container.begin(), sz - 1, compare);
    }
    void push(_Type &&t)
    {
        container.push_back(t);
        size_t sz = container.size();
        swim_up(container.begin(), sz - 1, compare);
    }

private:
    //上浮与下沉功能
    template <typename _RandomAccessIterator, typename _Cmp>
    static void swim_up(_RandomAccessIterator begin, size_t index, _Cmp &comp)
    {
        size_t n = index, j;
        //上浮：和父亲节点比较，如果满足比较条件就上浮，直到不满足为止
        while ((j = (n - 1) / 2) >= 0 && comp(*(begin + j), *(begin + n)) && n != 0)
        {
            auto head = begin + j, tail = begin + n;
            auto temp = *head;
            *head = *tail;
            *tail = temp;
            n = j;
        }
    }
    template <typename _RandomAccessIterator, typename _Cmp>
    static void sink_down(_RandomAccessIterator begin, _RandomAccessIterator end, size_t index, _Cmp &comp)
    {
        size_t len = end - begin;
        size_t n = index, j;
        j = 2 * n + 1;

        //下沉：和左右儿子比较，如果满足交换条件就交换
        if (j + 1 < len && comp(*(begin + j), *(begin + (j + 1))))
            ++j;
        while (j < len && comp(*(begin + n), *(begin + j)))
        {
            auto head = begin + j, tail = begin + n;
            auto temp = *head;
            *head = *tail;
            *tail = temp;
            n = j;
            j = 2 * n + 1;
            if (j + 1 < len && comp(*(begin + j), *(begin + (j + 1))))
                ++j;
        }
    }
};

#endif