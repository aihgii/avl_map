#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <bits/stl_algobase.h>
#include <bits/allocator.h>
//#include <bits/stl_function.h>
//#include <bits/cpp_type_traits.h>
#include <ext/alloc_traits.h>
#include <ext/aligned_buffer.h>

namespace not_std
{
    enum _Rb_tree_color { _S_red = false, _S_black = true };

    struct _Avl_tree_node_base
    {
        typedef _Avl_tree_node_base* _Base_ptr;
        typedef const _Avl_tree_node_base* _Const_Base_ptr;

        _Rb_tree_color	_M_color;
        _Base_ptr		_M_parent;
        _Base_ptr		_M_left;
        _Base_ptr		_M_right;

        static _Base_ptr
        _S_minimum(_Base_ptr __x) noexcept
        {
            while (__x->_M_left != 0) __x = __x->_M_left;
            return __x;
        }

        static _Const_Base_ptr
        _S_minimum(_Const_Base_ptr __x) noexcept
        {
            while (__x->_M_left != 0) __x = __x->_M_left;
            return __x;
        }

        static _Base_ptr
        _S_maximum(_Base_ptr __x) noexcept
        {
            while (__x->_M_right != 0) __x = __x->_M_right;
            return __x;
        }

        static _Const_Base_ptr
        _S_maximum(_Const_Base_ptr __x) noexcept
        {
            while (__x->_M_right != 0) __x = __x->_M_right;
            return __x;
        }
    };

    template<typename _Val>
    struct _Avl_tree_node : public _Avl_tree_node_base
    {
        typedef _Avl_tree_node<_Val>* _Link_type;

        __gnu_cxx::__aligned_membuf<_Val> _M_storage;

        _Val*
        _M_valptr()
        { return _M_storage._M_ptr(); }

        const _Val*
        _M_valptr() const
        { return _M_storage._M_ptr(); }
    };

    _GLIBCXX_PURE _Avl_tree_node_base*
    _Avl_tree_increment(_Avl_tree_node_base* __x) throw ();

    _GLIBCXX_PURE const _Avl_tree_node_base*
    _Avl_tree_increment(const _Avl_tree_node_base* __x) throw ();

    _GLIBCXX_PURE _Avl_tree_node_base*
    _Avl_tree_decrement(_Avl_tree_node_base* __x) throw ();

    _GLIBCXX_PURE const _Avl_tree_node_base*
    _Avl_tree_decrement(const _Avl_tree_node_base* __x) throw ();

    template<typename _Tp>
    struct _Avl_tree_iterator
    {
        typedef _Tp  value_type;
        typedef _Tp& reference;
        typedef _Tp* pointer;

        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef std::ptrdiff_t                      difference_type;

        typedef _Avl_tree_iterator<_Tp>         _Self;
        typedef _Avl_tree_node_base::_Base_ptr  _Base_ptr;
        typedef _Avl_tree_node<_Tp>*            _Link_type;

        _Avl_tree_iterator() noexcept
                : _M_node() { }

        explicit
        _Avl_tree_iterator(_Base_ptr __x) noexcept
                : _M_node(__x) { }

        reference
        operator*() const noexcept
        { return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

        pointer
        operator->() const noexcept
        { return static_cast<_Link_type> (_M_node)->_M_valptr(); }

        _Self&
        operator++() noexcept
        {
            _M_node = _Avl_tree_increment(_M_node);
            return *this;
        }

        _Self
        operator++(int) noexcept
        {
            _Self __tmp = *this;
            _M_node = _Avl_tree_increment(_M_node);
            return __tmp;
        }

        _Self&
        operator--() noexcept
        {
            _M_node = _Avl_tree_decrement(_M_node);
            return *this;
        }

        _Self
        operator--(int) noexcept
        {
            _Self __tmp = *this;
            _M_node = _Avl_tree_decrement(_M_node);
            return __tmp;
        }

        bool
        operator==(const _Self& __x) const noexcept
        { return _M_node == __x._M_node; }

        bool
        operator!=(const _Self& __x) const noexcept
        { return _M_node != __x._M_node; }

        _Base_ptr _M_node;
    };

    template<typename _Tp>
    struct _Avl_tree_const_iterator
    {
        typedef _Tp        value_type;
        typedef const _Tp& reference;
        typedef const _Tp* pointer;

        typedef _Avl_tree_iterator<_Tp> iterator;

        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef std::ptrdiff_t                           difference_type;

        typedef _Avl_tree_const_iterator<_Tp>           _Self;
        typedef _Avl_tree_node_base::_Const_Base_ptr    _Base_ptr;
        typedef const _Avl_tree_node<_Tp>*               _Link_type;

        _Avl_tree_const_iterator() noexcept
                : _M_node() { }

        explicit
        _Avl_tree_const_iterator(_Base_ptr __x) noexcept
                : _M_node(__x) { }

        _Avl_tree_const_iterator(const iterator& __it) noexcept
                : _M_node(__it._M_node) { }

        iterator
        _M_const_cast() const noexcept
        { return iterator(const_cast<typename iterator::_Base_ptr>(_M_node)); }

        reference
        operator*() const noexcept
        { return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

        pointer
        operator->() const noexcept
        { return static_cast<_Link_type>(_M_node)->_M_valptr(); }

        _Self&
        operator++() noexcept
        {
            _M_node = _Avl_tree_increment(_M_node);
            return *this;
        }

        _Self
        operator++(int) noexcept
        {
            _Self __tmp = *this;
            _M_node = _Avl_tree_increment(_M_node);
            return __tmp;
        }

        _Self&
        operator--() noexcept
        {
            _M_node = _Avl_tree_decrement(_M_node);
            return *this;
        }

        _Self
        operator--(int) noexcept
        {
            _Self __tmp = *this;
            _M_node = _Avl_tree_decrement(_M_node);
            return __tmp;
        }

        bool
        operator==(const _Self& __x) const noexcept
        { return _M_node == __x._M_node; }

        bool
        operator!=(const _Self& __x) const noexcept
        { return _M_node != __x._M_node; }

        _Base_ptr _M_node;
    };

    template<typename _Val>
    inline bool
    operator==(const _Avl_tree_iterator<_Val>& __x,
               const _Avl_tree_const_iterator<_Val>& __y) noexcept
    { return __x._M_node == __y._M_node; }

    template<typename _Val>
    inline bool
    operator!=(const _Avl_tree_iterator<_Val>& __x,
               const _Avl_tree_const_iterator<_Val>& __y) noexcept
    { return __x._M_node != __y._M_node; }

    void
    _Avl_tree_insert_and_rebalance(const bool __insert_left,
                                   _Avl_tree_node_base* __x,
                                   _Avl_tree_node_base* __p,
                                   _Avl_tree_node_base& __header) throw ();

    _Avl_tree_node_base*
    _Avl_tree_rebalance_for_erase(_Avl_tree_node_base* const __z,
                                  _Avl_tree_node_base& __header) throw ();

