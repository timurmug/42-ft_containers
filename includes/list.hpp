#ifndef LIST_HPP
# define LIST_HPP

#include <memory>
#include <iostream>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class list {

public:
/* Types */
	typedef T 											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference 			reference;
	typedef typename allocator_type::const_reference	const_reference;
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
		s_node				*next;
		s_node				*prev;
		value_type			*data;
	}						t_node;

/* Local variables */
	allocator_type			_alloc;
	size_type				_size;
	t_node					*_beginNode;
	t_node					*_endNode;

	typedef typename allocator_type::template rebind<t_node>::other allocator_rebind_type;
	allocator_rebind_type 	_alloc_rebind;


public:
/* Constructors */
	// (1) empty container constructor (default constructor)
	explicit list (const allocator_type& alloc = allocator_type()) 	: _alloc(alloc), _size(0) { _initStartNodes(); }
	// (2) fill constructor
	explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
																	: _alloc(alloc), _size(0) {
		_initStartNodes();
		while (n--)
			this->push_back(val);
	}
	// (3) range constructor
	template <class InputIterator>
  	list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
																	: _alloc(alloc), _size(0) {
        _initStartNodes();
		while (first != last){
			this->push_back(*first);
			first++;
		}
	}
	// (4) copy constructor
    list (const list& x) : _alloc(x._alloc), _size(0) { _initStartNodes(); *this = x; }

/* Assignation operator */

list& operator=(const list& x) {
	if (this != &x) {
        clear();
	    _alloc = x._alloc;
	    const_iterator first = x.begin();
	    const_iterator last = x.end();
	    while (first != last){
	        this->push_back(*first);
	        first++;
	    }
	}
	return *this;
}

/* Destructor */
	~list() {
		// std::cout << "delete" << std::endl;
		_deleteAllNotes();
	}
/* Iterators classes */
    class iterator {
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

        value_type& operator*() const { return *this->_node_ptr->data; }
        value_type * operator->() const { return this->_node_ptr->data; }

        iterator& operator++() { this->_node_ptr = this->_node_ptr->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; operator++(); return tmp; }
        iterator& operator--() { this->_node_ptr = this->_node_ptr->prev; return *this; }
        iterator operator--(int) { iterator tmp = *this; operator--(); return tmp; }

        t_node *getNodePtr() const { return _node_ptr; }
    };

    class const_iterator {
    private:
        t_node   *_node_ptr;
    public:
        const_iterator() : _node_ptr(NULL) {}
        const_iterator(t_node* node_ptr) : _node_ptr(node_ptr) { }
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

        bool operator==(const const_iterator& rhs) const { return this->_node_ptr == rhs._node_ptr; }
        bool operator!=(const const_iterator& rhs) const { return this->_node_ptr != rhs._node_ptr; }

        value_type& operator*() const { return *this->_node_ptr->data; }
        value_type * operator->() const { return this->_node_ptr->data; }

        const_iterator& operator++() { this->_node_ptr = this->_node_ptr->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; operator++(); return tmp; }
        const_iterator& operator--() { this->_node_ptr = this->_node_ptr->prev; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; operator--(); return tmp; }
    };

    class reverse_iterator {
    private:
        t_node   *_node_ptr;
    public:
        reverse_iterator() : _node_ptr(NULL) { }
        reverse_iterator(t_node* node_ptr) : _node_ptr(node_ptr) { }
        reverse_iterator(const reverse_iterator& src) { *this = src; }
        virtual ~reverse_iterator() { }

        reverse_iterator & operator=(reverse_iterator const & rhs) {
            if (this != &rhs)
                this->_node_ptr = rhs._node_ptr;
            return *this;
        }

        bool operator==(const reverse_iterator& rhs) const { return this->_node_ptr == rhs._node_ptr; }
        bool operator!=(const reverse_iterator& rhs) const { return this->_node_ptr != rhs._node_ptr; }

        value_type& operator*() const { return *this->_node_ptr->data; }
        value_type * operator->() const { return this->_node_ptr->data; }

        reverse_iterator& operator++() { this->_node_ptr = this->_node_ptr->prev; return *this; }
        reverse_iterator operator++(int) { reverse_iterator tmp = *this; operator++(); return tmp; }
        reverse_iterator& operator--() { this->_node_ptr = this->_node_ptr->next; return *this; }
        reverse_iterator operator--(int) { reverse_iterator tmp = *this; operator--(); return tmp; }

        t_node *getNodePtr() const { return _node_ptr; }
    };

    class const_reverse_iterator {
    private:
        t_node   *_node_ptr;
    public:
        const_reverse_iterator() : _node_ptr(NULL) { }
        const_reverse_iterator(t_node* node_ptr) : _node_ptr(node_ptr) { }
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

        bool operator==(const const_reverse_iterator& rhs) const { return this->_node_ptr == rhs._node_ptr; }
        bool operator!=(const const_reverse_iterator& rhs) const { return this->_node_ptr != rhs._node_ptr; }

        value_type& operator*() const { return *this->_node_ptr->data; }
        value_type * operator->() const { return this->_node_ptr->data; }

        const_reverse_iterator& operator++() { this->_node_ptr = this->_node_ptr->prev; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; operator++(); return tmp; }
        const_reverse_iterator& operator--() { this->_node_ptr = this->_node_ptr->next; return *this; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; operator--(); return tmp; }
    };

