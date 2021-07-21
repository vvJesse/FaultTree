//
// Created by Bertrand on 2021/7/20.
//

#ifndef FAULTTREEANALYSIS_FAULTTREE_H
#define FAULTTREEANALYSIS_FAULTTREE_H

#include <iostream>
#include "node.h"

class FaultTree {

    int node_n;
    int cut_n;
    int mini_cut[50][50];
    node* TreeNodes[100];

public:
    FaultTree(int num_of_nodes){
        node_n = num_of_nodes;
        cut_n = 0;

        for(int i = 0; i < num_of_nodes; i++){
            int num_of_child = 0, node_t = 0;
            double possible = 0.0;
            std::cin >> num_of_child >> node_t;

            if(!node_t)
                std::cin >> possible;

            TreeNodes[i] = new node(num_of_child, node_t, possible);
        }

        for(int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                mini_cut[i][j] = -1;
            }
        }

    }

    void print_arr(){

        for(int i = 0; i < cut_n; i++){
            int length = 2;
            if(!mini_cut[i][1]) {
                length += mini_cut[i][0];
            }
            for(int j = 0; j < length; j++) {
                std::cout << mini_cut[i][j] << " ";
            }
            std::cout << std::endl;
        }

    }

    void getAllSubnode(){
        int *temp = new int[50];
        calculateAllSubnode(temp);
        delete(temp);
        print_arr();
    }

    //copy the number of length of elements in a[] right from pos1 to b[] right from pos2
    void copy_array(int a[], int pos1, int length, int b[], int pos2){
        for(int i = 0; i < length; i++) {
            b[pos2 + i] = a[pos1 + i];
        }
    }

    int getLengthOfCut(int arr[]){
        int i = 0;
        while(arr[i] != -1) i++;
        return i;
    }

    void calculateAllSubnode(int t_node[]){

        int length = getLengthOfCut(t_node);
        for(int i = 0; i < length; i++){

        }
    }

};


#endif //FAULTTREEANALYSIS_FAULTTREE_H
