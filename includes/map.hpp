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
    #define RED     1
    #define BLACK   0

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
            clear();
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
        clear();
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
    iterator 				begin()             { return (!_size) ? iterator(_endNode) : iterator(_beginNode->parent);}
    const_iterator 		    begin()     const   { return (!_size) ? const_iterator(_endNode) : const_iterator(_beginNode->parent); }
    iterator				end()               { return iterator(_endNode); }
    const_iterator			end()       const   { return const_iterator(_endNode); }

    reverse_iterator		rbegin()            { return (!_size) ? reverse_iterator(_beginNode) : reverse_iterator(_endNode->parent); }
    const_reverse_iterator	rbegin()    const   { return (!_size) ? const_reverse_iterator(_beginNode) : const_reverse_iterator(_endNode->parent); }
    reverse_iterator		rend()              { return reverse_iterator(_beginNode); }
    const_reverse_iterator	rend()      const   { return const_reverse_iterator(_beginNode); }


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
    void erase (iterator position) {
        erase(position->first);
    }
//    (2)
    size_type erase (const key_type& k) {
        if (_size == 0 || find(k) == end())
            return 0;
        _eraseNode(_rootNode, k);
//        t_node *p = _rootNode;
//        while (!_compare(k, p->key_value->first) && !_compare(p->key_value->first, k)) {
//            if (_compare(p->key_value->first, k))
//                p = p->right;
//            else
//                p = p->left;
//        }
//        if (!p->left && !p->right) { // нет детей
//            if (p == _rootNode)
//                _rootNode = nullptr; // TODO delete нужен
//            else {
//                // TODO delete нужен
//                if (p->parent->left == p)
//                    p->parent->left = nullptr;
//                else
//                    p->parent->right = nullptr;
//            }
//            return 1;
//        }
//
//        t_node *y = nullptr;
//        t_node *q = nullptr;
//        if (!p->left || !p->right) { // один ребенок
//            // TODO delete нужен
//            if (p->parent->left == p)
//                p->parent->left = (p->left) ? p->left : p->right;
//            else
//                p->parent->right = (p->right) ? p->right : p->left;
//        }
//        else { // два ребенка
//            // TODO delete нужен
//            y = (++iterator(p).getNodePtr()); // у нее нет левого ребенка
//            if (y->right)
//                y->right->parent = y->parent;
//            if (y == _rootNode)
//                _rootNode = y->right;
//            else
//                y->parent =
//
//        }
//
//        if (y != p) {
//            p->color = y->color;
//            p->key_value->first = y->first;
//        }
//        if (y->color == BLACK)
////            fixDeleting(q)

        return 1;
    }

//    t_node *				_findMaxNode(t_node* node) {
//        if (node->right)
//            return _findMaxNode(node->right);
//        return node;
//    }



