#ifndef KD_TREE_H__
#define KD_TREE_H__

#include <memory>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const int k = 10;

//kd_node is the k-d tree node structure 
struct kd_node {
    vector<int> patientData; //vector to store patient demographics and radiographic variables
    float ihotScore; //float to store baseline iHOT-12 score, NOT USED FOR SPLITTING
    
    bool isLeftChild;
    bool deleted;

    kd_node* parent;
    kd_node* left; //pointer to left subtree
    kd_node* right; //pointer to right subtree
};

class KDT {
public:
    //Constructur - initializes class variables and pointers 
    KDT();

    //Deconstructor - cleans memory
    ~KDT();

    //new_node intializes a new kd_node with the given inputs, false boolean, and two null children. 
    //returns a pointer to the new node.
    kd_node* new_node(vector<int> data, float ihot);

    //node_exists searches the nodes in the current KDT. Returns a pointer to the matching node if it exists and null otherwise.
    //may be called with insert_node function to ensure duplicate nodes are not inserted in the KDT.
    //May also be used independently to determine if an exact match for the target exists in the KDT. Takes a target
    //vector as an input and returns pointer to the matching node if it exists.
    kd_node* node_search(vector<int> target);

    //insert_node inserts a new node into the correct position in the tree
    //node must be created with new_node before it can be inserted. insert_node only takes a pointer as an input.
    //Does not return an output, but the KDT is updated with the new node in it.
    void insert_node(kd_node* new_node);

    //insert_new_node combines the functions new_node and insert_node. When called, this function creates a new node 
    //containing the input data and ihot values. Then it inserts the new node into the current k-d tree.
    void insert_new_node(vector<int> data, float ihot);

    //delete_node employs lazy deletion. Searches for the node if it exists and updates deleted boolean to false if 
    //node is found. Takes a target vector as an input and updates the node but does not return anything. 
    void remove_node(vector<int> target, kd_node* root);

    //size finds and returns the size of the current k-d tree
    int size();

    //get_root finds and returns the root (node 0) of the current k-d tree. Needed for testing since root is a private member function
    kd_node* get_root();
    
    //NN_search finds the node in KDT that is closest to a given input. Will use recursive search method with 
    //backtracking. Takes a target vector as an input and returns a kd_node pointer to the kd_node nearest to 
    //the specified input data.
    kd_node* NN_search(kd_node* root, vector<int> target, double& minDist, kd_node*& nearestNeighbor);

    //kNN_search finds the k closest neightbors to a target node. Takes a target vector as an input and the desired numebr of neighbors.
    //returns a vector of kd_node pointers to the number of neighbors nearest to the target.
    vector<kd_node*> kNN_search(vector<int> target, int numNeighbors);

    //range_search returns all nodes within a specified k-dimensional range. Takes integer vectors as inputs for
    //the upper and lower bounds. Returns a vector of kd_node pointers that are within the specified range.
    vector<kd_node*> range_search(vector<int> lowerBound, vector<int> upperBound);

    //get_ihot locates the node containing the specified target data within the current k-d tree and returns the ihot score of the node
    //returns 0 if node is not found in the tree
    int get_iHOT(vector<int> target);

    void print_tree();

private:
    //double pointer that always points to the root pointer of the tree
    kd_node** root;

   
    //tree_depth searches the tree and returns the current depth of the tree
    int find_depth(kd_node* node);

   //exists_bool converts the output of node_exists from a kd_node to a boolean 
    bool node_exists(vector<int> target);

    //euclidean_distance calculates the square root of the sum of squared distances between two vectors
    double euclidean_distance(kd_node* root, vector<int> target);

    //print_tree performs in order traversal to print the tree
    void print(kd_node* root, int& nodeID, int depth);

    //delete_nodes frees the memory currently being used by the KDT by deleting existing nodes
    //called in the KDT deconstructor
    void delete_nodes(kd_node* node);

};

#endif //KD_TREE_H__
