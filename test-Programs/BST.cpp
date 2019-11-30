//
//  graph.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/10/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <queue>


using namespace std;

class node {

public:
    
    node *left;
    node *right;
    node *parent;
    int value;
    int hd; // horizontal distance required for vertical traversal
    
    node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {};
};

class BST {
public:
    
    node *root;
    static node *leftMostNode(node*);
    static node *nextNode(node*);
    //static template<typename T> T* createBST(int arr[], int, int);
    //static template<> node *createBST<node>(int arr[], int, int);
    static void inOrderTraversal(node*);
    static bool isBST(node *root);
    static bool isBST(node *root, int min, int max);
};


template <typename T>
T* createBST(int arr[], int low, int high) {
    if (low > high) return nullptr;
    
    int mid = (low + high)/ 2;
    T *midnode = new T(arr[mid]);
    
    T *leftnode = createBST<T>(arr, low, mid - 1);
    T *rightnode = createBST<T>(arr, mid + 1, high);
    midnode->left = leftnode;
    midnode->right = rightnode;
    return midnode;
}

template <>
node* createBST<node>(int arr[], int low, int high) {
    if (low > high) return nullptr;
    
    int mid = (low + high)/ 2;
    node *midnode = new node(arr[mid]);
    
    node *leftnode = createBST<node>(arr, low, mid - 1);
    node *rightnode = createBST<node>(arr, mid + 1, high);
    midnode->left = leftnode;
    midnode->right = rightnode;
    
    if (leftnode) {
        leftnode->parent = midnode;
    }
    if (rightnode) {
        rightnode->parent = midnode;
    }
    return  midnode;
}


node*  BST::leftMostNode(node *root)
{
    
    node *node = root;
    while (node->left) {
        node = node->left;
    }
    return node;
}

void BST::inOrderTraversal(node *root) {
    
    if (!root) return;
    
    if (root->left)
        inOrderTraversal(root->left);
    
    cout << " " << root->value;
    
    if (root->right)
        inOrderTraversal(root->right);
}
// Iterative solution to inorder traversal -
// Push elements of the left subtree in the stack - top will be the leftmost node.
// for each node popped from the stack, push that node to the vector and then move to the
// right sub-tree of the node.

void BST::inorderTraversal (vector<int>& nodes, node* root) {
    stack<node*> todo;
    while (root || !todo.empty()) {
        while (root) {
            todo.push(root);
            root = root -> left;
        }
        root = todo.top();
        todo.pop();
        nodes.push_back(root -> val);
        root = root -> right;
    }
    return;
}


// Write an algo to get the next node in the BST - Binary search tree.

node* BST::nextNode (node *root) {
//
//  if node has a right sub-tree, return the left most node in the right sub-tree.
//  If node does not have a right sub-tree, traverse up the parent till we get to the
//  left node of the parent.
    node *node = root;
    if (node->right) {
        return leftMostNode(node->right);
    } else {
        // traverse up till we get to the the left node of the parent.
        while (node->parent && node->parent->right == node) {
            node = node->parent;
        }
        return node;
    }
}


// Write an algo to check if the BST is balanced:
//        Left and Right subtree height differ by no more than 1.
//        Get the height of the Sub tree: get the height of the ST + 1;

