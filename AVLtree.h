//
// Created by AlexHoring on 2022/6/7.
//

#ifndef SEARCH101_AVLTREE_H
#define SEARCH101_AVLTREE_H

#include <functional>

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
    Type data;

    AVLnodeEntity(Type &dat = Type());

    ~AVLnodeEntity();

    template<typename T, typename C>
    friend
    class AVLtree;

private:
    BalanceFactor balanceFactor;
    AVLnodeEntity *leftChild, *rightChild;


};
//将其指针类型定义为node，因为其最常被使用
template<typename Type>
using AVLnode = AVLnodeEntity<Type> *;

/**
 * @author AlexHoring
 * @brief 平衡树主框架
 * @tparam _Type 平衡树元素的类型
 * @tparam _Compare 平衡树的比较仿函数类型
 */
template<typename Type, typename Compare=std::less<Type> >
class AVLtree {
public:
    using AVLnodeType = AVLnode<Type>;
    AVLtree(Compare compare = Compare());

    ~AVLtree();

    /**
     * @author AlexHoring
     * @brief 向平衡二叉树中插入一个元素
     * @param element 要插入的元素
     */
    void insert(Type element);

    /**
     * @author AlexHoring
     * @brief 在平衡二叉树中寻找指定元素
     * @param toSearch 待寻找的元素
     * @return 查找成功返回指向该节点的指针，否则返回nullptr
     * @todo 待完善
     */
    AVLnodeType find(Type toSearch);

    /**
     * @author AlexHoring
     * @brief 删除指定节点
     * @param deleteNode 要删除的节点
     * @todo 完善
     */
    void erase(AVLnodeType deleteNode);

private:
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
    bool insert_element(AVLnodeType &treeRoot, Type &element, bool &taller);
};

template<typename Type>
AVLnodeEntity<Type>::AVLnodeEntity(Type &dat) {
    this->data = dat;
    balanceFactor = EQUAL_HEIGHT;
    leftChild = rightChild = nullptr;
}

template<typename Type>
AVLnodeEntity<Type>::~AVLnodeEntity() {
    delete this->leftChild;
    delete this->rightChild;
}

template<typename Type, typename Compare>
AVLtree<Type, Compare>::AVLtree(Compare compare) {
    this->root = nullptr;
    this->compare = compare;
    this->nodeNumber = 0;
}

template<typename Type, typename Compare>
AVLtree<Type, Compare>::~AVLtree() {
    delete this->root;
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::rotate_right(AVLnodeType &node) {
    AVLnode<Type> t = node->leftChild;
    node->leftChild = t->rightChild;
    t->rightChild = node;
    node = t;
}

template<typename Type, typename Compare>
void AVLtree<Type, Compare>::rotate_left(AVLnodeType &node) {
    AVLnode<Type> t = node->rightChild;
    node->rightChild = t->leftChild;
    t->leftChild = node;
    node = t;
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
    }
}

template<typename Type, typename Compare>
bool AVLtree<Type, Compare>::insert_element(AVLnodeType &treeRoot, Type &element, bool &taller) {
    if (treeRoot == nullptr) {
        treeRoot = new AVLnodeEntity<Type>(element);
        taller = true;
    } else {
        //不大于并且不小于，就是相等
        if (!compare(element, treeRoot->data) && !compare(treeRoot->data, element)) {
            return false;
        }
        if (compare(element, treeRoot->data)) {
            if (!insert_element(treeRoot->leftChild, element, taller)) {
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
            if (!insert_element(treeRoot->rightChild, element, taller)) {
                return false;
            }
            if (taller) {
                switch (treeRoot->balanceFactor) {
                    case LEFT_HIGHER:
                        treeRoot->balanceFactor = EQUAL_HEIGHT;
                        taller = false;
                        break;
                    case EQUAL_HEIGHT:
                        treeRoot = RIGHT_HIGHER;
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
    if (insert_element(this->root, element, taller)) {
        this->nodeNumber++;
    }
}

#endif //SEARCH101_AVLTREE_H
