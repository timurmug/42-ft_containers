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
    allocator_type          _alloc;
    size_type				_size;
    size_type				_capacity;
    pointer                 _buffer;

public:
/* Constructors */
//    default (1)
    explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _buffer(nullptr) { }
//    fill (2)
    explicit vector (size_type n, const value_type& val = value_type(),
                     const allocator_type& alloc = allocator_type())  : _alloc(alloc), _size(n), _buffer(nullptr) {
        if (n) {
            _capacity = n;
            _buffer = _alloc.allocate(_capacity);
            value_type *buffer_p = _buffer;
            while (n--)
                _alloc.construct(buffer_p++, val);
        }
    }
//    range (3)
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _alloc(alloc), _size(0), _capacity(0), _buffer(nullptr) {
        while (first != last){
            this->push_back(*first);
            first++;
        }
    }
//    copy (4)
    vector (const vector& x) : _size(0), _capacity(0) { *this = x; }

    ~vector() {
        _clean();
    }

    vector& operator= (const vector& x) {
        if (this != &x) {
            _clean();
            _alloc = x._alloc;
            _capacity = 0;
            _size = 0;
            _buffer = nullptr;
            const_iterator it = x.begin();
            const_iterator ite = x.end();
            while (it != ite) {
                push_back(*it);
                it++;
            }
        }
        return *this;
    }

