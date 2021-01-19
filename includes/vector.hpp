#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft {

template<bool Cond, class T = void>
struct enable_if {};
template<class T>
struct enable_if<true, T> { typedef T type; };

template < class T, class Alloc = std::allocator<T> >
class vector {

public:
/* Member types */
    typedef T                                           value_type;
    typedef Alloc                                       allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    class												iterator;
    class												const_iterator;
    class												reverse_iterator;
    class												const_reverse_iterator;
    typedef ptrdiff_t									difference_type;
    typedef size_t										size_type;

private:
/* Local variables */
//    typedef typename allocator_type::template rebind<value_type>::other allocator_rebind_type;
//    allocator_rebind_type 	_alloc_rebind;
    allocator_type          _alloc;
    size_type				_size;
    size_type				_capacity;
    value_type              *_buffer;

public:
/* Constructors */
//    default (1)
    explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _buffer(nullptr) { }
//    fill (2)
    explicit vector (size_type n, const value_type& val = value_type(),
                     const allocator_type& alloc = allocator_type())  : _alloc(alloc), _size(n), _buffer(nullptr) {
        _capacity = !n ? 0 : n;
        _buffer = _alloc.allocate(_capacity);
        value_type *buffer_p = _buffer;
        while (n--)
            _alloc.construct(buffer_p++, val);
    }
//    range (3)
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _alloc(alloc), _size(0), _capacity(0), _buffer(nullptr) {
//        _buffer = _alloc.allocate(1);
        while (first != last){
            this->push_back(*first);
            first++;
        }
    }
//    copy (4)
    vector (const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity) { *this = x; }

    ~vector() {
        for (size_type i = 0; i < _size; i++) {
            _alloc.destroy(_buffer + i);
        }
        _alloc.deallocate(_buffer, _capacity);
    }

/* Iterators classes */
    class  iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        value_type  *_elem_ptr;
    public:
        iterator() : _elem_ptr(nullptr) { }
        iterator(value_type* elem_ptr) : _elem_ptr(elem_ptr) { }
        iterator(const iterator& src) { *this = src; }
        virtual ~iterator() { }
        iterator & operator=(iterator const & rhs) {
            if (this != &rhs)
                this->_elem_ptr = rhs._elem_ptr;
            return *this;
        }

        bool operator==(const iterator& rhs) const { return this->_elem_ptr == rhs._elem_ptr; }
        bool operator!=(const iterator& rhs) const { return this->_elem_ptr != rhs._elem_ptr; }

        value_type& operator*() const { return *_elem_ptr; }
        value_type* operator->() const { return _elem_ptr; }

        iterator& operator++() { _elem_ptr++; return *this; }
        iterator operator++(int) { iterator tmp = *this; operator++(); return tmp; }
        iterator& operator--() { _elem_ptr--; return *this; }
        iterator operator--(int) { iterator tmp = *this; operator--(); return tmp; }

        iterator& operator+(difference_type const & rhs) { return iterator(&(*_elem_ptr + rhs)); }
        iterator& operator-(difference_type const & rhs) { return iterator(&(*_elem_ptr - rhs)); }

        bool operator<(const iterator& rhs) const { return this->_elem_ptr < rhs._elem_ptr; }
        bool operator>(const iterator& rhs) const { return this->_elem_ptr > rhs._elem_ptr; }
        bool operator<=(const iterator& rhs) const { return this->_elem_ptr <= rhs._elem_ptr; }
        bool operator>=(const iterator& rhs) const { return this->_elem_ptr >= rhs._elem_ptr; }

        iterator& operator+=(difference_type const & rhs) { _elem_ptr = &(*_elem_ptr + rhs); return *this; }
        iterator& operator-=(difference_type const & rhs) { _elem_ptr = &(*_elem_ptr - rhs); return *this; }

        iterator& operator[](difference_type const & i) { return *(_elem_ptr + i); }
    };

/* Iterators */
    iterator 				begin()             { return iterator(_buffer); }
    iterator				end()               { return iterator(_buffer + _size);	}

/* Capacity */
    size_type   size()                  const       { return _size; }
    size_type   capacity()              const       { return _capacity;}
    void        reserve(size_type n)                {
        if (n <= _capacity)
            return;
        if (_capacity != 0) {
            value_type *temp_buffer = _alloc.allocate(n);
            memmove(temp_buffer, _buffer, _size * sizeof(value_type));
            _alloc.deallocate(_buffer, _capacity);
            _buffer = temp_buffer;
            _capacity = n;
        }
        else {
            _buffer = _alloc.allocate(1);
            _capacity = 1;
        }
    }

/* Modifiers */
    void push_back (const value_type& val) {
        if (_size == _capacity)
            reserve(!_capacity ? 1 : _capacity * 2);
        _alloc.construct(_buffer + _size++, val);
    }
};

}

#endif