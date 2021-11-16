#ifndef BST_BASIC_H
#define BST_BASIC_H

#include "iostream"
#include "queue"
#include <assert.h>
#include <algorithm>

using namespace std;
/*该文件包含的功能：
 * 1.插入一个新结点（可使用循环插入来构建一棵BST）-InsertionNode()；
 * 2.查询某个Key值在BST树中是否存在-Cotian();
 * 3.前序/中序/后序遍历-PreOrder()/InOrder()/PostOrder();
 * 4.查询BST树中最小/最大键值的结点-MinKey()/MaxKey()；
 * 5.层序遍历BST树-LevelOrder();
 * 6.删除BST树中键值小/最大的结点-DeleteMin()/DeleteMax()；
 * 7.删除BST树中任意一个结点。
*/

template<typename key,typename value>
class BST{
private:
    struct node{
        key Key;        //结点键值
        value Value;    //结点附加域
        node* left;
        node* right;

        node(key Key,value Value){  //结构体构造函数
            this->Key = Key;
            this->Value = Value;
            this->left = this->right = nullptr;
        }
        node(node* Node){
            this->Key = Node->Key;
            this->Value = Node->Value;
            this->left = Node->left;
            this->right = Node->right;
        }
    };
    node* root;         //根结点
    int count;          //BST中的结点个数

private:
/*
 * 1)递归Recursion在插入结点键值不等于根结点键值情况下发生；
 * 2)递归出口:当递归到叶子结点（左右指针都空）时将返回一个指向新结点的指针，
 *   这个指针将会被其父结点继承，递归树逐层返回最终为这棵树的根结点；
 * 3)__InsertNode操作最终返回这棵树的根结点。
*/
    node* __InsertNode(node* Node,key Key,value Value){
        if(Node == nullptr){
            count++;
            return new node(Key,Value);
        }
        if(Key == Node->Key)
            Node->Value=Value;
        else if(Key < Node->Key)
            Node->left = __InsertNode(Node->left,Key,Value);
        else if(Key > Node->Key)
            Node->right = __InsertNode(Node->right,Key,Value);
        return Node;
    }

// 查看以node为根的二分搜索树中是否包含键值为key的节点, 使用递归算法
    bool __Contain(node* Node,key Key){
        if(Node == nullptr)
            return false;
        if(Node->Key == Key)
            return true;
        else if(Node->Key > Key)
            return __Contain(Node->left,Key);
        else if(Node->Key < Key)
            return __Contain(Node->right,Key);
    }

/*----------------------------------------------------*/
    void visit(node *Node){
        cout<<Node->Key<<" ";
    }

    void __Preorder(node* Node){
        if(Node != nullptr){
            visit(Node);
            __Preorder(Node->left);
            __Preorder(Node->right);
        }
    }

    void __Inorder(node* Node){
        if(Node != nullptr){
            __Inorder(Node->left);
            visit(Node);
            __Ineorder(Node->right);
        }
    }

