#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include "stack.hpp"

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
    public:
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
    t_node                  *_rootNode;

    t_node                  *_endNode;
    t_node                  *_beginNode;

    size_type				_size;
    key_compare             _compare;

public:
/* Constructors */
//    empty (1)
    explicit map (const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) :  _alloc(alloc), _size(0), _compare(comp) { }
//    range (2)
    template <class InputIterator>
    map (InputIterator first, InputIterator last,
         const key_compare& comp = key_compare(),
         const allocator_type& alloc = allocator_type(),
         typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _alloc(alloc), _size(0), _compare(comp) {
        while (first != last) {
            insert(*first);
            first++;
        }
    }
//    copy (3)
    map (const map& x)  {
        *this = x;
    }

/* Assignation operator */
    map& operator=(const map& x) {
        if (this != &x) {
            _clear();
            _alloc_rebind = x._alloc_rebind;
            _alloc = x._alloc;
            _size = 0;
            _compare = x._compare;
            const_iterator first = x.begin();
            const_iterator last = x.end();
            while (first != last) {
                insert(*first);
                first++;
            }
        }
        return *this;
    }

/* Destructor */
    ~map() {
        _clear();
    }

/* Iterators classes */
    class iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        t_node  *_node_ptr;
        void    _findNextNode() {
            if (_node_ptr->right)
            {
                _node_ptr = _node_ptr->right;
                while (_node_ptr->left)
                    _node_ptr = _node_ptr->left;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->right);
            }
        }
        void    _findPrevNode() {
            if (_node_ptr->left)
            {
                _node_ptr = _node_ptr->left;
                while (_node_ptr && _node_ptr->right)
                    _node_ptr = _node_ptr->right;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->left);
            }
        }
    public:
        iterator() : _node_ptr(NULL) {  }
        iterator(t_node* node_ptr) : _node_ptr(node_ptr) {  }
        iterator(const iterator& src) { *this = src; }
        virtual ~iterator() { }

        iterator & operator=(iterator const & rhs) {
            if (this != &rhs)
                this->_node_ptr = rhs._node_ptr;
            return *this;
        }

        bool        operator==(const iterator& rhs)     const   { return this->_node_ptr == rhs._node_ptr; }
        bool        operator!=(const iterator& rhs)     const   { return this->_node_ptr != rhs._node_ptr; }

        value_type& operator*()                         const   { return *this->_node_ptr->key_value; }
        value_type* operator->()                        const   { return this->_node_ptr->key_value; }

        iterator&   operator++()                                { _findNextNode(); return *this; }
        iterator    operator++(int)                             { iterator tmp = *this; operator++(); return tmp; }
        iterator&   operator--()                                { _findPrevNode(); return *this; }
        iterator    operator--(int)                             { iterator tmp = *this; operator--(); return tmp; }

        t_node      *getNodePtr()                       const   { return _node_ptr; }
    };

    class const_iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        t_node  *_node_ptr;
        void    _findNextNode() {
            if (_node_ptr->right)
            {
                _node_ptr = _node_ptr->right;
                while (_node_ptr->left)
                    _node_ptr = _node_ptr->left;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->right);
            }
        }
        void    _findPrevNode() {
            if (_node_ptr->left)
            {
                _node_ptr = _node_ptr->left;
                while (_node_ptr && _node_ptr->right)
                    _node_ptr = _node_ptr->right;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->left);
            }
        }
    public:
        const_iterator() : _node_ptr(NULL) {  }
        const_iterator(t_node* node_ptr) : _node_ptr(node_ptr) {  }
        const_iterator(const const_iterator& src) { *this = src; }
        const_iterator(const iterator& src) { *this = src; }
        virtual ~const_iterator() { }

        const_iterator & operator=(const_iterator const & rhs) {
            if (this != &rhs)
                this->_node_ptr = rhs._node_ptr;
            return *this;
        }
        const_iterator & operator=(iterator const & rhs) {
            this->_node_ptr = rhs.getNodePtr();
            return *this;
        }

        bool        operator==(const const_iterator& rhs)     const   { return this->_node_ptr == rhs._node_ptr; }
        bool        operator!=(const const_iterator& rhs)     const   { return this->_node_ptr != rhs._node_ptr; }

        value_type& operator*()                               const   { return *this->_node_ptr->key_value; }
        value_type* operator->()                              const   { return this->_node_ptr->key_value; }

        const_iterator&   operator++()                                { _findNextNode(); return *this; }
        const_iterator    operator++(int)                             { const_iterator tmp = *this; operator++(); return tmp; }
        const_iterator&   operator--()                                { _findPrevNode(); return *this; }
        const_iterator    operator--(int)                             { const_iterator tmp = *this; operator--(); return tmp; }

        t_node            *getNodePtr()                       const   { return _node_ptr; }
    };

    class reverse_iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        t_node  *_node_ptr;
        void    _findNextNode() {
            if (_node_ptr->right)
            {
                _node_ptr = _node_ptr->right;
                while (_node_ptr->left)
                    _node_ptr = _node_ptr->left;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->right);
            }
        }
        void    _findPrevNode() {
            if (_node_ptr->left)
            {
                _node_ptr = _node_ptr->left;
                while (_node_ptr && _node_ptr->right)
                    _node_ptr = _node_ptr->right;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->left);
            }
        }
    public:
        reverse_iterator() : _node_ptr(NULL) {  }
        reverse_iterator(t_node* node_ptr) : _node_ptr(node_ptr) {  }
        reverse_iterator(const reverse_iterator& src) { *this = src; }
        virtual ~reverse_iterator() { }

        reverse_iterator & operator=(reverse_iterator const & rhs) {
            if (this != &rhs)
                this->_node_ptr = rhs._node_ptr;
            return *this;
        }

        bool                operator==(const reverse_iterator& rhs)     const   { return this->_node_ptr == rhs._node_ptr; }
        bool                operator!=(const reverse_iterator& rhs)     const   { return this->_node_ptr != rhs._node_ptr; }

        value_type&         operator*()                                 const   { return *this->_node_ptr->key_value; }
        value_type*         operator->()                                const   { return this->_node_ptr->key_value; }

        reverse_iterator&   operator++()                                        { _findPrevNode(); return *this; }
        reverse_iterator    operator++(int)                                     { reverse_iterator tmp = *this; operator++(); return tmp; }
        reverse_iterator&   operator--()                                        { _findNextNode(); return *this; }
        reverse_iterator    operator--(int)                                     { reverse_iterator tmp = *this; operator--(); return tmp; }

        t_node              *getNodePtr()                               const   { return _node_ptr; }
    };

    class const_reverse_iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        t_node  *_node_ptr;
        void    _findNextNode() {
            if (_node_ptr->right)
            {
                _node_ptr = _node_ptr->right;
                while (_node_ptr->left)
                    _node_ptr = _node_ptr->left;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->right);
            }
        }
        void    _findPrevNode() {
            if (_node_ptr->left)
            {
                _node_ptr = _node_ptr->left;
                while (_node_ptr && _node_ptr->right)
                    _node_ptr = _node_ptr->right;
            }
            else
            {
                t_node *child;
                do
                {
                    child = _node_ptr;
                    _node_ptr = _node_ptr->parent;
                } while (_node_ptr && child == _node_ptr->left);
            }
        }
    public:
        const_reverse_iterator() : _node_ptr(NULL) {  }
        const_reverse_iterator(t_node* node_ptr) : _node_ptr(node_ptr) {  }
        const_reverse_iterator(const const_reverse_iterator& src) { *this = src; }
        const_reverse_iterator(const reverse_iterator& src) { *this = src; }
        virtual ~const_reverse_iterator() { }

        const_reverse_iterator & operator=(const_reverse_iterator const & rhs) {
            if (this != &rhs)
                this->_node_ptr = rhs._node_ptr;
            return *this;
        }
        const_reverse_iterator & operator=(reverse_iterator const & rhs) {
            this->_node_ptr = rhs.getNodePtr();
            return *this;
        }

        bool                        operator==(const const_reverse_iterator& rhs)   const   { return this->_node_ptr == rhs._node_ptr; }
        bool                        operator!=(const const_reverse_iterator& rhs)   const   { return this->_node_ptr != rhs._node_ptr; }

        value_type&                 operator*()                                     const   { return *this->_node_ptr->key_value; }
        value_type*                 operator->()                                    const   { return this->_node_ptr->key_value; }

        const_reverse_iterator&     operator++()                                            { _findPrevNode(); return *this; }
        const_reverse_iterator      operator++(int)                                         { const_reverse_iterator tmp = *this; operator++(); return tmp; }
        const_reverse_iterator&     operator--()                                            { _findNextNode(); return *this; }
        const_reverse_iterator      operator--(int)                                         { const_reverse_iterator tmp = *this; operator--(); return tmp; }

        t_node                      *getNodePtr()                                   const   { return _node_ptr; }
    };

