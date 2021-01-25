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
        bool                isblack;
    }						t_node;

/* Local variables */
    typedef typename allocator_type::template rebind<t_node>::other allocator_rebind_type;
    allocator_rebind_type 	_alloc_rebind;
    allocator_type          _alloc;
    t_node                  *_beginNode;
    size_type				_size;



/* Additional functions */
private:
    void _initBeginNode() {
        _beginNode = _alloc_rebind.allocate(1);
        _beginNode->parent = nullptr;
        _beginNode->left = nullptr;
        _beginNode->right = nullptr;

        _beginNode->key_value = _alloc.allocate(1);

        _beginNode->isblack = _alloc.allocate(1);
        _alloc.construct(_beginNode->isblack, true);
    }

    t_node * _newNode(const value_type& val, t_node *parentNode, t_node *leftNode, t_node *rightNode) {
        t_node *newNode = _alloc_rebind.allocate(1);
        newNode->parent = parentNode;
        newNode->left = leftNode;
        newNode->right = rightNode;

        newNode->key_value = _alloc.allocate(1);
        _alloc.construct(newNode->key_value, val);

        _beginNode->isblack = _alloc.allocate(1);
        if (parentNode->isblack)
            _alloc.construct(_beginNode->isblack, false);
        else {

//            _alloc.construct(_beginNode->isblack, true);

        }

        return newNode;
    }

    void _changeNodeColor(t_node *node) {
        _alloc.construct(node->isblack, !node->isblack);
    }

    void _deleteNode(t_node *node) {
        _alloc.destroy(node->key_value);
        _alloc.deallocate(node->key_value, 1);

        _alloc.destroy(node->isblack);
        _alloc.deallocate(node->isblack, 1);
    }

    void _clear() {
        iterator it = begin();
        iterator ite = end();
        while (it != ite) {
            _deleteNode(*it);
            it++;
        }
        _alloc_rebind.deallocate(_beginNode, 1);
    }

};

}

#endif