#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <time.h>

#include "names.h"
#include "random.h"
#define PER 50
#define CAP 5
#define NO_O_NODES 10
#define NO_O_TOLLS 10

using namespace std;


class Vechicle{
    bool Ready;
    bool in_Queue;
    int Destination;
    int Id;

    public:
    Vechicle(int id, int destination){
        this->Id = id;
        this->Ready = false;
        this->in_Queue = true;
        this->Destination = destination;
        //cout << "A vechicle was created" << endl;
    }

    bool operator==(const Vechicle& v) {
        if(this->Id == v.Id) return true;
        else return false;
    }

    void make_ready(){
        //cout << "Vechicle " << Id << " is set ready" << endl;
        this->Ready = true;
    }

    bool move(){
        if(this->Ready == true){
            //cout << "Vehicle " << Id << " is trying to move" << endl;
            this->Ready = false;
            return true;
        }
        else{
            cout << "Vehicle " << Id << " is not ready to move" << endl;
            return false;
        }
    }
    int id(){
        return Id;
    }

    bool in_q(){
        if(this->in_Queue){
            this->in_Queue = false;
            return true;
        }
        return false;
    }

    int destination(){
        return this->Destination;
    }

    void exit(){
        cout << "Vechicle " << Id << " is exiting" << endl;
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

    void add(Vechicle vechicle){
        //cout << "Toll add" << endl;
        Queue.push_back(vechicle);
    }

    void take_out(Vechicle vechicle){
        //cout << "Toll take out" << endl;
        Queue.erase(remove(Queue.begin(), Queue.end(), vechicle), Queue.end());
    }

    // bool move(Vechicle vechicle){
    //     cout << "Toll move" << endl;
    //     if(vechicle.move() && exists(vechicle)){
    //         this->take_out(vechicle);
    //         return true;
    //     }
    //     else return false;
    // }

    bool move(Vechicle vechicle){
        //cout << "Toll move" << endl;
        if(vechicle.move()){
            this->take_out(vechicle);
            return true;
        }
        else return false;
    }

    bool exists(Vechicle vechicle){
        //cout << "Toll exists" << endl;
        if(find(Queue.begin(), Queue.end(), vechicle) != Queue.end()) {
            return true;
        } else {
            return false;
        }
    }

    Vechicle get_vechicle(int index){
        return Queue[index];
    }

    int queue_size(){
        return Queue.size();
    }
};

class Segment{
    vector<Vechicle> Vechicles;
    int Capacity;

    public:
    Segment(int capacity){
        this->Capacity = capacity;
        //cout << "A segment was created" << endl;
    }

    bool add(Vechicle vechicle){
        if(not_full()){
            Vechicles.push_back(vechicle);
            return true;
        }
        else{
            return false;
        }
    }

    void take_out(Vechicle vechicle){
        //cout << "Segment take out" << endl;
        Vechicles.erase(remove(Vechicles.begin(), Vechicles.end(), vechicle), Vechicles.end());
    }

    bool move(Vechicle vechicle){
        //cout << "Segment move" << endl;
        if(vechicle.move()){
            this->take_out(vechicle);
            return true;
        }
        else return false;
    }

    bool exists(Vechicle vechicle){
        if(find(Vechicles.begin(), Vechicles.end(), vechicle) != Vechicles.end()){
            return true;
        } 
        else{
            cout << "Vechicle " << vechicle.id() <<" not in segment" << endl;
            return false;
        }
    }

    bool not_full(){
        if(Vechicles.size() >= Capacity){
            cout << "Segment is full" << endl;
            return false;
        }
        else return true;
    }
};

class Node{
    int Id, t_Num;
    string Name;
    Segment* Seg;
    Toll* Tolls;

    public:
    vector<Vechicle> Vechicles;
    Node* Next;
    Node(int id, string name){
        this->Id = id;
        this->Name = name;
        this->Next = NULL;
        this->Seg = new Segment(CAP);

        t_Num = NO_O_TOLLS; //A node can have 1 to 10 tolls
        Tolls = new Toll[t_Num];
        for(int i = 0 ; i < t_Num; i++){
            Tolls[i] = Toll(random_number(5), coin_flip());
        }

        //cout << "A node was created" << endl;
    }

