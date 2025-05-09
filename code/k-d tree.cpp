#include "k-d tree.h"
#include <iostream>
#include <cmath>
#include <vector>

//Constructor for k-d tree
KDT::KDT() {
    root = new kd_node*;
    *root = NULL;
}

//Deconstructor for k-d tree
KDT::~KDT() { 
    delete_nodes(*root); //frees memory of all nodes in KDT
}

//PUBLIC FUNCTIONS

kd_node* KDT::new_node(vector<int> data, float ihot) {
   

    kd_node* newPatient(new kd_node); //creates a pointer to new kd_node in heap
    
    newPatient->patientData = data; //updates patientData vector within node with data values
    newPatient->ihotScore = ihot; //updates ihotScore based on input ihot

    newPatient->isLeftChild = false; //initializes isLeftChild boolean to false

    newPatient->left = nullptr; //initializes left child to null
    newPatient->right = nullptr; //initalizes right child to null
    newPatient->parent = nullptr; //initializes parent pointer to null

    return newPatient;
}

kd_node* KDT::node_search(vector<int> target) {
    //checks if current tree is empty
    if (root == nullptr) {
        return nullptr; //return null 
    }

    //otherwise, tree contains at least 1 node 

    kd_node* cursor = *root; //creates cursor for tree traversal initialized to the root
    int depth = 0; //creates variable to store current depth as loop iterates
    int currDimension = 0; //creates variable to store current dimension as loop iterate
    
    //iterates until null pointer is reached
    while (cursor != nullptr) { 
        
        //checks if cursor node patientData matches target data
        if (cursor->patientData == target) { 
            return cursor; //returns matching node if found
        }
        
        currDimension = depth % k; //finds current dimension based on location in tree
        
        //checks if value of target node at current dimension is less than value of current node at current dimension
        if (target[currDimension] < cursor->patientData[currDimension]) { 
            cursor = cursor->left; //traverse left subtree
        }
        else { //otherwise, value of target node at current dimension is >= current node
            cursor = cursor->right; //traverse right subtree
        }

        depth++; //increments depth before next iteration 

    } //end of while loop, if met no node match was found
   
    return nullptr; //return false 
}

void KDT::insert_node(kd_node* new_node) {
    //checks if the node being inserted is empty
    if (!new_node) { 
        return; //if empty, exit
    }

    //checks if tree is empty
    if (*root == NULL) {
        *root = new_node; //if root is empty, new_node becomes root
        return; //exit
    }

    //checks if node being added is a duplicate 
    if (node_exists(new_node->patientData)) { 
       return; //if node is already in tree, exit
    }

    //if all checks are false, proceed with adding new_node to current tree

    kd_node* cursor = *root; //creates cursor for traversal initialized to current tree root
    kd_node* parent = NULL; //creates parent node pointer intialized to null
    int depth = 0; //creates integer to track current depth in tree while looping
    int currDimension = 0; //creates integer to track current dimension for split while looping through tree 

    //iterate until cursor reaches null node
    while (cursor != NULL) {
        currDimension = depth % k; //updates current dimension based on current depth
        parent = cursor; //updates parent pointer to current cursor position

        //checks if value in new node indexed at current dimension is less than value at current index in cursor node
        if (new_node->patientData[currDimension] < cursor->patientData[currDimension]) {
            //if value of patientData in new node at current dimension is less than the cursor
            
            cursor = cursor->left; //traverse left subtree
        }
        else { //otherwise, value of current dimension in new node is >= value of cursor node at current dimension index
            
            cursor = cursor->right; //traverse right subtree
        }

        depth++; //increment depth before next iteration

    } //end of while loop, cursor will be null, parent stores last valid node traversed 


    //checks if value at current dimension index of new node is less than value of current dimension in parent
    if (new_node->patientData[currDimension] < parent->patientData[currDimension]){
        //if value of new node at current dimension is less than parent
        parent->left = new_node; //insert on the left
        new_node->parent = parent;
        new_node->isLeftChild = true;
    }
    else { //otherwise, value at current dimension in new node is >= parent node
        parent->right = new_node; //insert on the right
        new_node->parent = parent;
        new_node->isLeftChild = false;
    }
} 