    template<typename _Cmp, typename _SfinaeType, typename = std::__void_t<>>
    struct __has_is_transparent
    { };

    template<typename _Cmp, typename _SfinaeType>
    struct __has_is_transparent<_Cmp, _SfinaeType, std::__void_t<typename _Cmp::is_transparent>>
    { typedef void type; };

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc = std::allocator<_Val> >
    class _Avl_tree
    {
        typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
        rebind<_Avl_tree_node<_Val> >::other _Node_allocator;

        typedef __gnu_cxx::__alloc_traits<_Node_allocator> _Alloc_traits;

    protected:
        typedef _Avl_tree_node_base* 		_Base_ptr;
        typedef const _Avl_tree_node_base* 	_Const_Base_ptr;
        typedef _Avl_tree_node<_Val>* 		_Link_type;
        typedef const _Avl_tree_node<_Val>*	_Const_Link_type;

    private:
        // Functor recycling a pool of nodes and using allocation once the pool
        // is empty.
        struct _Reuse_or_alloc_node
        {
            _Reuse_or_alloc_node(_Avl_tree& __t)
                    : _M_root(__t._M_root()), _M_nodes(__t._M_rightmost()), _M_t(__t)
            {
                if (_M_root)
                {
                    _M_root->_M_parent = 0;

                    if (_M_nodes->_M_left)
                        _M_nodes = _M_nodes->_M_left;
                }
                else
                    _M_nodes = 0;
            }

            _Reuse_or_alloc_node(const _Reuse_or_alloc_node&) = delete;

            ~_Reuse_or_alloc_node()
            { _M_t._M_erase(static_cast<_Link_type>(_M_root)); }

            template<typename _Arg>
            _Link_type
            operator()(_Arg&& __arg)
            {
                _Link_type __node = static_cast<_Link_type>(_M_extract());
                if (__node)
                {
                    _M_t._M_destroy_node(__node);
                    _M_t._M_construct_node(__node, _GLIBCXX_FORWARD(_Arg, __arg));
                    return __node;
                }

                return _M_t._M_create_node(_GLIBCXX_FORWARD(_Arg, __arg));
            }

        private:
            _Base_ptr
            _M_extract()
            {
                if (!_M_nodes)
                    return _M_nodes;

                _Base_ptr __node = _M_nodes;
                _M_nodes = _M_nodes->_M_parent;
                if (_M_nodes)
                {
                    if (_M_nodes->_M_right == __node)
                    {
                        _M_nodes->_M_right = 0;

                        if (_M_nodes->_M_left)
                        {
                            _M_nodes = _M_nodes->_M_left;

                            while (_M_nodes->_M_right)
                                _M_nodes = _M_nodes->_M_right;

                            if (_M_nodes->_M_left)
                                _M_nodes = _M_nodes->_M_left;
                        }
                    }
                    else // __node is on the left.
                    _M_nodes->_M_left = 0;
                }
                else
                    _M_root = 0;

                return __node;
            }

            _Base_ptr _M_root;
            _Base_ptr _M_nodes;
            _Avl_tree& _M_t;
        };

        // Functor similar to the previous one but without any pool of nodes to
        // recycle.
        struct _Alloc_node
        {
            _Alloc_node(_Avl_tree& __t)
                    : _M_t(__t) { }

            template<typename _Arg>
            _Link_type
            operator()(_Arg&& __arg) const
            { return _M_t._M_create_node(_GLIBCXX_FORWARD(_Arg, __arg)); }

        private:
            _Avl_tree& _M_t;
        };

    public:
        typedef _Key 				key_type;
        typedef _Val 				value_type;
        typedef value_type* 		pointer;
        typedef const value_type* 	const_pointer;
        typedef value_type& 		reference;
        typedef const value_type& 	const_reference;
        typedef std::size_t 				size_type;
        typedef std::ptrdiff_t 			difference_type;
        typedef _Alloc 				allocator_type;

        _Node_allocator&
        _M_get_Node_allocator() noexcept
        { return *static_cast<_Node_allocator*>(&this->_M_impl); }

        const _Node_allocator&
        _M_get_Node_allocator() const noexcept
        { return *static_cast<const _Node_allocator*>(&this->_M_impl); }

        allocator_type
        get_allocator() const noexcept
        { return allocator_type(_M_get_Node_allocator()); }

    protected:
        _Link_type
        _M_get_node()
        { return _Alloc_traits::allocate(_M_get_Node_allocator(), 1); }

        void
        _M_put_node(_Link_type __p) noexcept
        { _Alloc_traits::deallocate(_M_get_Node_allocator(), __p, 1); }

        template<typename... _Args>
        void
        _M_construct_node(_Link_type __node, _Args&&... __args)
        {
            __try
            {
                ::new(__node) _Avl_tree_node<_Val>;
                _Alloc_traits::construct(_M_get_Node_allocator(),
                                         __node->_M_valptr(),
                                         std::forward<_Args>(__args)...);
            }
            __catch(...)
            {
                __node->~_Avl_tree_node<_Val>();
                _M_put_node(__node);
                __throw_exception_again;
            }
        }

        template<typename... _Args>
        _Link_type
        _M_create_node(_Args&&... __args)
        {
            _Link_type __tmp = _M_get_node();
            _M_construct_node(__tmp, std::forward<_Args>(__args)...);
            return __tmp;
        }

        void
        _M_destroy_node(_Link_type __p) noexcept
        {
            _Alloc_traits::destroy(_M_get_Node_allocator(), __p->_M_valptr());
            __p->~_Avl_tree_node<_Val>();
        }

        void
        _M_drop_node(_Link_type __p) noexcept
        {
            _M_destroy_node(__p);
            _M_put_node(__p);
        }

        template<typename _NodeGen>
        _Link_type
        _M_clone_node(_Const_Link_type __x, _NodeGen& __node_gen)
        {
            _Link_type __tmp = __node_gen(*__x->_M_valptr());
            __tmp->_M_color = __x->_M_color;
            __tmp->_M_left = 0;
            __tmp->_M_right = 0;
            return __tmp;
        }

    protected:
        // Unused _Is_pod_comparator is kept as it is part of mangled name.
        template<typename _Key_compare>
        struct _Avl_tree_impl : public _Node_allocator
        {
            _Key_compare		    _M_key_compare;
            _Avl_tree_node_base 	_M_header;
            size_type 		        _M_node_count; // Keeps track of size of tree.

            _Avl_tree_impl()
                    : _Node_allocator(), _M_key_compare(), _M_header(), _M_node_count(0)
            { _M_initialize(); }

            _Avl_tree_impl(const _Key_compare& __comp, const _Node_allocator& __a)
                    : _Node_allocator(__a), _M_key_compare(__comp), _M_header(), _M_node_count(0)
            { _M_initialize(); }

