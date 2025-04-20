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







//private function - free memory occupied by nodes in KDT 
void KDT::delete_nodes(kd_node* node) {
    if (node == nullptr) { //base case
        return; 
    }
    //recursively delete all left and right children
    delete_nodes(node->left); 
    delete_nodes(node->right);
}