#include <iostream>
#include "FaultTree.h"
#include "node.h"
#include "BDD.h"

/* Programmer: Wang Jincheng
 * Date: 2021/7/19 - 2021/7/25
 * Object: To implement Fault Tree with C++ and analyze the corelation between the top event and basic event
 * Functions: The functions to implement are as below
 *            1. Accept data and construct a Fault Tree
 *            2. Solve for the minimum cut set
 *              2.1. Solve for all the cut set
 *              2.2. Find the minimum cut set with prime number
 *              2.3. Output the result
 *            3. Solve the occurrence probability of top event,
 *            the probability significance of the bottom event,
 *            and the relative probability importance.
 *            4. Depict a binary decision diagram(BDD) for decision
 * */

int main() {
    printf("Please input the basic information of the fault tree. "
           "\nThe input format can be referred to the example in example.txt.\n");

    // Analyze the fault tree and output the result
    int n;
    std::cin >> n;
    FaultTree tree(n);
    tree.FaultTreeAnalyze();
    tree.PrintAnalysis();
    // Build a binary decision diagram(BDD)
    // with the fault tree
    BDD bdd_tree(&tree);
    bdd_tree.Build_BDD();
    // Enter information to test the BDD
    bdd_tree.EnterInformation();
    bdd_tree.printResult();
    system("pause");
    return 0;
}