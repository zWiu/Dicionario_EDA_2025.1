#include <iostream>
#include <exception>

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

namespace std {
    template <>
    struct hash<Pares> {
        size_t operator()(const Pares& p) const {
            return hash<int>()(p.k) ^ (hash<std::string>()(p.v) << 1);
        }
    };
}

#include "ChainedHashTable.hpp"
#include "AVL.hpp"
void testChainedHashTable()
{
    ChainedHashTable<Pares, int> tabela(7, 1.5);

    Pares p1(1, "A");
    Pares p2(2, "B");
    Pares p3(3, "C");
    Pares p4(4, "D");
    Pares p5(5, "E");

    // Teste de adição
    cout << "Adicionando elementos:" << endl;
    if(tabela.add(p1, 10))
        cout << "Adicionado " << p1 << ", " << 10 << endl; 
    if(tabela.add(p2, 20))
        cout << "Adicionado " << p2 << ", " << 20 << endl;
    if(tabela.add(p3, 30))
        cout << "Adicionado " << p3 << ", " << 30 << endl;
    if(tabela.add(p4, 40))
        cout << "Adicionado " << p4 << ", " << 40 << endl;
    if(tabela.add(p5, 50))
        cout << "Adicionado " << p5 << ", " << 50 << endl;

    // Tamanho e fator de carga
    cout << "\nTamanho atual: " << tabela.size() << endl;
    cout << "Fator de carga: " << tabela.load_factor() << endl;

    // Teste de contains
    cout << "\nContém p3? " << (tabela.contains(p3) ? "Sim" : "Não") << endl;

    // Teste do método at
    try {
        cout << "Valor associado a p2: " << tabela.at(p2) << endl;
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    // Teste do operador []
    cout << "\nAcessando p4 com operador []: " << tabela[p4] << endl;
    tabela[p4] = 100;
    cout << "Novo valor de p4: " << tabela[p4] << endl;

    // Teste de remoção
    cout << "\nRemovendo p1..." << endl;
    bool removido = tabela.remove(p1);
    cout << (removido ? "Removido com sucesso." : "Não encontrado.") << endl;

    cout << "Contém p1? " << (tabela.contains(p1) ? "Sim" : "Não") << endl;

    // Teste de bucket e bucket_size
    cout << "\nBucket de p3: " << tabela.bucket(p3) << endl;
    cout << "Tamanho do bucket de p3: " << tabela.bucket_size(tabela.bucket(p3)) << endl;

    // Teste de rehash forçado via reserve
    cout << "\nExecutando reserve(50)..." << endl;
    tabela.reserve(50);
    cout << "Novo bucket_count: " << tabela.bucket_count() << endl;

    // Contadores:
    cout << "\nContador de comparações feitas nas chaves: " << tabela.get_cont_comparator() << endl;
    cout << "Contador de colisões: " << tabela.get_cont_collisions() << endl;

    // Teste de clear
    cout << "\nLimpando a tabela..." << endl;
    tabela.clear();
    cout << "Tabela está vazia? " << (tabela.empty() ? "Sim" : "Não") << endl;
}

int main(){
    
    testChainedHashTable();
}