/* Iterators */
    iterator 				begin()             { return iterator(_minNode); }
    const_iterator 		    begin()     const   { return const_iterator(_minNode); }
    iterator				end()               { if (_size) return iterator(_endNode); return begin(); }
    const_iterator			end()       const   { if (_size) return const_iterator(_endNode); return begin(); }

    reverse_iterator 		rbegin()            { return reverse_iterator(_maxNode); }
    reverse_iterator		rend()              { if (_size) return reverse_iterator(_beginNode); return rbegin(); }
    const_reverse_iterator 	rbegin()    const   { return const_reverse_iterator(_maxNode); }
    const_reverse_iterator	rend()      const   { if (_size) return const_reverse_iterator(_beginNode); return rbegin(); }


/* Capacity */
    bool                    empty()     const   { return (this->_size == 0); }
    size_type               size()      const   { return this->_size; }
    size_type               max_size()  const   { return std::numeric_limits<size_type>::max()/ sizeof(map<Key, T, Compare, Alloc>); }
/* Element access */
    mapped_type& operator[] (const key_type& k) { return (*((this->insert(std::make_pair(k,mapped_type()))).first)).second; }

/* Modifiers */
//    single element (1)
    std::pair<iterator, bool> insert (const value_type& val) {
        t_node *newNode = nullptr;

        if (!_size) {                                                           // случай 1 - вставляем в корень
            _initRoot(val);
            return std::pair<iterator, bool>(iterator(_rootNode), true);
        }

        t_node *parent;
        bool rightOrEqual = _searchWhereToInsert(val, &parent);
        if (rightOrEqual && parent->key_value->first == val.first)               // элемент уже есть
            return std::pair<iterator, bool>(iterator(parent), false);

        newNode = _insertAfterNode(parent, rightOrEqual, val);
        if (parent->color == BLACK)                                            // случай 2 - предок черный
            return std::pair<iterator, bool>(iterator(newNode), true);

        // остальные случаи проваливаются сюда из-за возможной рекурсии
        _changesAfterInsert_case3(newNode);
        return std::pair<iterator, bool>(iterator(newNode), true);
    }
