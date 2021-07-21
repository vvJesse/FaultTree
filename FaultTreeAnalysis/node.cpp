//
// Created by Bertrand on 2021/7/20.
//

#include "node.h"

node::node(int num_of_child, int node, double possible)
        :subtree_n(num_of_child), node_type(node), possibility(possible){

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