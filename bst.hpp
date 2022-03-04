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
    
    template <class T, class Compare, class lol, class Alloc = std::allocator<T> >
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

        node* search(const T val) const { return search(root, val); }

        node* insert(const T val) { return insert(root, val); }

        void erase(const T &val) { return erase(root, val); }

        

        void clear() { clear(root); }

        node* min(node* n) const
        {
            node* current = n;

            while (current && current->left)
            {
                current = current->left;
            }

            return current;
        }

        void printTree() const
        {
            std::cout << "printing tree\n\n";
            if (root)
            {
                printHelper(root, "", true);
            }
        }

        node *get_root() const
        {
            return root; 
        }

        node *get_end_node() const
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

        size_type getSize() const
        {
            return size;
        }
    private:
        node* create(const T val, node *parent)
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
        
        node* search(node *n, const T val) const
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

        void erase(node *&root, const T &val)
        {
            node *cur = search(val);
            if (cur == NULL)
                return ;

            if (cur->left == NULL && cur->right == NULL)
            {
                if (cur != root)
                {
                    if (cur->parent->left == cur)
                        cur->parent->left = NULL;
                    else
                        cur->parent->right = NULL;
                }
                else
                    root = NULL;
                size--;
                nodeAllocator.destroy(cur);
                nodeAllocator.deallocate(cur, 1);
            }
            else if (cur->left && cur->right)
            {
                node *tmp = min(cur->right);
                T tmpval = tmp->val;
                erase(root, tmp->val);

                lol* ptr = const_cast<lol*>(&(cur->val.first));
                *ptr = tmpval.first;
                cur->val.second = tmpval.second;
            }
            else
            {
                node *child = (cur->left) ? cur->left : cur->right;
                if (cur != root)
                {
                    if (cur == cur->parent->left)
                        cur->parent->left = child;
                    else
                        cur->parent->right = child;
                }
                else
                    root = child;
                size--;
                nodeAllocator.destroy(cur);
                nodeAllocator.deallocate(cur, 1);
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

        void fixRoot(node* n, node* newRoot)
        {
            if (!n || !root) return;
            
            if (n->val.first == root->val.first)
            {
                
                root = newRoot;
            }
        }

        // node* erase(node* n, T val)
        // {
        //     if (!n) return NULL;

        //     if (n->val.first == val.first)
        //     {
        //         if (n->left == NULL && n->right == NULL)
        //         {
        //             nodeAllocator.destroy(n);
        //             nodeAllocator.deallocate(n, 1);
        //             size--;
        //             fixRoot(n, NULL);
        //             return NULL;
        //         }
        //         else if (n->left == NULL)
        //         {
        //             n->right->parent = n->parent;

        //             node* ret = n->right;
        //             nodeAllocator.destroy(n);
        //             nodeAllocator.deallocate(n, 1);
        //             size--;
        //             fixRoot(n, ret);
        //             return ret;
        //         }
        //         else if (n->right == NULL)
        //         {
        //             n->left->parent = n->parent;

        //             node* ret = n->left;
        //             nodeAllocator.destroy(n);
        //             nodeAllocator.deallocate(n, 1);
        //             size--;
        //             fixRoot(n, ret);
        //             return ret;
        //         }
        //         else
        //         {
        //             T temp = min(n->right)->val;
                    
        //             // node* replacement = create(temp, n->parent);
        //             // replacement->left = n->left;
        //             // replacement->right = n->right;
        //             // *n = *replacement; //LEAKY LEAKY BROKEN
                    
        //             // n->val = make_pair(temp.first, temp.second);
        //             // n->val = temp;
        //             lol* ptr = const_cast<lol*>(&(n->val.first));
        //             *ptr = temp.first;

        //             // n->val.first = temp.first;
        //             n->val.second = temp.second;
        //             fixRoot(n, min(n->right));
        //             n->right = erase(n->right, temp);
        //         }
        //     }
        //     else if (compare(val.first, n->val.first))
        //     {
        //         n->left = erase(n->left, val);
        //     }
        //     else
        //     {
        //         n->right = erase(n->right, val);
        //     }

        //     return n;
        // }

        void clear(node* n)
        {
            if (!n) return;

            clear(n->left);
            clear(n->right);

            nodeAllocator.destroy(n);
            nodeAllocator.deallocate(n, 1);
        }

        void printHelper(const node *n, std::string indent, bool last) const
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
