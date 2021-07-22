//
// Created by Bertrand on 2021/7/22.
//

#ifndef FAULTTREEANALYSIS_BDD_NODE_H
#define FAULTTREEANALYSIS_BDD_NODE_H

#include <stddef.h>

class BDD_node {
public:
    int ID;
    BDD_node* NO = NULL;
    BDD_node* YES = NULL;
    BDD_node(int id);
};


#endif //FAULTTREEANALYSIS_BDD_NODE_H