/* Iterators */
    iterator 				begin()             { return iterator(_beginNode); }
    const_iterator 		    begin()     const   { return const_iterator(_beginNode); }
    iterator				end()               { return iterator(_endNode);	}
    const_iterator			end()       const   { return const_iterator(_endNode); }
    reverse_iterator 		rbegin()            { return reverse_iterator(_endNode->prev); }
    reverse_iterator		rend()              { return reverse_iterator(_beginNode->prev);	}
    const_reverse_iterator 	rbegin()    const   { return const_reverse_iterator(_endNode->prev); }
    const_reverse_iterator	rend()      const   { return const_reverse_iterator(_beginNode->prev); }

/* Capacity */
    bool        empty()     const { return (this->_size == 0); }
	size_type   size()      const { return this->_size; }
    size_type   max_size()  const { return std::numeric_limits<std::size_t>::max() / sizeof(t_node); }

/* Element access */
    reference       front()         { return *_beginNode->data; }
    const_reference front() const   { return *_beginNode->data; }
    reference       back()          { return *_endNode->prev->data; }
    const_reference back()  const   { return *_endNode->prev->data; }

/* Modifiers */
//  range (1)
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {
        clear();
        while (first != last){
            this->push_back(*first);
            first++;
        }

    }
//  fill (2)
    void assign (size_type n, const value_type& val) {
        clear();
        while (n--)
            this->push_back(val);
    }

    void push_front(const value_type& val) {
        t_node *newNode = _newNode(val, _endNode, _beginNode);
        _beginNode->prev = newNode;
        _beginNode = newNode;
        _size++;
    }

    void pop_front() {
        _remove_beginNode();
        _size--;
    }

    void push_back (const value_type& val) {
        t_node *newNode = _newNode(val, _endNode->prev, _endNode);
		_endNode->prev->next = newNode;
        _endNode->prev = newNode;
        _size++;
		if (_size == 1) {
			_beginNode = newNode;
			_endNode->next = newNode;
			_endNode->prev = newNode;
		}
	}

    void pop_back() {
        t_node	*end = _endNode;
        _endNode = _endNode->prev;
        _alloc.destroy(end->data);
        _alloc.deallocate(end->data, 1);
        _alloc_rebind.destroy(end);
        _alloc_rebind.deallocate(end, 1);
        _size--;
        if (_size == 0) {
            _beginNode = _endNode;
            _endNode->next = _endNode;
            _endNode->prev = _endNode;
        }
    }

//  single element (1)
    iterator insert (iterator position, const value_type& val) {
        t_node *prevNode = position.getNodePtr()->prev;
        t_node *nextNode = position.getNodePtr();
        t_node *newNode = _newNode(val, prevNode, nextNode);
        prevNode->next = newNode;
        nextNode->prev = newNode;
        _size++;
        if (_size == 1) {
            _beginNode = newNode;
            _endNode->next = newNode;
            _endNode->prev = newNode;
        }
        return iterator(newNode);
    }
//  fill (2)
    void insert (iterator position, size_type n, const value_type& val) {
        while (n--)
            insert(position, val);
    }
//  range (3)
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {
        for (; first != last; first++)
            insert(position, *first);
    }

    iterator erase (iterator position) {
        t_node	*nodeToDelete = position.getNodePtr();
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
        if (position == begin()) {
            _beginNode = nodeToDelete->next;
            _endNode->next = nodeToDelete->next;
        }
        _alloc.destroy(nodeToDelete->data);
        _alloc.deallocate(nodeToDelete->data, 1);
        _alloc_rebind.destroy(nodeToDelete);
        _alloc_rebind.deallocate(nodeToDelete, 1);
        _size--;
        if (_size == 0) {
            _beginNode = _endNode;
            _endNode->next = _endNode;
            _endNode->prev = _endNode;
        }
        return ++position;
    }
    iterator erase (iterator first, iterator last){
        iterator it;
        while (first != last)
            it = erase(first++);
        return it;
    }

    void swap (list& x) {
        t_node *temp_node = this->_beginNode;
        this->_beginNode = x._beginNode;
        x._beginNode = temp_node;
        temp_node = this->_endNode;
        this->_endNode = x._endNode;
        x._endNode = temp_node;

        size_type temp_size = this->_size;
        this->_size = x._size;
        x._size = temp_size;
    }

    void resize (size_type n, value_type val = value_type()) {
        while (n < _size)
            pop_back();
        while (n > _size)
            push_back(val);
    }

    void clear() {
        while (_beginNode != _endNode)
            _remove_beginNode();
        _beginNode = _endNode;
        _endNode->next = _endNode;
        _endNode->prev = _endNode;
        _size = 0;
    }

