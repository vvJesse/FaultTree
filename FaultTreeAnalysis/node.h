//
// Created by Bertrand on 2021/7/20.
//

#ifndef FAULTTREEANALYSIS_NODE_H
#define FAULTTREEANALYSIS_NODE_H

#include <iostream>

class node{

public:
    int subtree_n;          // range in 0-10
    int node_type;          // 1 means OR, 2 means AND, 0 means a basic event(no subtree)
    double possibility;     // range in 0-1, only available for basic event
    int subtree_vector[10]; // the index of the subtree

    node(int num_of_child = 0, int node = 0, double possible = 0.0)
            :subtree_n(num_of_child), node_type(node), possibility(possible){

        for(int i = 0; i < 10; i++)
            subtree_vector[i] = 0;

        for(int i = 0; i < subtree_n; i++)
            std::cin >> subtree_vector[i];

    }
};


#endif //FAULTTREEANALYSIS_NODE_H