int getHeight(node *root) {
    if (!root) return -1;
    
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

bool isBalanced(node *root) {
    return std::abs(getHeight(root->left) - getHeight(root->right)) <= 1;
}

bool BST::isBST (node *root) {
    return isBST(root, 0, 0);
}
bool BST::isBST (node *root, int min, int max) {
    // handle null case
    if (!root) {
        return true;
    }
    // check for the min and max
    if ((min && root->value < min) || (max && root->value >= max)) {
        return false;
    }
    // recurse
    if (!isBST(root->left, min, root->value) ||
        !isBST(root->right, root->value, max)) {
        return false;
    }
    return true;
}
// Is T1 subtree of T2?

// Claim: If t1 and t2 are identical binary trees then, their string representation of
//        pre-order traversal (with null nodes marked as X) is identical.
//        reverse claim: If theie string rep is identical then they are identical BTs.


void getOrderString(node *root, string &str)
{
    if (root == NULL) {
        str += 'X';
    }
    str += to_string(root->value);
    getOrderString(root->left, str);
    getOrderString(root->right, str);
}

bool containsTree(node *t1, node *t2)
{
    string str1 = "";
    string str2 = "";
    
    getOrderString(t1, str1);
    getOrderString(t2, str2);
    
    return (str1.find(str2) != std::string::npos);
}


// Random Node: You are implementing a binary search tree class from scratch, which, in addition to insert, find, and delete, has a method getRandomNode()
//  which returns a random node from the tree. All nodes should be equally likely to be chosen.
//  We dont know the size of the tree hence it is difficult to get the range for which random number is desired.
//  Soution: Store size in every node in the BST. pick the random number i and i should match the in-order traversal index.

#if GETRANDOMNODE
node * getRandomNode(node *root, int rand) {
    
    if (rand == left.size() + 1) {
        return root;
    } else if (rand > left.size() + 1) {
        // get to the right sbt
        getRandomNode(root->right, rand);
    } else {
        getRandomNode(root->left, rand - (left.size() + 1));
    }
}
#endif


// Paths with Sum: You are given a binary tree in which each node contains an integer value (which might be positive or negative).
// Design an algorithm to count the number of paths that sum to a given value.The path does not need to start or end at the root or a leaf, but
// it must go downwards (traveling only from parent nodes to child nodes).

// RunningSum_x = RunningSum_y - TargetSum ==> Use this principle to get the sub-paths having the same targetSum


// TopView of the BST - Breadth first search of the BST and then store the map of the <horizontal-distance, node*> so that
// Very first node seen with the same HD gets viewed rather than the subsequent elements.

void topView (node * root) {
    // Breadth first traversal so that nodes at higher levels get viewed before nodes at lower levels.
    
    queue<node*> bfs_queue;
    map<int, node*> hd_map;
    
    if (!root) {
        return;
    }
    root->hd = 0;
    // root node is having HD as zero
    bfs_queue.push(root);
    
    // traverse through the queue and push back nodes in the queue as we traverse
    while (bfs_queue.size()) {
        node *running = bfs_queue.front();
        
        if (hd_map.count(running->hd) == 0) {
            // no node with that HD
            hd_map[running->hd] = running;
        }
        if (running->left) {
            // if left node add it to the queue post HD update
            running->left->hd = running->hd - 1;
            bfs_queue.push(running->left);
        }
        if (running->right) {
            // if right node add it to the queue post HD udpate
            running->right->hd = running->hd + 1;
            bfs_queue.push(running->right);
        }
        // remove the front node from the Q
        bfs_queue.pop();
    }
    // hd_map is now ready with the top view of nodes for all HDs.
    for (auto i : hd_map) {
        cout << " " << i.second->value;
    }
}


// in-place conversion of BST to sorted DLL
// in-order traversal and then keep the prev node pointer so that
// we can make the prev and next accordingly.


class dllnode {
public:
    int value;
    dllnode *left;
    dllnode *right;
    
    dllnode(int val) : value(val) {};
    
    void traverse (dllnode *head) {
        dllnode *n = head;
        cout << "The sorted DLL is: " << endl;
        while (n) {
            cout << " " << n->value;
            n = n->right;
        }
        cout << endl;
    }
    
};

void BST2SDLL (dllnode *root, dllnode **head) {
    
    if (!root) {
        return;
    }
    
    static dllnode *prev = NULL;
    
    BST2SDLL(root->left, head);
    
    // Set the node pointers right
    root->left = prev;
    if (prev) {
        prev->right = root;
    } else {
        *head = root;
    }
    prev = root;
    
    BST2SDLL(root->right, head);
    
}


// LCA - Least common Ancestor
// LCA (node * root, node *p, node *q)
// Traverse from root, figuring out if P & Q lie on the same side of the subtree.
// Which ever node, their sub-tree diverges ( one on left and other on right ), that
// is the LCA.

// bool covers(node *root, node *p) {
//     if (!root || !p) return false;
//     if (root == p) return true;
//     return covers(root->left, p) || covers(root->right, p);
// }

// node * getLCA(node *root, node *p, node *q) {
//    bool pisonLeft = covers(root.left, p);
//    bool qisonLeft = covers(root->left, q);
//    if (pisonLeft != qisonLeft) {
//        // different side - LCA
//        return root;
//    }
//    getLCA(pisonLeft ? root->left : root->right, p, q);
// }

// node * LCA ( node * root, node *p,node *q) {
    // if one node is not in the tree
//    if (!covers(root, p) || !covers(root, q)) {
//        return NULL;
//    }
//     return getLCA(root, p, q);
// }


//////////////////
// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
//
// For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

//    1
//   / \
//   2   2
//  / \  / \
//  3  4 4  3
///////////////


// bool isSymmetric(node *root) {
//     if (!root) return true;
//     return helper(root->left, root->right);
// }

// bool helper(node* p, node* q) {
//     if (!p && !q) {
//         return true;
//     } else if (!p || !q) {
//         return false;
//     }
//
//     if (p->val != q->val) {
//         return false;
//     }
//
//     return helper(p->left,q->right) && helper(p->right, q->left);
// }

// non-recursive solution for symmetry BT - Store in-order sequence of the Left Subtree
//            and then in-order of right subtree should match the pop sequence of the stack.


vector<vector<int>> levelOrder(node* root) {
    queue<node*> bft_q;
    vector<vector<int>> finalvec;
    // BFT -
    if (!root) {
        return vector<vector<int>>();
    }
    bft_q.push(root);
    bft_q.push(NULL);
    vector<int> intvec = {root->value};
    finalvec.push_back(intvec);
    intvec.clear();
    while (!bft_q.empty()) {
        // pop the node and create a new vector for this level
        node *node = bft_q.front();
        if (node && node->left) {
            intvec.push_back(node->left->value);
            bft_q.push(node->left);
        }
        if (node && node->right) {
            intvec.push_back(node->right->value);
            bft_q.push(node->right);
        }
        if (bft_q.front() == NULL) {
            // reached marker - flush the vector and add new node to the Q
            finalvec.push_back(intvec);
            intvec.clear();
            if (bft_q.size() > 1) {
                bft_q.push(NULL);
            }
        }
        bft_q.pop();
    }
    return finalvec;
}



node *buildTree (vector<int> &preorder, vector<int> &inorder) {
    // cache the inorder map of value to index: value->index
    map<int, int> iomap;
    int i = 0;
    for (auto val : inorder) {
        iomap.insert(pair<int, int>(val, i));
    }
    create(preorder, inorder, iomap, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

node *create(vector<int>& preorder, vector<int> &inorder, map<int, int>& iomap,
             int ps, int pe, int is, int ie) {
    if (ps > pe) {
        return nullptr;
    }
    node *node = new node(preorder[ps]);
    map<int, int>::iterator it;
    if ((it = iomap.find(node->value)) != iomap.end()) {
        // found the root
        pos = *it;
    } else {
        assert(0);
    }
    node->left = create(preorder, inorder, iomap, ps + 1, ps + pos - is, is, pos - 1);
    node->right = create(preorder, inorder, iomap, pe - ie + pos + 1, pe, pos + 1, ie);
    return node;
}


// Construct Binary Tree from Preorder and Inorder Traversal

/********************************************************************************

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

TreeNode* create(vector<int>& preorder, vector<int>& inorder, int ps, int pe, int is, int ie){
    if(ps > pe){
        return nullptr;
    }
    TreeNode* node = new TreeNode(preorder[ps]);
    int pos;
    for(int i = is; i <= ie; i++){
        if(inorder[i] == node->val){
            pos = i;
            break;
        }
    }
    node->left = create(preorder, inorder, ps + 1, ps + pos - is, is, pos - 1);
    node->right = create(preorder, inorder, pe - ie + pos + 1, pe, pos + 1, ie);
    return node;
}
The first element in preorder array can divide inorder array into two parts.
 Then we can divide preorder array into two parts. Make this element a node.
 And the left sub-tree of this node is the left part, right sub-tree of this
 node is the right part. This problem can be solved following this logic.

 
 IO : [1,2,3,4,5,6,7]
 PO:  [4,2,1,3,6,5,7]
 
 step-1: partition IO and PO as follows. root as [4]
 IO : LS as [1,2,3] and RS as [5,6,7]
 PO:   LS as [2,1,3] and RS as [6,5,7]
 
**********************************************************************************/




int main() {
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    vector<int> nums = {-10,-3,0,5,9};
    dllnode *head = NULL;
    node *root = createBST<node>(arr, 0, 10);
    node *newBst = createBST<node>(nums.data(), 0, 4);
    dllnode *root1 = createBST<dllnode>(arr, 0, 10);
    // BST to DLL
    BST2SDLL(root1, &head);
    head->traverse(head);
    // Check inorder traversal
    BST::inOrderTraversal(root);
    BST::inOrderTraversal(newBst);
    // next node of the root
    node *next = BST::nextNode(root);
    cout << "next node is " << next->value;
    // isBst
    string bst = BST::isBST(root) == true ? "Yes" : "No";
    cout << "is BST:" << bst;
    cout << "Top View: " << endl;
    // topView
    topView(root);
    // Level Order
    vector<vector<int>> vec = levelOrder(root);
    for (auto v : vec) {
        cout << "[";
        for (auto i : v) {
            cout << " " << i;
        }
        cout << "]" << endl;
    }
    
}