/* Iterators classes */
    class  iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        pointer  _elem_ptr;
    public:
        iterator()                  : _elem_ptr(nullptr)    { }
        iterator(pointer elem_ptr)  : _elem_ptr(elem_ptr)   { }
        iterator(const iterator& src)                       { *this = src; }
        virtual ~iterator()                                 { }
        iterator & operator=(iterator const & rhs)          {
            if (this != &rhs)
                this->_elem_ptr = rhs._elem_ptr;
            return *this;
        }

        bool                operator==(const iterator& rhs)         const   { return this->_elem_ptr == rhs._elem_ptr; }
        bool                operator!=(const iterator& rhs)         const   { return this->_elem_ptr != rhs._elem_ptr; }

        value_type&         operator*()                             const   { return *_elem_ptr; }
        value_type*         operator->()                            const   { return _elem_ptr; }

        iterator&           operator++()                                    { _elem_ptr++; return *this; }
        iterator            operator++(int)                                 { iterator tmp = *this; operator++(); return tmp; }
        iterator&           operator--()                                    { _elem_ptr--; return *this; }
        iterator            operator--(int)                                 { iterator tmp = *this; operator--(); return tmp; }

        iterator            operator+(difference_type const & rhs)  const   { return iterator(_elem_ptr + rhs); }
        iterator            operator-(difference_type const & rhs)  const   { return iterator(_elem_ptr - rhs); }

        bool                operator<(const iterator& rhs)          const   { return this->_elem_ptr < rhs._elem_ptr; }
        bool                operator>(const iterator& rhs)          const   { return this->_elem_ptr > rhs._elem_ptr; }
        bool                operator<=(const iterator& rhs)         const   { return this->_elem_ptr <= rhs._elem_ptr; }
        bool                operator>=(const iterator& rhs)         const   { return this->_elem_ptr >= rhs._elem_ptr; }

        iterator&           operator+=(difference_type const & rhs)         { _elem_ptr += rhs; return *this; }
        iterator&           operator-=(difference_type const & rhs)         { _elem_ptr -= rhs; return *this; }

        value_type&         operator[](difference_type const & i)           { return *(_elem_ptr + i); }
    };

    class  const_iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        pointer  _elem_ptr;
    public:
        const_iterator()                            : _elem_ptr(nullptr)    { }
        const_iterator(pointer elem_ptr)            : _elem_ptr(elem_ptr)   { }
        const_iterator(const const_iterator& src)                           { *this = src; }
        const_iterator(const iterator& src)                                 { *this = src; }
        virtual ~const_iterator()                                           { }
        const_iterator & operator=(const_iterator const & rhs)              {
            if (this != &rhs)
                this->_elem_ptr = rhs._elem_ptr;
            return *this;
        }
        const_iterator & operator=(iterator const & rhs)                    {
            this->_elem_ptr = rhs.operator->();
            return *this;
        }

        bool                operator==(const const_iterator& rhs)   const   { return this->_elem_ptr == rhs._elem_ptr; }
        bool                operator!=(const const_iterator& rhs)   const   { return this->_elem_ptr != rhs._elem_ptr; }

        reference           operator*()                             const   { return *_elem_ptr; }
        value_type*         operator->()                            const   { return _elem_ptr; }

        const_iterator&     operator++()                                    { _elem_ptr++; return *this; }
        const_iterator      operator++(int)                                 { const_iterator tmp = *this; operator++(); return tmp; }
        const_iterator&     operator--()                                    { _elem_ptr--; return *this; }
        const_iterator      operator--(int)                                 { const_iterator tmp = *this; operator--(); return tmp; }

        const_iterator      operator+(difference_type const & rhs)  const   { return const_iterator(_elem_ptr + rhs); }
        const_iterator      operator-(difference_type const & rhs)  const   { return const_iterator(_elem_ptr - rhs); }

        bool                operator<(const const_iterator& rhs)    const   { return this->_elem_ptr < rhs._elem_ptr; }
        bool                operator>(const const_iterator& rhs)    const   { return this->_elem_ptr > rhs._elem_ptr; }
        bool                operator<=(const const_iterator& rhs)   const   { return this->_elem_ptr <= rhs._elem_ptr; }
        bool                operator>=(const const_iterator& rhs)   const   { return this->_elem_ptr >= rhs._elem_ptr; }

        const_iterator&     operator+=(difference_type const & rhs)         { _elem_ptr += rhs; return *this; }
        const_iterator&     operator-=(difference_type const & rhs)         { _elem_ptr -= rhs; return *this; }

        reference           operator[](difference_type const & i)           { return *(_elem_ptr + i); }
    };

    class  reverse_iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        pointer  _elem_ptr;
    public:
        reverse_iterator()                  : _elem_ptr(nullptr)    { }
        reverse_iterator(pointer elem_ptr)  : _elem_ptr(elem_ptr)   { }
        reverse_iterator(const reverse_iterator& src)                       { *this = src; }
        virtual ~reverse_iterator()                                 { }
        reverse_iterator & operator=(reverse_iterator const & rhs)          {
            if (this != &rhs)
                this->_elem_ptr = rhs._elem_ptr;
            return *this;
        }

        bool                operator==(const reverse_iterator& rhs) const   { return this->_elem_ptr == rhs._elem_ptr; }
        bool                operator!=(const reverse_iterator& rhs) const   { return this->_elem_ptr != rhs._elem_ptr; }

        value_type&         operator*()                             const   { return *_elem_ptr; }
        value_type*         operator->()                            const   { return _elem_ptr; }

        reverse_iterator&   operator++()                                    { _elem_ptr--; return *this; }
        reverse_iterator    operator++(int)                                 { reverse_iterator tmp = *this; operator++(); return tmp; }
        reverse_iterator&   operator--()                                    { _elem_ptr++; return *this; }
        reverse_iterator    operator--(int)                                 { reverse_iterator tmp = *this; operator--(); return tmp; }

        reverse_iterator    operator+(difference_type const & rhs)  const   { return reverse_iterator(_elem_ptr - rhs); }
        reverse_iterator    operator-(difference_type const & rhs)  const   { return reverse_iterator(_elem_ptr + rhs); }

        bool                operator<(const reverse_iterator& rhs)  const   { return this->_elem_ptr > rhs._elem_ptr; }
        bool                operator>(const reverse_iterator& rhs)  const   { return this->_elem_ptr < rhs._elem_ptr; }
        bool                operator<=(const reverse_iterator& rhs) const   { return this->_elem_ptr >= rhs._elem_ptr; }
        bool                operator>=(const reverse_iterator& rhs) const   { return this->_elem_ptr <= rhs._elem_ptr; }

        reverse_iterator&   operator+=(difference_type const & rhs)         { _elem_ptr -= rhs; return *this; }
        reverse_iterator&   operator-=(difference_type const & rhs)         { _elem_ptr += rhs; return *this; }

        value_type&         operator[](difference_type const & i)           { return *(_elem_ptr - i); }
    };

    class  const_reverse_iterator : public std::iterator<std::input_iterator_tag, value_type> {
    private:
        pointer  _elem_ptr;
    public:
        const_reverse_iterator()                  : _elem_ptr(nullptr)                  { }
        const_reverse_iterator(pointer elem_ptr)  : _elem_ptr(elem_ptr)                 { }
        const_reverse_iterator(const const_reverse_iterator& src)                       { *this = src; }
        const_reverse_iterator(const reverse_iterator& src)                             { *this = src; }
        virtual ~const_reverse_iterator()                                                     { }
        const_reverse_iterator & operator=(const_reverse_iterator const & rhs)          {
            if (this != &rhs)
                this->_elem_ptr = rhs._elem_ptr;
            return *this;
        }
        const_reverse_iterator & operator=(reverse_iterator const & rhs)                {
            this->_elem_ptr = rhs.operator->();
            return *this;
        }

        bool                    operator==(const const_reverse_iterator& rhs)   const   { return this->_elem_ptr == rhs._elem_ptr; }
        bool                    operator!=(const const_reverse_iterator& rhs)   const   { return this->_elem_ptr != rhs._elem_ptr; }

        value_type&             operator*()                                     const   { return *_elem_ptr; }
        value_type*             operator->()                                    const   { return _elem_ptr; }

        const_reverse_iterator& operator++()                                            { _elem_ptr--; return *this; }
        const_reverse_iterator  operator++(int)                                         { const_reverse_iterator tmp = *this; operator++(); return tmp; }
        const_reverse_iterator& operator--()                                            { _elem_ptr++; return *this; }
        const_reverse_iterator  operator--(int)                                         { const_reverse_iterator tmp = *this; operator--(); return tmp; }

        const_reverse_iterator  operator+(difference_type const & rhs)          const   { return const_reverse_iterator(_elem_ptr - rhs); }
        const_reverse_iterator  operator-(difference_type const & rhs)          const   { return const_reverse_iterator(_elem_ptr + rhs); }

        bool                    operator<(const const_reverse_iterator& rhs)    const   { return this->_elem_ptr > rhs._elem_ptr; }
        bool                    operator>(const const_reverse_iterator& rhs)    const   { return this->_elem_ptr < rhs._elem_ptr; }
        bool                    operator<=(const const_reverse_iterator& rhs)   const   { return this->_elem_ptr >= rhs._elem_ptr; }
        bool                    operator>=(const const_reverse_iterator& rhs)   const   { return this->_elem_ptr <= rhs._elem_ptr; }

        const_reverse_iterator& operator+=(difference_type const & rhs)                 { _elem_ptr -= rhs; return *this; }
        const_reverse_iterator& operator-=(difference_type const & rhs)                 { _elem_ptr += rhs; return *this; }

        value_type&             operator[](difference_type const & i)                   { return *(_elem_ptr - i); }
    };

