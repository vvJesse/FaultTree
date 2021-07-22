//
// Created by Bertrand on 2021/7/20.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "node.h"

node::node(int num_of_child, int node, double possible)
        :subtree_n(num_of_child), node_type(node), possibility(possible){

    SetPbSignificance(0);
    SetRelaPbSignificance(0);

    for(int i = 0; i < 10; i++)
        subtree_vector[i] = 0;

    for(int i = 0; i < subtree_n; i++)
        std::cin >> subtree_vector[i];

}

double node::GetPossibility() {
    return possibility;
}

double node::GetPbSignificance(){
    return PbSignificance;
}

double node::GetRelaPbSignificance(){
    return RelaPbSignificance;
}

void node::SetPbSignificance(double PbSgc){
    PbSignificance = PbSgc;
}

void node::SetRelaPbSignificance(double RPbSgc){
    RelaPbSignificance = RPbSgc;
}

void node::println() {
    switch (node_type){
        case 0: std::cout << "Basic_Et\t"; break;
        case 1: std::cout << "AND_Gate\t"; break;
        case 2: std::cout << "OR__Gate\t"; break;
    }
    printf("%.3f\t%.3f\t%.3f\t", possibility, GetPbSignificance(), GetRelaPbSignificance());
//    std::cout << std::setprecision(4) << possibility << "\t\t"
//                << GetPbSignificance()<<"\t\t" << GetRelaPbSignificance() << "\t";
    for(int i = 0; i < subtree_n; i++)
        std::cout << subtree_vector[i] << " ";
    std::cout << std::endl;
}