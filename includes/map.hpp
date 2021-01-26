#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

template<bool Cond, class T = void>
struct enable_if {};
template<class T>
struct enable_if<true, T> { typedef T type; };

namespace ft {



template < class Key,                                               // map::key_type
        class T,                                                    // map::mapped_type
        class Compare = std::less<Key>,                             // map::key_compare
        class Alloc = std::allocator<std::pair<const Key,T> > >     // map::allocator_type
class map {

public:
/* Member types */
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef std::pair<const key_type, mapped_type>      value_type;
    typedef Compare                                     key_compare;
    class   value_compare : public std::binary_function<value_type, value_type, bool>
    {
    protected:
        Compare comp;
        value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        bool operator() (const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }
    };
    typedef Alloc                                       allocator_type;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer			pointer;
    typedef typename allocator_type::const_pointer		const_pointer;
    class												iterator;
    class												const_iterator;
    class												reverse_iterator;
    class												const_reverse_iterator;
    typedef ptrdiff_t									difference_type;
    typedef size_t										size_type;

private:

    typedef struct			s_node {
        pointer             key_value;
        s_node				*parent;
        s_node				*right;
        s_node				*left;
        bool                color;
    }						t_node;

/* Local variables */
    #define RED     0
    #define BLACK   1

    typedef typename allocator_type::template rebind<t_node>::other allocator_rebind_type;
    allocator_rebind_type 	_alloc_rebind;
    allocator_type          _alloc;
    t_node                  *_minNode;
    t_node                  *_maxNode;
//    t_node                  *_endNode;
    t_node                  *_rootNode;
    size_type				_size;
    key_compare             _compare;
    size_type				_blacksHeight;

public:
/* Constructors */
//    empty (1)
    explicit map (const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) :  _alloc(alloc), _size(0), _compare(comp), _blacksHeight(0)  {
//        _initBeginNode();
    }
//    range (2)
    template <class InputIterator>
    map (InputIterator first, InputIterator last,
         const key_compare& comp = key_compare(),
         const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _compare(comp), _blacksHeight(0) {
        (void)first;
        (void)last;
    }
//    copy (3)
    map (const map& x)  {
        (void)x;
    }


/* Iterators classes */
    class iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        t_node   *_node_ptr;
    public:
        iterator() : _node_ptr(NULL) { }
        iterator(t_node* node_ptr) : _node_ptr(node_ptr) { }
        iterator(const iterator& src) { *this = src; }
        virtual ~iterator() { }

        iterator & operator=(iterator const & rhs) {
            if (this != &rhs)
                this->_node_ptr = rhs._node_ptr;
            return *this;
        }

        bool operator==(const iterator& rhs) const { return this->_node_ptr == rhs._node_ptr; }
        bool operator!=(const iterator& rhs) const { return this->_node_ptr != rhs._node_ptr; }

        value_type& operator*() const { return *this->_node_ptr->key_value; }
        value_type * operator->() const { return this->_node_ptr->key_value; }

        iterator& operator++() { this->_node_ptr = this->_node_ptr->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; operator++(); return tmp; }
        iterator& operator--() { this->_node_ptr = this->_node_ptr->prev; return *this; }
        iterator operator--(int) { iterator tmp = *this; operator--(); return tmp; }

//        t_node *getNodePtr() const { return _node_ptr; }
    };


/* Capacity */
    bool        empty()     const { return (this->_size == 0); }
    size_type   size()      const { return this->_size; }
    size_type   max_size()  const { return std::numeric_limits<std::size_t>::max() / sizeof(t_node); }


/* Modifiers */
//    single element (1)
    std::pair<iterator, bool> insert (const value_type& val) {
        t_node *newNode = nullptr;

        if (!_size) {                                                       // случай 1 - вставляем в корень
            newNode = _initRoot(val);
            return std::pair<iterator, bool>(iterator(newNode), true);
        }

        t_node *p;
        bool rightOrEqual = _find(val, &p);
        if (rightOrEqual && p->key_value->first == val.first)               // элемент уже есть
            return std::pair<iterator, bool>(iterator(p), false);

        if (p->color == BLACK) {                                            // случай 2 - предок черный
            newNode = _insertAfterNode(p, rightOrEqual, val);
            return std::pair<iterator, bool>(iterator(newNode), true);
        }

        // остальные случаи проваливаются сюда из-за возможной рекурсии
//        newNode = _newNode(val, nullptr, nullptr, nullptr);
//        insert_case3(newNode);
        return std::pair<iterator, bool>(iterator(newNode), true);
    }
//    with hint (2)
//    iterator insert (iterator position, const value_type& val) { (void)position; (void)val; }
//    range (3)
//    template <class InputIterator>
//    void insert (InputIterator first, InputIterator last) { (void)first; (void)last; }


/* Additional functions */
private:
    void insert_case1(t_node *node)
    {
        if (node->parent == NULL)
            node->color = BLACK;
        else
            insert_case2(node);
    }

//    void insert_case2(t_node *node)
//    {
//        if (node->parent->color == BLACK)
//            return;
//        else
//            insert_case3(node);
//    }

