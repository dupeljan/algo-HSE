#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <utility>

namespace ttt{

struct Node
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


    /*
     * Recalculate child max
     * when one node is separated
     * on two nodes
     */
    bool update_child_max()
    {
        auto childs_max_old = child_max;
        // If child is a leaf
        auto value = (!childs[0]->childs.size())?
                    [](Node x) -> int {return x.key;} : // just save key
                    ///ERROR HERE
                    [](Node x) -> int {
            return *std::max_element(x.child_max.begin(),x.child_max.end());}; // else save the max of child_max list

        child_max.clear();
        for(auto &ch : childs)
            child_max.push_back(value(*ch.get()));

        return ! std::equal(child_max.begin(),child_max.end(),childs_max_old.begin(),childs_max_old.end());
    }

    void change_childs(std::vector<std::shared_ptr<Node>>&& childs_)
    {
        childs.clear();
        auto ref = std::shared_ptr<Node>(this);
        for(auto &ch : childs_)
        {
            childs.push_back(std::shared_ptr<Node>(ch));
            ch->parent = ref;
        }
    }
};

/*
struct search_out
{
    std::shared_ptr<Node> prev, cur;
    search_out(std::shared_ptr<Node> prev_,std::shared_ptr<Node> cur_):
    prev(prev_), cur(cur_)
    {}
};
*/

class Two_thee_tree
{
    std::shared_ptr<Node> root;

public:
     Two_thee_tree()
     {
        root = nullptr;
     }

     void insert(int key);
     void _delete(int key);
     std::shared_ptr<Node> search(int key);
private:
     void update_childs_max(std::shared_ptr<Node> parent);
};

}

#endif // TWO_THREE_TREE_H
