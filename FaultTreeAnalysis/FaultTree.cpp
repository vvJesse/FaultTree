//
// Created by Bertrand on 2021/7/20.
//

#include "node.h"
#include "FaultTree.h"

FaultTree::FaultTree(int num_of_nodes){
    node_n = num_of_nodes;
    cut_n = 0;
    top_probability = 0.0;

    for(int i = 0; i < num_of_nodes; i++)
    {
        // enter the sub node
        int num_of_child = 0, node_t = 0;
        double possible = 0.0;
        std::cin >> num_of_child >> node_t;

        // enter possibility when it is a basic event
        if(!node_t){
            std::cin >> possible;
        }
        tree_nodes[i] = new node(num_of_child, node_t, possible);
    }
    // by default -1 means no initialized by valid data
    for(int i = 0; i < 50; i++) {
        InitArray(mini_cut[i]);
    }

}

void FaultTree::PrintMiniCut(){

    // formatted output
    std::cout << "\n**************** Minimum Cut *****************" << std::endl;
    for(int i = 0; i < cut_n; i++){
        //int length = GetLengthOfCut(mini_cut[i]);
        std::cout << "Minimum cut " << i << ":\t";
        int j = 0;
        while(j < 50 && mini_cut[i][j] != -1)
            std::cout << mini_cut[i][j++] << " ";
        std::cout << std::endl;
    }

}

void FaultTree::InitArray(int *arr){
    for(int i = 0; i < 50; i++)
        arr[i] = -1;
}

void FaultTree::GetAllSubnode(){
    int *temp = new int[50];
    InitArray(temp);
    // 0 is the index of the top event
    temp[0] = 0;
    // calculation begins at the top event
    CalculateAllSubnode(temp);
    DeleteAllRepeat();
    delete(temp);
    //PrintMiniCut();
}

//copy the number of length of elements in a[] right from pos1 to b[] right from pos2
void FaultTree::CopyArray(int *&a, int pos1, int length, int *b, int pos2){
    for(int i = 0; i < length; i++)
    {
        b[pos2 + i] = a[pos1 + i];
    }
}

int FaultTree::GetLengthOfCut(int* &arr){
    int i = 0;
    while(arr[i] != -1) i++;
    return i;
}

// find the position of the first AND_Gate or OR_Gate int the cut
int FaultTree::FindGate(int* &arr){
    int i = 0;
    while(arr[i] != -1 && tree_nodes[arr[i]]->node_type == 0) i++;
    return i;
}

void FaultTree::CalculateAllSubnode(int *t_node){

    int length = GetLengthOfCut(t_node);
    int position = FindGate(t_node);
    if(position == length)
    {
        // t_node have been a minimum cut when position equals to length, and should be added to subNode[]
        CopyArray(t_node, 0, length, mini_cut[cut_n++], 0);
    }
    else if(tree_nodes[t_node[position]]->node_type == 1)
    {
        // OR gate
        for(int i = 0; i < tree_nodes[t_node[position]]->subtree_n; i++)
        {
            // construct arrays for each subNode
            int array[50];
            InitArray(array);

            // replace the upNode with each subNode in the array and other data in the array should remain
            CopyArray(t_node, 0, position, array, 0);
            array[position] = tree_nodes[t_node[position]]->subtree_vector[i];
            CopyArray(t_node, position + 1, length - position - 1, array, position + 1);

            // a OR gate is deleted
            // array may still not be a minimum cut, so recurses
            CalculateAllSubnode(array);
        }

    }
    else if(tree_nodes[t_node[position]]->node_type == 2)
    {
        // AND gate
        // construct a array for all the sub nodes
        int array[50];
        InitArray(array);
        int num_of_subtree = tree_nodes[t_node[position]]->subtree_n;

        // replace the upNode with all sub nodes, other data in the array remains
        CopyArray(t_node, 0, position, array, 0);
        for (int i = 0; i < num_of_subtree; i++)
        {
            array[position + i] = tree_nodes[t_node[position]]->subtree_vector[i];
        }
        CopyArray(t_node, position + 1, length - position - 1, array, position + num_of_subtree);

        // a AND gate is deleted
        // array may still not be a minimum cut, so recurses
        CalculateAllSubnode(array);
    }

}

// delete the repeated index in all the cut
void FaultTree::DeleteAllRepeat(){
    for(int i = 0; i < cut_n; i++)
        DeleteRepeat(mini_cut[i]);
}

