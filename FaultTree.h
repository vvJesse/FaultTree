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

        for(int i = 0; i < num_of_nodes; i++)
        {
            int num_of_child = 0, node_t = 0;
            double possible = 0.0;
            std::cin >> num_of_child >> node_t;

            if(!node_t)
            {
                std::cin >> possible;
            }

            TreeNodes[i] = new node(num_of_child, node_t, possible);
        }

        for(int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++)
            {
                mini_cut[i][j] = -1;
            }
        }

    }

    void print_arr(){

        for(int i = 0; i < cut_n; i++){
            //int length = getLengthOfCut(mini_cut[i]);
            int j = 0;
            while(j < 50 && mini_cut[i][j] != -1)
                std::cout << mini_cut[i][j++] << " ";
            std::cout << std::endl;
        }

    }

    void init_array(int arr[]){
        for(int i = 0; i < 50; i++)
            arr[i] = -1;
    }

    void getAllSubnode(){
        int *temp = new int[50];
        init_array(temp);
        temp[0] = 0;
        calculateAllSubnode(temp);
        DeleteAllRepeat();
        delete(temp);
        print_arr();
    }

//copy the number of length of elements in a[] right from pos1 to b[] right from pos2
    void copy_array(int *&a, int pos1, int length, int *b, int pos2){
        for(int i = 0; i < length; i++)
        {
            b[pos2 + i] = a[pos1 + i];
        }
    }

    int getLengthOfCut(int* &arr){
        int i = 0;
        while(arr[i] != -1) i++;
        return i;
    }

    int FindGate(int* &arr){
        int i = 0;
        while(arr[i] != -1 && TreeNodes[arr[i]]->node_type == 0) i++;
        return i;
    }

    void calculateAllSubnode(int t_node[]){

        int length = getLengthOfCut(t_node);
        int position = FindGate(t_node);
        if(position == length)
        {
            // t_node have been a minimum cut when position equals to length, and should be added to subNode[]
            copy_array(t_node, 0, length, mini_cut[cut_n++], 0);
        }
        else if(TreeNodes[t_node[position]]->node_type == 1)
        {
            // OR gate
            for(int i = 0; i < TreeNodes[t_node[position]]->subtree_n; i++)
            {
                int array[50];
                init_array(array);

                copy_array(t_node, 0, position, array, 0);
                array[position] = TreeNodes[t_node[position]]->subtree_vector[i];
                copy_array(t_node, position + 1, length - position - 1, array, position + 1);

                calculateAllSubnode(array);
            }

        }
        else if(TreeNodes[t_node[position]]->node_type == 2)
        {
            // AND gate
            int array[50];
            init_array(array);
            int num_of_subtree = TreeNodes[t_node[position]]->subtree_n;
            copy_array(t_node, 0, position, array, 0);
            for (int i = 0; i < num_of_subtree; i++)
            {
                array[position + i] = TreeNodes[t_node[position]]->subtree_vector[i];
            }
            copy_array(t_node, position+1,length-position-1, array, position+num_of_subtree);
            calculateAllSubnode(array);
        }

    }

    void DeleteAllRepeat(){
        for(int i = 0; i < cut_n; i++)
            DeleteRepeat(mini_cut[i]);
    }

    void DeleteRepeat(int arr[]){
        int length = getLengthOfCut(arr);
        int repeated[50] = {0};

        for(int i = 0; i < length-1; i++){
            if(!repeated[i]){
                for(int j = i + 1; j < length; j++){
                    if(arr[i] == arr[j])
                        repeated[j] = 1;
                }
            }
        }

        for(int i = 0, j = 0; i < length; i++){
            if(!repeated[i])
                arr[j++] = arr[i];
            else
                arr[i] = -1;
        }
    }

    void FindMiniCut(){
        int prime[101] = {0};
        int ScoreList[100] = {0};
        bool reserved[100];
        generatePrimeTable(prime);
        generateScoreList(ScoreList, prime);
        SelectReserved(ScoreList, reserved);
        print_arr();
    }

    void SelectReserved(int ScoreList[], bool reserved[]){

        for(int i = 0; i < cut_n; i++)
            reserved[i] = true;

        for(int i = 0; i < cut_n-1; i++){
            for(int j = i + 1; j < cut_n; j++){
                if(ScoreList[i] % ScoreList[j] == 0)
                    reserved[i] = false;
                if(ScoreList[j] % ScoreList[i] == 0)
                    reserved[j] = false;
            }
        }

        int i = 0, j = 0;
        while(j < cut_n){
            if(reserved[j]){
                int k = 0;
                while(mini_cut[j][k] != -1) {
                    mini_cut[i][k] = mini_cut[j][k];
                    k++;
                }
                while(mini_cut[i][k] != -1)
                    mini_cut[i][k++] = -1;
                i++;
            }
            j++;
        }

        int copy_cut_n = i;
        while(i < cut_n){
            int k = 0;
            while(mini_cut[i][k] != -1)
                mini_cut[i][k++] = -1;
            i++;
        }
        cut_n = copy_cut_n;
    }

    void generateScoreList(int ScoreList[], int prime[]){
        for(int i = 0; i < cut_n; i++)
            ScoreList[i] = score(mini_cut[i], prime);
    }

    int score(int cut[], int prime[]){
        int i = 0, score = 1;
        while(cut[i] != -1){
            score = score * prime[cut[i++]];
        }
        return score;
    }

    void generatePrimeTable(int arr[]){
        int originTable[1001] = {0};
        originTable[0] = originTable[1] = 1;

        for(int i = 2; i <= 500; i++)
            if(originTable[i] == 0)
                for (int j = 2; i * j <= 1000; j++)
                    originTable[i * j] = 1;

        int i = 0, j = 0;
        while(i < 100 && j < 1000){
            if(originTable[j] == 0)
                arr[i++] = j;
            j++;
        }

    }
};


#endif //FAULTTREEANALYSIS_FAULTTREE_H
