//
// Created by Bertrand on 2021/7/20.
//

#ifndef FAULTTREEANALYSIS_NODE_H
#define FAULTTREEANALYSIS_NODE_H

#include <iostream>

class node{
private:
    double possibility;     // range in 0-1, only available for basic event
    double PbSignificance;
    double RelaPbSignificance;

public:

    int subtree_n;          // range in 0-10
    int node_type;          // 1 means OR, 2 means AND, 0 means a basic event(no subtree)
    int subtree_vector[10]; // the index of the subtree

    node(int num_of_child, int node, double possible);
    double GetPossibility();
    double GetPbSignificance();
    double GetRelaPbSignificance();
    void SetPbSignificance(double PbSgc);
    void SetRelaPbSignificance(double RPbSgc);
};


#endif //FAULTTREEANALYSIS_NODE_H
