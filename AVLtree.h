//
// Created by AlexHoring on 2022/6/7.
//

#ifndef SEARCH101_AVLTREE_H
#define SEARCH101_AVLTREE_H

#include <functional>
#include <queue>
#include <iostream>

typedef short BalanceFactor;
const short RIGHT_HIGHER = -1;
const short EQUAL_HEIGHT = 0;
const short LEFT_HIGHER = 1;

/**
 * @author AlexHoring
 * @brief 平衡树的节点定义
 * @tparam _Type 存储的数据类型
 */
template<typename Type>
class AVLnodeEntity {
public:
    Type *data;

    AVLnodeEntity(Type dat = Type());

    ~AVLnodeEntity();

    template<typename T, typename C>
    friend
    class AVLtree;

    template<typename T>
    friend
    class AVLnodeIterator;

private:
    BalanceFactor balanceFactor;
    AVLnodeEntity *leftChild, *rightChild;
    AVLnodeEntity *father;
};
//将其指针类型定义为node，因为其最常被使用
template<typename Type>
using AVLnode = AVLnodeEntity<Type> *;

/**
 * @author AlexHoring
 * @brief 为其构造一个迭代器类型
 * @tparam Type 存储的元素类型
 */
template<typename Type>
class AVLnodeIterator {
public:
    template<typename T, typename C>
    friend
    class AVLtree;

    AVLnodeIterator();

    ~AVLnodeIterator() = default;

    /**
     * @author AlexHoring
     * @brief 重载取内容运算符
     * @return 该迭代器指向的元素
     */
    Type& operator*();

    /**
     * @author AlexHoring
     * @brief 重载前置++运算符
     * @return 自增后自己的引用
     */
    AVLnodeIterator &operator++();

    /**
     * @author AlexHoring
     * @brief 重载后置++运算符
     * @return 自增前的迭代器对象
     */
    const AVLnodeIterator operator++(int);

    /**
     * @author AlexHoring
     * @brief 重载前置--运算符
     * @return 自减后自己的引用
     */
    AVLnodeIterator &operator--();

    /**
     * @author Alexhoring
     * @brief 重载后置--运算符
     * @return 自减前的迭代器对象
     */
    const AVLnodeIterator operator--(int);

    /**
     * @author AlexHoring
     * @brief 重载相等运算符
     * @param a 比较的另一个对象
     * @return 内部指针指向地址相同则true否则false
     */
    bool operator==(AVLnodeIterator<Type> a);

    /**
     * @author AlexHoring
     * @brief 重载不等运算符
     * @param a 比较的另一个对象
     * @return 内部指针指向地址不同则true否则false
     */
    bool operator!=(AVLnodeIterator<Type> a);

private:
    /**
     * @author Alexhoring
     * @brief 带参构造函数，不对外暴露
     * @param it 节点
     */
    AVLnodeIterator(AVLnode<Type> it);

    AVLnode<Type> iterator;
    Type rubbish;
};

/**
 * @author AlexHoring
 * @brief 平衡树主框架,root是哑元，类似链表的头节点
 * @tparam _Type 平衡树元素的类型
 * @tparam _Compare 平衡树的比较仿函数类型
 */
template<typename Type, typename Compare=std::less<Type> >
class AVLtree {
public:
    using AVLnodeType = AVLnode<Type>;
    using iterator = AVLnodeIterator<Type>;

    AVLtree();

    ~AVLtree();

    virtual /**
     * @author AlexHoring
     * @brief 获取指向首元素的迭代器
     * @return 首元素迭代器
     */
    iterator begin();

    virtual /**
     * @author AlexHoring
     * @brief 获取指向“尾元素下一位”的迭代器
     * @return “尾元素后一位”的迭代器
     */
    iterator end();

    virtual /**
     * @author AlexHoring
     * @brief 向平衡二叉树中插入一个元素
     * @param element 要插入的元素
     */
    void insert(Type element);

    virtual /**
     * @author AlexHoring
     * @brief 清除平衡二叉树的所有节点
     */
    void clear();

