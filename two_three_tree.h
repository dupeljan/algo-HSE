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

namespace ttt {

const double EPS(1e-5);

struct Node: std::enable_shared_from_this<Node>
{
    double key; // Node key
    std::shared_ptr<Segment> value; // Node value
    std::vector<double> child_max; // Maximum element key in child subtree
    std::vector<std::shared_ptr<Node>> childs; // Ordered vector of childs
    std::shared_ptr<Node> parent;
    bool is_null;

    Node():
    key(-1),
    is_null(false)
    {}

    Node(std::vector<double> child_max_p,
         std::vector<std::shared_ptr<Node>> childs_p,
                            std::shared_ptr<Node> parent_p):
    key(-1),
    child_max(child_max_p),
    childs(childs_p),
    parent(parent_p),
    is_null(false)
    {}

    Node(double key_p,std::shared_ptr<Segment> value_p):
    key(key_p),
    value(value_p),
    child_max({}),
    childs({}),
    parent(nullptr),
    is_null(false)
    {}

    Node(double key_p,std::shared_ptr<Segment> value_p, std::shared_ptr<Node> parent_p):
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

     void insert(double key, std::shared_ptr<Segment> value);
     void remove(double key);
     std::shared_ptr<Node> next(double key);
     std::shared_ptr<Node> prev(double key);
     std::shared_ptr<Node> search(double key);

private:
     void update_childs_max(const std::shared_ptr<Node> node);
     void add_and_balance(const std::shared_ptr<Node> parent_p, const std::shared_ptr<Node> node);
     std::shared_ptr<Node> find_nearest_brother(std::shared_ptr<Node> node, Mode mode = some);
     std::shared_ptr<Node> get(double key,Mode direction);
};

}

#endif // TWO_THREE_TREE_H
