# finalproject-kd-tree

Background:

The goal of this project is create a k-d tree that serves as a clinical decision making tool for the treatment of patients with mild hip instability. Hip instability is defined as extraphysiologic movement of the femoral head that causes pain and limits function. Mild hip instability, otherwise known as microinstability, is a form of hip instability that is not overtly during physical examination. The translation of the femoral head in mild instability cases is on average < 2 mm, however research has shown that this small amount of translation generates symptoms and may require surgical intervention. 

Surgical intervention options for patients with hip instability include isolated hip arthroscopy or hip arthroscopy combined with periacetabular osteotomy (PAO). During a hip arthroscopy, a surgeon uses an arthroscopic camera to address underlying intra-articular pathology such as labral tears, bony impingement, or capsular ligament degeneration, to restore hip stability and function. In more severe cases of instability, where anterior coverage of the femoral head is insufficient, a PAO may be preformed to reorient the acetabulum and restore femoral head coverage. In patients with mild hip instability, it can be difficult to determine the best treatment method. Often patients do well with isolated hip arthroscopy, however some patients continue to experience symptoms with this treatment and thus move to a PAO. proloning their recovery. Determining the correct course of treatment for this patient cohort is important for preventing symptoms continuation or severity, and the need for secondary surgical procedures. 

Implentation Rationale: 

A k-d tree is a data structure that organizes points in k-dimensional spaces and are effective for performing searches that involve multidimensional search keys and creating point clouds. In this project, several pre-operative patient features will be stored for each patient including demographics and radiographic measurements. The k-d tree effectively allows for the organizaiton and searching of multidimensional data which fits the needs of this project as several preoperative features will be included for each patient. Additionally, this structure satisifies the goal of this project which is to output previously treated patietns who are similar to a current patient so the surgeon can compare treatment types and outcomes. This allows them to make informed decisions regarding treatment approach for the current patient, based on data from previous cases. 

In a k-d tree, each node is a k-dimensional point. For the purposes of this project, each patient will be represented as a node with their associated features (demographics, readiographic measurements, treatment type and outcomes) stored as separate dimensions. k-d trees are considered balances ad the nodes to the left of a current node have values smaller than the current node and nodes to the right have values larger than the current node. Given that k-d trees have k-dimensions left and right splits occur in planes, aligning with the axis of the variable being split. This allows for fast and efficient searching of similar patients with specific values.

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
7. Alpha Angle @ 1:00 (AA1), integer, range 35-95
8. Alpha Angle @ 2:00 (AA2, integer, range 35-95
9. Femoral Torsion, integer, range -10-30
10. Femoral Neck Shaft Angle (FNSA), integer, range 120-175
11. Combind Version, integer, range 5-50

Additionally each node will contain the variables below. These variables will only be stored in the node and not used for splitting. 
1. treatment type
2. Baseline iHOT12 score 