void KDT::insert_new_node(vector<int> data, float ihot) {
    insert_node(new_node(data, ihot));
    return;
}

void KDT::remove_node(vector<int> target) {
    //lazy deletion implementation
    
    //checks if current tree is empty
    if (root == nullptr) {
        return; //exit 
    }

    //checks if node being removed exists
    if (!node_exists(target)) { 
        return; //exit if no match is found
    }
    
    //otherwise, tree is not empty and contains the target node

    //returns the node to be removed 
    kd_node* target_node = node_search(target);

    //checks if node is a leaf node by looking at children 
    if (target_node->right == nullptr && target_node->left == nullptr) {
       
        //checks if node being removed is the root
        if (target_node == *root) {
            *root = nullptr; //sets root to null
        }
        
        //checks if target_node is a left child
        else if (target_node->isLeftChild) {
            target_node->parent->left = nullptr; //updates parent of target_node's left pointer to null
        }
        
        else { //target_node is a right child
            target_node->parent->right = nullptr; //updates parent of target_node's right pointer to null
        }
        
        delete target_node; //frees memory occupied by target_node
        return; //exits function
    }

    //checks if target_node has a right child
    else if (target_node->left == nullptr && target_node->right != nullptr) {
        kd_node* child = target_node->right; //assigns target_node's right child to child pointer
        
        //checks if target_node is tree root 
        if (target_node == *root) {
            *root = child; //update root to target_node's right child
        }

        //checks if target_node is a left child
        else if (target_node->isLeftChild) {
            target_node->parent->left = child; //assigns target_node's parent left pointer to child 
        }

        else { //target_node is a right child
            target_node->parent->right = child;
        }

        delete target_node; //frees memory occupied by target node
        return; //exits function 
    }

    //checks if target_node has a left child
    else if (target_node-> left != nullptr && target_node->right == nullptr) {
        kd_node* child = target_node->left; //assigns target_node's left child to childpointer

        //checks if target_node is tree root
        if (target_node == *root) {
            *root = child; //updates root to target_node's left child
        }
        
        //checks if target_node is a left child
        else if (target_node->isLeftChild) {
            target_node->parent->left = child; //assigns left pointer of target_node's parent to child
        }
        else { //target node is a right child
            target_node->parent->right = child; //assigns right pointer of target_node's parent to child
        }
        delete target_node; //frees memory occupied by target_node
        return; //exits function
    }

    //target_node has two children
    else {
        kd_node* successor = target_node->right; //assigns target_node's right child as the successor;

        //iterates until null ptr is reached marking the end of the tree
        while (successor->left != nullptr) {
            successor = successor->left; //updates successor to the leftmost child of the right subtree
        }

        target_node = successor; //updates target node to successor 

        delete successor; //free memory occupied by successor
        return; //exits function
    }
    

}

int KDT::size() {
   return find_depth(*root);
}

kd_node* KDT::get_root() {
    //checks if tree is empty
    if (*root == NULL) {
        return nullptr; //returns null
    }
    return *root; //returns root 
}

void KDT::print_node_data(vector<int> target) {
    //checks if target data exists in current tree
    if (node_exists(target)){
         kd_node* target_node = node_search(target); //searches for node containing target data

        //prints data for current node
        cout << "iHOT-12 Score: " << target_node->ihotScore << " Data: ";  //prints iHOT-12 score and data label
        for (int i = 0; i < k; i++) { //iterates through each value in patientData
             cout << target_node->patientData[i]; //prints value at patientData index
            if (i < k - 1) {cout << ", "; } //prints comma for internal values, does not print comma after last value
        }
        cout << endl; //prints new line 
    }
    return; //exits function
}
    
