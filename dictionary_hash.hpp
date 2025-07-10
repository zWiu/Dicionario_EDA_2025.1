#ifndef DICTIONARY_HASH_HPP
#define DICTIONARY_HASH_HPP

#include <utility>
#include <functional>
#include <list>

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash = std::hash<Key>>
class Dictionary_Hash
{
private:
    Structure<Key, Value, Hash> dictionary;

public:
    // Construtor vazio
    Dictionary_Hash();

    // Construtor inicializado com lista de pares Chave-Valor
    Dictionary_Hash(std::list<std::pair<Key, Value>> initial_list);

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

    // Esvazia o dicionário.
    void clear();

    // Destrutor
    ~Dictionary_Hash();
};

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
Dictionary_Hash<Structure, Key, Value, Hash>::Dictionary_Hash()
    : dictionary{} {}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
Dictionary_Hash<Structure, Key, Value, Hash>::Dictionary_Hash(std::list<std::pair<Key, Value>> initial_list)
{
    for (const auto &par : initial_list)
    {
        dictionary.add(par.first, par.second);
    }
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
void Dictionary_Hash<Structure, Key, Value, Hash>::insert(Key key, Value value)
{
    dictionary.add(key, value);
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
void Dictionary_Hash<Structure, Key, Value, Hash>::update(Key key, Value value)
{
    dictionary.update(key, value);
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
Value &Dictionary_Hash<Structure, Key, Value, Hash>::at(Key key)
{
    return dictionary.at(key);
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
void Dictionary_Hash<Structure, Key, Value, Hash>::remove(Key key)
{
    dictionary.remove(key);
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
bool Dictionary_Hash<Structure, Key, Value, Hash>::contains(Key key)
{
    return dictionary.contains(key);
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
Value &Dictionary_Hash<Structure, Key, Value, Hash>::operator[](Key key)
{
    if (!dictionary.contains(key))
        insert(key, Value());
    return dictionary[key];
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
size_t Dictionary_Hash<Structure, Key, Value, Hash>::size()
{
    return dictionary.size();
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
void Dictionary_Hash<Structure, Key, Value, Hash>::show()
{
    dictionary.show();
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
void Dictionary_Hash<Structure, Key, Value, Hash>::clear()
{
    dictionary.clear();
}

template <template <typename, typename, typename> class Structure, typename Key, typename Value, typename Hash>
Dictionary_Hash<Structure, Key, Value, Hash>::~Dictionary_Hash()
{
    dictionary.clear();
}

#endif