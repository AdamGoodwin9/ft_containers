#ifndef BST_HPP
#define BST_HPP

#include <functional>
#include <iostream>

#include <typeinfo>

namespace ft
{
    template <typename T>
    struct bst_node
    {
        T val;
        bst_node *parent;
        bst_node *left;
        bst_node *right;
    };

    template <class T, class Compare, class Key, class Alloc = std::allocator<T> >
    class bst
    {
    public:
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef bst_node<T> node;

    private:
        size_type size;
        node *root;
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
            root = end_node;
            std::cout << "\n\nC\n\n";
        }

        bst &operator=(bst const &other)
        {
            clear();
            std::cout << "cleared " << size << std::endl;
            // printTree();
            other.printTree();
            std::cout << "heyyy ------( ͡° ͜ʖ ͡°)---------> " << end_node << std::endl;
            insertAllBF(other.root);
            std::cout << "later ---------------> " << end_node << std::endl;
            printTree();
            end_node->parent = max(root);
            return (*this);
        }

        node *search(const T val) const { return search(root, val); }

        node *insert(const T val) { return insert(root, val); }

        void erase(const T &val)
        {
            erase(root, val);
            end_node->parent = max(root);
        }

        void clear()
        {
            clear(root);
            root = end_node;
            end_node->parent = NULL;
            std::cout << "\n\nD\n\n";
        }

        node *max(node *n) const
        {
            node *current = n;

            while (current && current->right)
            {
                current = current->right;
            }

            return current;
        }

        node *min(node *n) const
        {
            node *current = n;

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

        void swap(bst &that)
        {
            node *n = this->root;
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

        void insertAllBF(node* other)
        {
            for (int i = 1; i <= height(other); i++)
            {
                currentLevel(other, i);
            }
        }

    private:
        int height(node *n)
        {
            if (n == NULL)
            {
                return 0;
            }
            else
            {
                int l = height(n->left);
                int r = height(n->right);
                if (l > r)
                {
                    return l + 1;
                }
                else
                {
                    return r + 1;
                }
            }
        }

        void currentLevel(node *n, int k)
        {
            if (n == NULL) return;

            if (k == 1)
            {
                std::cout << "inserting (" << n << " - ("<< n->val.first << ", " << n->val.second << "), r(" << root->val.first << ", " << root->val.second << "), e: " << end_node << std::endl;
                insert(n->val);
                printTree();
                std::cout << "root: " << root << std::endl;
            }
            else if (k > 1)
            {
                currentLevel(n->left, k - 1);
                currentLevel(n->right, k - 1);
            }
        }

        void insertAllDF(node *n)
        {
            if (n == NULL)
                return;

            insert(n->val);
            insertAll(n->left);
            insertAll(n->right);
        }

        node *create(const T val, node *parent)
        {
            node n = {val, NULL, NULL, NULL};
            n.parent = parent;

            node *ret = nodeAllocator.allocate(1);
            nodeAllocator.construct(ret, n);

            std::cout << "ret: "<< ret << std::endl;
            if (end_node->parent == NULL || compare(end_node->parent->val.first, ret->val.first))
                end_node->parent = ret;
            size++;

            return ret;
        }

        node *search(node *n, const T val) const
        {
            if (!n)
                return end_node;

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
            if (cur == end_node)
                return;

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
                {
                    std::cout << "\n\nA\n\n";
                    root = end_node;
                    end_node->parent = NULL;
                }
                size--;
                nodeAllocator.destroy(cur);
                nodeAllocator.deallocate(cur, 1);
            }
            else if (cur->left && cur->right)
            {
                node *tmp = min(cur->right);
                T tmpval = tmp->val;
                erase(root, tmp->val);

                Key *ptr = const_cast<Key *>(&(cur->val.first));
                *ptr = tmpval.first;
                cur->val.second = tmpval.second;
            }
            else
            {
                node *child = (cur->left) ? cur->left : cur->right;
                child->parent = cur->parent;
                if (cur != root)
                {
                    if (cur == cur->parent->left)
                        cur->parent->left = child;
                    else
                        cur->parent->right = child;
                }
                else
                {
                    
                    std::cout << "\n\nB\n\n";
                    root = child;
                    root->parent = NULL;
                }
                size--;
                nodeAllocator.destroy(cur);
                nodeAllocator.deallocate(cur, 1);
            }
        }

        node *insert(node *&n, T val)
        {
            if (n == end_node)
            {
                std::cout << "n: " << n << " | " << end_node << std::endl;
                    std::cout << "\n\nHIT\n\n";
                n = create(val, NULL);
                std::cout << "rooooot: " << root << std::endl;
                std::cout << "rooooot??: " << n << std::endl;
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

        // void fixRoot(node *n, node *newRoot)
        // {
        //     if (!n || !root)
        //         return;

        //     if (n->val.first == root->val.first)
        //     {

        //         root = newRoot;
        //     }
        // }

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
        //             Key* ptr = const_cast<Key*>(&(n->val.first));
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

        void clear(node *n)
        {
            if (!n)
                return;

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

                std::cout << "(" << n->val.first << ", " << n->val.second << ")\t\t";
                if (n->parent)
                    std::cout << " p: (" << n->parent->val.first << ", " << n->parent->val.second << ")";
                else
                    std::cout << " p: (null)";
                if (n->left)
                    std::cout << " l: (" << n->left->val.first << ", " << n->left->val.second << ")";
                else
                    std::cout << " l: (null)";
                if (n->right)
                    std::cout << " r: (" << n->right->val.first << ", " << n->right->val.second << ")";
                else
                    std::cout << " r: (null)";
                std::cout << std::endl;
                printHelper(n->left, indent, false);
                printHelper(n->right, indent, true);
            }
        }
    };
}

#endif
