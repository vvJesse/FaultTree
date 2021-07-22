//
// Created by Bertrand on 2021/7/22.
//

#include "BDD.h"

BDD::BDD(FaultTree* a_ft){
    a_FaultTree = a_ft;
    BDD_head = NULL;
}

void BDD::AddBDDNode(BDD_node* head, int child){
    BDD_node* p = head;
    //New node is always added to "yes"
    while(p->YES != NULL)
        p = p->YES;
    p->YES = new BDD_node(child);
}

BDD_node* BDD::BuildSubTree(int cut_i){
    // Cut_i is the index of a minimum cut
    // The first node is the head node of the subtree by default
    BDD_node* head = new BDD_node(a_FaultTree->mini_cut[cut_i][0]);
    int i = 1;
    // Add other nodes to the subtree
    while(a_FaultTree->mini_cut[cut_i][i] != -1){
        AddBDDNode(head, a_FaultTree->mini_cut[cut_i][i++]);
    }
    return head;
}

/* The subTree should be added when its head choose yes.
 * Or when all the nodes in parentTree choose no
 * */
void BDD::MergeSubtree(BDD_node* head, BDD_node* subTree){
    if(head == NULL || subTree == NULL) return;


    if(head->ID != subTree->ID) {
        // if the head ID is not equal to subTree head ID,
        // the head of subTree haven't choose yes,
        // so examine the left and right subtree
        if (head->YES != NULL){
            MergeSubtree(head->YES, subTree);
        }
        if (head->NO != NULL){
            MergeSubtree(head->NO, subTree);
        }
        // all the nodes except the last one in parentTree choose yes
        // the subTree should be added to NO
        if (head->YES == NULL && head->NO == NULL)
            head->NO = subTree;
    }else{
        // when the head ID is equal to subTree head ID
        // if the head choose yes, the subTree should be added
        BDD_node* p = subTree, *q = head, *t;
        while(p->YES && q->YES && p->YES->ID == q->YES->ID){
            t = p;
            p = p->YES;
            q = q->YES;
            delete(t);
        }
        // here p points to the last one equals q
        if(p->YES){
            if(q->YES) {
                q = q->YES;
                t = p;
                p = p->YES;
                delete(t);
                if(!q->NO)
                    q->NO = p;
                else
                    MergeSubtree(q->NO, p);
            }else{
                // subtree doesn't work for decision
                while(p){
                    t = p;
                    p = p->YES;
                    delete(t);
                }
            }
        }else{
            // p is a single repeated node, deleted.
            delete(p);
        }
//        if(subTree->YES && head->YES)
//            MergeSubtree(head->YES, subTree->YES);
//        delete(subTree);
    }
}

bool BDD::cmp(int a, int b){
    int i = 0;
    // compare minicut[a] and minicut[b]
    while(a_FaultTree->mini_cut[a][i] == a_FaultTree->mini_cut[b][i]) i++;
    return a_FaultTree->mini_cut[a][i] > a_FaultTree->mini_cut[b][i];
}

void BDD::sort(int index[], int length){
    // Bubble sort for index[]
    // index[] is the index of the minimum cut
    for(int i = 0; i < length; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (cmp(index[j], index[j + 1])) {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

void BDD::Build_BDD(){
    BDD_node* head_array[100];              // to save the subTree head
    for(int i = 0; i < 100; i++)
        head_array[i] = NULL;
    int cut_n = a_FaultTree->cut_n;
    // Build subtree
    for(int i = 0; i < cut_n; i++)
        head_array[i] = BuildSubTree(i);

    // initialize the index[]
    int index[100] = {0};
    for(int i = 0; i < a_FaultTree->cut_n; i++){
        index[i] = i;
    }
    // sort the index[], and merge the subtree according in order
    sort(index, a_FaultTree->cut_n);
    BDD_head = head_array[index[0]];
    for(int i = 1; i < cut_n; i++)
        MergeSubtree(BDD_head, head_array[index[i]]);
}

void BDD::EnterInformation(){
    std::cout << "************** BDD Information ***************\n";
    std::cout << "All the basic events are as follows:" << std::endl;
    for(int i = 0; i < a_FaultTree->node_n; i++)
        if(a_FaultTree->tree_nodes[i]->node_type == 0)
            std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "Please enter the number and the index of the happened basic events: \n"
              << "The format can be referred to the example.txt\n";
    std::cin >> happened_num;
    //std::cout << std::endl;
    for(int i = 0; i < happened_num; i++) {
        int temp;
        std::cin >> temp;
        happened_event[temp] = true;
    }
}

bool BDD::DetermineTopEvent(){
    BDD_node* p = BDD_head;
    bool result = false;
    // Find result with BDD
    while(p!=NULL){
        if(happened_event[p->ID] == true) {
            p = p->YES;
            result = true;
        }
        else {
            p = p->NO;
            result = false;
        }
    }
    return result;
}

void BDD::printResult(){
    std::cout << "************** TopEvent Result ***************\n";
    if(DetermineTopEvent())
        std::cout << "The top event happened." << std::endl;
    else
        std::cout << "The top event doesn't happened." << std::endl;
}