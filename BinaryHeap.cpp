//
// Created by Trowood on 2022/6/5.
//

#include "BinaryHeap.h"

template <
        typename _Type,
        typename _Compare = std::less<_Type>,
        typename _Container = std::vector<_Type>>

template <typename _RandomAccessIterator, typename _Cmp>
static void BinaryHeap::MakeHeap(_RandomAccessIterator begin, _RandomAccessIterator end, _Cmp comp = _Compare())
{
    _RandomAccessIterator flag;
    size_t i;
    size_t len = end - begin;
    for (i = len / 2, flag = begin + i; flag != begin - 1; --flag, --i)
    {
        sink_down(begin, end, i, comp);
    }
}

BinaryHeap::BinaryHeap(const _Container &c = _Container(),
                       const _Compare &cp = _Compare())
        : container(c), compare(cp)
{
    MakeHeap(container.begin(), container.end(), compare);
}

template <typename _RandomAccessIterator>
BinaryHeap::BinaryHeap(_RandomAccessIterator begin,
           _RandomAccessIterator end,
           const _Container &c = _Container(),
           const _Compare &cp = _Compare())
        : container(c), compare(cp)
{
    container.assign(begin, end);
    MakeHeap(container.begin(), container.end(), compare);
}

 bool BinaryHeap::empty() const
{
    return container.empty();
}

size_t BinaryHeap::size() const
{
    return container.size();
}

const _Type & BinaryHeap::top() const
{
    return container.front();
}


void BinaryHeap::pop()
{
    //头尾交换，删除尾部，然后下沉
    auto head = container.begin(), tail = container.end() - 1;
    auto temp = *head;
    *head = *tail;
    *tail = temp;
    container.pop_back();

    sink_down(container.begin(), container.end(), 0, compare);
}

void BinaryHeap::push(_Type &t)
{
    container.push_back(t);
    size_t sz = container.size();
    swim_up(container.begin(), sz - 1, compare);
}
void BinaryHeap::push(_Type &&t)
{
    container.push_back(t);
    size_t sz = container.size();
    swim_up(container.begin(), sz - 1, compare);
}

template <typename _RandomAccessIterator, typename _Cmp>
static void BinaryHeap::swim_up(_RandomAccessIterator begin, size_t index, _Cmp &comp)
{
    size_t n = index, j;
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
static void BinaryHeap::sink_down(_RandomAccessIterator begin, _RandomAccessIterator end, size_t index, _Cmp &comp)
{
    size_t len = end - begin;
    size_t n = index, j;
    j = 2 * n + 1;

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