    void __postorder(node* Node){
        if(Node != nullptr){
            __Postorder(Node->left);
            __Postorder(Node->right);
            visit(Node);
        }
    }
/*----------------------------------------------------*/
//寻找BST中Key键值最大/最小的那个结点并返回指针
    node* __Maximum(node* Node){
        if(Node->right == nullptr)
            return Node;
        __Maximum(Node->right);
    }
    node* __Minimum(node* Node){
        if(Node->left == nullptr)
            return Node;
        return __Minimum(Node->left);
    }
//以上最后一行的写法都正确，Minimum中只是更严谨地将return加到出if之外


/*---------------------------------------------------------------------------------------
 * 1）删除掉以node为根的二分搜索树中的最小节点 并 返回删除节点后新的二分搜索树的根；
 * 2）BST中最小键值就是最左边的那个子节点，向下递归直至其左孩子为空即找到；
 *    但这最左的子节点可能还有右子树，删除该节点前先保存其右子树的指针；
 * 3）运用递归，Node->left = __removeMin(Node->left);左边是指向41；
 *    右边返回的是指向33的指针，这就把[22]的右结点挂到了‘41’的左左子树上。
 Node->41                     41
     /    \   删除结点[22]  /    \
   [22]    58 ===========> 33    58
     \    /                 \    /
  -> 33  50                 37  50
       \
       37
*/
    node* __removeMin(node* Node){
        if(Node->left == nullptr){
            node* RightNode = Node->right;
            delete Node;
            count--;
            return RightNode;
        }
        Node->left = __removeMin(Node->left);
        return Node;
    }
    node* __removeMax(node* Node){
        if(Node->right == nullptr){
            node* LeftNode = Node->left;
            delete Node;
            count--;
            return LeftNode;
        }
        Node->right = __removeMax(Node->right);
        return Node;
    }

/*---------------------------------------------------------------------------
 * 1）BST删除操作依据Key值向下进行递归遍历，
 * 2）当找到要生产的结点后要判断该结点的左右子树情况：
 *    1.左子树为空； 2.右子树为空； 3.左右子树都不为空；
 *1&2：1保存被删除结点左/右子树的指针情况，2然后直接删除，
 *     3最后返回指针，使被删除结点的父节点能够衔接。
 * 3：1先拷贝一份被删除结点右子树中最小值结点的信息__Minimum();
 *     2然后用这个副本结点去覆盖被删除结点，被删除结点信息丢失，即被删除；
 *     3最后返回这个结点，递归回溯使得被删除结点的父结点指向它，斜街完成。
 *
       Node=> 41                       	41
             /  \					   /  \
  Node->right=>	58      删除结点58		  59
               /  \    	=>变换后=>		 /  \
              50  60				    50  60
                 /  \						  \
successorNode=> 59  63					 '59'  63
*/
    node* __remove(node* Node,key Key){
        if(Node == nullptr)
            return nullptr;
        if(Key < Node->Key){
//待删除结点的父结点要指向 被删除结点的孩子结点 或者 覆盖被删除结点的新结点
            Node->left = __remove(Node->left,Key);
            return Node;
        }
        else if(Key > Node->Key){
            Node->right = __remove(Node->right,Key);
            return Node;
        }
        else {
            if(Node->left == nullptr){
                node* RightNode = Node->right;
                delete Node;
                count--;
                return RightNode;
            }
            if(Node->right == nullptr){
                node* LeftNode = Node->left;
                delete Node;
                count--;
                return LeftNode;
            }
/*将待删除结点右子树的最小值结点拷贝一份下来，然后将其删除，最后把这个
  拷贝的结点覆盖待删除的结点，就达到了先交换这两个阶段的值然后再删除的操作*/
            node* SuccessorNode = new node(__Minimum(Node->right));
            SuccessorNode->right = __removeMin(Node->right);
            SuccessorNode->left = Node->left;
            count--;
            return SuccessorNode;
        }
    }
/*写在最后：
 * 1.能不能就函数返回值定义成void类型的，这样在if中简化了代码？
 *   那就要使用非递归的方法了，因为在递归调用中,在找到待删除结点后的操作只是
 *   处理了被删除结点左右孩子指针，并没有使被删除结点的父结点指向它，所以指针
 *   要回溯到上一级使被删除结点的父结点要指向这个被删除结点的孩子或者是被覆盖的新结点。
------------------------------------------------------------------------------------*/

public:
    BST(){
        root=NULL;
        count=0;
    }
    ~BST(){}

    int size(){
        return count;
    }
    bool isEmpty(){
        return count==0;
    }

public:
// 向二分搜索树中插入一个新的(key, value)数据对
    void InsertionNode(key Key,value Value){
        root=__InsertNode(root,Key,Value);
    }

// 查看二分搜索树中是否存在键key
    bool IsContain(key Key){
        return __Contain(root,Key);
    }

//先序遍历
    void preOrder(){
        __Preorder(root);
    }
//中序遍历
    void InOrder(){
        __Inorder(root);
    }
//后序遍历
    void PostOrder(){
        __postorder(root);
    }

/*
 * --广度优先遍历（层序遍历），使用队列实现。
 * 1.先让根结点入队，然后出队接受访问，
 * 2.对出队结点进行访问，包括以该节点为实参调用函数，获取子节点
 * 3.让存在的子节点都入队；
 * 4.之后重复2-3，出队接受访问和获取存在的子节点并让其入队，
 *   直至队列中没有结点元素为止。
*/
    void LevelOrder(){
        queue<node*> q;
        q.push(root);               //根节点入队
        while(!q.empty()){          //直至队列为空
            node* Node=q.front();   //对头元素为一个结点
            q.pop();                //队头元素出队
            visit(Node);            //以被访问元素为实参调用函数
            if(Node->left)          //使左右存在的子节点入队
                q.push(Node->left);
            if(Node->right)
                q.push(Node->right);
        }
    }

//查询并返回BST中的最大值/最小值
    key MaxKey(){
        assert(count != 0);
        node* Node = __Maximum(root);
        return Node->Key;
    }
    key MinKey(){
        assert(count != 0);
        node* Node = __Minimum(root);
        return Node->Key;
    }

//删除BST中最小值/最大值
    void RemoveMin(){
        __removeMin(root);
    }
    void RemoveMax(){
        __removeMax(root);
    }

//删除任意一个结点
    void RemoveNode(key Key){
        assert(count > 0);
        root = __remove(root,Key);
    }
};

#endif // BST_BASIC_H
