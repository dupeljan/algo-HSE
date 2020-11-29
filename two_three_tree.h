#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <utility>

namespace ttt {

struct Node: std::enable_shared_from_this<Node>
{
    int key; // Node key
    std::vector<int> child_max; // Maximum element key in child subtree
    std::vector<std::shared_ptr<Node>> childs; // Ordered vector of childs
    std::shared_ptr<Node> parent;
    bool is_null;

    Node():
    key(-1),
    is_null(false)
    {}

    Node(std::vector<int> child_max_p,
         std::vector<std::shared_ptr<Node>> childs_p,
                            std::shared_ptr<Node> parent_p):
    key(-1),
    child_max(child_max_p),
    childs(childs_p),
    parent(parent_p),
    is_null(false)
    {}

    Node(int key_p):
    key(key_p),
    child_max({}),
    childs({}),
    parent(nullptr),
    is_null(false)
    {}

    Node(int key_p, std::shared_ptr<Node> parent_p):
    key(key_p),
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
};


class Two_thee_tree
{

public:

     std::shared_ptr<Node> root;

     Two_thee_tree()
     {
        root = nullptr;
     }

     void insert(int key);
     void delete_(int key);
     std::shared_ptr<Node> search(int key);

private:
     void update_childs_max(const std::shared_ptr<Node> node);
     void add_and_balance(const std::shared_ptr<Node> parent_p, const std::shared_ptr<Node> node);
};

}

#endif // TWO_THREE_TREE_H