/* Operations */
//    entire list (1)
    void splice (iterator position, list& x) {
        t_node *nodeToSplice =  position.getNodePtr();  // элемент в this list, до которого нужно прицепить элементы
        nodeToSplice->prev->next = x._beginNode;        // прицепляем начало листа х до nodeToSplice
        x._beginNode->prev = nodeToSplice->prev;
        nodeToSplice->prev = x._endNode->prev;          // прицепляем конец листа х до nodeToSplice
        x._endNode->prev->next = nodeToSplice;
        if (position == begin()) {                      // если прицепляем в начало, то нужно поменять _beginNode
            _beginNode = x._beginNode;
            _endNode->next = x._beginNode;
            if (_size == 0)
                _endNode->prev = x._endNode->prev;
        }
        x._endNode->prev = x._endNode;                  // в листе х теперь нет ссылок на элементы,
        x._endNode->next = x._endNode;                  // но элементы не удалены
        x._beginNode = x._endNode;
        _size += x._size;
        x._size = 0;
    }
//    single element (2)
    void splice (iterator position, list& x, iterator i) {
        if (i == x.begin()) {                           // если из листа х нужно убрать первый элемент, то меняем ему _beginNode
            x._beginNode = i.getNodePtr()->next;
            x._endNode->next = x._beginNode;
            if (x._size == 1)
                x._endNode->prev = x._endNode;
        }
        t_node *newNode = i.getNodePtr();               // элемент в x list, который нужно прицепить к this list
        newNode->prev->next = newNode->next;            // расцепляем элемент в x list
        newNode->next->prev = newNode->prev;
        t_node *nodeToSplice =  position.getNodePtr();  // элемент в this list, до которого нужно прицепить элемент
        nodeToSplice->prev->next = newNode;             // прицепляем newNode в this list до nodeToSplice
        newNode->prev = nodeToSplice->prev;
        newNode->next = nodeToSplice;
        nodeToSplice->prev = newNode;
        if (position == begin()) {                      // если прицепляем в начало, то нужно поменять _beginNode
            _beginNode = newNode;
            _endNode->next = newNode;
            if (_size == 0) {
                _endNode->prev = newNode;
            }
        }
        _size++;
        x._size--;
    }
//    element range (3)
    void splice (iterator position, list& x, iterator first, iterator last) {
        while (first != last)
            splice(position, x, first++);
    }

    void remove (const value_type& val) {
        iterator it = begin();
        iterator ite = end();
        while (it != ite) {
            if (*it == val)
                erase(it);
            else
                it++;
        }
    }

    template <class Predicate>
    void remove_if (Predicate pred) {
        iterator it = begin();
        iterator ite = end();
        while (it != ite) {
            if (pred(*it)) {
                erase(it);
            }
            it++;
        }
    }

    void unique() {
        iterator it = begin();
        iterator ite = end();
        while (it != ite) {
            t_node *currNode = it.getNodePtr();
            if (it != begin() && *currNode->data == *currNode->prev->data)
                erase(it);
            it++;
        }
    }
    template <class BinaryPredicate>
    void unique (BinaryPredicate binary_pred) {
        iterator it = begin();
        iterator ite = end();
        while (it != ite) {
            t_node *currNode = it.getNodePtr();
            if (it != begin() && binary_pred(*currNode->data, *currNode->prev->data))
                erase(it);
            it++;
        }
    }

private:

/* Additional functions */
	void _initStartNodes() {
		_beginNode = _alloc_rebind.allocate(1);
		_beginNode->next = _beginNode;
		_beginNode->prev = _beginNode;
		_beginNode->data = _alloc.allocate(1);
		_endNode = _beginNode;
	}

	void _remove_beginNode() {
        t_node	*begin = _beginNode;
        _beginNode = _beginNode->next;
        _alloc.destroy(begin->data);
        _alloc.deallocate(begin->data, 1);
        _alloc_rebind.destroy(begin);
        _alloc_rebind.deallocate(begin, 1);
        if (_size == 1) {
            _beginNode = _endNode;
            _endNode->next = _endNode;
            _endNode->prev = _endNode;
        }
	}

    t_node * _newNode(const value_type& val, t_node *prevNode, t_node *nextNode) {
        t_node *newNode = _alloc_rebind.allocate(1);
        newNode->prev = prevNode;
        newNode->next = nextNode;
        newNode->data = _alloc.allocate(1);
        _alloc.construct(newNode->data, val);
        return newNode;
	}

	void _deleteAllNotes() {
        clear();
		// while (_beginNode != _endNode) {
		// 	t_node	*begin = _beginNode;
		// 	_beginNode = _beginNode->next;
		// 	_alloc.destroy(begin->data);
		// 	_alloc.deallocate(begin->data, 1);
		// 	// begin->data = nullptr;
		// 	_alloc_rebind.destroy(begin);
		// 	_alloc_rebind.deallocate(begin, 1);
		// 	// begin = nullptr;
		// }
		_alloc.deallocate(_endNode->data, 1);
		_alloc_rebind.deallocate(_endNode, 1);
		// _endNode = nullptr;
	}

};

}

#endif
