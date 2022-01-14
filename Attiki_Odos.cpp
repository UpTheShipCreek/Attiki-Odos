class Node{
    int ID;
    String Name;
    Toll Tolls[]; //may use vector

    public:
    Node() = default;
    Node(int id, String name, int toll_num){
        this->ID = id;
        this->Name = name;

        Toll Tolls[toll_num];
        for(int i = 0; i < toll_num; i++){
            Tolls[i] = new Toll; //needs values
            Tolls[i].values(1, false); //random values for now
        }
    }
    String get_name(){
        return this->Name;
    }
}

class Segment{
    Vechicle Vechicles[]; //may use vector
    Node Entrance;
    Node Exit;

    public:
    Segment() = default;
    Segment(Node entrance, Node exit, Vechicle vechicles[]){
        this->Entrance = entrance;
        this->Exit = exit;
        this->Vechicles[] = vechicles[]; //just bullshiting
    }
}

class Vechicle{
    bool is_Ready;
    bool is_Waiting;
    Node Destination;

    public:
    Vechicle() = default;
    Vechicle(){
        this->is_Ready = false;
    }
    void set_ready(){
        this->is_Ready = true;
    }
}

class Toll{
    int Price;
    bool is_Electronic; //this is true if the toll is electronic and false if there is a conductor

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