            _Avl_tree_impl(const _Key_compare& __comp, _Node_allocator&& __a)
                    : _Node_allocator(std::move(__a)), _M_key_compare(__comp), _M_header(), _M_node_count(0)
            { _M_initialize(); }

            void
            _M_reset()
            {
                this->_M_header._M_parent = 0;
                this->_M_header._M_left = &this->_M_header;
                this->_M_header._M_right = &this->_M_header;
                this->_M_node_count = 0;
            }

        private:
            void
            _M_initialize()
            {
                this->_M_header._M_color = _S_red;
                this->_M_header._M_parent = 0;
                this->_M_header._M_left = &this->_M_header;
                this->_M_header._M_right = &this->_M_header;
            }
        };

        _Avl_tree_impl<_Compare> _M_impl;

    protected:
        _Base_ptr&
        _M_root() noexcept
        { return this->_M_impl._M_header._M_parent; }

        _Const_Base_ptr
        _M_root() const noexcept
        { return this->_M_impl._M_header._M_parent; }

        _Base_ptr&
        _M_leftmost() noexcept
        { return this->_M_impl._M_header._M_left; }

        _Const_Base_ptr
        _M_leftmost() const noexcept
        { return this->_M_impl._M_header._M_left; }

        _Base_ptr&
        _M_rightmost() noexcept
        { return this->_M_impl._M_header._M_right; }

        _Const_Base_ptr
        _M_rightmost() const noexcept
        { return this->_M_impl._M_header._M_right; }

        _Link_type
        _M_begin() noexcept
        { return static_cast<_Link_type>(this->_M_impl._M_header._M_parent); }

        _Const_Link_type
        _M_begin() const noexcept
        {
            return static_cast<_Const_Link_type>
            (this->_M_impl._M_header._M_parent);
        }

        _Base_ptr
        _M_end() noexcept
        { return &this->_M_impl._M_header; }

        _Const_Base_ptr
        _M_end() const noexcept
        { return &this->_M_impl._M_header; }

        static const_reference
        _S_value(_Const_Link_type __x)
        { return *__x->_M_valptr(); }

        static const _Key&
        _S_key(_Const_Link_type __x)
        { return _KeyOfValue()(_S_value(__x)); }

        static _Link_type
        _S_left(_Base_ptr __x) noexcept
        { return static_cast<_Link_type>(__x->_M_left); }

        static _Const_Link_type
        _S_left(_Const_Base_ptr __x) noexcept
        { return static_cast<_Const_Link_type>(__x->_M_left); }

        static _Link_type
        _S_right(_Base_ptr __x) noexcept
        { return static_cast<_Link_type>(__x->_M_right); }

        static _Const_Link_type
        _S_right(_Const_Base_ptr __x) noexcept
        { return static_cast<_Const_Link_type>(__x->_M_right); }

        static const_reference
        _S_value(_Const_Base_ptr __x)
        { return *static_cast<_Const_Link_type>(__x)->_M_valptr(); }

        static const _Key&
        _S_key(_Const_Base_ptr __x)
        { return _KeyOfValue()(_S_value(__x)); }

        static _Base_ptr
        _S_minimum(_Base_ptr __x) noexcept
        { return _Avl_tree_node_base::_S_minimum(__x); }

        static _Const_Base_ptr
        _S_minimum(_Const_Base_ptr __x) noexcept
        { return _Avl_tree_node_base::_S_minimum(__x); }

        static _Base_ptr
        _S_maximum(_Base_ptr __x) noexcept
        { return _Avl_tree_node_base::_S_maximum(__x); }

        static _Const_Base_ptr
        _S_maximum(_Const_Base_ptr __x) noexcept
        { return _Avl_tree_node_base::_S_maximum(__x); }

    public:
        typedef _Avl_tree_iterator<value_type>       iterator;
        typedef _Avl_tree_const_iterator<value_type> const_iterator;

        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        std::pair<_Base_ptr, _Base_ptr>
        _M_get_insert_unique_pos(const key_type& __k);

        std::pair<_Base_ptr, _Base_ptr>
        _M_get_insert_equal_pos(const key_type& __k);

        std::pair<_Base_ptr, _Base_ptr>
        _M_get_insert_hint_unique_pos(const_iterator __pos,
                                      const key_type& __k);

        std::pair<_Base_ptr, _Base_ptr>
        _M_get_insert_hint_equal_pos(const_iterator __pos,
                                     const key_type& __k);

    private:
        template<typename _Arg, typename _NodeGen>
        iterator
        _M_insert_(_Base_ptr __x, _Base_ptr __y, _Arg&& __v, _NodeGen&);

        iterator
        _M_insert_node(_Base_ptr __x, _Base_ptr __y, _Link_type __z);

        template<typename _Arg>
        iterator
        _M_insert_lower(_Base_ptr __y, _Arg&& __v);

        template<typename _Arg>
        iterator
        _M_insert_equal_lower(_Arg&& __x);

        iterator
        _M_insert_lower_node(_Base_ptr __p, _Link_type __z);

        iterator
        _M_insert_equal_lower_node(_Link_type __z);

        template<typename _NodeGen>
        _Link_type
        _M_copy(_Const_Link_type __x, _Base_ptr __p, _NodeGen&);

        _Link_type
        _M_copy(_Const_Link_type __x, _Base_ptr __p)
        {
            _Alloc_node __an(*this);
            return _M_copy(__x, __p, __an);
        }

        void
        _M_erase(_Link_type __x);

        iterator
        _M_lower_bound(_Link_type __x, _Base_ptr __y,
                       const _Key& __k);

        const_iterator
        _M_lower_bound(_Const_Link_type __x, _Const_Base_ptr __y,
                       const _Key& __k) const;

        iterator
        _M_upper_bound(_Link_type __x, _Base_ptr __y,
                       const _Key& __k);

        const_iterator
        _M_upper_bound(_Const_Link_type __x, _Const_Base_ptr __y,
                       const _Key& __k) const;

    public:
      // allocation/deallocation
      _Avl_tree() { }

      _Avl_tree(const _Compare& __comp,
                const allocator_type& __a = allocator_type())
              : _M_impl(__comp, _Node_allocator(__a)) { }

      _Avl_tree(const _Avl_tree& __x)
              : _M_impl(__x._M_impl._M_key_compare,
                        _Alloc_traits::_S_select_on_copy(__x._M_get_Node_allocator()))
      {
          if (__x._M_root() != 0)
          {
              _M_root() = _M_copy(__x._M_begin(), _M_end());
              _M_leftmost() = _S_minimum(_M_root());
              _M_rightmost() = _S_maximum(_M_root());
              _M_impl._M_node_count = __x._M_impl._M_node_count;
          }
      }

        _Avl_tree(const allocator_type& __a)
                : _M_impl(_Compare(), _Node_allocator(__a))
        { }

