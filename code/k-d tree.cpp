#include "k-d tree.h"
#include <iostream>
#include <cmath>

//Constructor for k-d tree
KDT::KDT() {
    root = new kd_node*;
    *root = nullptr;
}

//Deconstructor for k-d tree
KDT::~KDT() { 
    delete_nodes(*root); //frees memory of all nodes in KDT
}

//PUBLIC FUNCTIONS

kd_node* KDT::new_node(vector<int> data, string treatment, float ihot) {
   

    kd_node* newPatient = new kd_node; //create a pointer to new kd_node in heap
    
    //iterates through each variable stored in data input vector
    for (int i = 0; i < k; i++) {
        newPatient->patientData[i] = data[i]; //updates patientData vector within node with data values
    }

    newPatient->treatmentType = treatment; //updates treatmentType based on input treatment
    newPatient->ihotScore = ihot; //updates ihotScore based on input ihot

    newPatient->deleted = false; //initializes deleted bool to false
    newPatient->left = nullptr; //initializes left child to null
    newPatient->right = nullptr; //initalizes right child to null

    return newPatient;
}

kd_node* KDT::node_search(vector<int> target, kd_node* root) {
    //checks if current tree is empty
    if (root == nullptr) {
        return nullptr; //return null 
    }

    //otherwise, tree contains at least 1 node 

    kd_node* cursor = root; //creates cursor for tree traversal initialized to the root
    
    //iterates until null pointer is reached
    while (cursor != nullptr) { 
        
        //checks if cursor node patientData matches target data
        if (cursor->patientData == target) { 
            return cursor; //returns matching node if found
        }
        
        unsigned currDimension = find_depth(cursor) % k; //finds current dimension based on location in tree
        
        //checks if value of target node at current dimension is less than value of current node at current dimension
        if (target[currDimension] < cursor->patientData[currDimension]) { 
            cursor = cursor->left; //traverse left subtree
        }
        else { //otherwise, value of target node at current dimension is >= current node
            cursor = cursor->right; //traverse right subtree
        }
    } //end of while loop, if met no node match was found
   
    return nullptr; //return false 
}

void KDT::insert_node(kd_node* new_node) {
    //checks if the node being inserted is empty
    if (new_node == nullptr) { 
        return; //if empty, exit
    }

    //checks if tree is empty
    if (root == nullptr) {
        *root = new_node; //if root is empty, new_node becomes root
        return; //exit
    }

    //checks if node being added is a duplicate 
    if (node_exists(new_node->patientData, *root)) { 
        return; //if node is already in tree, exit
    }

    //if all checks are false, proceed with adding new_node to current tree

    kd_node* cursor = *root; //creates cursor for traversal initialized to current tree root
    kd_node* parent = nullptr; //creates parent node pointer intialized to null
    unsigned currDimension = 0; //creates unsigned integer to track current dimension in tree while looping

    //iterate until cursor reaches null node
    while (cursor != nullptr) {
        
        //find current dimensions of kd tree
        currDimension = find_depth(cursor) % k; //find current dimension of tree
        
        parent = cursor; //updates parent pointer to current cursor position

        //checks if value in new node indexed at current dimension is less than value at current index in cursor node
        if (new_node->patientData[currDimension] < cursor->patientData[currDimension]) {
            //if value of patientData in new node at current dimension is less than the cursor
            
            cursor = cursor->left; //traverse left subtree
        }
        else { //otherwise, value of current dimension in new node is >= value of cursor node at current dimension index
            
            cursor = cursor->right; //traverse right subtree
        }
    } //end of while loop, cursor will be null, parent stores last valid node traversed 

    currDimension = find_depth(parent) % k; //ensures current dimension is calculated based on parent location 

    //checks if value at current dimension index of new node is less than value of current dimension in parent
    if (new_node->patientData[currDimension] < parent->patientData[currDimension]){
        //if value of new node at current dimension is less than parent
        parent->left = new_node; //insert on the left
    }
    else { //otherwise, value at current dimension in new node is >= parent node
        parent->right = new_node; //insert on the right
    }
} 

void KDT::remove_node(vector<int> target, kd_node* root) {
    //lazy deletion implementation
    
    //checks if current tree is empty
    if (root == nullptr) {
        return; //exit 
    }

    //checks if node being removed exists
    if (!node_exists(target, root)) { 
        return; //exit if no match is found
    }
    //otherwise, tree is not empty and contains the target node
    else {
        kd_node* delete_node = node_search(target, root); //finds targeted node
        delete_node->deleted = true; //updates deleted boolean to true
    }
    return;
}
 
kd_node* KDT::NN_search(vector<int> target) {

}





void KDT::print_tree(kd_node* root, int& nodeID) {
    //checks if current tree is empty
    if (root == nullptr) {
        return; //exit
    }

    //otherwise, tree is not empty 
    print_tree(root->left, nodeID); //recurses left subtree

    //iterates through each data point in patientData
    cout << "Node: " << nodeID << "Radiographic Measurements: "; //prints node label, current node index, and measurement label
    for (int i = 0; i < k; i++) {
        cout << root->patientData[i]; //prints value of patientData at current index
        if (i < k - 1) cout << ", "; //if current index is < k, prints a comma following the number
    }
        
    cout << endl; //prints a new line
    nodeID++; //increments nodeID before traversling next node

    print_tree(root->right, nodeID); //recurses right subtree
}

//PRIVATE FUNCTIONS

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

bool KDT::node_exists(vector<int> target, kd_node* root) {
   if (node_search(target, root) == nullptr) { 
        return true;
    }
    else {
        return false;
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