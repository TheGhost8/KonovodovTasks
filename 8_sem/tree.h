#pragma once

#include <memory>
#include <iostream>

namespace bintree {
    template <typename T>
    struct TNode : public std::enable_shared_from_this<TNode<T>> {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeWeakPtr = std::weak_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;
        using TNodeConstWeakPtr = std::weak_ptr<const TNode<T>>;

private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        TNodeWeakPtr parent = nullptr;

        TNode(T v)
            : value(v)
            , parent()
        {
        }
        TNode(T v, TNodePtr left, TNodePtr right)
            : value(v)
            , left(left)
            , right(right)
            , parent()
        {
        }

        static void setParentNullptr(TNodePtr node) {
            if (node)
                node->parent.reset();
        }

        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = TNodeWeakPtr(parent);
        }

public:
        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            return bool(parent);
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }
        
        TNodePtr getLeft() {
            return left;
        }
        
        TNodePtr getRight() {
            return right;
        }

        TNodePtr getParent() {
            return parent.lock();
        }
        
        TNodeConstPtr getLeft() const {
            return left;
        }
        
        TNodeConstPtr getRight() const {
            return right;
        }
        
        TNodeConstPtr getParent() const {
            return parent.lock();
        }
        
        static TNodePtr createLeaf(T v) {
            return std::make_shared<TNode>(TNode(v));
        }

        static TNodePtr fork(T v, TNodePtr left, TNodePtr right) {
            TNodePtr ptr = std::make_shared<TNode>(TNode(v, left, right));
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }

        TNodePtr replaceLeft(TNodePtr l) {
            setParent(l, this->shared_from_this());
            setParentNullptr(left);
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            setParent(r, this->shared_from_this());
            setParentNullptr(right);
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }

        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }

        void printNode() {
            if (!parent.expired()) {
                std::cout << "parent: " << std::to_string(parent.use_count()) << std::endl;
            }
                std::cout << "node:   " << std::to_string(value) << std::endl;
            if (left) {
                std::cout << "left:   " << std::to_string(left->value) << std::endl;
            }
            if (right) {
                std::cout << "right:  " << std::to_string(right->value) << std::endl;
            }
            std::cout << "------------------\n";
        }
    };
}
