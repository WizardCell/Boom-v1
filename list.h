#ifndef LIST_H_
#define LIST_H_
#include<stdlib.h>
using namespace std;

template<class T>
class Node {
    T* Data;
    Node<T>* Left;
    Node<T>* Right;
public:
    Node(const T &data, Node<T> *leftNode= nullptr, Node<T> *rightNode= nullptr) {///I've added default for left and right
        Data = new T(data);
        Left = leftNode;
        Right = rightNode;
    }

    Node() : Data(nullptr), Left(nullptr), Right(nullptr) {} /////////CHANGED FROM Data(new T()) to this

    Node(const Node<T>& node){
        Data=node.Data;
        Left=node.Left;
        Right=node.Right;
    }

    ~Node() {
        delete Data;
    }

    Node& operator=(const Node<T>&node){
        Data=node.Data;
        Left=node.Left;
        Right=node.Right;
    }

    Node<T>* getLeftNode() const{
        if(this==nullptr) return nullptr;
        return Left;
    }

    Node<T>* getRightNode() const{
        if(this==nullptr) return nullptr;
        return Right;
    }

    T* getData() const{
        if(this== nullptr) return nullptr;
        return Data;
    };

    void updateData(const T& data){
        if(this== nullptr) return;
        delete(this->Data);
        this->Data=data;
    }
    void setRightNode(Node<T>* Right){
        if(this== nullptr) return;
        this->Right=Right;
    }

    void setLeftNode(Node<T>* Left){
        if(this== nullptr) return;
        this->Left=Left;
    }

};

template<class T>
class List{

public:
    Node<T>* Head;
    Node<T>* Last;
    int Length;

    List(): Head(nullptr), Last(nullptr), Length(0) {}

    ~List(){
        Node<T>* Current=Head;
        for(int i=0; i<Length; i++){
            Node<T>* toDelete=Current;
            Current=Current->getRightNode();
            delete toDelete; //To be reviewed.
        }
    }

    void insertLast(Node<T>* newNode)
    {
        if (this->isEmpty())
        {
            this->Head = newNode;
            newNode->Left = nullptr;
            newNode->Right = nullptr;
            this->Last = newNode;
            this->Length++;
            return;
        }
        Node<T> *ptr = this->Head;
        while(ptr!= nullptr && ptr->Data<newNode->Data) {
            ptr = ptr -> Right;
        }
        if(ptr== nullptr)
        {
            this->Last->Right=newNode;
            newNode->Left=this->Last;
            this->Last=ptr;
            newNode->Right = nullptr;
            this->Length++;
            return;
        }
        ptr->Left->Right=newNode;
        newNode->Right=ptr;
        newNode->Left=ptr->Left;
        ptr->Left = newNode;
        this->Length++;
    }

    void removeNodeByPtr(Node<T>* nodeToDelete){
        if(nodeToDelete==nullptr) return;

        else if(nodeToDelete==Head){
            Head=nodeToDelete->getRightNode();
            Head->setLeftNode(nullptr);
            delete nodeToDelete;
            Length=Length-1;
            if(Head==nullptr){
                Last=nullptr;
                return;
            }
            Head->setLeftNode(nullptr);
            return;
        }

        else if(nodeToDelete==Last){
            Last=nodeToDelete->getLeftNode();
            delete nodeToDelete;
            Length=Length-1;
            Last->setRightNode(nullptr);
            return;
        }

        else{///changed here
            nodeToDelete->getLeftNode()->setRightNode(nodeToDelete->getRightNode());
            nodeToDelete->getRightNode()->setLeftNode(nodeToDelete->getLeftNode());
            delete nodeToDelete;
            Length=Length-1;
            return;
        }
    }

    bool isEmpty(){
        if(Head==nullptr){
            return true;
        }
        return false;
    }


};



#endif