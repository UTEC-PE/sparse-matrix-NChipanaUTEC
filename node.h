#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {

public:
    int x, y;
    T data;
    Node* next;
    Node* down;
    Node(int x, int y, T data, Node* next, Node* down):x(x),y(y),data(data),next(next),down(down){}
};

#endif
