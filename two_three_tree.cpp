#include "two_three_tree.h"

using namespace ttt;
/*
 * Insert element in tree with
 * given key value
 * params:
 *          key - given key value
 */
void ttt::Two_thee_tree::insert(key_type key, std::shared_ptr<Segment> value)
{
    if(root == nullptr)
    {
        root = std::shared_ptr<ttt::Node>(new ttt::Node(key,value));
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
        auto right_child = std::shared_ptr<ttt::Node>(new ttt::Node(key,value, root_new));
        if(x->key - key > EPS)
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
    auto elem_new = std::shared_ptr<ttt::Node>(new ttt::Node(key,value));
    // Make child list correct
    add_and_balance(parent,elem_new);

}

/*
 * Remove element from tree
 * by given key value
 * params:
 *          key - given key value
 */
void ttt::Two_thee_tree::remove(key_type key)
{
    // Find node to remove
    auto t = search(key);

    // If it doesn't exist
    if(t == nullptr || t->is_null)
    {
        //std::cout << "Attempt to remove elem which doesn't exist\n";
        return;
    }

    // If it has no parent ->
    // It's the root node
    auto parent = t->parent;
    if(parent == nullptr)
    {
        // Expect automated memory alloc
        root = nullptr;
        return;
    }

    // If p has three sons ->
    // just remove one of them
    if(parent->childs.size() == 3)
    {
        // Remove t from childs vector
        parent->childs.erase(std::remove(parent->childs.begin(),parent->childs.end(),t)
                                                                      ,parent->childs.end());
        // Remove t from child_max vector
        parent->child_max.erase(std::remove(parent->child_max.begin(),parent->child_max.end(),t->key)
                                ,parent->child_max.end());
        // Recalculate child_max recursevly
        update_childs_max(parent);

        return;
    }

    // Thus parent have two child nodes


    auto g_parent = parent->parent;
    auto node = find_nearest_brother(t);
    // If parent is root
    // Then remained node is root
    if(g_parent == nullptr)
    {
        root = node;
        node->parent = nullptr;
        return;
    }
    // While parent node has only one child and it's
    // not the tree root
    do
    {
        // Find closest neighbor of parent
        auto parent_new = find_nearest_brother(parent);
        // remove it from g_parent
        g_parent->childs.erase(std::remove(g_parent->childs.begin(),
                                            g_parent->childs.end(),
                                            parent),
                                g_parent->childs.end());
        // Connect node to new parent
        if(node->childs.size())
            node->key = node->child_max.back();
        add_and_balance(parent_new,node);

        // Iterate
        node = parent_new;
        parent = g_parent;
        g_parent = g_parent->parent;

    }while(g_parent != nullptr && parent->childs.size() == 1);
    // If root have only one child
    // his child become root
    if (g_parent == nullptr && parent->childs.size() == 1)
    {
        // Swap root and parent node
        node->parent = nullptr;
        root = node;
    }
}

/*
 * Get next node after node
 * with given key
 * params:
 *          key - given key
 * return:
 *          node after given key
 *          if there is node after given key
 *          else nullptr. If there is no node
 *          with given key - return nullptr
 */
std::shared_ptr<Node> Two_thee_tree::next(key_type key)
{
    return get(key,right);
}

/*
 * Get next node after node
 * with given key
 * params:
 *          key - given key
 * return:
 *          node before given key
 *          if there is node before given key
 *          else nullptr. If there is no node
 *          with given key - return nullptr
 */
std::shared_ptr<Node> Two_thee_tree::prev(key_type key)
{
    return get(key,left);
}

/*
 * Get next or prev node by key
 * depend on given direction
 * params:
 *          key - given key
 *          direction - given direction
 * return:
 *          node before/after given key
 *          if there is node before/after given key
 *          else nullptr. If there is no node
 *          with given key - return nullptr
 */
std::shared_ptr<Node> Two_thee_tree::get(key_type key, Mode direction)
{
        auto node = search(key);
        if(node == nullptr || node->is_null)
            return nullptr;
       // Go up untill find node
       // which have right brother
       auto parent = node->parent;
       std::shared_ptr<Node> brother;
       do
       {
           brother = find_nearest_brother(node,direction);
           parent = node->parent;
           node = parent;
       }
       while(parent != nullptr && brother == nullptr);

       // If there is no right brother at all
       // thus there is no next node
       if(parent == nullptr && brother == nullptr)
           return nullptr;
       // Else go to the left
       // until leaf
       while(brother->childs.size())
       {
           if(direction == right)
               brother = brother->childs[0];
            else // if direction == left
               brother = brother->childs.back();
       }
       // The leaf will be next
       return brother;
}

/*
 * Search by given key
 * params:
 *          key - given key
 * return:
 *          node if it's exist
 *          or left node with params is_null == true
 */
std::shared_ptr<Node> ttt::Two_thee_tree::search(key_type key)
{
    if (root == nullptr)
        return nullptr;

   // If root is a list
   if (!root->childs.size())
       return (root->key == key)? root : std::shared_ptr<Node>(new Node(root, true));
   // Search most appropriate list
   auto x = root;
   while(x->childs.size())
   {
       if(x->childs.size() == 2)
           x = (key  <= x->child_max[0])? x->childs[0] : x->childs[1];
       else // x child size == 3
           x = (key <= x->child_max[0] )? x->childs[0] :
               ( (key <= x->child_max[1] )? x->childs[1] : x->childs[2] );
   }

   // Return null if key is not equal
   // else return x
   if(x->key == key)
       return x;
   return std::shared_ptr<ttt::Node>(new Node(x,true));
}

/*
 * Update_child_max for all nodes
 * from parent of given node to root
 * params:
 *          node - given node
 */
void ttt::Two_thee_tree::update_childs_max(const std::shared_ptr<Node> node)
{
    auto parent = node;
    do
    {parent = parent->parent;}
    while(parent != nullptr && parent->update_child_max());
}

/*
 * Add node to parent node, balance tree and
 * recompute all child_max
 * params:
 *          parent - node which child list appended
 *                   by given node
 *          node   - given node
 */
void ttt::Two_thee_tree::add_and_balance(const std::shared_ptr<ttt::Node> parent_p,const std::shared_ptr<ttt::Node> node)
{
    auto parent = parent_p;
    auto key = node->key;

    // Setup parents relation
    node->parent = parent_p;
    // If there is only two childs
    if (parent->childs.size() == 2)
    {
        // Just add another one and return
        int child_place = (key <  parent->child_max[0] )? 0
                                    : ((key <  parent->child_max[1])? 1 : 2);
        parent->childs.insert(parent->childs.begin() + child_place, node);
        // Update children max
        //parent->child_max.insert(parent->child_max.begin()+child_place, key);

        update_childs_max(node);
        return;
    }

    // Find palce and add element
    int child_place = (key < parent->child_max[0])? 0
                               : ((key < parent->child_max[1] )? 1
                                   : (((key < parent->child_max[2])? 2 : 3)));

    parent->childs.insert(parent->childs.begin() + child_place, node);
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
        const auto child_place =
                std::find(grandpa->childs.begin(),grandpa->childs.end(),parent);
        if (child_place == grandpa->childs.end())
            std::cout << "ALERT\n";

        // Past new childs
        const auto child_place_insert =  grandpa->childs.erase(child_place);
        const auto child_new = std::vector<std::shared_ptr<ttt::Node>>({left_node,right_node});
        grandpa->childs.insert(child_place_insert,child_new.begin(),child_new.end());

        // Update max child
        grandpa->update_child_max();

        // Continue to split
        parent = grandpa;

    }

    // Update max child for all nodes to the root
    update_childs_max(parent);
}