// delete the repeated index in one cut
void FaultTree::DeleteRepeat(int arr[]){
    int length = GetLengthOfCut(arr);
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

// reserve the minimum cut with prime
void FaultTree::FindMiniCut(){
    int prime[101] = {0};
    int ScoreList[100] = {0};
    bool reserved[100];
    GeneratePrimeTable(prime);
    // score with prime
    GenerateScoreList(ScoreList, prime);
    SelectReserved(ScoreList, reserved);
    //PrintMiniCut();
}

void FaultTree::SelectReserved(int ScoreList[], bool reserved[]){

    // initialize reserved[]
    for(int i = 0; i < cut_n; i++)
        reserved[i] = true;

    // a cut is not a minimum cut if its score can be divided by others'
    for(int i = 0; i < cut_n-1; i++){
        for(int j = i + 1; j < cut_n; j++){
            if(ScoreList[i] % ScoreList[j] == 0)
                reserved[i] = false;
            if(ScoreList[j] % ScoreList[i] == 0)
                reserved[j] = false;
        }
    }

    // copy the minimum cuts to the front of the array
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

    // deleted the needless cut
    int copy_cut_n = i;
    while(i < cut_n){
        int k = 0;
        while(mini_cut[i][k] != -1)
            mini_cut[i][k++] = -1;
        i++;
    }

    // reset the number of cut
    cut_n = copy_cut_n;
}

void FaultTree::GenerateScoreList(int *ScoreList, int *prime){
    // score for each cut
    for(int i = 0; i < cut_n; i++)
        ScoreList[i] = score(mini_cut[i], prime);
}

int FaultTree::score(int cut[], int prime[]){
    int i = 0, score = 1;
    while(cut[i] != -1){
        score = score * prime[cut[i++]];
    }
    return score;
}

// generate a prime table for each node
void FaultTree::GeneratePrimeTable(int *arr){
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

// Calculate the possibility of a cut
double FaultTree::CalculateThePossibilityOfACut(int cut[]){
    int length = GetLengthOfCut(cut);
    double result = 1;
    for(int i = 0; i < length; i++){
        result = result * tree_nodes[cut[i]]->GetPossibility();
    }
    return result;
}

// calculate the possibility of the top event
double FaultTree::TopCalculation(double possibility[]){
    double result = 0.0;
    if(cut_n < 20)
    {
        // when cut_n is small, calculate according to the class principle

        // mulipleof2 is an array of the multiple of 2: 1 2 4 8, etc.
        // initialize the mulipleOf2[]
        int mulipleOf2[20];
        mulipleOf2[0] = 1;
        for (int i = 1; i < 20; i++)
            mulipleOf2[i] = mulipleOf2[i - 1] << 1;

        // class principle
        for (int i = 1; i < mulipleOf2[cut_n]; i++) {
            double probability = 1;
            int pieces_of_event = 0;
            for (int j = 0; j < cut_n; j++) {
                if (i & mulipleOf2[j]) {
                    probability *= possibility[j];
                    pieces_of_event++;
                }
            }
            if (pieces_of_event & 1)
                result += probability;
            else
                result -= probability;
        }
    }else{
        // if the cut_n is big, conduct an approximate calculation
        for(int i = 0; i < cut_n; i++)
            result += possibility[i];
    }
    return result;
}

double FaultTree::CalculateTopEventPossibility(){
    double possibility[50] = {0};
    for(int i = 0; i < cut_n; i++){
        possibility[i] = CalculateThePossibilityOfACut(mini_cut[i]);
    }
    double result = TopCalculation(possibility);
    SetTopProb(result);
    return result;
}

void FaultTree::SetTopProb(double TPr){
    top_probability = TPr;
}

double FaultTree::GetTopProb(){
    return top_probability;
}

// calculate the possibility significance of a node
double FaultTree::PbSCalculation(int node_i){
    double PbS = 0;
    for(int i = 0; i < cut_n; i++){
        int j = 0;
        double result = 1;
        while(mini_cut[i][j] != -1){
            if(mini_cut[i][j] != node_i)
                result *= tree_nodes[mini_cut[i][j]]->GetPossibility();
            j++;
        }
        PbS += result;
    }
    return PbS;
}

// calculate the possibility significance of all nodes
void FaultTree::CalculatePbSignificance(){
    for(int i = 0; i < node_n; i++){
        if(tree_nodes[i]->node_type == 0) {
            double PbS = PbSCalculation(i);
            tree_nodes[i]->SetPbSignificance(PbS);
        }else{
            tree_nodes[i]->SetPbSignificance(0);
        }
    }
}

// calculate the relative possibility significance of a node
double FaultTree::RePbSCalculation(int node_i){
    if(tree_nodes[node_i]->node_type != 0) return 0;
    double Pbs = PbSCalculation(node_i);
    return Pbs * tree_nodes[node_i]->GetPossibility() / GetTopProb();
}

// calculate the relative possibility significance of all nodes
void FaultTree::CalculateRePbSignificance(){
    for(int i = 0; i < node_n; i++){
        double RePbS = RePbSCalculation(i);
        tree_nodes[i]->SetRelaPbSignificance(RePbS);
    }
}

void FaultTree::PrintNodeInformation(){
    std::cout << "************** Node Information **************" << std::endl;
    std::cout << "Index\tnode_type\tPosb\tPoSGC\tRePoSGC\tSubNode" << std::endl;
    for(int i = 0; i < node_n; i++){
        std::cout << "node " << i << "\t";
        tree_nodes[i]->println();
    }
}

void FaultTree::PrintAnalysis() {
    PrintMiniCut();
    PrintNodeInformation();
}

void FaultTree::FaultTreeAnalyze(){
    GetAllSubnode();
    FindMiniCut();
    CalculateTopEventPossibility();
    CalculatePbSignificance();
    CalculateRePbSignificance();
}