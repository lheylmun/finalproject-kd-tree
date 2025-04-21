#include "k-d tree.h"
#include <iostream>

//Constructor for k-d tree
KDT::KDT() {
    root = new kd_node*;
    *root = nullptr;
}

//Deconstructor for k-d tree
KDT::~KDT() { 
    delete_nodes(*root); //frees memory of all nodes in KDT
}

kd_node* KDT::new_node(vector<int> data, string treatment, float ihot) {
    //create new kd_node with specified inputs

    kd_node* newPatient = new kd_node; //create a pointer for the new kd_node
    
    for (int i = 0; i < k; i++) {
        newPatient->patientData[i] = data[i];
    }

    newPatient->treatmentType = treatment; //update treatmentType based on input treatment
    newPatient->ihotScore = ihot; //update ihotScoew based on input ihot

    newPatient->deleted = false; //initialize deleted bool to false
    newPatient->left = nullptr; //initialize left child to null
    newPatient->right = nullptr; //initalize right child to null
}

kd_node* KDT::node_exists(vector<int> target, kd_node* root) {
    //searches for a node that matches the target input to determine if the target already
    //exists in the tree 
    if (root == nullptr) {
        return nullptr;
    }

    kd_node* cursor = root; //create and initialize cursor to root 
    
    while (cursor != nullptr) { //while cursor is valid
        
        if (cursor->patientData == target) { //check if cursor node patientData matches target data
            return cursor; //return true if match is detected
        }
        
        unsigned currDimension = find_depth(cursor) % k; //find current dimension based on location in tree
        if (target[currDimension] < cursor->patientData[currDimension]) { //if value of target at current dimension is smaller
            cursor = cursor->left; //search left subtree
        }
        else {
            cursor = cursor->right; //otherwise, search right subtree
        }
    }
    return nullptr; //return false if no match is found 
}

void KDT::insert_node(kd_node* new_node) {
    if (new_node == nullptr) { 
        return; //exit if node is empty
    }

    if (root == nullptr) {
        *root = new_node; //if root is empty, new_node becomes root
        return;
    }

    if (node_exists(new_node->patientData, *root) != nullptr) {
        return; //if node is already in tree, return current tree
    }

    //otherwise, proceed with inserting new_node into KDT
    kd_node* cursor = *root; //set cursor to root of tree
    kd_node* parent = nullptr; //set parent to nullptr for now
    unsigned currDimension;

    while (cursor != nullptr) { //traverse through tree while cursor is valid
        
        //find current dimensions of kd tree
        currDimension = find_depth(cursor) % k; //find current dimension of tree
        
        parent = cursor; //update parent to current position

        if (new_node->patientData[currDimension] < cursor->patientData[currDimension]) {
            //if value of patientData in newNode at current dimension is less than the cursor
            //traverse to the left subtree
            cursor = cursor->left;
        }
        else {
            //otherwise, traverse right subtree because value of new_node at current dimension is >= cursor
            cursor = cursor->right;
        }
    } //end of while loop, cursor will be null, parent will store prev cursor position

    if (new_node->patientData[currDimension] < parent->patientData[currDimension]){
        //if value of new node at current dimension is less than parent
        parent->left = new_node; //insert on the left
    }
    else {
        parent->right = new_node; //insert on the right
    }
}

void KDT::remove_node(vector<int> target, kd_node* root) {
    if (root == nullptr) { //tree is empty
        return; //exit function
    }
    if (node_exists(target, root) == nullptr) { //node does not exist in tree
        return; //exit function
    }
    else { //tree is not empty and contains the node
        kd_node* delete_node = node_exists(target, root); //store node being deleted
        delete_node->deleted = true; //update boolean to true
    }
    return;
}
 
vector<kd_node*> kNN_search(vector<int> target, int numNeighbors) {
    //bookmark


}


//private function - find the depth of a tree 
//called in insert_node, node_exists
int find_depth(kd_node* node) {
    if (node == nullptr) {
        return 0; //return 0 if node is null
    }
    
    //recursively traverse left and right trees, adding 1 with each iteration
    int left_depth = find_depth(node->left);
    int right_depth = find_depth(node->right);

    //return depth of tree 
    return max(left_depth, right_depth) + 1;
}

//private function - free memory occupied by nodes in KDT 
//called in deconstructor
void KDT::delete_nodes(kd_node* node) {
    if (node == nullptr) { //base case
        return; 
    }
    //recursively delete all left and right children
    delete_nodes(node->left); 
    delete_nodes(node->right);
}