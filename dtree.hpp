#ifndef MAP_BINARY_TREE
# define MAP_BINARY_TREE

# include "utils.hpp"
# include "map_bidirectional_iterator.hpp"
# include "map_bidirectional_const_iterator.hpp"

namespace rb
{
	enum Color
	{
		black = 0,
		red
	};

	template <class T, class Alloc, class Compare = std::less<T> >
	class Tree
	{
	public:
		typedef T value_type;
		typedef Compare compare;
		typedef Alloc				allocator_type;
		class node_type;
		typedef std::size_t size_type;

	protected:
		compare comp;
		node_type *root;
		typename allocator_type::template rebind<node_type>::other			node_alloc;
		allocator_type alloc;

	private:
		void rotate(node_type *p, bool right)
		{
			if (!p->getParent())
				root = right ? p->getLeft() : p->getRight();
			p->rotate(right);
		}

		void fixViolation(const node_type *n)
		{
			node_type *p = n->parent;
			if (!p || p->color == black)
				return;
			node_type *g = p->parent;
			if (g == NULL)
			{
				p->color = black;
				return;
			}
			int dir = p->isRight();
			node_type *u = g->child[1 - dir];
			if (u == NULL || u->color == black)
			{
				if (n == p->child[1 - dir])
				{
					rotate(p, dir);
					n = p;
					p = g->child[dir];
				}
				rotate(g, 1 - dir);
				p->color = black;
				g->color = red;
				return;
			}
			p->color = black;
			u->color = black;
			g->color = red;
			n = g;
			fixViolation(n);
		}

		node_type *insert(value_type val, node_type *p)
		{
			node_type tmp = node_type(val, p);
			tmp.setColor(red);
			tmp.setLeft(NULL);
			tmp.setRight(NULL);
			node_type *n = node_alloc.allocate(1);
			node_alloc.construct(n, tmp);

			if (p == NULL)
				root = n;
			else
			{
				p->child[!comp(n->value, p->value)] = n;
				fixViolation(n);
			}
			return n;
		}

		void subtree_shift(node_type *from, node_type *to)
		{
			if (!from->getParent())
				root = to;
			else if (from == from->getParent()->getLeft())
				from->getParent()->setLeft(to);
			else
				from->getParent()->setRight(to);
			if (to)
				to->setParent(from->getParent());
		}

		void shift(node_type *n)
		{
			if (!n->getLeft())
				subtree_shift(n, n->getRight());
			else if (!n->getRight())
				subtree_shift(n, n->getLeft());
			else
			{
				node_type *s = n->getSuccessor();
				if (s->getParent() != n)
				{
					subtree_shift(s, s->getRight());
					s->setRight(n->getRight());
					s->getRight()->setParent(s);
				}
				subtree_shift(n, s);
				s->setLeft(n->getLeft());
				s->getLeft()->setParent(s);
			}
		}

	public:
		Tree(const compare &comp = compare(), const allocator_type &alloc = allocator_type()) : comp(comp), alloc(alloc)
		{root = NULL;}

		Tree(const node_type &n, const compare &comp = compare(), const allocator_type &alloc = allocator_type()) : comp(comp), alloc(alloc), root(n)
		{}

		Tree(const Tree &x) : comp(x.comp), alloc(x.alloc)
		{root = NULL;insert(x.root);}

		~Tree()
		{clear();}

		Tree &operator=(const Tree &x)
		{
			if (this != &x)
				assign(x.root);
			return *this;
		}

		void assign(const node_type *n)
		{
			clear();
			insert(n);
		}

		void assign(const Tree &x)
		{
			clear();
			insert(x.root);
		}

		node_type *insert(value_type val)
		{
			node_type *p = NULL;
			node_type *tmp = root;
			while (tmp != NULL)
			{
				p = tmp;
				tmp = tmp->child[!comp(val, tmp->value)];
			}
			return insert(val, p);
		}

		void insert(const node_type *n)
		{
			if (!n)
				return;
			insert(n->value);
			insert(n->getLeft());
			insert(n->getRight());
		}

		void swap(Tree &x)
		{
			node_type *tmp = root;
			root = x.root;
			x.root = tmp;
		}

		void clear()
		{clear(root);}

		void clear(node_type *n)
		{
			if (!n)
				return;
			if (n == root)
				root = NULL;
			clear(n->getLeft());
			clear(n->getRight());
			node_alloc.destroy(n);
			node_alloc.deallocate(n, 1);
		}

		void remove(node_type *n)
		{
			shift(n);
			node_alloc.destroy(n);
			node_alloc.deallocate(n, 1);
			assign(Tree(*this));
		}

		node_type *get_root() {return root;}

