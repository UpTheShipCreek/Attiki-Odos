#include <vector>
#include <algorithm>
#include "names.h" //includes iostream string and namespace std
#include "random.h"
#define SOFT_CAP 400
#define DISPARITY 200


class Node;

class Vechicle{
    bool is_Ready;
    bool in_Queue;
    Node* Destination;
    Node* Current;

    public:
    Vechicle() = default;
    Vechicle(Node* destination){
        this->is_Ready = false;
        this->Destination = destination;
    }

    void set_ready(){
        this->is_Ready = true;
    }

    

};

class Toll{
    int Price;
    bool is_Electronic;
    vector<Vechicle> Queue;

    public:
    Toll() = default;
    Toll(int price, bool is_electronic){
        this->Price = price;
        this->is_Electronic = is_electronic;
    }   

    void toll_add_to_q(Vechicle vechicle){
        Queue.insert(Queue.begin(), vechicle);
    }

    void toll_exit_from_q(){
        Queue.pop_back();
    }

    int toll_queue_size(){
        return Queue.size();
    }
};

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
    Node* Start_Node;
    Node* End_Node;

    public:
    Segment* Previous;
    Segment* Next;
    Segment() = default;
    Segment(int capacity, Node* start_node, Node* end_node){
        Previous = NULL;
        Next = NULL;
        this->Capacity = capacity;
        this->Start_Node = start_node;
        this->End_Node = end_node;
    }
    
    int segment_get_capacity(){
        return this->Capacity;
    }

    Node* segment_get_start_node(){
        return this->Start_Node;
    }

    Node* segment_get_end_node(){
        return this->End_Node;
    }

    void print(){
        cout << "This segment starts at the node " << this->Start_Node->node_get_name() << ", ends at the node " <<  this->End_Node->node_get_name()
        << " and has a capacity of " << this->Capacity << " vechicles."<< endl;
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
        Node* seg_start_node = this->Start;
        temp = Start->Next;
        if(temp != NULL){
            this->First_Seg = new Segment(SOFT_CAP + random_number(DISPARITY), seg_start_node, seg_start_node->Next);
            temp = temp->Next;
            seg_start_node = seg_start_node->Next;
        }
        Segment* temp_Seg = First_Seg;
        Segment* new_Seg;
        while(temp != NULL){
            new_Seg = new Segment(SOFT_CAP + random_number(DISPARITY), seg_start_node, seg_start_node->Next);
            new_Seg->Previous = temp_Seg;
            new_Seg->Next = NULL;

            temp_Seg->Next = new_Seg;
            temp_Seg = temp_Seg->Next;

            temp = temp->Next;
            seg_start_node = seg_start_node->Next;
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
            temp_Seg->print();
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

    Node* node_get_in_position(int position){
        // if(position >= this->Size){ //it can't be equal since the positioning starts counting from 0, meaning that the position equal to the size never exists
        //     return; //some error
        // }
        int i = 0;
        Node* temp = this->Start;
        while(i < position){
            temp = temp->Next;
            i++;
        }
        return temp;
    }

    Segment* segment_get_in_position(int position){
        // if(position >= this->Size-1){
        //     return; //can't be equal to the size-1 since #ofsegments are #ofnodes-1
        // }
        int i = 0;
        Segment* temp_Seg = this->First_Seg;
        while(i < position){
            temp_Seg = temp_Seg->Next;
            i++;
        }
        return temp_Seg;
    }

    Segment* segment_get_starting_from_node(Node* node){
        int i, seg_no;
        seg_no = this->Size -1;
        for(i = 0; i < seg_no; i++){
            if(segment_get_in_position(i)->segment_get_start_node() == node){
                return segment_get_in_position(i);
            }
            // else if(segment_get_in_position(i)->segment_get_end_node() == node){
            //     return segment_get_in_position(i+1);
            // }
        }
        return this->First_Seg; //error message probably
    }

    int get_size(){
        return this->Size;
    }
};

int main(void){
    srand(time(NULL));

    Toll my_toll(random_number(5), false);
    for(int i = 0; i < 10; i++){
        Vechicle my_vechicle;
        my_toll.toll_add_to_q(my_vechicle);
    }
    Vechicle my_vechicle;
    my_toll.toll_exit_from_q();

    cout << my_toll.toll_queue_size() << endl;

    Motorway my_motorway(21);
    for(int i = 0; i < 21; i++){
        cout << my_motorway.node_get_in_position(i)->node_get_id() << endl;
        cout << my_motorway.segment_get_starting_from_node(my_motorway.node_get_in_position(i))->segment_get_start_node()->node_get_id() << endl;
    }




    return 0;
}