    virtual /**
     * @author AlexHoring
     * @brief 在平衡二叉树中寻找指定元素
     * @param toSearch 待寻找的元素
     * @return 查找成功返回指向该节点的迭代器，否则返回end()
     * @todo 待完善
     */
    iterator find(Type toSearch);

    virtual /**
     * @author AlexHoring
     * @brief 删除指定节点
     * @param deleteLocale 要删除的节点的迭代器
     */
    void erase(iterator deleteLocale);

    virtual /**
     * @author AlexHoring
     * @brief 返回元素的个数
     * @return 元素个数
     */
    size_t size();

    //临时函数，将被删除
    void print() {
        AVLnodeType cur;
        std::queue<AVLnodeType> que;
        que.push(this->root);
        while (que.size()) {
            cur = que.front();
            que.pop();
            if (cur->leftChild != nullptr) {
                std::cout << *(cur->leftChild->data) << ' ' << *(cur->leftChild->father->data) << std::endl;
                que.push(cur->leftChild);
            }
            if (cur->rightChild != nullptr) {
                std::cout << *(cur->rightChild->data) << ' ' << *(cur->rightChild->father->data) << std::endl;
                que.push(cur->rightChild);
            }
        }
        std::cout << std::endl;
    }

protected:
    AVLnode<Type> root;
    Compare compare;
    size_t nodeNumber;

    /**
     * @author AlexHoring
     * @brief 右旋
     * @param node 待旋转的子树的根节点
     */
    void rotate_right(AVLnodeType &node);

    /**
     * @author AlexHoring
     * @brief 左旋
     * @param node 待旋转的子树的根节点
     */
    void rotate_left(AVLnodeType &node);

    /**
     * @author AlexHoring
     * @brief 将左子树调平衡
     * @param node 待调整的根节点
     */
    void balance_left(AVLnodeType &node);

    /**
     * @author AlexHoring
     * @brief 将右子树调平衡
     * @param node 待调整的根节点
     */
    void balance_right(AVLnodeType &node);

    /**
     * @author AlexHoring
     * @brief 插入工作真正的实现者。
     * @param treeRoot 插入的子树
     * @param element 插入的元素
     * @param taller 子树高度是否增加的判断变量
     * @return 插入成功与否
     */
    bool insert_element(AVLnodeType father, AVLnodeType &treeRoot, Type &element, bool &taller);

    /**
     * @author AlexHoring
     * @brief 查找工作的真正实现者
     * @param treeRoot 待查找的子树
     * @param element 查找的元素
     * @return 元素所在的节点，若找不到则返回nullptr
     */
    AVLnodeType find_element(AVLnodeType treeRoot, Type &element);

    /**
     * @author AlexHoring
     * @brief 根节点左子树高度下降时的调整函数
     * @param treeRoot 待调整子树根节点
     */
    void down_left(AVLnodeType treeRoot);

    /**
     * @author AlexHoring
     * @brief 根节点右子树高度下降时的调整函数
     * @param treeRoot 待调整子树根节点
     */
    void down_right(AVLnodeType treeRoot);
};

template<typename Type>
AVLnodeEntity<Type>::AVLnodeEntity(Type dat) {
    this->data = new Type(dat);
    balanceFactor = EQUAL_HEIGHT;
    leftChild = rightChild = father = nullptr;
}

template<typename Type>
AVLnodeEntity<Type>::~AVLnodeEntity() {
    delete this->leftChild;
    delete this->rightChild;
    delete this->data;
}

template<typename Type>
AVLnodeIterator<Type>::AVLnodeIterator() {
    this->iterator = nullptr;
    this->rubbish=Type();
}

template<typename Type>
AVLnodeIterator<Type>::AVLnodeIterator(AVLnode<Type> it) {
    this->iterator = it;
    this->rubbish=Type();
}

template<typename Type>
Type& AVLnodeIterator<Type>::operator*() {
    if (this->iterator == nullptr) {
        return rubbish;
    } else {
        return *(iterator->data);
    }
}