kd_node* KDT::NN_search(kd_node* root, vector<int> target, double& minDist, kd_node*& nearestNeighbor) {
    //checks if tree is empty
    if (root == nullptr) {
        return nullptr; //return null
    }

    int currDimension = find_depth(root) % k; //finds depth of current tree
    double dist = euclidean_distance(root, target); //computes euclidean distance between current node and target data

    //checks if current distance is less than current minimum distance
    if (dist < minDist) {
        minDist = dist; //updates minimum distance to current distance
        nearestNeighbor = root; //updates nearest neighbor to current node
    }

    kd_node* next_node = nullptr; //initializes next node to null pointer
    kd_node* opp_node = nullptr; //initializes opposite node to nullptr
    
     //checks if value of target data at current dimension is less than current dimension value of patientData in current node
    if (target[currDimension] < root->patientData[currDimension]) {
        next_node = root->left; //updated next node to left child
        opp_node = root->right; //updates opposite node to right child
    } 

     //otherwise, value of target at current dimension is >= value at current dimension in current node
    else {
        next_node = root->right; //updates next node to right child
        opp_node = root->left; //updates opposite node to left child
    }

    NN_search(next_node, target, minDist, nearestNeighbor); //recurses NN search with next node

    double currentDimDist = target[currDimension] - root->patientData[currDimension]; //calculates the distance between target and node data in the current dimension
    //checks if square of the distance between target and node values in the current dimension is less than the current minimum distance
    if ((currentDimDist * currentDimDist) < minDist) {
        NN_search(opp_node, target, minDist, nearestNeighbor); //recurses NN search with opposite node
    }
        
    return nearestNeighbor; //returns pointer to nearest neighbor
}
    
void KDT::print_tree() {
    int nodeID = 0;
    print(*root, nodeID, 0);
}


//PRIVATE FUNCTIONS

int KDT::find_depth(kd_node* node) {
    if (node == nullptr) {
        return 0; //return 0 if node is null
    }
    
    //recursively traverse left and right trees, adding 1 with each iteration
    int left_depth = find_depth(node->left);
    int right_depth = find_depth(node->right);

    //return depth of tree 
    return left_depth + right_depth + 1; //computes sum of left_depth and right_depth + 1 to measure total tree depth
}

bool KDT::node_exists(vector<int> target) {
   if (node_search(target) == nullptr) { 
        return false;
    }
    else {
        return true;
    }
}

double KDT::euclidean_distance(kd_node* node, vector<int> target) {
    
    double distance = 0.0; //creates var distance to store distance calcualtions with type double
    
    //iterates through each index in patientData vector
    for (int i = 0; i < k; i++) {
        distance += (node->patientData[i] - target[i]) * (node->patientData[i] - target[i]); //computes squared distance between value at current index of node and target
    }
    double euclidean_dist = sqrt(distance); //calculates square root of sum of squared distances per euclidean distance equation

    return euclidean_dist;
}

void KDT::print(kd_node* root, int& nodeID, int depth) {
    //checks if current tree is empty
    if (root == nullptr) {
        return; //exit
    }

    int currDimension = depth % k;

    cout << "Node: " << nodeID
         << " | Depth: " << depth 
         << " | Split Dimension: " << currDimension;

    if (root->parent != nullptr) {
        cout << " | Parent " << root->parent->ihotScore;
    }
    else {
        cout << " | Parent NA";
    }

    cout << " | Left Child: " << (root->isLeftChild ? "Yes" : "No ")
         << " | iHOT-12: " << root->ihotScore
         << " | Data: ";
    for (int i = 0; i < k; i++) {
        cout << root->patientData[i]; //prints value of patientData at current index
        if (i < k - 1) cout << ", "; //if current index is < k, prints a comma following the number
    }
    cout << endl; //prints a new line

    nodeID++; //increments nodeID before traversling next node
    depth++;

    //otherwise, tree is not empty 
    print(root->left, nodeID, depth); //recurses left subtree
    print(root->right, nodeID, depth); //recurses right subtree
}

//only called by deconstructor - frees memory occupied by KD tree
void KDT::delete_nodes(kd_node* node) {

    if (node == nullptr) { //base case
        return; 
    }
    //recursively delete all left and right children
    delete_nodes(node->left); 
    delete_nodes(node->right);
}




