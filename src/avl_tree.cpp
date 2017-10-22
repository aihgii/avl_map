#include "../include/avl_tree.h"

namespace not_std
{

    static _Avl_tree_node_base*
    local_Avl_tree_increment(_Avl_tree_node_base* __x) throw ()
    {
        if (__x->_M_right != 0)
        {
            __x = __x->_M_right;
            while (__x->_M_left != 0)
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
        if (__x->_M_left != 0)
        {
            __x = __x->_M_left;
            while (__x->_M_right != 0)
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
            ? __x->_M_left->_M_height : 0;
        _Avl_tree_height hr = __x->_M_right
            ? __x->_M_right->_M_height : 0;
        __x->_M_height = (hl > hr ? hl : hr) + 1;
    }

    static void
    local_Avl_tree_rotate_left(_Avl_tree_node_base* const __x,
                              _Avl_tree_node_base*& __root)
    {
        _Avl_tree_node_base* const __y = __x->_M_right;

        __x->_M_right = __y->_M_left;
        if (__y->_M_left !=0)
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
        if (__y->_M_right != 0)
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

    void
    _Avl_tree_insert_and_rebalance(const bool          __insert_left,
                                  _Avl_tree_node_base* __x,
                                  _Avl_tree_node_base* __p,
                                  _Avl_tree_node_base& __header) throw ()
    {
        _Avl_tree_node_base *& __root = __header._M_parent;

        // Initialize fields in new node to insert.
        __x->_M_parent = __p;
        __x->_M_left = 0;
        __x->_M_right = 0;
        __x->_M_color = _S_red;

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
        // Rebalance.
        while (__x != __root
               && __x->_M_parent->_M_color == _S_red)
        {
            _Avl_tree_node_base* const __xpp = __x->_M_parent->_M_parent;

            if (__x->_M_parent == __xpp->_M_left)
            {
                _Avl_tree_node_base* const __y = __xpp->_M_right;
                if (__y && __y->_M_color == _S_red)
                {
                    __x->_M_parent->_M_color = _S_black;
                    __y->_M_color = _S_black;
                    __xpp->_M_color = _S_red;
                    __x = __xpp;
                }
                else
                {
                    if (__x == __x->_M_parent->_M_right)
                    {
                        __x = __x->_M_parent;
                        local_Avl_tree_rotate_left(__x, __root);
                    }
                    __x->_M_parent->_M_color = _S_black;
                    __xpp->_M_color = _S_red;
                    local_Avl_tree_rotate_right(__xpp, __root);
                }
            }
            else
            {
                _Avl_tree_node_base* const __y = __xpp->_M_left;
                if (__y && __y->_M_color == _S_red)
                {
                    __x->_M_parent->_M_color = _S_black;
                    __y->_M_color = _S_black;
                    __xpp->_M_color = _S_red;
                    __x = __xpp;
                }
                else
                {
                    if (__x == __x->_M_parent->_M_left)
                    {
                        __x = __x->_M_parent;
                        local_Avl_tree_rotate_right(__x, __root);
                    }
                    __x->_M_parent->_M_color = _S_black;
                    __xpp->_M_color = _S_red;
                    local_Avl_tree_rotate_left(__xpp, __root);
                }
            }
        }
        __root->_M_color = _S_black;
    }

    _Avl_tree_node_base*
    _Avl_tree_rebalance_for_erase(_Avl_tree_node_base* const __z,
                                 _Avl_tree_node_base& __header) throw ()
    {
        _Avl_tree_node_base *& __root = __header._M_parent;
        _Avl_tree_node_base *& __leftmost = __header._M_left;
        _Avl_tree_node_base *& __rightmost = __header._M_right;
        _Avl_tree_node_base* __y = __z;
        _Avl_tree_node_base* __x = 0;
        _Avl_tree_node_base* __x_parent = 0;

        if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
            __x = __y->_M_right;     // __x might be null.
        else
        if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
            __x = __y->_M_left;    // __x is not null.
        else
        {
            // __z has two non-null children.  Set __y to
            __y = __y->_M_right;   //   __z's successor.  __x might be null.
            while (__y->_M_left != 0)
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
                __x_parent = __y->_M_parent;
                if (__x) __x->_M_parent = __y->_M_parent;
                __y->_M_parent->_M_left = __x;   // __y must be a child of _M_left
                __y->_M_right = __z->_M_right;
                __z->_M_right->_M_parent = __y;
            }
            else
                __x_parent = __y;
            if (__root == __z)
                __root = __y;
            else if (__z->_M_parent->_M_left == __z)
                __z->_M_parent->_M_left = __y;
            else
                __z->_M_parent->_M_right = __y;
            __y->_M_parent = __z->_M_parent;
            std::swap(__y->_M_color, __z->_M_color);
            __y = __z;
            // __y now points to node to be actually deleted
        }
        else
        {                        // __y == __z
            __x_parent = __y->_M_parent;
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
                if (__z->_M_right == 0)        // __z->_M_left must be null also
                    __leftmost = __z->_M_parent;
                    // makes __leftmost == _M_header if __z == __root
                else
                    __leftmost = _Avl_tree_node_base::_S_minimum(__x);
            }
            if (__rightmost == __z)
            {
                if (__z->_M_left == 0)         // __z->_M_right must be null also
                    __rightmost = __z->_M_parent;
                    // makes __rightmost == _M_header if __z == __root
                else                      // __x == __z->_M_left
                    __rightmost = _Avl_tree_node_base::_S_maximum(__x);
            }
        }
        if (__y->_M_color != _S_red)
        {
            while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
                if (__x == __x_parent->_M_left)
                {
                    _Avl_tree_node_base* __w = __x_parent->_M_right;
                    if (__w->_M_color == _S_red)
                    {
                        __w->_M_color = _S_black;
                        __x_parent->_M_color = _S_red;
                        local_Avl_tree_rotate_left(__x_parent, __root);
                        __w = __x_parent->_M_right;
                    }
                    if ((__w->_M_left == 0 ||
                         __w->_M_left->_M_color == _S_black) &&
                        (__w->_M_right == 0 ||
                         __w->_M_right->_M_color == _S_black))
                    {
                        __w->_M_color = _S_red;
                        __x = __x_parent;
                        __x_parent = __x_parent->_M_parent;
                    }
                    else
                    {
                        if (__w->_M_right == 0
                            || __w->_M_right->_M_color == _S_black)
                        {
                            __w->_M_left->_M_color = _S_black;
                            __w->_M_color = _S_red;
                            local_Avl_tree_rotate_right(__w, __root);
                            __w = __x_parent->_M_right;
                        }
                        __w->_M_color = __x_parent->_M_color;
                        __x_parent->_M_color = _S_black;
                        if (__w->_M_right)
                            __w->_M_right->_M_color = _S_black;
                        local_Avl_tree_rotate_left(__x_parent, __root);
                        break;
                    }
                }
                else
                {
                    // same as above, with _M_right <-> _M_left.
                    _Avl_tree_node_base* __w = __x_parent->_M_left;
                    if (__w->_M_color == _S_red)
                    {
                        __w->_M_color = _S_black;
                        __x_parent->_M_color = _S_red;
                        local_Avl_tree_rotate_right(__x_parent, __root);
                        __w = __x_parent->_M_left;
                    }
                    if ((__w->_M_right == 0 ||
                         __w->_M_right->_M_color == _S_black) &&
                        (__w->_M_left == 0 ||
                         __w->_M_left->_M_color == _S_black))
                    {
                        __w->_M_color = _S_red;
                        __x = __x_parent;
                        __x_parent = __x_parent->_M_parent;
                    }
                    else
                    {
                        if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
                        {
                            __w->_M_right->_M_color = _S_black;
                            __w->_M_color = _S_red;
                            local_Avl_tree_rotate_left(__w, __root);
                            __w = __x_parent->_M_left;
                        }
                        __w->_M_color = __x_parent->_M_color;
                        __x_parent->_M_color = _S_black;
                        if (__w->_M_left)
                            __w->_M_left->_M_color = _S_black;
                        local_Avl_tree_rotate_right(__x_parent, __root);
                        break;
                    }
                }
            if (__x) __x->_M_color = _S_black;
        }
        return __y;
    }

    unsigned int
    _Avl_tree_black_count(const _Avl_tree_node_base* __node,
                         const _Avl_tree_node_base* __root) throw ()
    {
        if (__node == 0)
            return 0;
        unsigned int __sum = 0;
        do
        {
            if (__node->_M_color == _S_black)
                ++__sum;
            if (__node == __root)
                break;
            __node = __node->_M_parent;
        }
        while (1);
        return __sum;
    }

} // namespace
