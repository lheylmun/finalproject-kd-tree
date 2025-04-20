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

    kd_node* newPatient(new kd_node); //create a pointer for the new kd_node
    newPatient->patientData[k] = data; //update patientData based on input data
    newPatient->treatmentType = treatment; //update treatmentType based on input treatment
    newPatient->ihotScore = ihot; //update ihotScoew based on input ihot

    newPatient->deleted = false; //initialize deleted bool to false
    newPatient->left = nullptr; //initialize left child to null
    newPatient->right = nullptr; //initalize right child to null
}

void KDT::insert_node(kd_node* new_node) {
    if (new_node == nullptr) { 
        return; //exit if node is empty
    }

    if (root == nullptr) {
        *root = new_node; //if root is empty, new_node becomes root
        return;
    }

    if (node_exists(*new_node->patientData) == true) {
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


//private function to find the depth of a tree 
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
void KDT::delete_nodes(kd_node* node) {
    if (node == nullptr) { //base case
        return; 
    }
    //recursively delete all left and right children
    delete_nodes(node->left); 
    delete_nodes(node->right);
}