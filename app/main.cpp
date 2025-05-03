#include <iostream>
#include "../code/k-d tree.h"

using namespace std;

//uses kd_node to initialize patientData and ihot scores for 20 simulated patients

//column order: 1) Patient ID, 2) Age, 3) Sex (0 = female), 4) LCEA, 5) Acetab. version, 6) Tonnis angle
//7) Acetab. coverage (%), 8) Alpha angle, 9) Femoral torsion, 10) Femoral NSA, 11) Combined verion 12) iHOT-12 score 
vector<kd_node> patients = {
    {{25, 1, 32, 15, 0, 68, 55, 12, 130, 27, 45}, 48},
    {{32, 0, 28, 13, 1, 64, 62, 14, 135, 30, 52}, 52},
    {{19, 1, 35, 12, 0, 70, 58, 16, 125, 29, 48}, 50},
    {{44, 0, 20, 18, 2, 60, 63, 10, 128, 26, 40}, 35},
    {{37, 1, 26, 14, 1, 66, 60, 11, 132, 28, 50}, 49},
    {{28, 0, 33, 16, 0, 69, 56, 15, 124, 29, 47}, 45},
    {{50, 1, 22, 11, 3, 55, 65, 13, 129, 27, 38}, 30},
    {{30, 0, 30, 10, 1, 67, 59, 17, 131, 25, 49}, 48},
    {{23, 1, 29, 17, 0, 63, 54, 16, 126, 28, 46}, 46},
    {{41, 0, 24, 19, 2, 61, 61, 12, 127, 30, 42}, 39},
    {{36, 1, 27, 15, 1, 65, 57, 14, 130, 26, 51}, 50},
    {{22, 0, 31, 13, 0, 68, 53, 15, 133, 27, 48}, 49},
    {{29, 1, 34, 11, 1, 70, 55, 16, 122, 29, 44}, 47},
    {{47, 0, 21, 12, 2, 62, 64, 11, 125, 30, 43}, 37},
    {{38, 1, 25, 14, 1, 66, 60, 13, 128, 28, 49}, 48},
    {{31, 0, 28, 16, 0, 69, 58, 17, 134, 25, 50}, 51},
    {{24, 1, 30, 10, 1, 67, 56, 12, 121, 26, 46}, 46},
    {{40, 0, 23, 18, 2, 60, 63, 14, 123, 27, 41}, 39},
    {{33, 1, 26, 15, 0, 65, 59, 13, 129, 29, 47}, 48},
    {{26, 0, 32, 13, 1, 68, 57, 15, 135, 28, 45}, 47}
};



// main driver program
int main() {
   KDT tree; //creates a new k-d tree

    //inserting patients into k-d tree
    for (int i = 0; i < patients.size(); i++) {
        kd_node* node = tree.new_node(patients[i].patientData, patients[i].ihotScore);
        tree.insert_node(node);
    };

    tree.print_tree();

}
