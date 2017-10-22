#include "../include/avl_tree.h"

namespace not_std
{

    static _Avl_tree_node_base*
    local_Avl_tree_increment(_Avl_tree_node_base* __x) throw ()
    {
        if (__x->_M_right != nullptr)
        {
            __x = __x->_M_right;
            while (__x->_M_left != nullptr)
                __x = __x->_M_left;
        }
        else
        {
            _Avl_tree_node_base* __y = __x->_M_parent;
            while (__x == __y->_M_right)
            {
                __x = __y;
                __y = __y->_M_parent;
            }
            if (__x->_M_right != __y)
                __x = __y;
        }
        return __x;
    }

    _Avl_tree_node_base*
    _Avl_tree_increment(_Avl_tree_node_base* __x) throw ()
    {
        return local_Avl_tree_increment(__x);
    }

    const _Avl_tree_node_base*
    _Avl_tree_increment(const _Avl_tree_node_base* __x) throw ()
    {
        return local_Avl_tree_increment(const_cast<_Avl_tree_node_base*>(__x));
    }

    static _Avl_tree_node_base*
    local_Avl_tree_decrement(_Avl_tree_node_base* __x) throw ()
    {
        if (__x->_M_left != nullptr)
        {
            __x = __x->_M_left;
            while (__x->_M_right != nullptr)
                __x = __x->_M_right;
        }
        else
        {
            _Avl_tree_node_base* __y = __x->_M_parent;
            while (__x == __y->_M_left)
            {
                __x = __y;
                __y = __y->_M_parent;
            }
            if (__x->_M_left != __y)
                __x = __y;
        }
        return __x;
    }

    _Avl_tree_node_base*
    _Avl_tree_decrement(_Avl_tree_node_base* __x) throw ()
    {
        return local_Avl_tree_decrement(__x);
    }

    const _Avl_tree_node_base*
    _Avl_tree_decrement(const _Avl_tree_node_base* __x) throw ()
    {
        return local_Avl_tree_decrement(const_cast<_Avl_tree_node_base*>(__x));
    }

    static void
    local_Avl_tree_fix_height(_Avl_tree_node_base* __x)
    {
        _Avl_tree_height hl = __x->_M_left
            ? __x->_M_left->_M_height
            : static_cast<_Avl_tree_height> (0);
        _Avl_tree_height hr = __x->_M_right
            ? __x->_M_right->_M_height
            : static_cast<_Avl_tree_height> (0);
        __x->_M_height = (hl > hr ? hl : hr)
                         + static_cast<_Avl_tree_height> (1);
    }

    static void
    local_Avl_tree_rotate_left(_Avl_tree_node_base* const __x,
                              _Avl_tree_node_base*& __root)
    {
        _Avl_tree_node_base* const __y = __x->_M_right;

        __x->_M_right = __y->_M_left;
        if (__y->_M_left != nullptr)
            __y->_M_left->_M_parent = __x;
        __y->_M_parent = __x->_M_parent;

        if (__x == __root)
            __root = __y;
        else if (__x == __x->_M_parent->_M_left)
            __x->_M_parent->_M_left = __y;
        else
            __x->_M_parent->_M_right = __y;
        __y->_M_left = __x;
        __x->_M_parent = __y;

        local_Avl_tree_fix_height(__x);
        local_Avl_tree_fix_height(__y);
    }

    static void
    local_Avl_tree_rotate_right(_Avl_tree_node_base* const __x,
                                _Avl_tree_node_base*& __root)
    {
        _Avl_tree_node_base* const __y = __x->_M_left;

        __x->_M_left = __y->_M_right;
        if (__y->_M_right != nullptr)
            __y->_M_right->_M_parent = __x;
        __y->_M_parent = __x->_M_parent;

        if (__x == __root)
            __root = __y;
        else if (__x == __x->_M_parent->_M_right)
            __x->_M_parent->_M_right = __y;
        else
            __x->_M_parent->_M_left = __y;
        __y->_M_right = __x;
        __x->_M_parent = __y;

        local_Avl_tree_fix_height(__x);
        local_Avl_tree_fix_height(__y);
    }

    static void
    local_Avl_tree_rebalance(_Avl_tree_node_base* const __x,
                             _Avl_tree_node_base*& __root)
    {
        _Avl_tree_node_base* __y = __x;

        do
        {
            auto __bfactor = _Avl_tree_node_base::_Balance_factor(__y);

            if (__bfactor > 1)
            {
                if (_Avl_tree_node_base::_Balance_factor(__y->_M_right) < 0)
                    local_Avl_tree_rotate_right(__y->_M_right, __root);
                local_Avl_tree_rotate_left(__y, __root);
            }
            else if (__bfactor < -1)
            {
                if (_Avl_tree_node_base::_Balance_factor(__y->_M_left) > 0)
                    local_Avl_tree_rotate_left(__y->_M_left, __root);
                local_Avl_tree_rotate_right(__y, __root);
            }
            local_Avl_tree_fix_height(__y);

            __y = __y->_M_parent;
        } while (__y != __root);
    }

