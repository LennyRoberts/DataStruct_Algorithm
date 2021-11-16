#ifndef SPARSE_H
#define SPARSE_H

#include "iostream"
#include "assert.h"
#include "vector"

using namespace std;

// 稀疏图 - 邻接表
class Sparse{
private:
    int Edge;                   //边数
    int Node;                   //结点数
    bool Directed;              //方向性标志
    vector<vector<int>> Graph;  //具体数据

public:
    Sparse(int Node,int Directed){
        this->Node = Node;
        this->Directed = Directed;
        this->Edge = 0;
        Graph = vector<vector<int>>(Node,vector<int>());

    }

};

#endif // SPARSE_H
