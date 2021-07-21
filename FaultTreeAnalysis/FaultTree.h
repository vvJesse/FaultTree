//
// Created by Bertrand on 2021/7/20.
//

#ifndef FAULTTREEANALYSIS_FAULTTREE_H
#define FAULTTREEANALYSIS_FAULTTREE_H

#include <iostream>
#include "node.h"

class FaultTree {

private:
    int node_n;
    int cut_n;
    int mini_cut[50][50];
    double TopProbability;
    node* TreeNodes[100];

    void copy_array(int *&a, int pos1, int length, int *b, int pos2);
    void DeleteRepeat(int arr[]);
    void init_array(int arr[]);
    void generatePrimeTable(int arr[]);
    void generateScoreList(int ScoreList[], int prime[]);
    void DeleteAllRepeat();
    void calculateAllSubnode(int t_node[]);
    void SelectReserved(int ScoreList[], bool reserved[]);
    void SetTopProb(double Tpr);
    void CalculatePbSignificance();
    void CalculateRePbSignificance();
    int getLengthOfCut(int* &arr);
    int score(int cut[], int prime[]);
    int FindGate(int* &arr);
    double CalculateThePossibilityOfACut(int cut[]);
    double TopCalculation(double possibility[]);
    double PbSCalculation(int node_i);
    double RePbSCalculation(int node_i);
    double CalculateTopEventPossibility();

public:
    FaultTree(int num_of_nodes);
    void printMiniCut();
    void getAllSubnode();
    void FindMiniCut();
    double GetTopProb();
    void FaultTreeAnalyze();
};


#endif //FAULTTREEANALYSIS_FAULTTREE_H