    void
    _Avl_tree_insert_and_rebalance(const bool          __insert_left,
                                  _Avl_tree_node_base* __x,
                                  _Avl_tree_node_base* __p,
                                  _Avl_tree_node_base& __header) throw ()
    {
        _Avl_tree_node_base *& __root = __header._M_parent;

        // Initialize fields in new node to insert.
        __x->_M_height = 0;
        __x->_M_parent = __p;
        __x->_M_left = nullptr;
        __x->_M_right = nullptr;

        // Insert.
        // Make new node child of parent and maintain root, leftmost and
        // rightmost nodes.
        // N.B. First node is always inserted left.
        if (__insert_left)
        {
            __p->_M_left = __x; // also makes leftmost = __x when __p == &__header

            if (__p == &__header)
            {
                __header._M_parent = __x;
                __header._M_right = __x;
            }
            else if (__p == __header._M_left)
                __header._M_left = __x; // maintain leftmost pointing to min node
        }
        else
        {
            __p->_M_right = __x;

            if (__p == __header._M_right)
                __header._M_right = __x; // maintain rightmost pointing to max node
        }

        local_Avl_tree_rebalance(__x, __root);
    }

    _Avl_tree_node_base*
    _Avl_tree_rebalance_for_erase(_Avl_tree_node_base* const __z,
                                  _Avl_tree_node_base& __header) throw ()
    {
        _Avl_tree_node_base *& __root = __header._M_parent;
        _Avl_tree_node_base *& __leftmost = __header._M_left;
        _Avl_tree_node_base *& __rightmost = __header._M_right;
        _Avl_tree_node_base* __y = __z;
        _Avl_tree_node_base* __x = nullptr;

        if (__y->_M_left == nullptr)     // __z has at most one non-null child. y == z.
            __x = __y->_M_right;     // __x might be null.
        else
        if (__y->_M_right == nullptr)  // __z has exactly one non-null child. y == z.
            __x = __y->_M_left;    // __x is not null.
        else
        {
            // __z has two non-null children.  Set __y to
            __y = __y->_M_right;   //   __z's successor.  __x might be null.
            while (__y->_M_left != nullptr)
                __y = __y->_M_left;
            __x = __y->_M_right;
        }
        if (__y != __z)
        {
            // relink y in place of z.  y is z's successor
            __z->_M_left->_M_parent = __y;
            __y->_M_left = __z->_M_left;
            if (__y != __z->_M_right)
            {
                if (__x) __x->_M_parent = __y->_M_parent;
                __y->_M_parent->_M_left = __x;   // __y must be a child of _M_left
                __y->_M_right = __z->_M_right;
                __z->_M_right->_M_parent = __y;
                local_Avl_tree_fix_height(__y->_M_right);
            }
            if (__root == __z)
                __root = __y;
            else if (__z->_M_parent->_M_left == __z)
                __z->_M_parent->_M_left = __y;
            else
                __z->_M_parent->_M_right = __y;
            __y->_M_parent = __z->_M_parent;
            local_Avl_tree_fix_height(__y);
            __y = __z;
            // __y now points to node to be actually deleted
        }
        else
        {   // __y == __z
            if (__x)
                __x->_M_parent = __y->_M_parent;
            if (__root == __z)
                __root = __x;
            else
            if (__z->_M_parent->_M_left == __z)
                __z->_M_parent->_M_left = __x;
            else
                __z->_M_parent->_M_right = __x;
            if (__leftmost == __z)
            {
                if (__z->_M_right == nullptr)        // __z->_M_left must be null also
                    __leftmost = __z->_M_parent;
                    // makes __leftmost == _M_header if __z == __root
                else
                    __leftmost = _Avl_tree_node_base::_S_minimum(__x);
            }
            if (__rightmost == __z)
            {
                if (__z->_M_left == nullptr)         // __z->_M_right must be null also
                    __rightmost = __z->_M_parent;
                    // makes __rightmost == _M_header if __z == __root
                else                      // __x == __z->_M_left
                    __rightmost = _Avl_tree_node_base::_S_maximum(__x);
            }
        }

        local_Avl_tree_fix_height(__z->_M_parent);
        local_Avl_tree_rebalance(__x->_M_parent, __root);

        return __y;
    }

//    unsigned int
//    _Avl_tree_black_count(const _Avl_tree_node_base* __node,
//                          const _Avl_tree_node_base* __root) throw ()
//    {
//        if (__node == nullptr)
//            return 0;
//        unsigned int __sum = 0;
//        do
//        {
//            if (__node->_M_color == _S_black)
//                ++__sum;
//            if (__node == __root)
//                break;
//            __node = __node->_M_parent;
//        }
//        while (true);
//        return __sum;
//    }

} // namespace