/* Iterators */
    iterator 				begin()             { return iterator(_buffer); }
    const_iterator          begin()     const   { return const_iterator(_buffer); }
    iterator				end()               { return iterator(_buffer + _size);	}
    const_iterator			end()       const   { return const_iterator(_buffer + _size); }
    reverse_iterator        rbegin()            { return reverse_iterator(_buffer + _size - 1); }
    const_reverse_iterator  rbegin()    const   { return const_reverse_iterator(_buffer + _size - 1); }
    reverse_iterator        rend()              { return reverse_iterator(_buffer - 1); }
    const_reverse_iterator  rend()      const   { return const_reverse_iterator(_buffer - 1); }

/* Capacity */
    size_type   size()                  const   { return _size; }
    size_type   max_size()              const   { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
    void        resize(size_type n, value_type val = value_type())  {
        if (n > _size)
            while (n > _size)
                push_back(val);
        else if (n < _size)
            while (n < _size)
                _alloc.destroy(_buffer + --_size);
    }
    size_type   capacity()              const   { return _capacity;}
    bool        empty()                 const   { return !_size; }
    void        reserve(size_type n)            {
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

/* Element access */
    reference       operator[] (size_type n)        { return *(_buffer + n); }
    const_reference operator[] (size_type n) const  { return *(_buffer + n); }

    reference       at (size_type n)                {
        if (n < _size)
            return operator[](n);
        else
            throw std::out_of_range{"vector"};
    }
    const_reference at (size_type n)        const   {
        if (n < _size)
            return operator[](n);
        else
            throw std::out_of_range{"vector"};
    }

    reference       front()                         { return *_buffer; }
    const_reference front()                 const   { return *_buffer; }
    reference       back()                          { return *(_buffer + _size - 1); }
    const_reference back()                  const   { return  *(_buffer + _size - 1); }

/* Modifiers */
//    range (1)
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
        _clean();
        while (first != last){
            push_back(*first);
            first++;
        }
    }
//    fill (2)
    void assign (size_type n, const value_type& val) {
        _clean();
        while (n--)
            push_back(val);
    }

    void push_back (const value_type& val) {
        if (_size == _capacity)
            reserve(!_capacity ? 1 : _capacity * 2);
        _alloc.construct(_buffer + _size++, val);
    }

    void pop_back() {
        _alloc.destroy(_buffer + _size - 1);
        _size--;
    }

//    single element (1)
    iterator insert (iterator position, const value_type& val) {
        difference_type offset = position.operator->() - _buffer;
        if (_size == _capacity) {
            reserve(!_capacity ? 1 : _capacity * 2);
        }

        if (_size) {
            std::memmove(_buffer + offset + 1,
                         _buffer + offset,
                         (_size - offset) * sizeof(value_type));
            _alloc.construct(_buffer + offset, val);
            _size++;
            return iterator(_buffer + offset);
        } else {
            _alloc.construct(_buffer, val);
            _size++;
            return iterator(_buffer);
        }
    }
//    fill (2)
    void insert (iterator position, size_type n, const value_type& val) {
        while (n--)
            insert(position, val);
    }
//    range (3)
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
        for (; first != last; first++)
            position =  insert(position, *first) + 1;
    }

    iterator erase (iterator position) {
        difference_type offset = position.operator->() - _buffer;

        _alloc.destroy(_buffer + offset);
        std::memmove(_buffer + offset,
                     _buffer + offset + 1,
                     (_size - offset) * sizeof(value_type));
        _size--;
        return iterator(_buffer + offset);
    }
    iterator erase (iterator first, iterator last) {
        difference_type offset_first = first.operator->() - _buffer;
        difference_type offset_last = last.operator->() - _buffer;

        for (difference_type i = offset_first; i < offset_last; i++) {
            _alloc.destroy(_buffer + i);
            _size--;
        }
        std::memmove(_buffer + offset_first,
                     _buffer + offset_last,
                     (offset_last - offset_first) * sizeof(value_type));
        return iterator(last);

    }

    void swap (vector& x) {
        pointer temp = _buffer;
        _buffer = x._buffer;
        x._buffer = temp;

        size_type temp_size = _size;
        _size = x._size;
        x._size = temp_size;

        size_type temp_cap = _capacity;
        _capacity = x._capacity;
        x._capacity = temp_cap;

        allocator_type temp_alloc = _alloc;
        _alloc = x._alloc;
        x._alloc = temp_alloc;
    }

    void clear() {
        _clean();
        _size = 0;
        _capacity = 0;
    }

/* Additional functions */
private:
    void _clean() {
        if (_size)
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_buffer + i);
        if (_capacity)
            _alloc.deallocate(_buffer, _capacity);
    }
};

/* Non-member function overloads */
    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
        typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
        typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
        typename ft::vector<T, Alloc>::const_iterator rhs_ite = rhs.end();
        while (lhs_it != lhs_ite) {
            if (rhs_it == rhs_ite || *lhs_it != *rhs_it)
                return false;
            lhs_it++;
            rhs_it++;
        }
        if (rhs_it != rhs_ite)
            return false;
        return true;
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
        typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
        typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
        typename ft::vector<T, Alloc>::const_iterator rhs_ite = rhs.end();
        while (lhs_it != lhs_ite && rhs_it != rhs_ite) {
            if (*rhs_it < *lhs_it)
                return false;
            if (*lhs_it < *rhs_it)
                return true;
            rhs_it++;
            lhs_it++;
        }
        return lhs_it == lhs_ite && rhs_it != rhs_ite; // lhs закончился, а rhs нет ?
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(rhs < lhs); }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return rhs < lhs; }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}

#endif