    void insert_case3(t_node *node) {
        t_node *uncleNode = _getUncle(node);
        t_node *grandparent;

        // если дядя тоже красный (родитель уже красный)
        if (uncleNode && uncleNode->color == RED) {
            node->parent->color = BLACK;
            uncleNode->color = BLACK;
            grandparent = _getGrandparent(node);
            grandparent->color = RED;
            insert_case1(node);
        }
        else
            insert_case4(node);
    }

    t_node * _initRoot(const value_type& val) {
        _minNode = _newNode(val, nullptr, nullptr, nullptr);
        _maxNode = _minNode;
        _rootNode = _minNode;
        _minNode->color = BLACK;
        _blacksHeight = 2;
        return _minNode;
    }

    t_node * _insertAfterNode(t_node *parent, bool isright, const value_type& val) {
        t_node *newNode = _newNode(val, parent, parent->left, parent->right);
        if (isright) {
            parent->right = newNode;
            if (parent == _maxNode)
                _maxNode = newNode;
        }
        else {
            parent->left = newNode;
            if (parent == _minNode)
                _minNode = newNode;
        }
        return newNode;
    }

    bool _find(const value_type& val, t_node **node) {
        bool result = false;

        t_node *temp_root = _rootNode;
        t_node *temp_parent;
        value_type *temp_key_value;

        while (temp_root) {
            temp_key_value = temp_root->key_value;
            if (val.first == temp_key_value->first) {
                *node = temp_root;
                return true;
            }
            else if (val.first < temp_key_value->first) {
                temp_parent = temp_root;
                result = false;
                temp_root = temp_root->left;
            }
            else {
                temp_parent = temp_root;
                result = true;
                temp_root = temp_root->right;
            }
        }

        *node = temp_parent;
        return result;
    }

    t_node * _getGrandparent(t_node *node) {
        if (node && node->parent)
            return node->parent->parent;
        else
            return nullptr;
    }

    t_node * _getUncle(t_node *node) {
        t_node *grandparent = _getGrandparent(node);
        if (!grandparent)
            return nullptr;
        else if (node->parent == grandparent->left)
            return grandparent->right;
        else
            return grandparent->left;
    }

    void _rotate_left(t_node *node) {
        t_node *pivot = node->right;

        pivot->parent = node->parent; // тут возможно, что pivot становится корнем дерева
        if (node->parent) { // если pivot - не корень
            if (node->parent->left == node) // если для предка node была левой нодой, то
                node->parent->left = pivot; // теперь у предка левая нода - pivot
            else
                node->parent->right = pivot; // иначе у предка правая нода - pivot
        }
        else
            _rootNode = pivot;

        node->right = pivot->left; // левая нода для pivot теперь правая нода для node
        if (pivot->left)
            pivot->left->parent = node;

        node->parent = pivot; // pivot - предок для node
        pivot->left = node;
    }

    void _rotate_right(t_node *node) {
        t_node *pivot = node->left;

        pivot->parent = node->parent; // тут возможно, что pivot становится корнем дерева
        if (node->parent) { // если pivot - не корень
            if (node->parent->left == node) // если для предка node была левой нодой, то
                node->parent->left = pivot; // теперь у предка левая нода - pivot
            else
                node->parent->right = pivot; // иначе у предка правая нода - pivot
        }
        else
            _rootNode = pivot;

        node->left = pivot->right; // правая нода для pivot теперь левая нода для node
        if (pivot->right)
            pivot->right->parent = node;

        node->parent = pivot; // pivot - предок для node
        pivot->right = node;
    }

    t_node * _newNode(const value_type& val, t_node *parentNode, t_node *leftNode, t_node *rightNode) {
        t_node *newNode = _alloc_rebind.allocate(1);
        newNode->parent = parentNode;
        newNode->left = leftNode;
        newNode->right = rightNode;

        newNode->key_value = _alloc.allocate(1);
        _alloc.construct(newNode->key_value, val);

        newNode->color = _alloc.allocate(1);
        newNode->color = RED;

        if (leftNode)
            leftNode->parent = newNode;
        if (rightNode)
            rightNode->parent = newNode;

        _size++;
        return newNode;
    }

    void _changeNodeColor(t_node *node) {
        node->color = !node->color;
    }

    void _deleteNode(t_node *node) {
        _alloc.destroy(node->key_value);
        _alloc.deallocate(node->key_value, 1);

        _alloc.destroy(node->color);
        _alloc.deallocate(node->color, 1);
    }

    void _clear() {
//        iterator it = begin();
//        iterator ite = end();
//        while (it != ite) {
//            _deleteNode(*it);
//            it++;
//        }
//        _alloc_rebind.deallocate(_beginNode, 1);
    }

};

}

#endif