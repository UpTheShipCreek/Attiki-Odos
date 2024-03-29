#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <ctime>

#include "names.h"
#include "random.h"
#define PER 30
#define CAP 5
#define NO_O_NODES 21
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
        //cout << "Vechicle " << Id << " has destination node " << Destination << endl;
    }

    // Vechicle(const Vechicle &v){
    //     this->Ready = v.Ready; 
    //     this->in_Queue = v.in_Queue; 
    //     this->Destination = v.Destination;
    //     this->Id = v.Id;
    // }

    // bool operator==(const Vechicle& v) {
    //     if(this->Id == v.Id && this->Destination == v.Destination) return true;
    //     else return false;
    // }

    bool ready(){  //if it was already ready return true
        if(this->Ready) return true;
        cout << "Setting vechicle " << Id << " ready" << endl;
        this->Ready = true;
        return false;
    }

    void make_ready(){
        this->Ready = true;
    }

    bool is_ready(){
        if(this->Ready) return true;
        else return false;
    }

    void unready(){
        this->Ready = false;
        //cout << "Vechicle " << this->Id << " is made unready" << endl; 
    }

    bool move(){
        //if(this->Ready) cout << "Vechicle " << this->Id << " is ready" << endl;
        return this->Ready;
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
    vector<Vechicle*> Queue;

    public:
    Toll() = default; 

    Toll(int price, bool is_electronic){
        this->Price = price;
        this->is_Electronic = is_electronic;
    }   

    void add(Vechicle* vechicle){
        //cout << "Toll add" << endl;
        Queue.push_back(vechicle);
    }

    void take_out(Vechicle* vechicle){
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

    bool move(Vechicle* vechicle){
        //cout << "Toll move" << endl;
        if(vechicle->move()){
            //vechicle.unready();
            this->take_out(vechicle);
            return true;
        }
        else return false;
    }

    bool exists(Vechicle* vechicle){
        //cout << "Toll exists" << endl;
        if(find(Queue.begin(), Queue.end(), vechicle) != Queue.end()) {
            return true;
        } else {
            return false;
        }
    }

    Vechicle* get_vechicle(int index){
        return Queue[index];
    }

    int queue_size(){
        return Queue.size();
    }
};

class Segment{
    vector<Vechicle*> Vechicles;
    int Capacity;

    public:
    Segment(int capacity){
        this->Capacity = capacity;
        //cout << "A segment was created" << endl;
    }

    // bool add(Vechicle vechicle){
    //     if(not_full()){
    //         Vechicles.push_back(vechicle);
    //         return true;
    //     }
    //     else{
    //         return false;
    //     }
    // }

    void add(Vechicle* vechicle){
        Vechicles.push_back(vechicle);  
    }

    void take_out(Vechicle* vechicle){
        //cout << "Segment take out" << endl;
        Vechicles.erase(remove(Vechicles.begin(), Vechicles.end(), vechicle), Vechicles.end());
    }

    bool move(Vechicle* vechicle){
        //cout << "Segment move" << endl;
        if(vechicle->move()){
            //vechicle.unready();
            this->take_out(vechicle);
            return true;
        }
        else return false;
    }

    bool exists(Vechicle* vechicle){
        if(find(Vechicles.begin(), Vechicles.end(), vechicle) != Vechicles.end()){
            return true;
        } 
        else{
            //cout << "Vechicle " << vechicle->id() <<" not in segment" << endl;
            return false;
        }
    }

    bool not_full(){
        if(Vechicles.size() >= Capacity){
            //cout << "Segment is full" << endl;
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
    vector<Vechicle*> Vechicles;
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

    int t_index(Vechicle* vechicle){
        //cout << "Nodes t index" << endl;
        for(int i = 0; i < t_Num; i++){
            if(Tolls[i].exists(vechicle)){
                return i;
            }
        }
        return -1;
    }

    void add_T(Vechicle* vechicle){
        //cout << "Nodes add T" << endl;
        int r = random_number(t_Num-1);
        this->Tolls[r].add(vechicle); //add to random toll
    }

    bool move_T(Vechicle* vechicle){
        //cout << "Nodes move T" << endl;
        if(this->Tolls[t_index(vechicle)].move(vechicle)){ //remove from the specific toll it was into
            return true;
        }
        else return false;
    }

    void add(Vechicle* vechicle){ 
        Vechicles.push_back(vechicle);
        if(vechicle->in_q()){ //every vechicle starts off in Queue
            add_T(vechicle);
        }
        else if(Seg->not_full()){
            Seg->add(vechicle);
        }
    }

    void take_out(Vechicle* vechicle){
        Vechicles.erase(remove(Vechicles.begin(), Vechicles.end(), vechicle), Vechicles.end());
    }

    bool move(Vechicle* vechicle){
        if(!exists(vechicle)) return false; //if the vechicle is not in the node return false

        //OVERSHOT
        if(this->id() >= vechicle->destination()){ //if the vechicle enters after its destination 
            take_out(vechicle);
            vechicle->exit();
            return true;
        }
        //OVERSHOT

        //NODE QUEUE CHECKS
        if(t_index(vechicle) == -1 && Seg->exists(vechicle) == false){ //if the vechicle was neither in toll queue or a segment
            if(Seg->not_full()){    // try to put it in a segment
                Seg->add(vechicle); 
                cout << "Vechicle " << vechicle->id() << " moving on from node " << Id << " queues, to the segment"  << endl;
                return true;
            }
            cout << "Vechicle " << vechicle->id() << " stuck in Node Queue" << endl;
            return false;
        }
        //NODE QUEUE CHECKS
        
        if(!vechicle->move()) return false; //if the vechicle is not ready to move return false
        vechicle->unready(); //the vechicle will move no matter what, so we put it back in the unready state

        //SEGMENT CHECKS
        if(Seg->exists(vechicle)){
            cout << "Vechicle " << vechicle->id() << " moving on from node " << Id << " segment"  << endl;
            Seg->take_out(vechicle);
            take_out(vechicle);
            if(this->Next != NULL){ //if there are more nodes
                if(this->Next->id() >= vechicle->destination()){ //if you have reached your destination leave
                    vechicle->exit();
                    return true;
                }
                this->Next->add(vechicle); //adding the vechicle to the next segment
                return true;
            }       
            vechicle->exit();    //if there are no any more nodes just leave
            return true;
        }
        //SEGMENT CHECKS

        //TOLL CHECKS
        int index = t_index(vechicle);
        if(index != -1){ //if the vechicle was in the tolls
            cout << "Vechicle " << vechicle->id() << " moving on from node " << Id << " tolls"  << endl;
            Tolls[index].take_out(vechicle); //remove it from the tolls
            if(Seg->not_full()){   //add to the segment if it is not full
                Seg->add(vechicle);
            }
            return true;
        }
        //TOLL CHECKS
        return false; //no way to come here I think
    }

    bool exists(Vechicle* vechicle){
        if(find(Vechicles.begin(), Vechicles.end(), vechicle) != Vechicles.end()){
            return true;
        } 
        else{
            cout << "Vechicle not in node" << endl;
            return false;
        }
    }

    int move_all(){ //returns the number of vechicles that moved(Toll->Segment, Segment->Segment, NodeQ->Segment)
        int i = 0;
        int vech_no, id; 
        int counter = 0;
        vech_no = Vechicles.size();
        while(i < vech_no){
            //if(w_coin_flip(PER)) Vechicles[i].make_ready(); //need to make coin_flip take the work with percentages
            id = Vechicles[i]->id();
            if(move(Vechicles[i])){
                //cout << "Vechicle " << id << " moved successfully" << endl;
                if(vech_no == Vechicles.size()) i++; //if the vector wasn't reduced in size increment the iterator 
                else vech_no--; //if the vector size was reduced update the number of vechicles to the new size
                counter++;
            }
            else{
                //cout << "Vechicle " << id << " couldn't move" << endl;
                i++;
            }
        }
        return counter;
    }

    bool empty(){
        if(Vechicles.size() == 0){
            return true;
        }
        else return false;
    }

};

class Motorway{
    //Node* First;
    int Size, Percentage;

    public:
    Node* First;
    Motorway(int no_of_nodes, int percentage){
        this->First = new Node(0, Names::node_name[0]);
        this->Size = no_of_nodes;
        this->Percentage = percentage;
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

    int no_o_vechicles(){
        int i;
        int c = 0;
        for(i = 0; i < Size; i++){
            c += node(i)->Vechicles.size();
        }
        return c;
    }

    void add(Vechicle* vechicle, int position){
        node(position)->add(vechicle);
        cout << "Vechicle " << vechicle->id() << " has entered the motorway in position " << position<< " with destination  " << vechicle->destination() << endl;
    }

    int ready(){
        int s, r; int i = 0;
        double p = (double)Percentage/100;
        int n = no_o_vechicles()*p;
        if(n == 0 && no_o_vechicles() != 0){
            n = 1;
        }
        while(i < n){
            r = rand()%Size; //pick a random node from the motorway
            while(node(r)->empty()){
                r = rand()%Size;
            }
            s = node(r)->Vechicles.size(); //random vechicle within the node
            if(!node(r)->Vechicles[random_number(s-1)]->ready()){
                i++;
            }
        }
        return i;
    }

    int move(){
        int j;
        int counter = 0;
        for(j = Size -1 ; j >= 0; j--){
            counter+= node(j)->move_all();
        }
        return counter;
    }

    bool empty(){
        if(no_o_vechicles() == 0) return true;
        return false;
    }

};

int main(void){
    int i, temp;
    Vechicle* v;
    srand(time(0));
    Motorway my_motorway(NO_O_NODES, PER);
    for(i = 0; i < 200; i++){
        temp = random_number(NO_O_NODES-1);
        v = new Vechicle(i, temp);
        my_motorway.add(v, temp - random_number(temp));
    }
    
    while(!my_motorway.empty()){
        my_motorway.ready();
        my_motorway.move();
    }
    
}