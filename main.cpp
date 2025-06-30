#include <iostream>
#include "AVL.hpp"
using namespace std;

struct Pares{
    int k;
    string v;

    Pares(int k = 0, string v = ""){
        this->k = k;
        this->v = v;
    }

    Pares(const Pares &p){
        this->k = p.k;
        this->v = p.v;
    }

    Pares &operator=(const Pares &p)
    {
        this->k = p.k;
        this->v = p.v;

        return *this;
    }

    bool operator<(const Pares &p){
        return this->v < p.v;
    }

    bool operator>(const Pares &p){
        return this->v > p.v;
    }

    bool operator==(const Pares &p)
    {
        return this->v == p.v;
    }

    bool operator!=(const Pares &p)
    {
        return this->v != p.v;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pares& p) {
        os << "(" << p.k << ", " << p.v << ")";
        return os;
    }
};

int main(){
    AVL<Pares> arvore;
    for(int i = 1; i <= 10; i++)
    {
        
        string str(1, 'A'+i);

        Pares temp(i, str);
        arvore.insert(temp);
    }
    Pares temp(4, "E");


    AVL<Pares> arvore2(arvore);

    arvore.show();
    arvore.erase(temp);
    arvore.show();
    arvore2.show();
}