		node_type *search(const value_type &val)
		{
			node_type *n = root;
			while (n)
				if (comp(val, n->value))
					n = n->getLeft();
				else if (comp(n->value, val))
					n = n->getRight();
				else
					break;
			return n;
		}

		node_type *min() const
		{
			if (!root)
				return NULL;
			return root->getMin();
		}

		node_type *max() const
		{
			if (!root)
				return NULL;
			return root->getMax();
		}

		size_type size() const
		{
			if (!root)
				return 0;
			size_type len = 1;
			node_type *first = min();
			node_type *last = max();
			while (first != last)
			{
				len++;
				first = first->getNext();
			}
			return len;
		}

		size_type max_size() const
		{return node_alloc.max_size();}

		bool empty() const
		{return !!root;}

		allocator_type get_allocator() const
		{return alloc;}
	};

	template <class T, class Alloc, class Compare>
	class Tree<T, Alloc, Compare>::node_type
	{
		friend class Tree<T, Alloc, Compare>;

	public:
		typedef T value_type;
		typedef value_type &reference;
		typedef value_type *pointer;

	protected:
		node_type *parent;
		node_type *child[2];
		Color color;
		bool linux;

	public:
		value_type value;

	private:
		void rotate(bool right)
		{
			node_type *gp = parent;
			node_type *s = child[!right];
			if (!s)
				return;
			node_type *cn = s->child[!!right];
			child[!right] = cn;
			if (cn)
				cn->parent = this;
			s->child[!!right] = this;
			parent = s;
			s->parent = gp;
			if (gp)
				gp->child[this == gp->getRight()] = s;
		}

		void setParent(node_type *p)
		{parent = p;}

		void setLeft(node_type *n)
		{child[false] = n;}

		void setRight(node_type *n)
		{child[true] = n;}

		void setColor(Color c)
		{color = c;}

	public:
		node_type(const value_type &val = value_type(), node_type *parent = NULL) : parent(parent), color(red), value(val)
		{
			child[0] = NULL;
			child[1] = NULL;
		}

		node_type(const node_type &x) : parent(x.parent), color(x.color), value(x.value)
		{
			child[0] = x.child[0];
			child[1] = x.child[1];
		}

		~node_type()
		{}

		node_type &operator=(const node_type &x)
		{
			if (this != &x)
			{
				parent = x.parent;
				child[0] = x.child[0];
				child[1] = x.child[1];
				color = x.color;
				value = x.value;
			}
			return *this;
		}
		
		node_type *getParent() const
		{return parent;};

		node_type *getLeft() const
		{return child[false];}

		node_type *getRight() const
		{return child[true];}

		Color getColor() const
		{return color;}

		int isRight()
		{
			if (!parent)
				return -1;
			return this == parent->getRight();
		}

		node_type *getGrandParent()
		{return parent && parent->parent;}

		node_type *getSibling()
		{return parent && parent->child[!isRight()];}

		node_type *getUncle()
		{return parent && parent->getSibling();}

		node_type *GetCloseNephew()
		{return getSibling() && getSibling()->child[getRight()];}

		node_type *GetDistantNephew()
		{return getSibling() && getSibling()->child[!getRight()];}

		node_type *getPrev()
		{
			if (getLeft())
			{
				node_type *n = getLeft();
				while (n->getRight())
					n = n->getRight();
				return n;
			}
			node_type *n = getParent();
			if (n && !isRight())
			{
				while (n->getParent() && !n->isRight())
					n = n->getParent();
				n = n->getParent();
			}
			return n;
		};

		node_type *getNext()
		{
			if (getRight())
			{
				node_type *n = getRight();
				while (n->getLeft())
					n = n->getLeft();
				return n;
			}
			node_type *n = getParent();
			if (n && isRight())
			{
				while (n->getParent() && n->isRight())
					n = n->getParent();
				n = n->getParent();
			}
			return n;
		};

		node_type *getMin()
		{
			if (getLeft())
				return getLeft()->getMin();
			return this;
		}

		node_type *getMax()
		{
			if (getRight())
				return getRight()->getMax();
			return this;
		}

		node_type *getSuccessor()
		{
			if (getRight())
				return getRight()->getMin();
			node_type *n = this;
			node_type *p = getParent();
			while (p && n == p->getRight())
			{
				n = p;
				p = p->getParent();
			}
			return p;
		}

		node_type *getPredecessor()
		{
			if (getLeft())
				return getLeft()->getMax();
			node_type *n = this;
			node_type *p = getParent();
			while (p && n == p->getLeft())
			{
				n = p;
				p = p->getParent();
			}
			return p;
		}
	};
}

#endif