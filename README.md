# finalproject-kd-tree

Background:

The goal of this project is implement a k-d tree as clinical support tool for to predict baseline symptom severity of patients with symptomatic hip pain. Hip pain may arise from a wide spectrum underlying pathologies often involving comples interaction between bony morphology, soft tissue structures and muscular dynamics. 

Radiographic imaging is the first clinical assessment tool for diagnosing hip pain. Computed Toomography (CT) scans provide detailed visualization of the anatomic structures of the hip, allowing surgeons to make accurate diagnosis and determine further treatment. Stryker HipMap (https://microapp.stryker.com/hipmap/) enhance visualization by generating interactive 3D models with heatmapping based on CT scan data. These models automate femoroacetabular morphology measurements providing quantitative information about a patient's anatomy. 

Predicting patient symptoms remains a challenge as many patients present with overlapping abnormalities. This project applies k-d trees as a symptom prediction tool based on age, sex, and femoracetabular morphology measurements. k-d trees enable fast nearest-neighbor searches with high dimensional data allowing for efficient searches of patients. This tool may be helpful to clinicians in estimate burden of disease using only imaging data with potential impacts for clinical decision-making and expectation management.

Implentation Rationale: 

A k-d tree is a data structure that organizes points in k-dimensional spaces and are effective for performing searches that involve multidimensional search keys and creating point clouds. In this project, several pre-operative patient features will be stored for each patient including demographics and radiographic measurements. The k-d tree effectively allows for the organizaiton and searching of multidimensional data which fits the needs of this project as several preoperative features will be included for each patient. Additionally, this structure satisifies the goal of this project which is to output previously treated patietns who are similar to a current patient so the surgeon can similar patient variables with outcomes. This allows them to make informed decisions regarding treatment approach for the current patient, based on data from previous cases. 

In a k-d tree, each node is a k-dimensional point. For the purposes of this project, each patient will be represented as a node with their associated features (demographics, readiographic measurements, and outcomes) stored as a vector within the node. The k-d tree will be organized by assessing each feature and dividing nodes depending on their value. Nodes contained in the left subtree will have values less than the value of the current node in the current dimension and the right subtree will have greater values. 

For the purpose of this project, I will follow the canonical method of k-d tree construction:

- The axes used to split each pane will cycle as you move down the tree 
- New nodes will be inserted by selecting the median of the points being added to the subtree 
- Nodes in the left subtree will have values less than the current node 
- Nodes in the right subtree will have values greater than the current node

List of dimensions/data contained in each node:

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



References: 

Implementation References:
- https://www.geeksforgeeks.org/kd-trees-in-cpp/
- https://www.geeksforgeeks.org/search-and-insertion-in-k-dimensional-tree/
- https://www.geeksforgeeks.org/introductory-guide-to-information-retrieval-using-knn-and-kdtree/
- https://pyimagesearch.com/2024/12/23/implementing-approximate-nearest-neighbor-search-with-kd-trees/
- https://en.wikipedia.org/wiki/Euclidean_distance