    ~Node(){
        delete Seg;
        delete[] Tolls;
    }

    int id(){
        return this->Id;
    }

    int t_index(Vechicle vechicle){
        //cout << "Nodes t index" << endl;
        for(int i = 0; i < t_Num; i++){
            if(Tolls[i].exists(vechicle)){
                return i;
            }
        }
        //cout << "No such vechicle" << endl;
        return -1;
    }

    void add_T(Vechicle vechicle){
        //cout << "Nodes add T" << endl;
        int r = random_number(t_Num-1);
        this->Tolls[r].add(vechicle); //add to random toll
    }

    bool move_T(Vechicle vechicle){
        //cout << "Nodes move T" << endl;
        if(this->Tolls[t_index(vechicle)].move(vechicle)){ //remove from the specific toll it was into
            return true;
        }
        else return false;
    }

    bool add(Vechicle vechicle){ //returns false if it couldn't add the vechicle to a segment or a toll queue, the vechicle still belongs in this node now though
        Vechicles.push_back(vechicle);
        if(vechicle.in_q()){ //every vechicle starts off in Queue
            add_T(vechicle);
            return true;
        }
        else if(Seg->add(vechicle)){
            return true;
        }
        cout << "Ka8hsteriseis sthn eisodo tou komvou " << this->Name << endl;
        return false;
    }

    void take_out(Vechicle vechicle){
        Vechicles.erase(remove(Vechicles.begin(), Vechicles.end(), vechicle), Vechicles.end());
    }

    bool move(Vechicle vechicle){
        if(t_index(vechicle) != -1){ //if the vechicle in in the toll queue move it to the segment
            if(move_T(vechicle)){ //remove it from the Toll queue 
                if(Seg->add(vechicle)){ //and put it in the Segment, not need to remove it from the Node
                    return true;
                }
                cout << "Ka8hsteriseis sthn eisodo tou komvou " << this->Name << endl;
            }
            return false;
        }
        else if(Seg->exists(vechicle)){
            if(Seg->move(vechicle)){ //remove it from the current segment and add it to the next, add the vechicle into the vector of the next node and remove it from this one
                if(this->Next != NULL){
                    if(this->Next->id() >= vechicle.destination()){ //if the vechicle is past its destination remove it 
                        take_out(vechicle);
                        vechicle.exit(); 
                        return true;
                    }
                    else if(Next->add(vechicle)){ // if there is a next node and the vechicle is not past its destination just put it in there, even if the segment is full
                        take_out(vechicle);
                        return true;
                    }
                    else return false;
                }
                else{ //if the Node doesn't have a next, just remove it
                    take_out(vechicle);
                    vechicle.exit(); 
                    return true;
                }
            }
            else return false;
        }
        else if(exists(vechicle)){  // if vechicle is in the node but neither in Queue or in the segment, then try to put it in the next segment
            if(Seg->add(vechicle)){
                return true;
            }
            cout << "Ka8hsteriseis sthn eisodo tou komvou " << this->Name << endl;
            return false;
        } 
        else return false;
    }

    bool exists(Vechicle vechicle){
        if(find(Vechicles.begin(), Vechicles.end(), vechicle) != Vechicles.end()){
            return true;
        } 
        else{
            cout << "Vechicle not in node" << endl;
            return false;
        }
    }

    void ready(int percentage){
        int i = 0;
        int size = Vechicles.size();
        int n = size*(50/100);

        while(i < n){
            Vechicles[random_number(size-1)].make_ready();
            i++;
        }
    }

