#include <string>
#include <vector>
#include "random.h"

class Node{
    int ID;
    String Name;
    vector <Toll> Tolls; 

    public:
    Node() = default;
    Node(int id, String name, int toll_num, int price){
        this->ID = id;
        this->Name = name;
        for(int i = 0; i < toll_num; i++){
            Toll T(price, coin_flip());
            Tolls.push_back(T);
        }
    }
    String get_name(){
        return this->Name;
    }
}

class Segment{
    int Capacity;
    vector <Vechicle> Vechicles; //may use vector
    Node Entrance;
    Node Exit;

    public:
    Segment() = default;
    Segment(int capacity, Node entrance, Node exit, vector <Vechicle> vechicles){
        this->Capacity = capacity;
        this->Entrance = entrance;
        this->Exit = exit;
        this->Vechicles = vechicles; //just bullshiting
    }
    bool is_full(){
        if(Vechicles.size() == this->Capacity){
            return true;
        }
        else return false;
    }
}

class Vechicle{
    bool is_Ready;
    bool is_Waiting;
    Node Destination;

    public:
    Vechicle() = default;
    Vechicle(Node destination){
        this->Destination = destination;
        this->is_Ready = false;
    }
    void set_ready(){
        this->is_Ready = true;
    }
}

class Toll{
    int Price;
    bool is_Electronic; //this is true if the toll is electronic and false if there is a conductor
    vector<Vechicle> Queue;

    public:
    Toll() = default;
    Toll(int price, bool is_electronic){
        this->Price = price;
        this->is_Electronic = is_electronic;
    }
    void values(int price, bool is_electronic){
        this->Price = price;
        this->is_Electronic = is_electronic;
    }
}