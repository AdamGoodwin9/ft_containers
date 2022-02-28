#ifndef BST_HPP
#define BST_HPP

#include <functional>

namespace ft
{
    template <class T, class Alloc = std::allocator<T>, class Compare = std::less<T> >
    class bst
    {
    public:
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;

        struct node
        {
            T val;
            node* left;
            node* right;
        };

        typedef node *tree;

    private:
        size_type size;
        node* root;
        Compare compare;
        typename allocator_type::template rebind<node>::other nodeAllocator;
        allocator_type allocator;

    public:

        bst() : size(0), root(NULL), compare(), allocator()
        {
        }

        node* create(T val)
        {
            node n = { val, NULL, NULL };

            node *ret = nodeAllocator.allocate(1);
            nodeAllocator.construct(ret, n);

            size++;
            return ret;
        }

        node* search(T val) { return search(val, root); }

        void insert(T val) { insert(root, val); }

        node* erase(T val) { return erase(root, val); }

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
            if (root)
            {
                printHelper(root, "", true);
            }
        }

    private:
        node* search(T val, node *n)
        {
            if (!n) return u_nullptr;

            if (val == n->val)
            {
                return n;
            }

            if (compare(val, n->val))
            {
                return search(val, n->left);
            }
            else
            {
                return search(val, n->right);
            }
        }

        node* insert(node*& n, T val) //maybe want to return the inserted element. also do not allow duplicates
        {
            if (!n)
            {
                n = create(val);
                return n;
            }

            if (n->val == val)
            {
                return n;
            }

            if (compare(val, n->val))
            {
                if (!n->left)
                {
                    n->left = create(val);
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
                    n->right = create(val);
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

            if (n->val == val)
            {
                if (n->left == NULL)
                {
                    node* temp = n->right;
                    nodeAllocator.destroy(n);
                    nodeAllocator.deallocate(n, 1);
                    size--;
                    return temp;
                }
                else if (n->right == NULL)
                {
                    node* temp = n->left;
                    nodeAllocator.destroy(n);
                    nodeAllocator.deallocate(n, 1);
                    size--;
                    return temp;
                }

                node* temp = min(n->right);
                n->val = temp->val;
                n->right = erase(n->right, temp->val);
            }
            else if (compare(val, n->val))
            {
                n->left = erase(n->left, val);
            }
            else
            {
                n->right = erase(n->right, val);
            }

            return n;
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

                std::cout << n->val << std::endl;
                printHelper(n->left, indent, false);
                printHelper(n->right, indent, true);
            }
        }
    };
}

#endif