template<typename Type>
AVLnodeIterator<Type> &AVLnodeIterator<Type>::operator++() {
    if (this->iterator != nullptr) {
        if (this->iterator->rightChild != nullptr) {
            this->iterator = this->iterator->rightChild;
            while (this->iterator->leftChild != nullptr) {
                this->iterator = this->iterator->leftChild;
            }
        } else {
            while (this->iterator->father != nullptr && this->iterator->father->rightChild == this->iterator) {
                this->iterator = this->iterator->father;
            }
            this->iterator = this->iterator->father;
        }
    }
    return *this;
}

template<typename Type>
const AVLnodeIterator<Type> AVLnodeIterator<Type>::operator++(int) {
    AVLnode<Type> previousIterator = this->iterator;
    ++(*this);
    return AVLnodeIterator<Type>(previousIterator);
}

template<typename Type>
AVLnodeIterator<Type> &AVLnodeIterator<Type>::operator--() {
    if (this->iterator != nullptr) {
        if (this->iterator->leftChild != nullptr) {
            this->iterator = this->iterator->leftChild;
            while (this->iterator->rightChild != nullptr) {
                this->iterator = this->iterator->rightChild;
            }
        } else {
            while (this->iterator->father != nullptr && this->iterator->father->leftChild == this->iterator) {
                this->iterator = this->iterator->father;
            }
            this->iterator = this->iterator->father;
        }
    }
    return *this;
}

template<typename Type>
const AVLnodeIterator<Type> AVLnodeIterator<Type>::operator--(int) {
    AVLnode<Type> previousIterator = this->iterator;
    --(*this);
    return AVLnodeIterator<Type>(previousIterator);
}

template<typename Type>
bool AVLnodeIterator<Type>::operator==(AVLnodeIterator<Type> a) {
    return this->iterator == a.iterator;
}

template<typename Type>
bool AVLnodeIterator<Type>::operator!=(AVLnodeIterator<Type> a) {
    return this->iterator != a.iterator;
}

template<typename Type, typename Compare>
AVLtree<Type, Compare>::AVLtree() {
    this->root = new AVLnodeEntity<Type>();
    this->compare = Compare();
    this->nodeNumber = 0;
}

