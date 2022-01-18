#include "names.h" //includes iostream string and namespace std
#include "random.h"
#define SOFT_CAP 400
#define DISPARITY 200

class Node{
    int ID;
    string Name;

    public:
    Node* Next;
    Node() = default;
    Node(int id, string name){
        this->ID = id;
        this->Name = name;
        Next = NULL;
    }

    int node_get_id(){
        return this->ID;
    }

    string node_get_name(){
        return this->Name;
    }
};

class Segment{
    int Capacity;

    public:
    Segment* Previous;
    Segment* Next;
    Segment() = default;
    Segment(int capacity){
        Previous = NULL;
        Next = NULL;
        this->Capacity = capacity;
    }
    
    int segment_get_capacity(){
        return this->Capacity;
    }
};

class Motorway{
    int Size;
    Node* Start;
    Segment* First_Seg;

    public:
    Motorway(int no_of_nodes){




        //Creating the Nodes
        this->Start = new Node(0, Names::node_name[0]);
        this->Size = no_of_nodes;
        Node* N;
        Node* temp = Start;
        for(int i = 1; i < Size; i++){
            N = new Node(i, Names::node_name[i]);
            N->Next = NULL;
            temp->Next = N;
            temp = temp->Next;
        }
        //Creating the Nodes






        //Creating the Segments
        temp = Start->Next;
        if(temp != NULL){
            this->First_Seg = new Segment(SOFT_CAP + random_number(DISPARITY));
            temp = temp->Next;
        }
        Segment* temp_Seg = First_Seg;
        Segment* new_Seg;
        while(temp != NULL){
            new_Seg = new Segment(SOFT_CAP + random_number(DISPARITY));
            new_Seg->Previous = temp_Seg;
            new_Seg->Next = NULL;

            temp_Seg->Next = new_Seg;
            temp_Seg = temp_Seg->Next;

            temp = temp->Next;
        }
        //Creating the Segment






        //Testing if the Nodes are being created correctly
        temp = Start;
        while(temp != NULL){
            cout << temp->node_get_id() << " " << temp->node_get_name() << endl;
            temp = temp->Next;
        }
        //Testing if the Nodes are being created correctly





        //Testing if the Segments are being created correctly
        temp_Seg = First_Seg;
        while(temp_Seg != NULL){
            cout << temp_Seg->segment_get_capacity() << endl;
            temp_Seg = temp_Seg->Next;
        }
        //Testing if the Segments are being created correctly

    }
    ~Motorway(){
        Node* temp;
        while(Start != NULL){
            temp = Start;
            Start = temp->Next;
            delete temp;
        }

        Segment* temp_Seg;
        while(First_Seg != NULL){
            temp_Seg = First_Seg;
            First_Seg = temp_Seg->Next;
            delete temp_Seg;
        }
    }

    int get_size(){
        return this->Size;
    }
};

int main(void){
    srand(time(NULL));
    Motorway my_motorway(21);

    return 0;
}