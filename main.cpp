#include <iostream>
#include <exception>
#include <windows.h>

using namespace std;

struct Pares
{
    int k;
    string v;

    Pares(int k = 0, string v = "")
    {
        this->k = k;
        this->v = v;
    }

    Pares(const Pares &p)
    {
        this->k = p.k;
        this->v = p.v;
    }

    Pares &operator=(const Pares &p)
    {
        this->k = p.k;
        this->v = p.v;

        return *this;
    }

    bool operator<(const Pares &p)
    {
        return this->v < p.v;
    }

    bool operator>(const Pares &p)
    {
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

    friend std::ostream &operator<<(std::ostream &os, const Pares &p)
    {
        os << "(" << p.k << ", " << p.v << ")";
        return os;
    }
};

namespace std
{
    template <>
    struct hash<Pares>
    {
        size_t operator()(const Pares &p) const
        {
            return hash<int>()(p.k) ^ (hash<std::string>()(p.v) << 1);
        }
    };
}
#include "./structures/ChainedHashTable.hpp"
#include "./structures/OpenAdressingHashTable.hpp"
#include "./structures/AVL.hpp"
#include "./structures/RBT.hpp"
#include "dictionary_tree.hpp"
#include "dictionary_hash.hpp"

void testChainedHashTable()
{
    ChainedHashTable<Pares, int> tabela(7, 1.5);

    Pares p1(10, "A");
    Pares p2(7, "B");
    Pares p3(15, "C");
    Pares p4(43, "D");
    Pares p5(5, "E");
    cout << "\n***TESTE DA CHAINED HASH TABLE***" << endl;

    // Teste de adição
    cout << "Adicionando elementos:" << endl;
    if (tabela.add(p1, 2))
        cout << "Adicionado " << p1 << ", " << 10 << endl;
    if (tabela.add(p2, 20))
        cout << "Adicionado " << p2 << ", " << 20 << endl;
    if (tabela.add(p3, 30))
        cout << "Adicionado " << p3 << ", " << 30 << endl;
    if (tabela.add(p4, 40))
        cout << "Adicionado " << p4 << ", " << 40 << endl;
    if (tabela.add(p5, 50))
        cout << "Adicionado " << p5 << ", " << 50 << endl;

    // Mostrando a tabela
    tabela.show();

    // Tamanho e fator de carga
    cout << "\nTamanho atual: " << tabela.size() << endl;
    cout << "Fator de carga: " << tabela.load_factor() << endl;

    // Teste de contains
    cout << "\nContém p3? " << (tabela.contains(p3) ? "Sim" : "Não") << endl;

    // Teste do método at
    try
    {
        cout << "Valor associado a p2: " << tabela.at(p2) << endl;
    }
    catch (const exception &e)
    {
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

void testOpenAdressingHashTable()
{
    OpenAdressingHashTable<Pares, int> tabela(7, 1.5);

    Pares p1(10, "A");
    Pares p2(7, "B");
    Pares p3(15, "C");
    Pares p4(43, "D");
    Pares p5(5, "E");
    cout << "\n***TESTE DA HASH TABLE***" << endl;

    // Teste de adição
    cout << "Adicionando elementos:" << endl;
    if (tabela.add(p1, 2))
        cout << "Adicionado " << p1 << ", " << 10 << endl;
    if (tabela.add(p2, 20))
        cout << "Adicionado " << p2 << ", " << 20 << endl;
    if (tabela.add(p3, 30))
        cout << "Adicionado " << p3 << ", " << 30 << endl;
    if (tabela.add(p4, 40))
        cout << "Adicionado " << p4 << ", " << 40 << endl;
    if (tabela.add(p5, 50))
        cout << "Adicionado " << p5 << ", " << 50 << endl;

    // Mostrando a tabela
    tabela.show();

    // Tamanho e fator de carga
    cout << "\nTamanho atual: " << tabela.size() << endl;
    cout << "Fator de carga: " << tabela.load_factor() << endl;

    // Teste de contains
    cout << "\nContém p3? " << (tabela.contains(p3) ? "Sim" : "Não") << endl;

    // Teste do método at
    try
    {
        cout << "Valor associado a p2: " << tabela.at(p2) << endl;
    }
    catch (const exception &e)
    {
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

void testAVL()
{
    AVL<Pares, int> arvore;

    Pares p1(10, "A");
    Pares p2(7, "B");
    Pares p3(15, "C");
    Pares p4(43, "D");
    Pares p5(5, "E");
    cout << "\n***TESTE DA AVL***" << endl;

    // Teste de adição
    cout << "Adicionando elementos:" << endl;
    arvore.add(p1, 2);
    cout << "Adicionado " << p1 << ", " << 10 << endl;
    arvore.add(p2, 20);
    cout << "Adicionado " << p2 << ", " << 20 << endl;
    arvore.add(p3, 30);
    cout << "Adicionado " << p3 << ", " << 30 << endl;
    arvore.add(p4, 40);
    cout << "Adicionado " << p4 << ", " << 40 << endl;
    arvore.add(p5, 50);
    cout << "Adicionado " << p5 << ", " << 50 << endl;

    cout << "Criando cópia da primeira árvore..." << endl;
    AVL<Pares, int> arvore_copia(arvore);

    // Estrutura da árvore
    arvore.show_tree();

    // Teste de remoção
    cout << "\nRemovendo elementos:" << endl;
    arvore.remove(p3);
    cout << "Elemento " << p3 << " removido da árvore 1" << endl;
    arvore_copia.remove(p2);
    cout << "Elemento " << p2 << " removido da árvore 2" << endl;

    // Teste do construtor de cópia
    cout << "\nResultado das remoções: " << endl;
    cout << "Árvore 1:" << endl;
    arvore.show();
    cout << "Árvore 2:" << endl;
    arvore_copia.show();

    // Teste de contains
    cout << "Contém " << p1 << " na árvore 1? " << (arvore.contains(p1) ? "Sim" : "Não") << endl;
    cout << "Contém " << p3 << " na árvore 1? " << (arvore.contains(p3) ? "Sim" : "Não") << endl;

    // Teste de update
    cout << "\nTestando a função de update" << endl;
    arvore.update(p2, 50);
    cout << "Elemento " << p2 << " atualizado na árvore 1" << endl;
    arvore.update(p1, 130);
    cout << "Elemento " << p1 << " atualizado na árvore 1" << endl;
    try
    {
        arvore.update(p3, 70);
    }
    catch (const exception &e)
    {
        cout << "Tentativa de atualização do elemento " << p3 << endl;
    }

    cout << "\nTeste do operator[]" << endl;
    cout << "Valor de " << p2 << " :" << arvore[p2] << endl;
    cout << "Valor de " << p3 << " :" << arvore[p3] << endl;

    cout << "\nResultado das atualizações: " << endl;
    cout << "Árvore 1:" << endl;
    arvore.show();

    // Teste de contadores
    cout << "\nContadores da árvore 1" << endl;
    cout << "Contador de comparações feitas nas chaves: " << arvore.get_cont_comparator() << endl;
    cout << "Contador de rotações realizadas na árvore: " << arvore.get_cont_rotation() << endl;

    cout << "\nContadores da árvore 2" << endl;
    cout << "Contador de comparações feitas nas chaves: " << arvore_copia.get_cont_comparator() << endl;
    cout << "Contador de rotações realizadas na árvore: " << arvore_copia.get_cont_rotation() << endl;

    // Teste de clear
    cout << "\nLimpando a arvore..." << endl;
    arvore.clear();
    cout << "Árvore está vazia? " << (arvore.empty() ? "Sim" : "Não") << endl;
}

void testRBT()
{
    RBT<Pares, int> arvore;

    Pares p1(10, "A");
    Pares p2(7, "B");
    Pares p3(15, "C");
    Pares p4(43, "D");
    Pares p5(5, "E");
    cout << "\n***TESTE DA RBT***" << endl;

    // Teste de adição
    cout << "Adicionando elementos:" << endl;
    arvore.add(p1, 2);
    cout << "Adicionado " << p1 << ", " << 2 << endl;
    arvore.add(p2, 20);
    cout << "Adicionado " << p2 << ", " << 20 << endl;
    arvore.add(p3, 30);
    cout << "Adicionado " << p3 << ", " << 30 << endl;
    arvore.add(p4, 40);
    cout << "Adicionado " << p4 << ", " << 40 << endl;
    arvore.add(p5, 50);
    cout << "Adicionado " << p5 << ", " << 50 << endl;

    // Teste de cópia
    RBT<Pares, int> arvore_copia(arvore);

    // Estrutura da árvore
    cout << "\nÁrvore 1:" << endl;
    arvore.show_tree();
    cout << "Árvore 2:" << endl;
    arvore_copia.show_tree();

    // Teste de remoção
    cout << "\nRemovendo elementos:" << endl;
    arvore.remove(p3);
    cout << "Elemento " << p3 << " removido da árvore 1" << endl;
    arvore_copia.remove(p2);
    cout << "Elemento " << p2 << " removido da árvore 1" << endl;

    // Teste do construtor de cópia
    cout << "\nResultado das remoções: " << endl;
    cout << "Árvore 1:" << endl;
    arvore.show();
    cout << "Árvore 2:" << endl;
    arvore_copia.show();

    // Teste de contains
    cout << "Contém " << p1 << " na árvore 1? " << (arvore.contains(p1) ? "Sim" : "Não") << endl;
    cout << "Contém " << p3 << " na árvore 1? " << (arvore.contains(p3) ? "Sim" : "Não") << endl;

    // Teste de update
    cout << "\nTestando a função de update" << endl;
    arvore.update(p2, 50);
    cout << "Elemento " << p2 << " atualizado na árvore 1" << endl;
    arvore.update(p1, 130);
    cout << "Elemento " << p1 << " atualizado na árvore 1" << endl;
    try
    {
        arvore.update(p3, 70);
    }
    catch (const invalid_argument &e)
    {
        cout << "Tentativa de atualização do elemento " << p3 << endl;
    }

    cout << "\nTeste do operator[]" << endl;
    cout << "Valor de " << p2 << " :" << arvore[p2] << endl;
    cout << "Valor de " << p3 << " :" << arvore[p3] << endl;

    cout << "\nResultado das atualizações: " << endl;
    cout << "Árvore 1:" << endl;
    arvore.show();
    cout << "Árvore 2:" << endl;
    arvore_copia.show();

    // Teste de contadores
    cout << "\nContadores da árvore 1" << endl;
    cout << "Contador de comparações feitas nas chaves: " << arvore.get_cont_comparator() << endl;
    cout << "Contador de rotações realizadas na árvore: " << arvore.get_cont_rotation() << endl;

    cout << "\nContadores da árvore 2" << endl;
    cout << "Contador de comparações feitas nas chaves: " << arvore_copia.get_cont_comparator() << endl;
    cout << "Contador de rotações realizadas na árvore: " << arvore_copia.get_cont_rotation() << endl;

    // Teste de clear
    cout << "\nLimpando a arvore..." << endl;
    arvore.clear();
    cout << "Árvore está vazia? " << (arvore.empty() ? "Sim" : "Não") << endl;
}

void testeDictionaryOpenHash()
{
    Dictionary_Hash<OpenAdressingHashTable, string, int> dicionario;

    // Testanto a inserção
    dicionario.insert("Pei", 2);

    // Testando o retorno
    cout << dicionario.at("Pei") << endl;

    dicionario.show();

    // Testando a remoção
    dicionario.remove("Pei");
    cout << "Concluido" << endl;
}

void testeDictionaryAVL()
{
    Dictionary_Tree<AVL, string, int> dicionario;
    cout << "Testando inserção" << endl;
    // Testanto a inserção
    dicionario.insert("Pei", 2);
    cout << "Testante update" << endl;
    // Testando a atualização
    dicionario.update("Pei", 10);
    cout << "testando operator[]" << endl;
    // Testando o retorno
    cout << dicionario["Pei"] << endl;

    dicionario.show();
    // Testando a remoção
    dicionario.remove("Pei");
}

int main(int argc, char *argv[])
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    string str;
    for (int i = 1; i <= argc; i++)
    {
        cout << argv[i] << endl;
        str = argv[i];
        if (str == "teste_chained_hash")
            testChainedHashTable();
        else if (str == "teste_open_hash")
            testOpenAdressingHashTable();
        else if (str == "teste_avl")
            testAVL();
        else if (str == "teste_rbt")
            testRBT();
        else if (str == "teste_dicionario_open_hash")
            testeDictionaryOpenHash();
        else if (str == "teste_dicionario_avl")
            testeDictionaryAVL();
    }
    cout << "Bye!";
}