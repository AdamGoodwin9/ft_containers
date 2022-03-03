#ifndef BST_HPP
#define BST_HPP

#include <functional>
#include <iostream>

#include <typeinfo>

namespace ft
{
    template<typename T>
    struct bst_node
    {
        T val;
        bst_node* parent;
        bst_node* left;
        bst_node* right;
    };
    
    template <class T, class Compare, class Alloc = std::allocator<T> >
    class bst
    {
    public:
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef bst_node<T> node;

    private:
        size_type size;
        node* root;
        Compare compare;
        typename allocator_type::template rebind<node>::other nodeAllocator;
        allocator_type allocator;
        node *end_node;

    public:

        bst() : size(0), root(NULL), compare(), allocator()
        {
            node end = {T(), NULL, NULL, NULL};

            end_node = nodeAllocator.allocate(1);
            nodeAllocator.construct(end_node, end);
        }

        node* search(T val) { return search(root, val); }

        node* insert(T val) { return insert(root, val); }

        node* erase(T val) { return erase(root, val); }

        void clear() { clear(root); }

        node* min(node* n)
        {
            node* current = n;

            while (current && current->left)
            {
                current = current->left;
            }

            return current;
        }

        void printTree()
        {
            std::cout << "printing tree\n\n";
            if (root)
            {
                printHelper(root, "", true);
            }
        }

        node *get_root()
        {
            return root; 
        }

        node *get_end_node()
        {
            return end_node;
        }

        void swap(bst& that)
        {
            node* n = this->root;
			this->root = that.root;
			that.root = n;

            int i = this->size;
            this->size = that.size;
            that.size = i;
        }

    private:
        node* create(T val, node *parent)
        {
            node n = { val, NULL, NULL, NULL };
            n.parent = parent;

            node *ret = nodeAllocator.allocate(1);
            nodeAllocator.construct(ret, n);

            if (end_node->parent == NULL || compare(end_node->parent->val.first, ret->val.first))
                end_node->parent = ret;
            size++;
            return ret;
        }
        
        node* search(node *n, T val)
        {
            if (!n) return end_node;

            if (val.first == n->val.first)
            {
                return n;
            }

            if (compare(val.first, n->val.first))
            {
                return search(n->left, val);
            }
            else
            {
                return search(n->right, val);
            }
        }

        node* insert(node*& n, T val)
        {
            if (!n)
            {
                n = create(val, NULL);
                return n;
            }

            if (n->val.first == val.first)
            {
                return n;
            }

            if (compare(val.first, n->val.first))
            {
                if (!n->left)
                {
                    n->left = create(val, n);
                    return n->left;
                }
                else
                {
                    return insert(n->left, val);
                }
            }
            else
            {
                if (!n->right)
                {
                    n->right = create(val, n);
                    return n->right;
                }
                else
                {
                    return insert(n->right, val);
                }
            }
        }

        node* erase(node* n, T val)
        {
            if (!n) return NULL;

            if (n->val.first == val.first)
            {
                if (n->left == NULL && n->right == NULL)
                {
                    nodeAllocator.destroy(n);
                    nodeAllocator.deallocate(n, 1);
                    size--;
                    return NULL;
                }
                else if (n->left == NULL)
                {
                    n->right->parent = n->parent;

                    node* ret = n->right;
                    nodeAllocator.destroy(n);
                    nodeAllocator.deallocate(n, 1);
                    size--;
                    return ret;
                }
                else if (n->right == NULL)
                {
                    n->left->parent = n->parent;

                    node* ret = n->left;
                    nodeAllocator.destroy(n);
                    nodeAllocator.deallocate(n, 1);
                    size--;
                    return ret;
                }
                else
                {
                    T temp = min(n->right)->val;
                    n->val = temp;
                    n->right = erase(n->right, temp);
                }
            }
            else if (compare(val.first, n->val.first))
            {
                n->left = erase(n->left, val);
            }
            else
            {
                n->right = erase(n->right, val);
            }

            return n;
        }

        void clear(node* n)
        {
            if (!n) return;

            clear(n->left);
            clear(n->right);

            nodeAllocator.destroy(n);
            nodeAllocator.deallocate(n, 1);
        }

        void printHelper(node *n, std::string indent, bool last)
        {
            if (n)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }

                std::cout << "(" << n->val.first << ", " << n->val.second << ")" << std::endl;
                printHelper(n->left, indent, false);
                printHelper(n->right, indent, true);
            }
        }
    };
}

#endif