        _Avl_tree(const _Avl_tree& __x, const allocator_type& __a)
                : _M_impl(__x._M_impl._M_key_compare, _Node_allocator(__a))
        {
            if (__x._M_root() != nullptr)
            {
                _M_root() = _M_copy(__x._M_begin(), _M_end());
                _M_leftmost() = _S_minimum(_M_root());
                _M_rightmost() = _S_maximum(_M_root());
                _M_impl._M_node_count = __x._M_impl._M_node_count;
            }
        }

        _Avl_tree(_Avl_tree&& __x)
                : _M_impl(__x._M_impl._M_key_compare,
                          std::move(__x._M_get_Node_allocator()))
        {
            if (__x._M_root() != 0)
                _M_move_data(__x, std::true_type());
        }

        _Avl_tree(_Avl_tree&& __x, const allocator_type& __a)
                : _Avl_tree(std::move(__x), _Node_allocator(__a))
        { }

        _Avl_tree(_Avl_tree&& __x, _Node_allocator&& __a);

        ~_Avl_tree() noexcept
        { _M_erase(_M_begin()); }

        _Avl_tree&
        operator=(const _Avl_tree& __x);

        // Accessors.
        _Compare
        key_comp() const
        { return _M_impl._M_key_compare; }

        iterator
        begin() noexcept
        { return iterator(this->_M_impl._M_header._M_left); }

        const_iterator
        begin() const noexcept
        { return const_iterator(this->_M_impl._M_header._M_left); }

        iterator
        end() noexcept
        { return iterator(&this->_M_impl._M_header); }

        const_iterator
        end() const noexcept
        { return const_iterator(&this->_M_impl._M_header); }

        reverse_iterator
        rbegin() noexcept
        { return reverse_iterator(end()); }

        const_reverse_iterator
        rbegin() const noexcept
        { return const_reverse_iterator(end()); }

        reverse_iterator
        rend() noexcept
        { return reverse_iterator(begin()); }

        const_reverse_iterator
        rend() const noexcept
        { return const_reverse_iterator(begin()); }

        bool
        empty() const noexcept
        { return _M_impl._M_node_count == 0; }

        size_type
        size() const noexcept
        { return _M_impl._M_node_count; }

        size_type
        max_size() const noexcept
        { return _Alloc_traits::max_size(_M_get_Node_allocator()); }

        void
        swap(_Avl_tree& __t)
        noexcept(std::__is_nothrow_swappable<_Compare>::value);

        // Insert/erase.
        template<typename _Arg>
        std::pair<iterator, bool>
        _M_insert_unique(_Arg&& __x);

        template<typename _Arg>
        iterator
        _M_insert_equal(_Arg&& __x);

        template<typename _Arg, typename _NodeGen>
        iterator
        _M_insert_unique_(const_iterator __pos, _Arg&& __x, _NodeGen&);

        template<typename _Arg>
        iterator
        _M_insert_unique_(const_iterator __pos, _Arg&& __x)
        {
            _Alloc_node __an(*this);
            return _M_insert_unique_(__pos, std::forward<_Arg>(__x), __an);
        }

        template<typename _Arg, typename _NodeGen>
        iterator
        _M_insert_equal_(const_iterator __pos, _Arg&& __x, _NodeGen&);

        template<typename _Arg>
        iterator
        _M_insert_equal_(const_iterator __pos, _Arg&& __x)
        {
            _Alloc_node __an(*this);
            return _M_insert_equal_(__pos, std::forward<_Arg>(__x), __an);
        }

        template<typename... _Args>
        std::pair<iterator, bool>
        _M_emplace_unique(_Args&&... __args);

        template<typename... _Args>
        iterator
        _M_emplace_equal(_Args&&... __args);

        template<typename... _Args>
        iterator
        _M_emplace_hint_unique(const_iterator __pos, _Args&&... __args);

        template<typename... _Args>
        iterator
        _M_emplace_hint_equal(const_iterator __pos, _Args&&... __args);

        template<typename _InputIterator>
        void
        _M_insert_unique(_InputIterator __first, _InputIterator __last);

        template<typename _InputIterator>
        void
        _M_insert_equal(_InputIterator __first, _InputIterator __last);

    private:
        void
        _M_erase_aux(const_iterator __position);

        void
        _M_erase_aux(const_iterator __first, const_iterator __last);

    public:
        _GLIBCXX_ABI_TAG_CXX11
        iterator
        erase(const_iterator __position)
        {
            const_iterator __result = __position;
            ++__result;
            _M_erase_aux(__position);
            return __result._M_const_cast();
        }


        _GLIBCXX_ABI_TAG_CXX11
        iterator
        erase(iterator __position)
        {
            iterator __result = __position;
            ++__result;
            _M_erase_aux(__position);
            return __result;
        }

        size_type
        erase(const key_type& __x);

        _GLIBCXX_ABI_TAG_CXX11
        iterator
        erase(const_iterator __first, const_iterator __last)
        {
            _M_erase_aux(__first, __last);
            return __last._M_const_cast();
        }

        void
        erase(const key_type* __first, const key_type* __last);

        void
        clear() noexcept
        {
            _M_erase(_M_begin());
            _M_impl._M_reset();
        }

        // Set operations.
        iterator
        find(const key_type& __k);

        const_iterator
        find(const key_type& __k) const;

        size_type
        count(const key_type& __k) const;

        iterator
        lower_bound(const key_type& __k)
        { return _M_lower_bound(_M_begin(), _M_end(), __k); }

        const_iterator
        lower_bound(const key_type& __k) const
        { return _M_lower_bound(_M_begin(), _M_end(), __k); }

        iterator
        upper_bound(const key_type& __k)
        { return _M_upper_bound(_M_begin(), _M_end(), __k); }

        const_iterator
        upper_bound(const key_type& __k) const
        { return _M_upper_bound(_M_begin(), _M_end(), __k); }

        std::pair<iterator, iterator>
        equal_range(const key_type& __k);

