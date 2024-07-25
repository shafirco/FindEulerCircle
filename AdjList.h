#ifndef ADJ_LIST_H
#define ADJ_LIST_H


template <typename T>
class AdjList {
public:
    template <typename U>
    struct Node {
        U data;
        Node<U>* next;
        Node(const U& value) : data(value), next(nullptr) {}
    };
    Node<T>* head;
    Node<T>* tail;
    int size = 0;

    AdjList() : head(nullptr), tail(nullptr) {}
    ~AdjList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T& getHead() { return head; }

    T& getTail() { return tail->data; };

    void append(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    int getSize() { return size; }

};

typedef int DirectedNighborData;

struct UndirectedNeighborData {
    int id;
    UndirectedNeighborData* twin; // save the same edge repesents in the other adjList.
    bool mark = false; // to check if it has been passed by this edge.

    UndirectedNeighborData(int id, UndirectedNeighborData* twin) : id(id), twin(twin){}
    void setTwin(UndirectedNeighborData* twinToAdd) { twin = twinToAdd; }
};

#endif // !ADJ_LIST_H
