#ifndef KD_TREE_H__
#define KD_TREE_H__

#include <memory>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const int k = 11;

//kd_node is the k-d tree node structure 
struct kd_node {
    vector<int> patientData[k]; //vector to store patient demographics and radiographic variables
    string treatmentType; //string to store treatment type, NOT USED FOR SPLITTING
    float ihotScore; //float to store baseline iHOT-12 score, NOT USED FOR SPLITTING

    kd_node* left; //pointer to left subtree
    kd_node* right; //pointer to right subtree
};

class KDT {
public:
    //Constructur - initializes class variables and pointers 
    KDT();

    //Deconstructor - clean memory used by KD_TREE but not returned with 'delete'
    ~KDT();

    //new_node intializes a new kd_node from the heap with the given inputs and two null children. 
    //returns a pointer to the new node
    kd_node* new_node(vector<int> data, string treatment, float ihot);

    //insert_node creates a new node with the given node inserts it into the correct position in the tree
    //node must be created with new_node before it can be inserted. insert_node only takes a pointer as an input.
    void insert_node(kd_node* new_node);

    //REVIEW possible inclusion of delete_node to remove a node from the KDT. Method is lazy deletion. Consider adding 
    //a boolean to indicate if a node is included in the tree or not. 
    void delete_node(vector<int> target);

    //node_exists searches the nodes in the current KDT. Returns true if a node matching the input node is found and false otherwise.
    //may be called with insert_node function to ensure duplicate nodes are not inserted in the KDT.
    bool node_exists(vector<int> target);

    //NN_search finds the node in KDT that is closest to a given input. Will use recursive search method with 
    //backtracking
    kd_node* NN_search(vector<int> target);

    //kNN_search finds the k closest neightbors to a target node.
    vector<kd_node*> kNN_search(vector<int> target, int numNeighbors);

    //range_search returns all nodes within a specified k-dimensional range 
    vector<kd_node*> range_search(vector<int> lowerBound, vector<int> upperBound);

private:

    kd_node* root;

};

#endif //KD_TREE_H__