        std::pair<const_iterator, const_iterator>
        equal_range(const key_type& __k) const;

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        iterator
        _M_find_tr(const _Kt& __k)
        {
            const _Avl_tree* __const_this = this;
            return __const_this->_M_find_tr(__k)._M_const_cast();
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        const_iterator
        _M_find_tr(const _Kt& __k) const
        {
            auto __j = _M_lower_bound_tr(__k);
            if (__j != end() && _M_impl._M_key_compare(__k, _S_key(__j._M_node)))
                __j = end();
            return __j;
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        size_type
        _M_count_tr(const _Kt& __k) const
        {
            auto __p = _M_equal_range_tr(__k);
            return std::distance(__p.first, __p.second);
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        iterator
        _M_lower_bound_tr(const _Kt& __k)
        {
            const _Avl_tree* __const_this = this;
            return __const_this->_M_lower_bound_tr(__k)._M_const_cast();
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        const_iterator
        _M_lower_bound_tr(const _Kt& __k) const
        {
            auto __x = _M_begin();
            auto __y = _M_end();
            while (__x != 0)
                if (!_M_impl._M_key_compare(_S_key(__x), __k))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                    __x = _S_right(__x);
            return const_iterator(__y);
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        iterator
        _M_upper_bound_tr(const _Kt& __k)
        {
            const _Avl_tree* __const_this = this;
            return __const_this->_M_upper_bound_tr(__k)._M_const_cast();
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        const_iterator
        _M_upper_bound_tr(const _Kt& __k) const
        {
            auto __x = _M_begin();
            auto __y = _M_end();
            while (__x != 0)
                if (_M_impl._M_key_compare(__k, _S_key(__x)))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                    __x = _S_right(__x);
            return const_iterator(__y);
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        std::pair<iterator, iterator>
        _M_equal_range_tr(const _Kt& __k)
        {
            const _Avl_tree* __const_this = this;
            auto __ret = __const_this->_M_equal_range_tr(__k);
            return { __ret.first._M_const_cast(), __ret.second._M_const_cast() };
        }

        template<typename _Kt,
                 typename _Req =
                 typename __has_is_transparent<_Compare, _Kt>::type>
        std::pair<const_iterator, const_iterator>
        _M_equal_range_tr(const _Kt& __k) const
        {
            auto __low = _M_lower_bound_tr(__k);
            auto __high = __low;
            auto& __cmp = _M_impl._M_key_compare;
            while (__high != end() && !__cmp(__k, _S_key(__high._M_node)))
                ++__high;
            return { __low, __high };
        }

        // Debugging.
        bool
        __avl_verify() const;

        _Avl_tree&
        operator=(_Avl_tree&&)
        noexcept(_Alloc_traits::_S_nothrow_move()
                 && std::is_nothrow_move_assignable<_Compare>::value);

        template<typename _Iterator>
        void
        _M_assign_unique(_Iterator, _Iterator);

        template<typename _Iterator>
        void
        _M_assign_equal(_Iterator, _Iterator);

    private:
        // Move elements from container with equal allocator.
        void
        _M_move_data(_Avl_tree&, std::true_type);

        // Move elements from container with possibly non-equal allocator,
        // which might result in a copy not a move.
        void
        _M_move_data(_Avl_tree&, std::false_type);

        // Move assignment from container with equal allocator.
        void
        _M_move_assign(_Avl_tree&, std::true_type);

        // Move assignment from container with possibly non-equal allocator,
        // which might result in a copy not a move.
        void
        _M_move_assign(_Avl_tree&, std::false_type);
    };

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline bool
    operator==(const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
               const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    {
        return __x.size() == __y.size()
               && std::equal(__x.begin(), __x.end(), __y.begin());
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline bool
    operator<(const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
              const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    {
        return std::lexicographical_compare(__x.begin(), __x.end(),
                                            __y.begin(), __y.end());
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
            typename _Compare, typename _Alloc>
    inline bool
    operator!=(const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
               const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return !(__x == __y); }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline bool
    operator>(const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
              const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return __y < __x; }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline bool
    operator<=(const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
               const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return !(__y < __x); }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline bool
    operator>=(const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
               const _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return !(__x < __y); }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline void
    swap(_Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
         _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { __x.swap(__y); }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _Avl_tree(_Avl_tree&& __x, _Node_allocator&& __a)
            : _M_impl(__x._M_impl._M_key_compare, std::move(__a))
    {
        using __eq = typename _Alloc_traits::is_always_equal;
        if (__x._M_root() != nullptr)
            _M_move_data(__x, __eq());
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_move_data(_Avl_tree& __x, std::true_type)
    {
        _M_root() = __x._M_root();
        _M_leftmost() = __x._M_leftmost();
        _M_rightmost() = __x._M_rightmost();
        _M_root()->_M_parent = _M_end();

        __x._M_root() = 0;
        __x._M_leftmost() = __x._M_end();
        __x._M_rightmost() = __x._M_end();

        this->_M_impl._M_node_count = __x._M_impl._M_node_count;
        __x._M_impl._M_node_count = 0;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_move_data(_Avl_tree& __x, std::false_type)
    {
        if (_M_get_Node_allocator() == __x._M_get_Node_allocator())
            _M_move_data(__x, std::true_type());
        else
        {
            _Alloc_node __an(*this);
            auto __lbd =
                    [&__an](const value_type& __cval)
                    {
                        auto& __val = const_cast<value_type&>(__cval);
                        return __an(std::move_if_noexcept(__val));
                    };
            _M_root() = _M_copy(__x._M_begin(), _M_end(), __lbd);
            _M_leftmost() = _S_minimum(_M_root());
            _M_rightmost() = _S_maximum(_M_root());
            _M_impl._M_node_count = __x._M_impl._M_node_count;
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_move_assign(_Avl_tree& __x, std::true_type)
    {
        clear();
        if (__x._M_root() != nullptr)
            _M_move_data(__x, std::true_type());
        std::__alloc_on_move(_M_get_Node_allocator(),
                             __x._M_get_Node_allocator());
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_move_assign(_Avl_tree& __x, std::false_type)
    {
        if (_M_get_Node_allocator() == __x._M_get_Node_allocator())
            return _M_move_assign(__x, std::true_type{});

        // Try to move each node reusing existing nodes and copying __x nodes
        // structure.
        _Reuse_or_alloc_node __roan(*this);
        _M_impl._M_reset();
        if (__x._M_root() != nullptr)
        {
            auto __lbd =
                    [&__roan](const value_type& __cval)
                    {
                        auto& __val = const_cast<value_type&>(__cval);
                        return __roan(std::move_if_noexcept(__val));
                    };
            _M_root() = _M_copy(__x._M_begin(), _M_end(), __lbd);
            _M_leftmost() = _S_minimum(_M_root());
            _M_rightmost() = _S_maximum(_M_root());
            _M_impl._M_node_count = __x._M_impl._M_node_count;
            __x.clear();
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    inline _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>&
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    operator=(_Avl_tree&& __x)
    noexcept(_Alloc_traits::_S_nothrow_move()
             && std::is_nothrow_move_assignable<_Compare>::value)
    {
        _M_impl._M_key_compare = __x._M_impl._M_key_compare;
        constexpr bool __move_storage =
                _Alloc_traits::_S_propagate_on_move_assign()
                || _Alloc_traits::_S_always_equal();
        _M_move_assign(__x, std::__bool_constant<__move_storage>());
        return *this;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Iterator>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_assign_unique(_Iterator __first, _Iterator __last)
    {
        _Reuse_or_alloc_node __roan(*this);
        _M_impl._M_reset();
        for (; __first != __last; ++__first)
            _M_insert_unique_(end(), *__first, __roan);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Iterator>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_assign_equal(_Iterator __first, _Iterator __last)
    {
        _Reuse_or_alloc_node __roan(*this);
        _M_impl._M_reset();
        for (; __first != __last; ++__first)
            _M_insert_equal_(end(), *__first, __roan);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>&
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    operator=(const _Avl_tree& __x)
    {
        if (this != &__x)
        {
            // Note that _Key may be a constant type.
            if (_Alloc_traits::_S_propagate_on_copy_assign())
            {
                auto& __this_alloc = this->_M_get_Node_allocator();
                auto& __that_alloc = __x._M_get_Node_allocator();
                if (!_Alloc_traits::_S_always_equal()
                    && __this_alloc != __that_alloc)
                {
                    // Replacement allocator cannot free existing storage, we need
                    // to erase nodes first.
                    clear();
                    std::__alloc_on_copy(__this_alloc, __that_alloc);
                }
            }

            _Reuse_or_alloc_node __roan(*this);
            _M_impl._M_reset();
            _M_impl._M_key_compare = __x._M_impl._M_key_compare;
            if (__x._M_root() != 0)
            {
                _M_root() = _M_copy(__x._M_begin(), _M_end(), __roan);
                _M_leftmost() = _S_minimum(_M_root());
                _M_rightmost() = _S_maximum(_M_root());
                _M_impl._M_node_count = __x._M_impl._M_node_count;
            }
        }

        return *this;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Arg, typename _NodeGen>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_(_Base_ptr __x, _Base_ptr __p, _Arg&& __v, _NodeGen& __node_gen)
    {
        bool __insert_left = (__x != 0 || __p == _M_end()
                              || _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

        _Link_type __z = __node_gen(_GLIBCXX_FORWARD(_Arg, __v));

        _Avl_tree_insert_and_rebalance(__insert_left, __z, __p,
                                       this->_M_impl._M_header);
        ++_M_impl._M_node_count;
        return iterator(__z);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Arg>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_lower(_Base_ptr __p, _Arg&& __v)
    {
        bool __insert_left = (__p == _M_end()
                              || !_M_impl._M_key_compare(_S_key(__p),
                                                         _KeyOfValue()(__v)));

        _Link_type __z = _M_create_node(_GLIBCXX_FORWARD(_Arg, __v));

        _Avl_tree_insert_and_rebalance(__insert_left, __z, __p,
                                       this->_M_impl._M_header);
        ++_M_impl._M_node_count;
        return iterator(__z);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Arg>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_equal_lower(_Arg&& __v)
    {
        _Link_type __x = _M_begin();
        _Base_ptr __y = _M_end();
        while (__x != 0)
        {
            __y = __x;
            __x = !_M_impl._M_key_compare(_S_key(__x), _KeyOfValue()(__v))
                  ? _S_left(__x) : _S_right(__x);
        }
        return _M_insert_lower(__y, _GLIBCXX_FORWARD(_Arg, __v));
    }

    template<typename _Key, typename _Val, typename _KoV,
             typename _Compare, typename _Alloc>
    template<typename _NodeGen>
    typename _Avl_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type
    _Avl_tree<_Key, _Val, _KoV, _Compare, _Alloc>::
    _M_copy(_Const_Link_type __x, _Base_ptr __p, _NodeGen& __node_gen)
    {
        // Structural copy. __x and __p must be non-null.
        _Link_type __top = _M_clone_node(__x, __node_gen);
        __top->_M_parent = __p;

        __try
        {
            if (__x->_M_right)
                __top->_M_right = _M_copy(_S_right(__x), __top, __node_gen);
            __p = __top;
            __x = _S_left(__x);

            while (__x != 0)
            {
                _Link_type __y = _M_clone_node(__x, __node_gen);
                __p->_M_left = __y;
                __y->_M_parent = __p;
                if (__x->_M_right)
                    __y->_M_right = _M_copy(_S_right(__x), __y, __node_gen);
                __p = __y;
                __x = _S_left(__x);
            }
        }
        __catch(...)
        {
            _M_erase(__top);
            __throw_exception_again;
        }
        return __top;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_erase(_Link_type __x)
    {
        // Erase without rebalancing.
        while (__x != 0)
        {
            _M_erase(_S_right(__x));
            _Link_type __y = _S_left(__x);
            _M_drop_node(__x);
            __x = __y;
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_lower_bound(_Link_type __x, _Base_ptr __y, const _Key& __k)
    {
        while (__x != 0)
            if (!_M_impl._M_key_compare(_S_key(__x), __k))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        return iterator(__y);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_lower_bound(_Const_Link_type __x, _Const_Base_ptr __y, const _Key& __k) const
    {
        while (__x != 0)
            if (!_M_impl._M_key_compare(_S_key(__x), __k))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        return const_iterator(__y);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_upper_bound(_Link_type __x, _Base_ptr __y, const _Key& __k)
    {
        while (__x != 0)
            if (_M_impl._M_key_compare(__k, _S_key(__x)))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        return iterator(__y);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_upper_bound(_Const_Link_type __x, _Const_Base_ptr __y, const _Key& __k) const
    {
        while (__x != 0)
            if (_M_impl._M_key_compare(__k, _S_key(__x)))
                __y = __x, __x = _S_left(__x);
            else
                __x = _S_right(__x);
        return const_iterator(__y);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
              typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    equal_range(const _Key& __k)
    {
        _Link_type __x = _M_begin();
        _Base_ptr __y = _M_end();
        while (__x != 0)
        {
            if (_M_impl._M_key_compare(_S_key(__x), __k))
                __x = _S_right(__x);
            else if (_M_impl._M_key_compare(__k, _S_key(__x)))
                __y = __x, __x = _S_left(__x);
            else
            {
                _Link_type __xu(__x);
                _Base_ptr __yu(__y);
                __y = __x, __x = _S_left(__x);
                __xu = _S_right(__xu);
                return std::pair<iterator, iterator>(_M_lower_bound(__x, __y, __k),
                                                     _M_upper_bound(__xu, __yu, __k));
            }
        }
        return std::pair<iterator, iterator>(iterator(__y),
                                             iterator(__y));
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator,
              typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    equal_range(const _Key& __k) const
    {
        _Const_Link_type __x = _M_begin();
        _Const_Base_ptr __y = _M_end();
        while (__x != 0)
        {
            if (_M_impl._M_key_compare(_S_key(__x), __k))
                __x = _S_right(__x);
            else if (_M_impl._M_key_compare(__k, _S_key(__x)))
                __y = __x, __x = _S_left(__x);
            else
            {
                _Const_Link_type __xu(__x);
                _Const_Base_ptr __yu(__y);
                __y = __x, __x = _S_left(__x);
                __xu = _S_right(__xu);
                return std::pair<const_iterator, const_iterator>(_M_lower_bound(__x, __y, __k),
                                                                 _M_upper_bound(__xu, __yu, __k));
            }
        }
        return std::pair<const_iterator, const_iterator>(const_iterator(__y),
                                                         const_iterator(__y));
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    swap(_Avl_tree& __t)
    noexcept(std::__is_nothrow_swappable<_Compare>::value)
    {
        if (_M_root() == 0)
        {
            if (__t._M_root() != 0)
            {
                _M_root() = __t._M_root();
                _M_leftmost() = __t._M_leftmost();
                _M_rightmost() = __t._M_rightmost();
                _M_root()->_M_parent = _M_end();
                _M_impl._M_node_count = __t._M_impl._M_node_count;

                __t._M_impl._M_reset();
            }
        }
        else if (__t._M_root() == 0)
        {
            __t._M_root() = _M_root();
            __t._M_leftmost() = _M_leftmost();
            __t._M_rightmost() = _M_rightmost();
            __t._M_root()->_M_parent = __t._M_end();
            __t._M_impl._M_node_count = _M_impl._M_node_count;

            _M_impl._M_reset();
        }
        else
        {
            std::swap(_M_root(),__t._M_root());
            std::swap(_M_leftmost(),__t._M_leftmost());
            std::swap(_M_rightmost(),__t._M_rightmost());

            _M_root()->_M_parent = _M_end();
            __t._M_root()->_M_parent = __t._M_end();
            std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
        }
        // No need to swap header's color as it does not change.
        std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);

        _Alloc_traits::_S_on_swap(_M_get_Node_allocator(),
                                  __t._M_get_Node_allocator());
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
              typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_unique_pos(const key_type& __k)
    {
        typedef std::pair<_Base_ptr, _Base_ptr> _Res;
        _Link_type __x = _M_begin();
        _Base_ptr __y = _M_end();
        bool __comp = true;
        while (__x != 0)
        {
            __y = __x;
            __comp = _M_impl._M_key_compare(__k, _S_key(__x));
            __x = __comp ? _S_left(__x) : _S_right(__x);
        }
        iterator __j = iterator(__y);
        if (__comp)
        {
            if (__j == begin())
                return _Res(__x, __y);
            else
                --__j;
        }
        if (_M_impl._M_key_compare(_S_key(__j._M_node), __k))
            return _Res(__x, __y);
        return _Res(__j._M_node, 0);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
              typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_equal_pos(const key_type& __k)
    {
        typedef std::pair<_Base_ptr, _Base_ptr> _Res;
        _Link_type __x = _M_begin();
        _Base_ptr __y = _M_end();
        while (__x != 0)
        {
            __y = __x;
            __x = _M_impl._M_key_compare(__k, _S_key(__x))
                  ? _S_left(__x) : _S_right(__x);
        }
        return _Res(__x, __y);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Arg>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_unique(_Arg&& __v)
    {
        typedef std::pair<iterator, bool> _Res;
        std::pair<_Base_ptr, _Base_ptr> __res
                = _M_get_insert_unique_pos(_KeyOfValue()(__v));

        if (__res.second)
        {
            _Alloc_node __an(*this);
            return _Res(_M_insert_(__res.first, __res.second,
                                   _GLIBCXX_FORWARD(_Arg, __v), __an),
                        true);
        }

        return _Res(iterator(__res.first), false);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    template<typename _Arg>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_equal(_Arg&& __v)
    {
        std::pair<_Base_ptr, _Base_ptr> __res
                = _M_get_insert_equal_pos(_KeyOfValue()(__v));
        _Alloc_node __an(*this);
        return _M_insert_(__res.first, __res.second,
                          _GLIBCXX_FORWARD(_Arg, __v), __an);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
              typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_hint_unique_pos(const_iterator __position, const key_type& __k)
    {
        iterator __pos = __position._M_const_cast();
        typedef std::pair<_Base_ptr, _Base_ptr> _Res;

        // end()
        if (__pos._M_node == _M_end())
        {
            if (size() > 0
                && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
                return _Res(0, _M_rightmost());
            else
                return _M_get_insert_unique_pos(__k);
        }
        else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
        {
            // First, try before...
            iterator __before = __pos;
            if (__pos._M_node == _M_leftmost()) // begin()
                return _Res(_M_leftmost(), _M_leftmost());
            else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k))
            {
                if (_S_right(__before._M_node) == 0)
                    return _Res(0, __before._M_node);
                else
                    return _Res(__pos._M_node, __pos._M_node);
            }
            else
                return _M_get_insert_unique_pos(__k);
        }
        else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
        {
            // ... then try after.
            iterator __after = __pos;
            if (__pos._M_node == _M_rightmost())
                return _Res(0, _M_rightmost());
            else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node)))
            {
                if (_S_right(__pos._M_node) == 0)
                    return _Res(0, __pos._M_node);
                else
                    return _Res(__after._M_node, __after._M_node);
            }
            else
                return _M_get_insert_unique_pos(__k);
        }
        else
            // Equivalent keys.
            return _Res(__pos._M_node, 0);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    template<typename _Arg, typename _NodeGen>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_unique_(const_iterator __position, _Arg&& __v, _NodeGen& __node_gen)
    {
        std::pair<_Base_ptr, _Base_ptr> __res
                = _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));

        if (__res.second)
            return _M_insert_(__res.first, __res.second,
                              _GLIBCXX_FORWARD(_Arg, __v),
                              __node_gen);
        return iterator(__res.first);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr,
              typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_Base_ptr>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_hint_equal_pos(const_iterator __position, const key_type& __k)
    {
        iterator __pos = __position._M_const_cast();
        typedef std::pair<_Base_ptr, _Base_ptr> _Res;

        // end()
        if (__pos._M_node == _M_end())
        {
            if (size() > 0
                && !_M_impl._M_key_compare(__k, _S_key(_M_rightmost())))
                return _Res(0, _M_rightmost());
            else
                return _M_get_insert_equal_pos(__k);
        }
        else if (!_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
        {
            // First, try before...
            iterator __before = __pos;
            if (__pos._M_node == _M_leftmost()) // begin()
                return _Res(_M_leftmost(), _M_leftmost());
            else if (!_M_impl._M_key_compare(__k, _S_key((--__before)._M_node)))
            {
                if (_S_right(__before._M_node) == 0)
                    return _Res(0, __before._M_node);
                else
                    return _Res(__pos._M_node, __pos._M_node);
            }
            else
                return _M_get_insert_equal_pos(__k);
        }
        else
        {
            // ... then try after.
            iterator __after = __pos;
            if (__pos._M_node == _M_rightmost())
                return _Res(0, _M_rightmost());
            else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), __k))
            {
                if (_S_right(__pos._M_node) == 0)
                    return _Res(0, __pos._M_node);
                else
                    return _Res(__after._M_node, __after._M_node);
            }
            else
                return _Res(0, 0);
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    template<typename _Arg, typename _NodeGen>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_equal_(const_iterator __position, _Arg&& __v, _NodeGen& __node_gen)
    {
        std::pair<_Base_ptr, _Base_ptr> __res
                = _M_get_insert_hint_equal_pos(__position, _KeyOfValue()(__v));

        if (__res.second)
            return _M_insert_(__res.first, __res.second,
                              _GLIBCXX_FORWARD(_Arg, __v),
                              __node_gen);

        return _M_insert_equal_lower(_GLIBCXX_FORWARD(_Arg, __v));
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_node(_Base_ptr __x, _Base_ptr __p, _Link_type __z)
    {
        bool __insert_left = (__x != 0 || __p == _M_end()
                              || _M_impl._M_key_compare(_S_key(__z),
                                                        _S_key(__p)));

        _Avl_tree_insert_and_rebalance(__insert_left, __z, __p,
                                       this->_M_impl._M_header);
        ++_M_impl._M_node_count;
        return iterator(__z);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_lower_node(_Base_ptr __p, _Link_type __z)
    {
        bool __insert_left = (__p == _M_end()
                              || !_M_impl._M_key_compare(_S_key(__p),
                                                         _S_key(__z)));

        _Avl_tree_insert_and_rebalance(__insert_left, __z, __p,
                                       this->_M_impl._M_header);
        ++_M_impl._M_node_count;
        return iterator(__z);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue,
             typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_equal_lower_node(_Link_type __z)
    {
        _Link_type __x = _M_begin();
        _Base_ptr __y = _M_end();
        while (__x != 0)
        {
            __y = __x;
            __x = !_M_impl._M_key_compare(_S_key(__x), _S_key(__z))
                  ? _S_left(__x) : _S_right(__x);
        }
        return _M_insert_lower_node(__y, __z);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    template<typename... _Args>
    std::pair<typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_emplace_unique(_Args&&... __args)
    {
        _Link_type __z = _M_create_node(std::forward<_Args>(__args)...);

        __try
        {
            typedef std::pair<iterator, bool> _Res;
            auto __res = _M_get_insert_unique_pos(_S_key(__z));
            if (__res.second)
                return _Res(_M_insert_node(__res.first, __res.second, __z), true);

            _M_drop_node(__z);
            return _Res(iterator(__res.first), false);
        }
        __catch(...)
        {
            _M_drop_node(__z);
            __throw_exception_again;
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    template<typename... _Args>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_emplace_equal(_Args&&... __args)
    {
        _Link_type __z = _M_create_node(std::forward<_Args>(__args)...);

        __try
        {
            auto __res = _M_get_insert_equal_pos(_S_key(__z));
            return _M_insert_node(__res.first, __res.second, __z);
        }
        __catch(...)
        {
            _M_drop_node(__z);
            __throw_exception_again;
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    template<typename... _Args>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_emplace_hint_unique(const_iterator __pos, _Args&&... __args)
    {
        _Link_type __z = _M_create_node(std::forward<_Args>(__args)...);

        __try
        {
            auto __res = _M_get_insert_hint_unique_pos(__pos, _S_key(__z));

            if (__res.second)
                return _M_insert_node(__res.first, __res.second, __z);

            _M_drop_node(__z);
            return iterator(__res.first);
        }
        __catch(...)
        {
            _M_drop_node(__z);
            __throw_exception_again;
        }
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    template<typename... _Args>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_emplace_hint_equal(const_iterator __pos, _Args&&... __args)
    {
        _Link_type __z = _M_create_node(std::forward<_Args>(__args)...);

        __try
        {
            auto __res = _M_get_insert_hint_equal_pos(__pos, _S_key(__z));

            if (__res.second)
                return _M_insert_node(__res.first, __res.second, __z);

            return _M_insert_equal_lower_node(__z);
        }
        __catch(...)
        {
            _M_drop_node(__z);
            __throw_exception_again;
        }
    }

    template<typename _Key, typename _Val, typename _KoV,
             typename _Cmp, typename _Alloc>
    template<class _II>
    void
    _Avl_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::
    _M_insert_unique(_II __first, _II __last)
    {
        _Alloc_node __an(*this);
        for (; __first != __last; ++__first)
            _M_insert_unique_(end(), *__first, __an);
    }

    template<typename _Key, typename _Val, typename _KoV, typename _Cmp, typename _Alloc>
    template<class _II>
    void
    _Avl_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::
    _M_insert_equal(_II __first, _II __last)
    {
        _Alloc_node __an(*this);
        for (; __first != __last; ++__first)
            _M_insert_equal_(end(), *__first, __an);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_erase_aux(const_iterator __position)
    {
        _Link_type __y =
                static_cast<_Link_type>(_Avl_tree_rebalance_for_erase
                        (const_cast<_Base_ptr>(__position._M_node),
                         this->_M_impl._M_header));
        _M_drop_node(__y);
        --_M_impl._M_node_count;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_erase_aux(const_iterator __first, const_iterator __last)
    {
        if (__first == begin() && __last == end())
            clear();
        else
            while (__first != __last)
                erase(__first++);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    erase(const _Key& __x)
    {
        std::pair<iterator, iterator> __p = equal_range(__x);
        const size_type __old_size = size();
        erase(__p.first, __p.second);
        return __old_size - size();
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    void
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    erase(const _Key* __first, const _Key* __last)
    {
        while (__first != __last)
            erase(*__first++);
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    find(const _Key& __k)
    {
        iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
        return (__j == end()
                || _M_impl._M_key_compare(__k,
                                          _S_key(__j._M_node))) ? end() : __j;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    find(const _Key& __k) const
    {
        const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
        return (__j == end()
                || _M_impl._M_key_compare(__k,
                                          _S_key(__j._M_node))) ? end() : __j;
    }

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    typename _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
    _Avl_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    count(const _Key& __k) const
    {
        std::pair<const_iterator, const_iterator> __p = equal_range(__k);
        const size_type __n = std::distance(__p.first, __p.second);
        return __n;
    }

    _GLIBCXX_PURE unsigned int
    _Avl_tree_black_count(const _Avl_tree_node_base* __node,
                          const _Avl_tree_node_base* __root) throw ();

    template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    bool
    _Avl_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::__avl_verify() const
    {
        if (_M_impl._M_node_count == 0 || begin() == end())
            return _M_impl._M_node_count == 0 && begin() == end()
                   && this->_M_impl._M_header._M_left == _M_end()
                   && this->_M_impl._M_header._M_right == _M_end();

        unsigned int __len = _Avl_tree_black_count(_M_leftmost(), _M_root());
        for (const_iterator __it = begin(); __it != end(); ++__it)
        {
            _Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
            _Const_Link_type __L = _S_left(__x);
            _Const_Link_type __R = _S_right(__x);

            if (__x->_M_color == _S_red)
                if ((__L && __L->_M_color == _S_red)
                    | (__R && __R->_M_color == _S_red))
              return false;

            if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
                return false;
            if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
                return false;

            if (!__L && !__R && _Avl_tree_black_count(__x, _M_root()) != __len)
                return false;
        }

        if (_M_leftmost() != _Avl_tree_node_base::_S_minimum(_M_root()))
            return false;
        if (_M_rightmost() != _Avl_tree_node_base::_S_maximum(_M_root()))
            return false;
        return true;
    }

} // namespace

#endif
