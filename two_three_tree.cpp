#include "two_three_tree.h"

void ttt::Two_thee_tree::insert(int key)
{

    if(root == nullptr)
    {
        root = std::shared_ptr<ttt::Node>(new ttt::Node(key));
        return;
    }


    auto x = search(key);
    // If we have same element in tree
    if(!x->is_null)
        return;

    auto parent = x->parent;
    // If only root in our tree
    if (parent == nullptr)
    {
        // Then x is root
        // Create new root
        auto root_new = std::shared_ptr<ttt::Node>(new ttt::Node());
        root->parent = root_new;
        auto left_child = root;
        auto right_child = std::shared_ptr<ttt::Node>(new ttt::Node(key, root_new));
        if(x->key > key)
        {
            std::swap(left_child,right_child);

        }
        // Bind root and childs
        root_new->childs = {left_child, right_child};
        root_new->child_max = {left_child->key, right_child->key};
        root = root_new;

        return;
    }

    // Insert element
    auto elem_new = std::shared_ptr<ttt::Node>(new ttt::Node(key,parent));
    // Make child list correct
    // If there is only two childs
    if (parent->childs.size() == 2)
    {
        // Just add another one and return
        int child_place = (key < parent->childs[0]->key)? 0
                                    : ((key < parent->childs[1]->key)? 1 : 2);
        parent->childs.insert(parent->childs.begin() + child_place, elem_new);
        // Update children max
        //parent->child_max.insert(parent->child_max.begin()+child_place, key);

        update_childs_max(elem_new);
        return;
    }

    // If there is thee childs - Balance the tree
    // Add fourth node
    int child_place = (key < parent->childs[0]->key)? 0
                               : ((key < parent->childs[1]->key)? 1
                                   : (((key < parent->childs[2]->key)? 2 : 3)));

    parent->childs.insert(parent->childs.begin() + child_place, elem_new);
    parent->child_max.insert(parent->child_max.begin()+child_place, key);

    // Balance it from leaf to root
    // Split node into two nodes recursively
    while(parent->childs.size() == 4)
    {

        // Create two new nodes
        auto left_node = std::shared_ptr<ttt::Node>(new ttt::Node());
        auto right_node = std::shared_ptr<ttt::Node>(new ttt::Node());

        // Do things below
        left_node->change_childs({parent->childs[0], parent->childs[1]});
        left_node->update_child_max();

        right_node->change_childs({parent->childs[2], parent->childs[3]});
        right_node->update_child_max();

        // Do thign above
        // Find place of the parent in grandpa child list
        auto grandpa = parent->parent;
        if(grandpa == nullptr)
        {
            // Create new root
            auto root_new = std::shared_ptr<ttt::Node>(new ttt::Node({},{root},nullptr));
            root->parent = root_new;
            grandpa = root_new;
            root = root_new;
        }
        // Connect nodes to grandpa
        left_node->parent = grandpa;
        right_node->parent = grandpa;
        // Find place to past new elems
        auto child_place =
                std::find(grandpa->childs.begin(),grandpa->childs.end(),parent);
        if (child_place == grandpa->childs.end())
            std::cout << "ALERT\n";

        // Past new childs
        grandpa->childs.erase(child_place);
        auto child_new = std::vector<std::shared_ptr<ttt::Node>>({left_node,right_node});
        grandpa->childs.insert(child_place,child_new.begin(),child_new.end());

        // Update max child
        grandpa->update_child_max();

        // Continue to split
        parent = grandpa;

    }

    // Update max child for all nodes to the root
    update_childs_max(parent);
}

std::shared_ptr<ttt::Node> ttt::Two_thee_tree::search(int key)
{
   // If root is a list
   if (!root->childs.size())
       return (root->key == key)? root : std::shared_ptr<Node>(new Node(root, true));
   // Search most appropriate list
   auto x = root;
   while(x->childs.size())
   {
       if(x->childs.size() == 2)
           x = (key < x->child_max[0])? x->childs[0] : x->childs[1];
       else // x child size == 3
           x = (key < x->child_max[0])? x->childs[0] :
               ( (key < x->child_max[1])? x->childs[1] : x->childs[2] );
   }

   // Return null if key is not equal
   // else return x
   if(x->key == key)
       return x;
   return std::shared_ptr<ttt::Node>(new Node(x,true));
}

void ttt::Two_thee_tree::update_childs_max(std::shared_ptr<Node> parent)
{
    do
    {parent = parent->parent;}
    while(parent != nullptr && parent->update_child_max());
}
