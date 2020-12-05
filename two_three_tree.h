#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <utility>
#include <exception>
#include "segment.h"

namespace ttt
{

typedef ttt_key key_type;
typedef std::shared_ptr<Segment> val_type;

struct Node: std::enable_shared_from_this<Node>
{
    static std::shared_ptr<Segment> get_value_shrd_ptr(std::shared_ptr<Node> n);

    key_type key; // Node key
    val_type value; // Node value
    std::vector<key_type> child_max; // Maximum element key in child subtree
    std::vector<std::shared_ptr<Node>> childs; // Ordered vector of childs
    std::shared_ptr<Node> parent;
    bool is_null;

    Node():
    is_null(false)
    {}

    Node(std::vector<key_type> child_max_p,
         std::vector<std::shared_ptr<Node>> childs_p,
                            std::shared_ptr<Node> parent_p):
    child_max(child_max_p),
    childs(childs_p),
    parent(parent_p),
    is_null(false)
    {}

    Node(key_type key_p,val_type value_p):
    key(key_p),
    value(value_p),
    child_max({}),
    childs({}),
    parent(nullptr),
    is_null(false)
    {}

    Node(key_type key_p,val_type value_p, std::shared_ptr<Node> parent_p):
    key(key_p),
    value(value_p),
    child_max({}),
    childs({}),
    parent(parent_p),
    is_null(false)
    {}
    Node(std::shared_ptr<Node> n, bool is_null_):
    key(n->key),
    child_max(n->child_max),
    childs(n->childs),
    parent(n->parent),
    is_null(is_null_)
    {}


    bool update_child_max();
    void change_childs(std::vector<std::shared_ptr<Node>>&& childs_);
    bool is_leaf(){return !childs.size();}
};

enum Mode {left, right, some};
class Two_thee_tree
{

public:

     std::shared_ptr<Node> root;

     Two_thee_tree()
     {
        root = nullptr;
     }

     void insert(key_type key, std::shared_ptr<Segment> value);
     void remove(key_type key);
     std::shared_ptr<Node> next(key_type key);
     std::shared_ptr<Node> prev(key_type key);
     std::shared_ptr<Node> search(key_type key);

private:
     void update_childs_max(const std::shared_ptr<Node> node);
     void add_and_balance(const std::shared_ptr<Node> parent_p, const std::shared_ptr<Node> node);
     std::shared_ptr<Node> find_nearest_brother(std::shared_ptr<Node> node, Mode mode = some);
     std::shared_ptr<Node> get(key_type key,Mode direction);
};

}

#endif // TWO_THREE_TREE_H
