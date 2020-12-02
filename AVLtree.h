#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <exception>
#include "iostream"
using std::exception;
using namespace std;
template<class K, class D>
class treeNode{

public:
    treeNode<K,D>* Father;
    treeNode<K,D>* LeftSon;
    treeNode<K,D>* RightSon;
    K* Key;
    D* Data;
    int BF;
    int Height;


    treeNode(): Father(nullptr), LeftSon(nullptr), RightSon(nullptr), Key(nullptr), Data(nullptr), BF(0), Height(0){}

    treeNode(const K& key, const D& data, treeNode* left_son= nullptr, treeNode* right_son= nullptr, int bf=0, int height=0):
            Father(nullptr), LeftSon(left_son), RightSon(right_son), Key(new K(key)), Data(new D(data)), BF(bf), Height(height){}

    treeNode(const K& key, D* data, treeNode* left_son= nullptr, treeNode* right_son= nullptr, int bf=0, int height=0):
            Father(nullptr), LeftSon(left_son), RightSon(right_son), Key(new K(key)), Data(data), BF(bf), Height(height){} ///Added this to prevent memory leak.

    treeNode(const treeNode& nodeToCopy):
            Father(nodeToCopy.Father), LeftSon(nodeToCopy.LeftSon), RightSon(nodeToCopy.RightSon),
            Key(nodeToCopy.Key), Data(nodeToCopy.Data), BF(nodeToCopy.BF), Height(nodeToCopy.Height){}

    ~treeNode(){
        delete Key;
        delete Data;
    }

    void updateHeight(){
        if(LeftSon== nullptr&&RightSon== nullptr){ ///leaf
            Height=0;
        }
        else if(LeftSon== nullptr){
            Height=RightSon->Height+1;
        }
        else if(RightSon== nullptr){
            Height=LeftSon->Height+1;
        }
        else if(LeftSon->Height>RightSon->Height){
            Height=LeftSon->Height+1;
        }
        else if(RightSon->Height>=LeftSon->Height){
            Height=RightSon->Height+1;
        }
    }

    int getBF(){
        return this->BF;
    }

    void updateBF(){
        int leftHeight=0, rightHeight=0;
        if(RightSon!= nullptr){
            rightHeight=1+RightSon->Height;
        }
        if(LeftSon!= nullptr){
            leftHeight=1+LeftSon->Height;
        }
        BF=leftHeight-rightHeight;
    }

    void Roll(){
        if(BF==2){
            if(LeftSon->BF>=0){
                RollLL();
                return;
            }
            else if(LeftSon->BF==-1){
                RollLR();
                return;
            }
        }
        else if(BF==-2){
            if(RightSon->BF<=0){
                RollRR();
                return;
            }
            else if(RightSon->BF==1){
                RollRL();
                return;
            }
        }
    }

    void RollLL(){ ///to be reviewed "need IFs"
        int position=0;
        if(this->Father!= nullptr){
            if(this->Father->LeftSon==this){
                position=-1;
            }
            else{
                position=1;
            }
        }
        treeNode* temp=this->LeftSon;
        this->LeftSon=temp->RightSon;
        temp->RightSon=this;
        temp->Father=this->Father;

        if(this->LeftSon!=nullptr){
            this->LeftSon->Father=this;
        }
        if(position==-1){
            this->Father->LeftSon=temp;
        }
        else if(position==1){
            this->Father->RightSon=temp;
        }

        this->Father=temp;

        this->updateHeight();
        this->updateBF();
    }

    void RollRR(){
        int position=0;
        if(this->Father!= nullptr){
            if(this->Father->LeftSon==this){
                position=-1;
            }
            else{
                position=1;
            }
        }
        treeNode* temp=this->RightSon;
        this->RightSon=temp->LeftSon;
        if(this->RightSon!=nullptr){
            this->RightSon->Father=this;
        }
        temp->LeftSon=this;
        temp->Father=this->Father;


        if(position==-1){
            this->Father->LeftSon=temp;
        }
        else if(position==1){
            this->Father->RightSon=temp;
        }

        this->Father=temp;

        this->updateHeight();
        this->updateBF();
    }