template<typename Type, typename Compare>
AVLtree<Type, Compare>::~AVLtree() {
    delete this->root;
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::rotate_right(AVLnodeType &node) {
    AVLnode<Type> t = node->leftChild;      //新的根节点：旧根左儿子
    node->leftChild = t->rightChild;        //旧根左儿子变为新根右儿子
    if (node->leftChild != nullptr) {
        node->leftChild->father = node;     //若存在则更新父亲
    }
    t->rightChild = node;                   //新根的右儿子变为旧根
    t->father = node->father;               //更新新根的父亲
    node->father = t;                       //更新旧根的父亲
    node = t;                               //更新旧根
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::rotate_left(AVLnodeType &node) {
    AVLnode<Type> t = node->rightChild;     //新的根节点：旧根右儿子
    node->rightChild = t->leftChild;        //旧根右儿子变为新根左儿子
    if (node->rightChild != nullptr) {
        node->rightChild->father = node;    //若存在，更新父亲
    }
    t->leftChild = node;                    //新根左儿子变为旧根
    t->father = node->father;               //更新新根的父亲
    node->father = t;                       //更新旧根的父亲
    node = t;                               //更新旧根
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::balance_left(AVLnodeType &node) {
    AVLnode<Type> l, lr;
    l = node->leftChild;
    switch (l->balanceFactor) {
        case LEFT_HIGHER:
            node->balanceFactor = l->balanceFactor = EQUAL_HEIGHT;
            rotate_right(node);
            break;
        case RIGHT_HIGHER:
            lr = l->rightChild;
            switch (lr->balanceFactor) {
                case LEFT_HIGHER:
                    node->balanceFactor = RIGHT_HIGHER;
                    l->balanceFactor = EQUAL_HEIGHT;
                    break;
                case EQUAL_HEIGHT:
                    node->balanceFactor = l->balanceFactor = EQUAL_HEIGHT;
                    break;
                case RIGHT_HIGHER:
                    node->balanceFactor = EQUAL_HEIGHT;
                    l->balanceFactor = LEFT_HIGHER;
                    break;
            }
            lr->balanceFactor = EQUAL_HEIGHT;
            rotate_left(node->leftChild);
            rotate_right(node);
            break;
        case EQUAL_HEIGHT:
            lr = l->rightChild;
            node->leftChild = lr;
            l->rightChild = node;
            lr->father = node;
            l->father = node->father;
            node->father = l;
            node->balanceFactor = LEFT_HIGHER;
            l->balanceFactor = RIGHT_HIGHER;
            node = l;
            break;
    }
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::balance_right(AVLnodeType &node) {
    AVLnode<Type> r, rl;
    r = node->rightChild;
    switch (r->balanceFactor) {
        case RIGHT_HIGHER :
            node->balanceFactor = r->balanceFactor = EQUAL_HEIGHT;
            rotate_left(node);
            break;
        case LEFT_HIGHER:
            rl = r->leftChild;
            switch (rl->balanceFactor) {
                case RIGHT_HIGHER:
                    node->balanceFactor = LEFT_HIGHER;
                    r->balanceFactor = EQUAL_HEIGHT;
                    break;
                case EQUAL_HEIGHT:
                    node->balanceFactor = r->balanceFactor = EQUAL_HEIGHT;
                    break;
                case LEFT_HIGHER:
                    node->balanceFactor = EQUAL_HEIGHT;
                    r->balanceFactor = RIGHT_HIGHER;
                    break;
            }
            rl->balanceFactor = EQUAL_HEIGHT;
            rotate_right(node->rightChild);
            rotate_left(node);
            break;
        case EQUAL_HEIGHT:
            rl = r->leftChild;
            node->rightChild = rl;
            r->leftChild = node;
            rl->father = node;
            r->father = node->father;
            node->father = r;
            node->balanceFactor = RIGHT_HIGHER;
            r->balanceFactor = LEFT_HIGHER;
            node = r;
            break;
    }
}

template<typename Type, typename Compare>
bool AVLtree<Type, Compare>::insert_element(AVLnodeType father, AVLnodeType &treeRoot, Type &element, bool &taller) {
    if (treeRoot == nullptr) {
        treeRoot = new AVLnodeEntity<Type>(element);
        treeRoot->father = father;
        taller = true;
    } else {
        //不大于并且不小于，就是相等
        if (!compare(element, *(treeRoot->data)) && !compare(*(treeRoot->data), element)) {
            return false;
        }
        if (compare(element, *(treeRoot->data))) {
            if (!insert_element(treeRoot, treeRoot->leftChild, element, taller)) {
                return false;
            }
            if (taller) {
                switch (treeRoot->balanceFactor) {
                    case LEFT_HIGHER:
                        balance_left(treeRoot);
                        taller = false;
                        break;
                    case EQUAL_HEIGHT:
                        treeRoot->balanceFactor = LEFT_HIGHER;
                        taller = true;
                        break;
                    case RIGHT_HIGHER:
                        treeRoot->balanceFactor = EQUAL_HEIGHT;
                        taller = false;
                        break;
                }
            }
        } else {
            if (!insert_element(treeRoot, treeRoot->rightChild, element, taller)) {
                return false;
            }
            if (taller) {
                switch (treeRoot->balanceFactor) {
                    case LEFT_HIGHER:
                        treeRoot->balanceFactor = EQUAL_HEIGHT;
                        taller = false;
                        break;
                    case EQUAL_HEIGHT:
                        treeRoot->balanceFactor = RIGHT_HIGHER;
                        taller = true;
                        break;
                    case RIGHT_HIGHER:
                        balance_right(treeRoot);
                        taller = false;
                        break;
                }
            }
        }
    }
    return true;
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::insert(Type element) {
    bool taller;
    if (insert_element(this->root, this->root->leftChild, element, taller)) {
        this->nodeNumber++;
    }
}

template<typename Type, typename Compare>
typename AVLtree<Type, Compare>::iterator AVLtree<Type, Compare>::begin() {
    AVLtree::AVLnodeType node = this->root;
    while (node->leftChild != nullptr) {
        node = node->leftChild;
    }
    return AVLtree::iterator(node);
}

template<typename Type, typename Compare>
typename AVLtree<Type, Compare>::iterator AVLtree<Type, Compare>::end() {
    return AVLtree::iterator(this->root);
}

template<typename Type, typename Compare>
typename AVLtree<Type, Compare>::AVLnodeType
AVLtree<Type, Compare>::find_element(AVLtree::AVLnodeType treeRoot, Type &element) {
    if (treeRoot == nullptr) {
        return nullptr;
    }
    if (compare(element, *(treeRoot->data))) {
        return find_element(treeRoot->leftChild, element);
    } else if (compare(*(treeRoot->data), element)) {
        return find_element(treeRoot->rightChild, element);
    } else {
        return treeRoot;
    }
}

template<typename Type, typename Compare>
typename AVLtree<Type, Compare>::iterator AVLtree<Type, Compare>::find(Type toSearch) {
    AVLnodeType findResult = find_element(this->root->leftChild, toSearch);
    if (findResult == nullptr) {
        return end();
    } else {
        return iterator(findResult);
    }
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::erase(iterator deleteLocale) {
    if (deleteLocale.iterator == nullptr || deleteLocale.iterator->father == nullptr) {
        return;
    }
    if (deleteLocale.iterator->leftChild == nullptr && deleteLocale.iterator->rightChild == nullptr) {
        AVLnodeType father = deleteLocale.iterator->father;
        bool isLeftChild = (father->leftChild == deleteLocale.iterator);
        delete deleteLocale.iterator;
        deleteLocale.iterator = nullptr;
        if (isLeftChild) {
            father->leftChild = nullptr;
            down_left(father);
        } else {
            father->rightChild = nullptr;
            down_right(father);
        }
    } else {
        Type *type = deleteLocale.iterator->data;
        iterator toDelete = deleteLocale;
        ++toDelete;
        if (toDelete.iterator->father == nullptr) {
            --toDelete;
            --toDelete;
        }
        deleteLocale.iterator->data = toDelete.iterator->data;
        toDelete.iterator->data = type;
        erase(toDelete);
    }
    this->nodeNumber--;
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::down_left(AVLtree::AVLnodeType treeRoot) {
    if (treeRoot->father == nullptr) {
        return;
    }
    bool isLeftChild = (treeRoot->father->leftChild == treeRoot);
    switch (treeRoot->balanceFactor) {
        case LEFT_HIGHER:
            treeRoot->balanceFactor = EQUAL_HEIGHT;
            if (isLeftChild) {
                down_left(treeRoot->father);
            } else {
                down_right(treeRoot->father);
            }
            break;
        case EQUAL_HEIGHT:
            treeRoot->balanceFactor = RIGHT_HIGHER;
            break;
        case RIGHT_HIGHER:
            if (isLeftChild) {
                balance_right(treeRoot->father->leftChild);
            } else {
                balance_right(treeRoot->father->rightChild);
            }
            break;
    }
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::down_right(AVLtree::AVLnodeType treeRoot) {
    if (treeRoot->father == nullptr) {
        return;
    }
    bool isLeftChild = (treeRoot->father->leftChild == treeRoot);
    switch (treeRoot->balanceFactor) {
        case RIGHT_HIGHER:
            treeRoot->balanceFactor = EQUAL_HEIGHT;
            if (isLeftChild) {
                down_left(treeRoot->father);
            } else {
                down_right(treeRoot->father);
            }
            break;
        case EQUAL_HEIGHT:
            treeRoot->balanceFactor = LEFT_HIGHER;
            break;
        case LEFT_HIGHER:
            if (isLeftChild) {
                balance_left(treeRoot->father->leftChild);
            } else {
                balance_left(treeRoot->father->rightChild);
            }
            break;
    }
}

template<typename Type,typename Compare>
size_t AVLtree<Type, Compare>::size() {
    return this->nodeNumber;
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::clear() {
    delete this->root->leftChild;
    this->root->leftChild= nullptr;
    this->nodeNumber=0;
}

#endif //SEARCH101_AVLTREE_H
