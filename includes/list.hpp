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
	    _clear();
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
    iterator 				begin()         { return iterator(_beginNode); }
    const_iterator 		    begin() const   { return const_iterator(_beginNode); }
    iterator				end()           { return iterator(_endNode);	}
    const_iterator			end() const     { return const_iterator(_endNode); }
    reverse_iterator 		rbegin()        { return reverse_iterator(_endNode->prev); }
    reverse_iterator		rend()          { return reverse_iterator(_beginNode->prev);	}
    const_reverse_iterator 	rbegin() const  { return const_reverse_iterator(_endNode->prev); }
    const_reverse_iterator	rend() const    { return const_reverse_iterator(_beginNode->prev); }

/* Capacity */
	size_type size() const { return this->size_type; }

/* Modifiers */
	void push_back (const value_type& val) {
//	    t_node *newNode = _createNode(val, _endNode, _endNode->prev);
		t_node *newNode = _alloc_rebind.allocate(1);
		_endNode->prev->next = newNode;
		newNode->prev = _endNode->prev;
		newNode->next = _endNode;
		newNode->data = _alloc.allocate(1);
        _endNode->prev = newNode;
		_alloc.construct(newNode->data, val);
		this->_size++;
		if (_size == 1) {
			_beginNode = newNode;
			_endNode->next = newNode;
			_endNode->prev = newNode;
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

	void _clear() {
		while (_beginNode != _endNode) {
			t_node	*begin = _beginNode;
			_beginNode = _beginNode->next;
			_alloc.destroy(begin->data);
			_alloc.deallocate(begin->data, 1);
			_alloc_rebind.destroy(begin);
			_alloc_rebind.deallocate(begin, 1);
		}
		_beginNode = _endNode;
		_endNode->next = _endNode;
		_endNode->prev = _endNode;
	}
	void _deleteAllNotes() {
		_clear();
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