    void RollLR(){
        this->LeftSon->RollRR();
        RollLL();
    }

    void RollRL(){
        this->RightSon->RollLL();
        RollRR();
    }

    D* getData(){
        return Data;
    }
};



template<class K, class D>
class AVLTree{
    treeNode<K,D>* Root;
    int nodesAmount;

public:

    class KeyExists : public exception{};
    class KeyDoesntExist : public exception{};

    AVLTree(): Root(nullptr), nodesAmount(0){}

    ~AVLTree(){
        DestroySubtree(Root);
    }

    void DestroySubtree(treeNode<K,D>* subRoot){
        if(subRoot== nullptr){
            return;
        }
        DestroySubtree(subRoot->LeftSon);
        DestroySubtree(subRoot->RightSon);
        delete subRoot;
        nodesAmount=nodesAmount-1;
    }

    treeNode<K,D>* getRoot(){
        return Root;
    }

    int getNodesAmount(){
        return nodesAmount;
    }

    /*void addTreeNode(treeNode<K,D>& new_node){
        treeNode<K,D>* copy=new treeNode<K,D>(*(new_node.Key), *(new_node.Data));
        if(nodesAmount==0){
            Root=copy;
            nodesAmount++;
            return;
        }
        treeNode<K,D>* current=Root;
        while(1){
            if(current!=nullptr && *(copy->Key) > *(current->Key)) {
                if (current->RightSon == nullptr) {
                    current->RightSon = copy;
                    copy->Father = current;
                    nodesAmount++;
                    fixTree(copy);
                    break;
                }
                else {
                    current = current->RightSon;

                }
            }
            else if(current!= nullptr && *(copy->Key) < *(current->Key)){
                if(current->LeftSon== nullptr){
                    current->LeftSon=copy;
                    copy->Father=current;
                    nodesAmount++;
                    fixTree(copy);
                    break;
                }
                else {
                    current = current->LeftSon;
                }
            }



        }

    }*/

    void addTreeNodeByPtr(treeNode<K,D>* nodePtr){
        nodePtr->RightSon=nullptr;
        nodePtr->LeftSon=nullptr;
        nodePtr->Father=nullptr;
        nodePtr->BF=0;
        nodePtr->Height=0;
        if(nodesAmount==0){
            Root=nodePtr;
            nodesAmount++;
            return;
        }
        treeNode<K,D>* current=Root;
        while(1){
            if(current!=nullptr && *(nodePtr->Key) > *(current->Key)) {
                if (current->RightSon == nullptr) {
                    current->RightSon = nodePtr;
                    nodePtr->Father = current;
                    nodesAmount++;
                    fixTree(nodePtr);
                    break;
                }
                else {
                    current = current->RightSon;

                }
            }
            else if(current!= nullptr && *(nodePtr->Key) < *(current->Key)){
                if(current->LeftSon== nullptr){
                    current->LeftSon=nodePtr;
                    nodePtr->Father=current;
                    nodesAmount++;
                    fixTree(nodePtr);
                    break;
                }
                else {
                    current = current->LeftSon;
                }
            }
        }
    }

    treeNode<K,D>* returnNodeByKey(const K& key){
        treeNode<K,D>* Current=Root;
        while(Current!= nullptr){
            if(key==*(Current->Key)){
                return Current;
            }
            else if(key> *(Current->Key)){
                Current=Current->RightSon;
            }
            else if(key< *(Current->Key)){
                Current=Current->LeftSon;
            }
        }
        return nullptr;
    }

