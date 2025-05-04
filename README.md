# finalproject-kd-tree

Background:

The goal of this project is implement a k-d tree as clinical support tool for to predict baseline symptom severity of patients with symptomatic hip pain based on past patients. Hip pain may arise from a wide spectrum underlying pathologies often involving complesx interactions between bony morphology, soft tissue structures and muscular dynamics. 

Radiographic imaging is the first clinical assessment tool for diagnosing hip pain. Computed Toomography (CT) scans provide detailed visualization of the anatomic structures of the hip, allowing surgeons to make accurate diagnosis and determine further treatment. Stryker HipMap (https://microapp.stryker.com/hipmap/) enhances these visualizations by generating interactive 3D models with heatmapping based on CT scan data. These models automate femoroacetabular morphology measurements providing quantitative information about a patient's anatomy. 

Predicting patient symptoms remains a challenge as many patients present with overlapping abnormalities. This project applies k-d trees as a symptom search tool based on age, sex, and femoracetabular morphology measurements. k-d trees enable fast nearest-neighbor searches with high dimensional data allowing for efficient searches of patients. This tool may be helpful to clinicians in estimating the burden of disease using only imaging data with potential impacts for clinical decision-making and expectation management.

Implentation Rationale: 

A k-d tree is a data structure that organizes points in k-dimensional spaces and are effective for performing efficient searches ofe multidimensional search keys. In this project, several pre-operative patient features will be stored for each patient including demographic and radiographic data. The k-d tree effectively allows for the organizaiton and searching of multidimensional data which fits the needs of this project as several preoperative features will be included for each patient. Additionally, this structure satisifies the goal of this project which is to output previously treated patietns who are similar to a current patient so the surgeon may compare. 

In a k-d tree, each node is a k-dimensional point. For the purposes of this project, each patient will be represented as a node with their associated features (demographics, readiographic measurements) stored as a vector within the node. iHOT scores are the intended outcome of this tree and thus are excluded from the k-vector. The intent is to use radiographic measurements to find ihot scores, not patients based on ihot scores themselves. Additionally, a pointer to the parent, left, and right child will be stored within a node to form the tree and provide information about node positioning. Lastly, booleans isLeftChild and deleted will be included in the node to give information about its existence in the tree and position.

The k-d tree will be organized by assessing each feature and dividing nodes depending on their value. The tree itself is not balanced. Nodes are added to the tree as the information is available. Nodes are split based on if they are smaller or larger than the current node's value in that dimension. Nodes contained in the left subtree will have values less than the value of the current node in the current dimension and the right subtree will have greater values. This method was chosen because nodes are be inserted one by one for this project. Additionally, the test file contains a maximum of 10 nodes. Given the small size of the dataset and dynamic nature of the data, balancing was not necessary. However, balancing based on the median would be necessary for analyzing 100+ patients. 

KD Tree Implementation Method:

- The axes used to split each pane will cycle as you move down the tree 
- Nodes in the left subtree will have values less than the current node 
- Nodes in the right subtree will have values greater than the current node

List of dimensions/data contained within the k-vector of each node:

Demographics:
1. Sex, boolean, 0 = female, 1 = male
2. Age, integer, range 18-65

Radiographic Measurements:
3. Lateral Center Edge Angle (LCEA), integer, range 0-60
4. Acetabular version @ 3:00 (AV3), integer, range -10-35
5. Tonnis Angle, integer, range -10-16
6. Acetabular coverage, integer, range 40-85
7. Alpha Angle (AA), integer, range 35-95
8. Femoral Torsion, integer, range -10-30
9. Femoral Neck Shaft Angle (FNSA), integer, range 120-175
10. Combind Version, integer, range 5-50

Additionally each node will contain the variables below. These variables will only be stored in the node and not used for splitting. 
1. Baseline iHOT12 score 
3. isLeftChild boolean to aid in determining position within tree
4. Parent pointer
5. Left child pointer
6. Right child pointer


This implementation includes several functions to add and remove nodes to the tree, search for specific nodes, find tree size, find tree root, perform nearest neighbor search and print the tree. Detailed function descriptions can be foound in the 'k-d tree.h' header file. 

The 'k-d tree.cpp' file contains the implementation of each function along with the constructor, deconstructor and private member functions. The performance of this program was tested using tests created in the 'test.cpp' file. The organization and testing of this project is similar to previous homework assignments. 


References: 

- https://www.geeksforgeeks.org/kd-trees-in-cpp/
- https://en.wikipedia.org/wiki/K-d_tree 
- https://www.geeksforgeeks.org/search-and-insertion-in-k-dimensional-tree/
- https://www.geeksforgeeks.org/introductory-guide-to-information-retrieval-using-knn-and-kdtree/
- https://pyimagesearch.com/2024/12/23/implementing-approximate-nearest-neighbor-search-with-kd-trees/
- https://en.wikipedia.org/wiki/Euclidean_distance
- CSPB 2700 hw-02 linked-lists (https://github.com/cu-cspb2270-2025/hw-02-linked-lists-lheylmun/tree/main/code)
- CSPB 2700 hw-03 binary search tree (https://github.com/cu-cspb2270-2025/hw-03-binary-search-tree-lheylmun/blob/main/code/BST.cpp)