/*
 * Return node
 * which is closest neighbor
 * of given node
 * params:
 *          node - given node
 * return:
 *          closets neighbor of given node
 */
std::shared_ptr<ttt::Node> ttt::Two_thee_tree::find_nearest_brother(std::shared_ptr<ttt::Node> node, Mode mode)
{
    // If parent is most left node for grand parent ->
    //            closest brother is in the right
    // If parent is most right node for grand parent ->
    //            closest brother is in the right
    // If parent is in the middle of grand parent childs vector ->
    //            it doesn't matter (right in our case)
    if(node->parent == nullptr)
        return nullptr;
    auto node_pos = std::distance(node->parent->childs.begin(),
        std::find(node->parent->childs.begin(),node->parent->childs.end(),
                  node));

    if (mode == some)
    {
        auto pos_nn = (node_pos + 1 == node->parent->childs.size())?
                                                                       node_pos - 1:
                                                                       node_pos + 1;
        return node->parent->childs[pos_nn];
    }

    if (mode == right)
        return (node_pos + 1 == node->parent->childs.size())? nullptr : node->parent->childs[node_pos+1];
    if (mode == left)
        return (node_pos > 0)? node->parent->childs[node_pos-1] : nullptr;


}

/*
 * Recalculate child max
 * when one node is separated
 * on two nodes
*/
bool ttt::Node::update_child_max()
{
    auto childs_max_old = child_max;
    // If child is a leaf
    auto value = (!childs[0]->childs.size())?
                [](Node x) -> double {return x.key;} : // just save key
                ///ERROR HERE
                [](Node x) -> double {
        return *std::max_element(x.child_max.begin(),x.child_max.end());}; // else save the max of child_max list

    child_max.clear();
    for(auto &ch : childs)
        child_max.push_back(value(*ch.get()));

    return ! std::equal(child_max.begin(),child_max.end(),childs_max_old.begin(),childs_max_old.end());
}

/*
 * Swap childs list to given list
 * without child_max recalculation
 * params:
 *          childs - given vector of nodes
 */
void ttt::Node::change_childs(std::vector<std::shared_ptr<Node>> &&childs_)
{
    childs.clear();
    auto ref = shared_from_this();
    for(auto &ch : childs_)
    {
        childs.push_back(std::shared_ptr<Node>(ch));
        ch->parent = ref;
    }
}

std::shared_ptr<Segment> Node::get_value_shrd_ptr(std::shared_ptr<Node> n)
{
    return (n == nullptr)? nullptr : n->value;
}
