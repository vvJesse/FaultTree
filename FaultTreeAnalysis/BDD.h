//
// Created by Bertrand on 2021/7/22.
//

#ifndef FAULTTREEANALYSIS_BDD_H
#define FAULTTREEANALYSIS_BDD_H


#include "FaultTree.h"
#include "BDD_node.h"

class BDD {
private:
    FaultTree* a_FaultTree;                 // The associated fault tree
    BDD_node* BDD_head;                     // The head of the fault tree of BDD structure
    int happened_num = 0;                   // The number of valid basic event
    int non_intersect_set[50][50];          // non_intersect_set
    bool happened_event[100] = {false};     // State of the node: Active or inactive
    bool cmp(int a, int b);                 // Compare 2 arrays in the minimum cuts index
    void sort(int index[], int length);     // Sort the minimum cuts index
    bool DetermineTopEvent();               // Decide the state of the top event with BDD
    BDD_node * AddBDDNode(BDD_node *head, int child, int parent);                 // ADD a BDD_node to the BDD tree
    static void MergeSubtree(BDD_node* head, BDD_node* subTree);       // Merge 2 subtrees

public:
    BDD(FaultTree* a_ft);               // Constructor
    void BuildSubTree(int index[], int end_index[]);  // Build a subtree
    void Build_BDD();                   // Build a BDD tree with subtree
    void EnterInformation();            // For users to enter information
    void printResult();                 // Print the result of decision

};


#endif //FAULTTREEANALYSIS_BDD_H
