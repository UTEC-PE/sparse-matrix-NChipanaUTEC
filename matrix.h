#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        Matrix():columns(0),rows(0){}
        Matrix(int sizeX, int sizeY):rows(sizeX),columns(sizeY){
          hRows = new Node<T>(-1,-1,0,nullptr,nullptr);
          hColumns = new Node<T>(-1,-1,0,nullptr,nullptr);
          Node<T>* temp = hColumns;
          for(int i = 1; i < rows; i++){
            Node<T>* nodonuevo = new Node<T>(0,0,i,nullptr,nullptr);
            temp -> next = nodonuevo;
            temp = temp -> next;
          }
          temp = hRows;
          for(int j = 1; j < columns; j++){
            Node<T>* nodonuevo = new Node<T>(0,0,j,nullptr,nullptr);
            temp -> down = nodonuevo;
            temp = temp -> down;
          }
        }
        void set(int x, int y, T data){
          if(data != 0 && x < rows && y < columns && 0 <= x && 0 <= y){
            Node<T>* nuevonodo = new Node<T>(x,y,data,nullptr,nullptr);

            Node<T>* temp1 = hColumns;
            for(int i = 0; i < y; i++){temp1 = temp1 -> next;}
            while(temp1 -> down && x > temp1->down->x){temp1 = temp1 -> down;}
            if(temp1->next)
                nuevonodo->down=temp1->down;
            temp1->down = nuevonodo;

            Node<T>* temp2 = hRows;
            for(int i = 0; i < x; i++){temp2 = temp2 -> down;}
            while(temp2 -> next && y > temp2->next->y){temp2 = temp2 -> next;}
            if(temp2 ->next)
                nuevonodo->next=temp2->next;
            temp2->next = nuevonodo;
          }
          else if(data == 0 && x < rows && y < columns && 0 <= x && 0 <= y){
              if(get(x,y)){
                  Node<T>* temp1 = hColumns;
                  for(int i = 0; i < y; i++){temp1 = temp1 -> next;}
                  while(temp1 -> down && x > temp1->down->x){temp1 = temp1 -> down;}

              }
          }
          else if(data != 0 && x > rows && y > columns && 0 <= x && 0 <= y){throw "ERROR: Posicion fuera de las dimensiones de la matriz";}
        }
        Node<T>* get(int x,int y){
          Node<T>* temp = hColumns;
          for(int i = 0; i < y; i++){temp = temp -> next;}
          Node<T>* temp2 = temp;
          while(temp2){
            if(temp2 -> y == y && temp2->x == x){return temp2;}
            temp2 = temp2->down;
          }
          return nullptr;
        }

        T operator()(int x, int y){
          Node<T>* temp = get(x,y);
          if(temp) return temp->data;
          else return 0;
        }

        Matrix<T> operator*(Matrix<T> other){
          if(columns == other.rows){
            Matrix<T> nuevo(columns,other.rows);
            for(int i=0;i<columns;++i){
                for(int j=0;j<other.rows;++j){
                    int mult = 0;
                    for(int k=0; k<columns;++k){
                        if(get(i,k)||other.get(k,j)){
                            mult += ((*this)(i,k))*(other(k,j));
                        }
                    }
                    nuevo.set(i,j,mult);
                }
            }
            return nuevo;
          }
          else
            throw "Error de dimensiones";
        }

        Matrix<T> operator*(T scalar){
          Matrix<T> nuevo(columns,rows);
          for(int i = 0; i<rows; i++){
            for(int j = 0;j<columns;j++){
              Node<T>* temp = get(i,j);
              if(temp){nuevo.set(i,j,temp->data*scalar);}
            }
          }
          return nuevo;
        }
        Matrix<T> operator+(Matrix<T> other){
          Matrix<T> nuevo(columns,rows);
          for(int i = 0; i<rows; i++){
            for(int j = 0;j<columns;j++){
              Node<T>* temp1 = get(i,j);
              Node<T>* temp2 = other.get(i,j);
              if(temp1&&!temp2){nuevo.set(i,j,temp1->data);}
              else if(!temp1&&temp2){nuevo.set(i,j,temp2->data);}
              else if(temp1&&temp2){nuevo.set(i,j,temp1->data+temp2->data);}
            }
          }
          return nuevo;
        }
        Matrix<T> operator-(Matrix<T> other){
          Matrix<T> nuevo(columns,rows);
          for(int i = 0; i<rows; i++){
            for(int j = 0;j<columns;j++){
              Node<T>* temp1 = get(i,j);
              Node<T>* temp2 = other.get(i,j);
              if(temp1&&!temp2){nuevo.set(i,j,temp1->data);}
              else if(!temp1&&temp2){nuevo.set(i,j,-temp2->data);}
              else if(temp1&&temp2){nuevo.set(i,j,temp1->data-temp2->data);}
            }
          }
          return nuevo;
        }
        Matrix<T> transposed(){
          Matrix<T> nuevo(columns,rows);
          for(int i = 0; i < rows; i++){
            for(int j = 0;j < columns;j++){
              nuevo.set(j,i,((*this)(i,j)));
            }
          }
          return nuevo;
        }
        Matrix<T> operator=(Matrix<T> other){
            if(columns == other.columns && rows==other.rows) {
                Matrix<T> nuevo(columns, rows);
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        Node<T> *temp = other.get(i, j);
                        if (temp) { nuevo.set(i, j, temp->data); }
                    }
                }
                return nuevo;
            }
            else{
                throw "Dimensiones diferentes, no se puede igualar";
            }
        }
        void print(){
          Node<T>* temp = hColumns;
          while(temp){
            cout << "\t"<<temp->data<<"->";
            temp = temp -> next;
          }
          cout << endl;
          temp = hRows;
          while(temp){
            cout << temp -> data<<"|";
            Node<T>* temp2 = temp;
            temp2 = temp2->next;
            cout <<"\t";
            while(temp2){
                cout << temp2->data<<"\t";
                temp2 = temp2 -> next;
            }
            cout << endl;
            temp = temp -> down;
          }
          cout << endl;
        }
        ~Matrix(){
            Node<T>* indices = hRows;
            while(indices) {
                Node<T> *temp = indices;
                while (temp) {
                    Node<T> *nododelete = temp;
                    temp = temp->next;
                    delete (nododelete);
                }
                indices = indices ->down;
            }
            indices = hRows;
            while(indices){
                Node<T> *temp = indices;
                indices = indices ->down;
                delete(temp);
            }
            indices = hColumns;
            while(indices){
                Node<T> *temp = indices;
                indices = indices ->next;
                delete(temp);
            }
        }
};

#endif