//    with hint (2)
    iterator insert (iterator position, const value_type& val) {
        (void)position;
        return insert(val).first;
    }
//    range (3)
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
        for ( ; first != last; ++first)
            insert(*first);
    }

//    (1)
//    void erase (iterator position) {
//
//    }
//    (2)
//    size_type erase (const key_type& k) {
//
//    }
//    (3)
//    void erase (iterator first, iterator last);

    void swap (map& x) {
        allocator_rebind_type 	alloc_rebindTemp = _alloc_rebind;
        _alloc_rebind = x._alloc_rebind;
        x._alloc_rebind = alloc_rebindTemp;

        allocator_type          allocTemp = _alloc;
        _alloc = x._alloc;
        x._alloc = allocTemp;

        t_node                  *minNodeTemp = _minNode;
        _minNode = x._minNode;
        x._minNode = minNodeTemp;

        t_node                  *maxNodeTemp = _maxNode;
        _maxNode = x._maxNode;
        x._maxNode = maxNodeTemp;

        t_node                  *rootNodeTemp = _rootNode;
        _rootNode = x._rootNode;
        x._rootNode = rootNodeTemp;

        t_node                  *endNodeTemp = _endNode;
        _endNode = x._endNode;
        x._endNode = endNodeTemp;

        t_node                  *beginNodeTemp = _beginNode;
        _beginNode = x._beginNode;
        x._beginNode = beginNodeTemp;

        size_type				sizeTemp = _size;
        _size = x._size;
        x._size = sizeTemp;

        key_compare             compareTemp = _compare;
        _compare = x._compare;
        x._compare = compareTemp;
    }