    void move_all(){
        int i = 0;
        int vech_no, id;
        vech_no = Vechicles.size();
        while(i < vech_no){
            if(coin_flip()) Vechicles[i].make_ready(); //need to make coin_flip take the work with percentages
            id = Vechicles[i].id();
            if(move(Vechicles[i])){
                cout << "Vechicle " << id << " moved successfully" << endl;
                if(vech_no == Vechicles.size()) i++; //if the vector wasn't reduced in size increment the iterator 
                else vech_no--; //if the vector size was reduced update the number of vechicles to the new size
            }
            else{
                cout << "Vechicle " << id << " couldn't move" << endl;
                i++;
            }
        }
    }

    bool empty(){
        if(Vechicles.size() == 0){
            return true;
        }
        else return false;
    }

};

class Motorway{
    Node* First;
    int Size, Percentage;

    public:
    Motorway(int no_of_nodes, int percentage){
        this->First = new Node(0, Names::node_name[0]);
        this->Size = no_of_nodes;
        Node* N;
        Node* temp = First;
        for(int i = 1; i < Size; i++){
            N = new Node(i, Names::node_name[i]);
            N->Next = NULL;
            temp->Next = N;
            temp = temp->Next;
        }
        //cout << "A motorway was created" << endl;
    }

    ~Motorway(){
        Node* temp;
        while(First != NULL){
            temp = First;
            First = temp->Next;
            delete temp;
        }
    }

    Node* node(int position){ //starting from 0
        if(position >= this->Size){ //it can't be equal since the positioning starts counting from 0, meaning that the position equal to the size never exists
            cout << "Node out of bounds" << endl;
            return this->First; //some error
        }
        int i = 0;
        Node* temp = this->First;
        while(i < position){
            temp = temp->Next;
            i++;
        }
        return temp;
    }

    void add(Vechicle vechicle, int position){
        if(node(position)->add(vechicle)){
            cout << "Vechicle " << vechicle.id() << " has entered the motorway" << endl;
        }
    }

    // void ready(){
    //     int i, j, n_size;
    //     for(i = 0; i < Size; i++){
    //         cout << "i loop" << endl;
    //         n_size = node(i)->Vechicles.size();
    //         for(j = 0; j < n_size*(Percentage/100); j++){
    //             cout << "j loop" << endl;
    //             node(j)->Vechicles[random_number(n_size)].set_ready();
    //             cout << "Setting random vechicle ready" << endl;
    //         }
    //     }
    // }

    void move(){
        int i = 0;
        int j, id, n_size, p;
        //ready_all();
        for(j = Size -1 ; j >= 0; j--){
            n_size = node(j)->Vechicles.size();
            //node(j)->ready(PER);
            node(j)->move_all();
            // while(i < node(p)->Vechicles.size()){ //while for all the vechicles in the node
            //     node(p)->Vechicles[i].set_ready(); //WILL REMOVE
            //     id = node(p)->Vechicles[i].id(); //getting the Id of the specific vechicle 
            //     if(node(p)->move(node(p)->Vechicles[i])){ //trying to move that specific vechicle
            //         cout << "Vechicle " << id << " moved successfully" << endl;
            //         if(n_size > node(p)->Vechicles.size()){ //if the vector got reduced then don't increase the counter
            //             n_size--; //save the size of the previous loop for comparison
            //         }
            //         else i++;
            //     }
            //     else{
            //         cout << "Vechicle " << id << " couldn't move" << endl;
            //         i++; //go to the next vechicle in the same vector since the since didn't change
            //     }
            // }
        }
    }

    void ready_all(){
        int i;
        for(i = 0; i < Size; i++){
            node(i)->ready(100);
        }
    }
    
    bool empty(){
        int i;
        Node* temp = First;
        if(!temp->empty()){
            return false;
        }
        for(i = 1; i < Size; i++){
            temp = temp->Next;
            if(!temp->empty()) return false;
        }
        return true;
    }

};

int main(void){
    int i;
    srand(time(0));
    Motorway my_motorway(NO_O_NODES, PER);
    for(i = 0; i < 100; i++){
        Vechicle vechicle(i, random_number(NO_O_NODES-1)); //id and destination index
        my_motorway.add(vechicle, random_number(NO_O_NODES-1));
    }
    
    while(!my_motorway.empty()){
        my_motorway.move();
    }
    
}