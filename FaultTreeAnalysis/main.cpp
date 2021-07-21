#include <iostream>
#include "FaultTree.h"
#include "node.h"

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
 *            4. Depict a binary decision diagram(BDD) and for decision
 * */

int main() {
    std::cout << "请输入结点个数（包括顶事件、中间事件和基本事件）：" << std::endl;
    int n;
    std::cin >> n;
    FaultTree tree(n);
    tree.getAllSubnode();
    tree.FindMiniCut();
    //std::cout << tree.CalculateTopEventPossibility() << std::endl;
    return 0;
}