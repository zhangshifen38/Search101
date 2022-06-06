//
// Created by Trowood on 2022/6/5.
//

#ifndef SUANFA_BINARYHEAP_H
#define SUANFA_BINARYHEAP_H

#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using  namespace  std;

template <
        typename _Type,
        typename _Compare = std::less<_Type>,
        typename _Container = std::vector<_Type>
                >
/**
 * @author Trowood
 * @brief 以二叉堆实现的优先队列
 */
 class BinaryHeap {
 protected:
     _Container container;
     _Compare compare;

 public:
     /**
      * @author Trowood
      * @brief 建造二叉堆
      * @param 接受队列内容类型的头，尾
      */
     template <typename _RandomAccessIterator, typename _Cmp>
     static void MakeHeap(_RandomAccessIterator begin, _RandomAccessIterator end, _Cmp comp = _Compare());
     /**
      * @author Trowood
      * @brief 类的构造函数
      * @param 接受容器和比较规则
      */
     BinaryHeap(const _Container &c = _Container(),const _Compare &cp = _Compare());
     template <typename _RandomAccessIterator>
	 /**
      * @author Trowood
      * @brief 类的构造函数
      * @param 接受连续序列的头尾，容器和比较规则
      */
     BinaryHeap(_RandomAccessIterator begin,
                _RandomAccessIterator end,
                const _Container &c = _Container(),
                const _Compare &cp = _Compare());
     /**
      * @author Trowood
      * @brief 检查是否为空：调用容器的相关函数
      * @return 为空返回1，不为空返回0
      */
     bool empty() const;
     /**
       * @author Trowood
       * @brief 返回元素个数
       * @return 返回值为元素的个数
       */
     size_t size() const;
     /**
        * @author Trowood
        * @brief 返回顶部元素
        * @return 返回顶部元素个数
        */
     const _Type &top() const;
    /**
        * @author Trowood
        * @brief 删除顶部元素
        */
     void pop();
     /**
         * @author Trowood
         * @brief 插入元素：插入尾部，然后上浮
		 * @param 接受一个左值 	
         */
     void push(_Type &t);
	 /**
         * @author Trowood
         * @brief 插入元素：插入尾部，然后上浮
	     * @param 接受一个右值 	
         */
     void push(_Type &&t);

 private:
     /**
         * @author Trowood
         * @brief 上浮功能
		 * @param 接受起始位置，操作对象位置，比较规则 
         */
     template <typename _RandomAccessIterator, typename _Cmp>
     static void swim_up(_RandomAccessIterator begin, size_t index, _Cmp &comp);
     /**
         * @author Trowood
         * @brief 下沉功能
		 * @param 接受起始位置，结束位置，操作对象位置，比较规则 
         */
     template <typename _RandomAccessIterator, typename _Cmp>
     static void sink_down(_RandomAccessIterator begin, _RandomAccessIterator end, size_t index, _Cmp &comp);
 };
#endif //SUANFA_BINARYHEAP_H