    bool searchKey(const K& key){
        treeNode<K,D>* Current=Root;
        while(Current!= nullptr){
            if(key==*(Current->Key)){
                return true;
            }
            else if(key> *(Current->Key)){
                Current=Current->RightSon;
            }
            else if(key< *(Current->Key)){
                Current=Current->LeftSon;
            }
        }
        return false;
    }

    void fixTree(treeNode<K,D>* node){
        treeNode<K,D>* temp= node;
        while(temp!=nullptr){
            temp->updateHeight();
            temp->updateBF();
            temp->Roll();
            if(temp->Father == nullptr){
                this->Root=temp;
            }
            temp=temp->Father;
        }
    }

    void removeTreeNode(treeNode<K,D>* toDelete){
        treeNode<K,D>* toDeleteFather=toDelete->Father;
        if(toDelete->RightSon== nullptr && toDelete->LeftSon== nullptr){///no sons(leaf)
            if(toDeleteFather!=nullptr){
                toDeleteFather->RightSon==toDelete? toDeleteFather->RightSon=nullptr: toDeleteFather->LeftSon=nullptr;
                fixTree(toDeleteFather);
                delete toDelete;
            }
            else {///tree have one node
                Root = nullptr;
                delete toDelete;
            }
            nodesAmount--;
        }

        else if(toDelete->RightSon== nullptr && toDelete->LeftSon!= nullptr){
            if(toDeleteFather!=nullptr){
                toDeleteFather->RightSon==toDelete? toDeleteFather->RightSon=toDelete->LeftSon: toDeleteFather->LeftSon=toDelete->LeftSon;
                toDelete->LeftSon->Father=toDeleteFather;
                fixTree(toDeleteFather);
                delete toDelete;
            }
            else{
                Root=toDelete->LeftSon;
                Root->Father=nullptr;
                delete toDelete;
            }
            nodesAmount--;
        }

        else if(toDelete->RightSon!= nullptr && toDelete->LeftSon== nullptr){
            if(toDeleteFather!=nullptr){
                toDeleteFather->RightSon==toDelete? toDeleteFather->RightSon=toDelete->RightSon: toDeleteFather->LeftSon=toDelete->RightSon;
                toDelete->RightSon->Father=toDeleteFather;
                fixTree(toDeleteFather);
                delete toDelete;
            }
            else{
                Root=toDelete->RightSon;
                Root->Father=nullptr;
                delete toDelete;
            }
            nodesAmount--;
        }

        else if(toDelete->RightSon!= nullptr&&toDelete->LeftSon!= nullptr){

            treeNode<K,D>*current=toDelete->RightSon;
            while(current->LeftSon!= nullptr){
                current=current->LeftSon;

            }


            K* keyTemp=toDelete->Key;
            D* dataTemp=toDelete->Data;


            toDelete->Key=current->Key;
            toDelete->Data=current->Data;

            current->Data=dataTemp;
            current->Key=keyTemp;

            removeTreeNode(current);

        }
    }

    /*void fillArrInorder(treeNode<K,D>* p,D arr[], int* i) {
        //K* temp=arr;

        //if (p == nullptr) return;
        //inorder(p->LeftSon, temp);
        // *temp=*(p->Key);
        //temp++;
        //cout<<*(p->Key )<<(" ");

        if (p == nullptr){
            return;
        }
        fillArrInorder(p->LeftSon, arr, i);
        arr[*(i)]=*(p->Data);
        (*i)++;
        fillArrInorder(p->RightSon, arr, i);
    }*/

    void reverseInorder(treeNode<K,D>* p, D arr[], int* i){ ///added this because the priority trees that we have are sorted from the smallest one to the highest one.
        if(p==nullptr){
            return;
        }
        reverseInorder(p->RightSon, arr, i);
        arr[*(i)]=*(p->Data);
        (*i)++;
        reverseInorder(p->LeftSon,arr,i);
    }
    void removeTreeNodeBykey(K& key){
        treeNode<K,D>* toRemove= returnNodeByKey(key);
        removeTreeNode(toRemove);
    }

};






#endif