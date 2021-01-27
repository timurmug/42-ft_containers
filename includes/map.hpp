#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
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

public:
/* Constructors */
//    empty (1)
    explicit map (const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) :  _alloc(alloc), _size(0), _compare(comp) {
//        _initBeginNode();
    }
//    range (2)
    template <class InputIterator>
    map (InputIterator first, InputIterator last,
         const key_compare& comp = key_compare(),
         const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _compare(comp) {
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
//        stack<t_node> stack;
        t_node *_getMinNode(t_node *node)  {
            if (node->left == nullptr)
                return node;
            return _getMinNode(node->left);
        }

        t_node *_mapIteratorNext(t_node *node)  {
            if (node->right)
                return _getMinNode(node->right);
            if (node->parent && node->parent->left == node)
                return node->parent;
            t_node *tmp = node;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return node->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }
        t_node * _Rb_tree_increment(t_node *node)
        {
            if (node->right != 0)
            {
                node = node->right;
                while (node->right != 0)
                    node = node->left;
            }
            else
            {
                t_node* temp = node->parent;
                while (node == temp->right)
                {
                    node = temp;
                    temp = temp->parent;
                }
                if (node->right != temp)
                    node = temp;
            }
            return node;
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

        bool operator==(const iterator& rhs) const { return this->_node_ptr == rhs._node_ptr; }
        bool operator!=(const iterator& rhs) const {
//            if (!rhs._node_ptr && !this->_node_ptr)
//                return true;
            return this->_node_ptr != rhs._node_ptr;
        }

        value_type& operator*() const { return *this->_node_ptr->key_value; }
        value_type * operator->() const { return this->_node_ptr->key_value; }

        iterator& operator++() {
//            this->_node_ptr = this->_node_ptr->next;
//            stack<t_node> stack;

//            if(_node_ptr)
//            {
//                if(_node_ptr->right)
//                {
//                    stack.push(*_node_ptr->right);
//                }
//
//                if(_node_ptr->left)
//                {
//                    _node_ptr = _node_ptr->left;
//                }
//                else
//                {
//                    _node_ptr = &stack.top();
//                    stack.pop();
//                }
//            }

//            this->_node_ptr = _mapIteratorNext(this->_node_ptr);
            this->_node_ptr = _Rb_tree_increment(this->_node_ptr);
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; operator++(); return tmp; }
        iterator& operator--() { this->_node_ptr = this->_node_ptr->prev; return *this; }
        iterator operator--(int) { iterator tmp = *this; operator--(); return tmp; }

//        t_node *getNodePtr() const { return _node_ptr; }
    };

/* Iterators */
    iterator 				begin()             { return iterator(_minNode); }
//    const_iterator 		    begin()     const   { return const_iterator(_beginNode); }
    iterator				end()               { return iterator(_maxNode->right);	}
//    const_iterator			end()       const   { return const_iterator(_endNode); }

/* Capacity */
    bool        empty()     const { return (this->_size == 0); }
    size_type   size()      const { return this->_size; }
    size_type   max_size()  const { return std::numeric_limits<std::size_t>::max() / sizeof(t_node); }


/* Modifiers */
//    single element (1)
    std::pair<iterator, bool> insert (const value_type& val) {
        t_node *newNode = nullptr;

        if (!_size) {                                                           // случай 1 - вставляем в корень
            newNode = _initRoot(val);
            return std::pair<iterator, bool>(iterator(newNode), true);
        }

        t_node *parent;
        bool rightOrEqual = _searchWhereToInsert(val, &parent);
        if (rightOrEqual && parent->key_value->first == val.first)               // элемент уже есть
            return std::pair<iterator, bool>(iterator(parent), false);

        newNode = _insertAfterNode(parent, rightOrEqual, val);
        if (parent->color == BLACK) {                                            // случай 2 - предок черный
//            newNode = _insertAfterNode(parent, rightOrEqual, val);
            return std::pair<iterator, bool>(iterator(newNode), true);
        }

        // остальные случаи проваливаются сюда из-за возможной рекурсии
//        newNode = _newNode(val, parent, nullptr, nullptr);
        _changesAfterInsert_case3(newNode);
        return std::pair<iterator, bool>(iterator(newNode), true);
    }
//    with hint (2)
//    iterator insert (iterator position, const value_type& val) { (void)position; (void)val; }
//    range (3)
//    template <class InputIterator>
//    void insert (InputIterator first, InputIterator last) { (void)first; (void)last; }


/* Additional functions */
private:
    void _changesAfterInsert_case1(t_node *node)
    {
        // если корень, то цвет должен быть черным
        if (node->parent == NULL)
            node->color = BLACK;
        else
            _changesAfterInsert_case2(node);
    }

    void _changesAfterInsert_case2(t_node *node)
    {
        // если предок черный, то все норм
        if (node->parent->color == BLACK)
            return;
        else
            _changesAfterInsert_case3(node);
    }

    void _changesAfterInsert_case3(t_node *node) {
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

    void _changesAfterInsert_case4(t_node *node)
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

    void _changesAfterInsert_case5(t_node *node)
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

    t_node * _initRoot(const value_type& val) {
        _minNode = _newNode(val, nullptr, nullptr, nullptr);
        _maxNode = _minNode;
        _rootNode = _minNode;
        _minNode->color = BLACK;
        return _minNode;
    }

    t_node * _insertAfterNode(t_node *parent, bool isright, const value_type& val) {
        t_node *newNode;
        if (isright) {
            if (parent->right)
                newNode = _newNode(val, parent, parent->left, parent->right);
            else
                newNode = _newNode(val, parent, nullptr, nullptr);
        }
        else {
            if (parent->left)
                newNode = _newNode(val, parent, parent->left, parent->right);
            else
                newNode = _newNode(val, parent, nullptr, nullptr);
        }

        if (isright) {
            parent->right = newNode;
            if (parent == _maxNode)
                _maxNode = newNode;
//                _minNode = newNode;
        }
        else {
            parent->left = newNode;
            if (parent == _minNode)
                _minNode = newNode;
//                _maxNode = newNode;
        }
        return newNode;
    }

    bool _searchWhereToInsert(const value_type& val, t_node **node) {
        bool result = false;

        t_node *temp_root = _rootNode;
        t_node *temp_parent;
        value_type *temp_key_value;

        while (temp_root) {
            temp_key_value = temp_root->key_value;
//            if (val.first == temp_key_value->first) {
            if (!_compare(val.first, temp_key_value->first) && !_compare(temp_key_value->first, val.first)) {
                *node = temp_root;
                return true;
            }
//            else if (val.first < temp_key_value->first) {
            else if (_compare(val.first, temp_key_value->first)) {
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