#ifndef DICTIONARY_TREE_HPP
#define DICTIONARY_TREE_HPP

#include <utility>
#include <list>
#include <chrono>

template <template <typename, typename> class Structure, typename Key, typename Value>
class Dictionary_Tree
{
private:
    Structure<Key, Value> dictionary;

    // Guarda o momento em que a estrutura foi criada 
    std::chrono::high_resolution_clock::time_point start_time;

public:

    // Construtor vazio
    Dictionary_Tree();

    // Construtor inicializado com lista de pares Chave-Valor
    Dictionary_Tree(std::list<std::pair<Key,Value>> initial_list);

    // Função de inserção do dicionário, adiciona um novo par de valores ao dicionário,
    // usa as funções de add das estruturas utilizadas no projeto.
    void insert(Key key, Value value);

    // Atualiza o valor de uma chave já inserida no dicionário.
    void update(Key key, Value value);

    // Recupera o valor associado a uma chave específica.
    Value &at(Key key);

    // Remove um par Chave-Valor do dicionário.
    void remove(Key key);

    // Verifica se uma chave está contida no dicionário
    bool contains(Key key);

    // Operator de indexação do dicionario, retorna a referencia ao valor associado a chave
    // se o falor não tiver sido inserido, insere e retorna a referencia a esse valor
    Value &operator[](Key key);

    // Retorna o tamanho do dicionário.
    size_t size();

    // Mostra todos os valores do dicionario, ordenados pela chave
    void show();

    // Retorna a duração do dicionario
    size_t get_duration();

    // Esvazia o dicionário.
    void clear();

    // Destrutor
    ~Dictionary_Tree();
};

template <template <typename, typename> class Structure, typename Key, typename Value>
Dictionary_Tree<Structure, Key,Value >::Dictionary_Tree()
: dictionary{}, start_time{std::chrono::high_resolution_clock::now()} {}

template <template <typename, typename> class Structure, typename Key, typename Value>
Dictionary_Tree<Structure, Key,Value >::Dictionary_Tree(std::list<std::pair<Key, Value>> initial_list)
{
    start_time = std::chrono::high_resolution_clock::now();
    for(const auto& par : initial_list)
    {
        dictionary.add(par.first, par.second);
    }
}

template <template <typename, typename> class Structure, typename Key, typename Value>
void Dictionary_Tree<Structure, Key,Value >::insert(Key key, Value value)
{
    dictionary.add(key, value);
}

template <template <typename, typename> class Structure, typename Key, typename Value>
void Dictionary_Tree<Structure, Key,Value >::update(Key key, Value value)
{
    dictionary.update(key, value);
}

template <template <typename, typename> class Structure, typename Key, typename Value>
Value &Dictionary_Tree<Structure, Key,Value >::at(Key key)
{
    return dictionary.at(key);
}

template <template <typename, typename> class Structure, typename Key, typename Value>
void Dictionary_Tree<Structure, Key,Value >::remove(Key key)
{
    dictionary.remove(key);
}

template <template <typename, typename> class Structure, typename Key, typename Value>
bool Dictionary_Tree<Structure, Key,Value >::contains(Key key)
{
    return dictionary.contains(key);
}

template <template <typename, typename> class Structure, typename Key, typename Value>
Value &Dictionary_Tree<Structure, Key,Value >::operator[](Key key)
{
    if(!dictionary.contains(key))
        insert(key, Value());
    return dictionary[key];
}

template <template <typename, typename> class Structure, typename Key, typename Value>
size_t Dictionary_Tree<Structure,Key,Value>::size()
{
    return dictionary.size();
}

template <template <typename, typename> class Structure, typename Key, typename Value>
void Dictionary_Tree<Structure,Key,Value>::show()
{
    std::cout << "Quantidade de elementos: " << dictionary.size() << std::endl;
    std::cout << "Comparações entre chaves realizadas(durante a construção do dicionário): " << dictionary.get_cont_comparator() << std::endl;
    std::cout << "Rotações ocorridas(durante a construção do dicionário): " << dictionary.get_cont_rotation() << std::endl;
    std::cout << "Tempo de construção do dicionário(até o momento): " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start_time).count() << "ms" << std::endl << std::endl;
    dictionary.show();
}


template <template <typename, typename> class Structure, typename Key, typename Value>
size_t Dictionary_Tree<Structure,Key,Value>::get_duration()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start_time).count();
}

template <template <typename, typename> class Structure, typename Key, typename Value>
void Dictionary_Tree<Structure,Key,Value>::clear()
{
    dictionary.clear();
    start_time = std::chrono::high_resolution_clock::now();
}

template <template <typename, typename> class Structure, typename Key, typename Value>
Dictionary_Tree<Structure, Key,Value >::~Dictionary_Tree()
{
    dictionary.clear();
}

#endif