//    (3)
    void erase (iterator first, iterator last) {
        while (first != last)
            erase(first++);
    }

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

    void clear() {

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
        return end();
    }

    size_type       count (const key_type& k) const {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return 1;
        return 0;
    }

    iterator lower_bound(const key_type& k) {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return iterator(node);
        return iterator(end());
    }
    const_iterator lower_bound (const key_type& k) const {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return const_iterator(node);
        return const_iterator(end());
    }

    iterator upper_bound (const key_type& k) {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return ++iterator(node);
        return iterator(end());
    }
    const_iterator upper_bound (const key_type& k) const {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return ++const_iterator(node);
        return const_iterator(end());
    }

    std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
        t_node *node;
        bool rightOrEqual = _find_key(k, &node);
        if (rightOrEqual && node->key_value->first == k)
            return std::pair<const_iterator,const_iterator>(const_iterator(node), ++const_iterator(node));
        return std::pair<const_iterator,const_iterator>(end(), end());
    }
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

    void 		_deleteNode(t_node * node) {
        _alloc.destroy(node->key_value);
        _alloc.deallocate(node->key_value, 1);
        _alloc_rebind.deallocate(node, 1);
        --_size;
    }

    /* for erase */
    bool 					_isRedNode(t_node* node) {
        if (!node)
            return BLACK;
        return node->color == RED;
    }

    t_node *				_findMinNode(t_node* node) {
        if (node->left)
            return _findMinNode(node->left);
        return node;
    }

    void 					_linkLeft(t_node * parent, t_node * left) {
        parent->left = left;
        if (left)
            left->parent = parent;
    };

    void 					_linkRight(t_node * parent, t_node * right) {
        parent->right = right;
        if (right)
            right->parent = parent;
    };

    void        _changeColors(t_node *node) {
        if (node->left && node->left != _beginNode)
            node->left->color = !node->left->color;
        if (node->right && node->right != _endNode)
            node->right->color = !node->right->color;
        if (node && node != _rootNode)
            node->color = !node->color;
    }

    t_node *    _rotate_left_erase(t_node *node) {
        t_node* tmp = node->right;

        tmp->parent = nullptr;
        if (node->parent) {
            if (node->parent->left == node)
                _linkLeft(node->parent, tmp);
            else
                _linkRight(node->parent, tmp);
        }
        else
            tmp->parent = node->parent;

        _linkRight(node, tmp->left);
        _linkLeft(tmp, node);
        if (node == _rootNode)
            _rootNode = tmp;

        tmp->color = node->color;
        node->color = RED;
        return tmp;
    }

    t_node*     _rotate_right_erase(t_node * node) {
        t_node* tmp = node->left;

        tmp->parent = nullptr;
        if (node->parent) {
            if (node->parent->left == node)
                _linkLeft(node->parent, tmp);
            else
                _linkRight(node->parent, tmp);
        }
        else
            tmp->parent = node->parent;

        _linkLeft(node, tmp->right);
        _linkRight(tmp, node);
        if (node == _rootNode)
            _rootNode = tmp;

        tmp->color = node->color;
        node->color = RED;
        return tmp;
    }

    t_node *    _moveRedLeft(t_node * node) {
        _changeColors(node);
        if (node->right && _isRedNode(node->right->left)) {
            node->right = _rotate_right_erase(node->right);
            node = _rotate_left_erase(node);
            _changeColors(node);
        }
        return node;
    }

    t_node *	_moveRedRight(t_node * node) {
        _changeColors(node);
        if (node->left && _isRedNode(node->left->left)) {
            node = _rotate_right_erase(node);
            _changeColors(node);
        }
        return node;
    }

    t_node *    _balance(t_node * node) {
        if (_isRedNode(node->right))
            node = _rotate_left_erase(node);
        if (_isRedNode(node->left) && _isRedNode(node->left->left))
            node = _rotate_right_erase(node);
        if (_isRedNode(node->left) && _isRedNode(node->right))
            _changeColors(node);
        return node;
    }

    t_node *    _eraseNode(t_node *node, const key_type& k) {
        if (node == nullptr)
            return nullptr;
        int cmp_result = _compare(k, node->key_value->first) + _compare(node->key_value->first, k) * 2;
        if (cmp_result == 1) {  //LEFT
            if (!_isRedNode(node->left) && !_isRedNode(node->left->left))
                node = _moveRedLeft(node);
            _linkLeft(node, _eraseNode(node->left, k));
        }
        else {                  // RIGHT or EQUAL
            if (_isRedNode(node->left)) {
                node = _rotate_right_erase(node);
                _linkRight(node, _eraseNode(node->right, k));
                return _balance(node);
            }
            if (cmp_result != 2 && (node->right == _endNode || node->right == nullptr)) {
                t_node *tmp = (!node->left && node->right == _endNode) ? node->right : node->left;
                _deleteNode(node);
                return tmp;
            }
            if (!_isRedNode(node->right) && node->right && !_isRedNode(node->right->left)) {
                node = _moveRedRight(node);
            }
            if (!_compare(node->key_value->first, k)) {
                t_node *min = _findMinNode(node->right);
                if (node == _rootNode)
                    _rootNode = min;
                if (min->parent != node) {
                    _linkLeft(min->parent, min->right);
                    _linkRight(min, node->right);
                }
                if (node->left == _beginNode) {
                    node->left->parent = min;
                    min->left = node->left;
                } else
                    _linkLeft(min, node->left);
                min->parent = nullptr;
                if (node->parent) {
                    if (node->parent->left == node)
                        _linkLeft(node->parent, min);
                    else
                        _linkRight(node->parent, min);
                }
                _deleteNode(node);
                node = min;
            } else
                _linkRight(node, _eraseNode(node->right, k));
        }
        return _balance(node);
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

//    t_node      *_find_max(t_node *node) {
//        t_node* temp = node;
//        while (temp&& temp->right)
//            temp = temp->right;
//        return temp;
//    }
};

}

#endif