#include "binary_search.h"
#include "bst_helper.h"
#include "bst_basic.h"
#include <ctime>

using namespace std;

int main(){
    int n=100;
    int *arr = BSTHelper::GenerateRandomArray(n,0,n);

    BST<int,int> bst = BST<int,int>();
//    bst.InsertionNode(28,2);
//    bst.InsertionNode(16,2);
//    bst.InsertionNode(30,2);
//    bst.InsertionNode(13,2);
//    bst.InsertionNode(22,2);
//    bst.InsertionNode(29,2);
//    bst.InsertionNode(42,2);

    for(int i=0;i<n;i++)
        bst.InsertionNode(arr[i],i);

    //cout<<bst.IsContain(4)<<endl;
    //bst.preOrder();
    //bst.LevelOrder();
    //cout<<bst.MaxKey()<<endl;
    cout<<bst.MinKey()<<endl;
    //bst.RemoveMax();
    //bst.RemoveMin();
    //bst.RemoveNode(28);

    cout<<endl;
    bst.LevelOrder();
    return 0;
}
