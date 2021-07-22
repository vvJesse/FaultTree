//
// Created by Bertrand on 2021/7/22.
//

#ifndef FAULTTREEANALYSIS_BDD_NODE_H
#define FAULTTREEANALYSIS_BDD_NODE_H

#include <stddef.h>

class BDD_node {
public:
    int ID;                     // the index of the basic node in fault tree
    BDD_node* NO = NULL;        // point to the node when choose NO
    BDD_node* YES = NULL;       // point to the node when choose YES
    BDD_node(int id);           // constructor
};


#endif //FAULTTREEANALYSIS_BDD_NODE_H