/* Observers */
    key_compare     key_comp()      const   { return _compare; }
    value_compare   value_comp()    const   { return value_compare(_compare); };


/* Operations */
    iterator        find (const key_type& k) {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return iterator(node);
        return map::end();
    }
    const_iterator  find (const key_type& k) const {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return const_iterator(node);
        return map::end();
    }

    size_type       count (const key_type& k) const {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return 1;
        return 0;
    }

//    std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
    std::pair<iterator,iterator>             equal_range (const key_type& k) {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return std::pair<iterator,iterator>(iterator(node), ++iterator(node));
        return std::pair<iterator,iterator>(end(), end());
    }


/* Additional functions */
private:
    void        _changesAfterInsert_case1(t_node *node)
    {
        // если корень, то цвет должен быть черным
        if (node->parent == NULL)
            node->color = BLACK;
        else
            _changesAfterInsert_case2(node);
    }

    void        _changesAfterInsert_case2(t_node *node)
    {
        // если предок черный, то все норм
        if (node->parent->color == BLACK)
            return;
        else
            _changesAfterInsert_case3(node);
    }

    void        _changesAfterInsert_case3(t_node *node) {
        t_node *uncleNode = _getUncle(node);
        t_node *grandparent;

        // если родитель и дядя красные
        if (uncleNode && uncleNode->color == RED) {
            node->parent->color = BLACK;
            uncleNode->color = BLACK;
            grandparent = _getGrandparent(node);
            grandparent->color = RED;
            _changesAfterInsert_case1(grandparent);
        }
        else
            _changesAfterInsert_case4(node);
    }

    void        _changesAfterInsert_case4(t_node *node)
    {
        //сюда программа проваливается, если родитель красный, а дядя черный
        t_node *grandparent = _getGrandparent(node);

        // если нода справа от родителя и родитель слева от дедушки
        if ((node == node->parent->right) && (node->parent == grandparent->left)) {
            _rotate_left(node->parent);
            node = node->left;
        }
        // если нода слева от родителя и родитель справа от дедушки
        else if ((node == node->parent->left) && (node->parent == grandparent->right)) {
            _rotate_right(node->parent);
            node = node->right;
        }
        _changesAfterInsert_case5(node);
    }

    void        _changesAfterInsert_case5(t_node *node)
    {
        /* Родитель P является красным, но дядя U — чёрный, текущий узел N — левый потомок P и P — левый потомок G.
        В этом случае выполняется поворот дерева на G. В результате получается дерево, в котором бывший родитель P
        теперь является родителем и текущего узла N и бывшего дедушки G. Известно, что G — чёрный, так как его бывший
        потомок P не мог бы в противном случае быть красным (без нарушения Свойства 4). Тогда цвета P и G меняются и
        в результате дерево удовлетворяет Свойству 4 (Оба потомка любого красного узла — чёрные). */
        t_node *grandparent = _getGrandparent(node);

        node->parent->color = BLACK;
        grandparent->color = RED;
        if ((node == node->parent->left) && (node->parent == grandparent->left))
            _rotate_right(grandparent);
        else
            _rotate_left(grandparent);
    }

    bool        _searchWhereToInsert(const value_type& val, t_node **node) {
        bool        rightOrEqual;
        t_node      *temp_root = _rootNode;
        t_node      *temp_parent;
        value_type  *temp_key_value;

        while (temp_root && temp_root->key_value) {
            temp_key_value = temp_root->key_value;
            if (!_compare(val.first, temp_key_value->first) && !_compare(temp_key_value->first, val.first)) {
                *node = temp_root;
                return true;
            }
            else if (_compare(val.first, temp_key_value->first)) {
                temp_parent = temp_root;
                rightOrEqual = false;
                temp_root = temp_root->left;
            }
            else {
                temp_parent = temp_root;
                rightOrEqual = true;
                temp_root = temp_root->right;
            }
        }

        *node = temp_parent;
        return rightOrEqual;
    }

    t_node      *_getGrandparent(t_node *node) {
        if (node && node->parent)
            return node->parent->parent;
        else
            return nullptr;
    }

    t_node      *_getUncle(t_node *node) {
        t_node *grandparent = _getGrandparent(node);
        if (!grandparent)
            return nullptr;
        else if (node->parent == grandparent->left)
            return grandparent->right;
        else
            return grandparent->left;
    }

    void        _rotate_left(t_node *node) {
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

    void        _rotate_right(t_node *node) {
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

    t_node *    _insertAfterNode(t_node *parent, bool isright, const value_type& val) {
        t_node *newNode;
        if (isright) {
            if (parent->right && parent->right == _endNode)     // если справа _endNode
                newNode = _initNewNode(val, parent, nullptr, _endNode);
            else if (parent->right)                             // если справа есть какая то нода
                newNode = _initNewNode(val, parent, parent->left, parent->right);
            else                                                // справа нет ноды, поэтому у новой ноды нет потомков
                newNode = _initNewNode(val, parent, nullptr, nullptr);
        }
        else {
            if (parent->left && parent->left == _beginNode)     // если слева _endNode
                newNode = _initNewNode(val, parent, _beginNode, nullptr);
            else if (parent->left)                              // если слева есть какая то нода
                newNode = _initNewNode(val, parent, parent->left, parent->right);
            else                                                // слева нет ноды, поэтому у новой ноды нет потомков
                newNode = _initNewNode(val, parent, nullptr, nullptr);
        }

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

    void        _initRoot(const value_type& val) {
        /* init root */
         _rootNode = _maxNode = _minNode = _initNewNode(val, nullptr, nullptr, nullptr);
         _rootNode->color = BLACK;

        /* init _endNode */
         _endNode = _alloc_rebind.allocate(1);
         _endNode->parent = _maxNode;
         _endNode->left = nullptr;
         _endNode->right = nullptr;

         _endNode->key_value = nullptr;
         _endNode->color = BLACK;
         _maxNode->right = _endNode;

        /* init _beginNode */
        _beginNode = _alloc_rebind.allocate(1);
        _beginNode->parent = _minNode;
        _beginNode->left = nullptr;
        _beginNode->right = nullptr;

        _beginNode->key_value = nullptr;
        _beginNode->color = BLACK;
        _minNode->left = _beginNode;
    }

    t_node *    _initNewNode(const value_type& val, t_node *parentNode, t_node *leftNode, t_node *rightNode) {
        t_node *newNode = _alloc_rebind.allocate(1);
        newNode->parent = parentNode;
        newNode->left = leftNode;
        newNode->right = rightNode;

        newNode->key_value = _alloc.allocate(1);
        _alloc.construct(newNode->key_value, val);

        newNode->color = RED;

        if (leftNode)
            leftNode->parent = newNode;
        if (rightNode)
            rightNode->parent = newNode;

        _size++;
        return newNode;
    }

    void        _deleteNode(t_node *node) {
//        _alloc.destroy(node->color);
//        _alloc.deallocate(node->color, 1);
//        delete node->color;
        _alloc.destroy(node->key_value);
        _alloc.deallocate(node->key_value, 1);
        _alloc_rebind.destroy(node);
        node = nullptr;

//        _alloc_rebind.deallocate(node, 1);
//        _alloc.deallocate(node->color, 1);
    }

    void        _clear() {

    }

    bool        _find_key(const key_type& k, t_node **node) const {
        bool        rightOrEqual;
        t_node      *temp_root = _rootNode;
        t_node      *temp_parent;
        value_type  *temp_key_value;

        while (temp_root && temp_root->key_value) {
            temp_key_value = temp_root->key_value;
            if (!_compare(k, temp_key_value->first) && !_compare(temp_key_value->first, k)) {
                *node = temp_root;
                return true;
            }
            else if (_compare(k, temp_key_value->first)) {
                temp_parent = temp_root;
                rightOrEqual = false;
                temp_root = temp_root->left;
            }
            else {
                temp_parent = temp_root;
                rightOrEqual = true;
                temp_root = temp_root->right;
            }
        }

        *node = temp_parent;
        return rightOrEqual;
    }
};

}

#endif