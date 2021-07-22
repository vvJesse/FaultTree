//
// Created by Bertrand on 2021/7/20.
//

#ifndef FAULTTREEANALYSIS_FAULTTREE_H
#define FAULTTREEANALYSIS_FAULTTREE_H


#include <iostream>
#include "node.h"


class FaultTree {

private:

    //copy the number of length of elements in a[] right from pos1 to b[] right from pos2
    void CopyArray(int *&a, int pos1, int length, int *b, int pos2);
    void DeleteRepeat(int arr[]); // delete the repeated index in one cut
    void InitArray(int *arr);
    void GeneratePrimeTable(int *arr); // generate a prime table for each node
    void GenerateScoreList(int *ScoreList, int *prime);
    void DeleteAllRepeat();
    void CalculateAllSubnode(int *t_node);
    void SelectReserved(int ScoreList[], bool reserved[]);
    void SetTopProb(double Tpr);    // set top event possibility
    void CalculatePbSignificance();
    void CalculateRePbSignificance();
    void PrintMiniCut();            // formatted output the minimum cut
    void PrintNodeInformation();
    int GetLengthOfCut(int* &arr);
    int score(int cut[], int prime[]);
    int FindGate(int* &arr);        // // find the position of the first AND_Gate or OR_Gate int the cut
    double CalculateThePossibilityOfACut(int cut[]);
    double TopCalculation(double possibility[]);
    double PbSCalculation(int node_i);
    double RePbSCalculation(int node_i);
    double CalculateTopEventPossibility();

public:
    int node_n;
    int cut_n;
    int mini_cut[50][50];
    double top_probability;
    node* tree_nodes[100];

    FaultTree(int num_of_nodes);
    void GetAllSubnode();
    void FindMiniCut();
    void PrintAnalysis();
    void FaultTreeAnalyze();
    double GetTopProb();
};


#endif //FAULTTREEANALYSIS_FAULTTREE_H
