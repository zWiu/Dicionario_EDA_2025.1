#ifndef CHAINED_HASHTABLE_HPP
#define CHAINED_HASHTABLE_HPP

#include <iostream>
#include <exception>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>

// Classe que implementa uma tabela hash com tratamento de
// colisao por encadeamento exterior (chained hash table).

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainedHashTable
{
public:
    // Construtor: cria uma tabela hash com um numero primo de slot
    ChainedHashTable(size_t size_table = 19, float load_factor = 1.0);

    // Retorna o número de elemento da tabela hash
    size_t size() const;

    // Se a tabela for vazia retorna true, senão retorna vazia
    bool empty() const;

    // Retorna o número de slots da HashTable, ou seja, o tamanho dela
    // Slots são os campos que um valor ocupar dentro da tabela,
    // essa função retorna tanto os vazios quanto ocupados.
    size_t bucket_count() const;

    // Recebe um número de slot n
    // Retorna o número de elementos naquele slot
    size_t bucket_size(size_t n) const;

    // Recebe a referência de uma chave constante k
    // Retorna o número do slot que a chave vai estar
    size_t bucket(const Key &k) const;

    // Retorna o fator de carga atual da tabela
    float load_factor() const;

    // Retorna o maior valor que o fator de carga pode ter
    float max_load_factor() const;

    // A tabela é limpa, ou seja, todos os seus valores são deletados
    // e seus atributos renicializados
    void clear();

    // Insere um novo elemento na tabela hash.
    // Se m_number_of_elements / m_table_size > m_max_load_factor entao a funcao
    // invoca a funcao rehash() passando o dobro do tamanho atual da tabela.
    // O elemento eh inserido somente se a chave dele ja nao estiver presente
    // na tabela (numa tabela hash, as chaves sao unicas).
    // Caso a insercao seja feita, isso incrementa o numero de elementos da tabela em 1 unidade.
    // Retorna true se e somente se a insercao for feita.
    bool add(const Key &k, const Value &v);

    // Recebe como entrada uma chave k e retorna true
    // se e somente se a chave k estiver presente na tabela hash.
    bool contains(const Key &k);

    // Retorna uma referencia para o valor associado a chave k.
    // Se k nao estiver na tabela, a funcao lanca uma out_of_range exception.
    Value &at(const Key &k);

    // Recebe um inteiro nao negativo m e faz com que o tamanho
    // da tabela seja um numero primo maior ou igual a m.
    // Se m for maior que o tamanho atual da tabela, um rehashing eh realizado.
    // Se m for menor que o tamanho atual da tabela, a funcao nao tem nenhum efeito.
    // Um rehashing eh uma operacao de reconstrucao da tabela:
    // Todos os elementos no container sao rearranjados de acordo
    // com o seu valor de hashing dentro na nova tabela.
    // Isto pode alterar a ordem de iteracao dos elementos dentro do container.
    // Operacoes de rehashing sao realizadas automaticamente pelo container
    // sempre que load_factor() ultrapassa o m_max_load_factor.
    void rehash(size_t m);

    // Remove da tabela hash o elemento com chave k se ele existir.
    // Ao remover o elemento, o numero de elementos eh decrementado em 1 unidade.
    // Retorna um booleano indicando se a remocao foi realizada.
    bool remove(const Key &k);

    // Redimensiona a tabela hash de modo que ela tenha
    // o tamanho mais apropriado a fim de conter pelo menos n elementos.
    // Se n > m_table_size * m_max_load_factor, entao a operacao
    // de rehash() eh executada sendo passado para ela o tamanho apropriado da nova tabela.
    // Se n <= m_table_size * m_max_load_factor, entao
    // a funcao nao tem efeito, nao faz nada.
    void reserve(size_t n);

    // Recebe um float lf e muda o valor
    // do atributo m_max_load_factor para esse valor.
    // Uma restricao eh que: 0 < m_max_load_factor.
    // Se lf nao estiver dentro desse intervalo entao uma
    // out_of_range exception eh lancada
    // Ao mudar o fator de carga, eh possivel que a tabela hash tenha
    // que ser redimensionada. Para isso, invocamos
    // a funcao reserve(m_number_of_elements).
    void set_max_load_factor(float lf);

    // Sobrecarga do operador de indexacao.
    // Se k corresponder a chave de um elemento na tabela, a funcao
    // retorna uma referencia ao seu valor mapeado. Caso contrario,
    // se k nao corresponder a chave de nenhum elemento na tabela,
    // a funcao insere um novo elemento com essa chave e retorna um
    // referencia ao seu valor mapeado. Observe que isso sempre aumenta
    // o tamanho da tabela em um, mesmo se nenhum valor mapeado for atribuido
    // ao elemento (o elemento eh construido usando seu construtor padrao)
    Value &operator[](const Key &k);

    // Versao const da sobrecarga do operador de indexacao.
    // Se k corresponder a chave de um elemento na tabela, a funcao
    // retorna uma referencia ao seu valor mapeado. Caso contrario,
    // se k nao corresponder a chave de nenhum elemento na tabela,
    // a funcao lanca uma out_of_range exception.
    const Value &operator[](const Key &k) const;

    // Retorna o contador de comparações de chave
    size_t get_cont_comparator() const;

    // Retoran o contador de colisões
    size_t get_cont_collisions() const;

    // Destrutor da HashTable
    ~ChainedHashTable();

private:
    // quantidade de pares (chave,valor)
    size_t m_number_of_elements;

    // tamanho atual da tabela
    size_t m_table_size;

    // O maior valor que o fator de carga pode ter.
    // Seja load_factor = m_number_of_elements/m_table_size.
    // Temos que load_factor <= m_max_load_factor.
    // Quando load_factor ultrapassa o valor de m_max_load_factor,
    // eh preciso executar a operacao de rehashing.
    float m_max_load_factor;

    // Tabela
    std::vector<std::list<std::pair<Key, Value>>> m_table;

    // Referencia para a funcao de codificacao
    Hash m_hashing;

    // Contador de comparações de chave
    size_t cont_comparator;

    // Contador de colisões
    size_t cont_collisions;

    // Incrementa o contador de comparações durante as operações da tabela.
    // Retorna verdadeiro para permitir seu uso dentro de expressões condicionais
    // sem interferir na lógica de decisão.
    bool cont_comp();

    // Retorna o menor numero primo que eh maior que ou igual
    // a x e maior que 2.
    size_t get_next_prime(size_t x);

    // Retorna um inteiro no intervalo [0 ... m_table_size-1].
    // Esta funcao recebe uma chave k e faz o seguinte:
    // (1) computa o codigo hash h(k) usando a
    //     funcao no atributo privado m_hashing
    // (2) computa um indice no intervalo [0 ... m_table_size-1]
    //     aplicando o metodo da divisao: h(k) % m_table_size
    size_t hash_code(const Key &k) const;
};

template <typename Key, typename Value, typename Hash>
ChainedHashTable<Key, Value, Hash>::ChainedHashTable(size_t size_table, float load_factor)
{
    m_number_of_elements = 0;
    m_table_size = get_next_prime(size_table);
    m_table.resize(m_table_size);
    cont_collisions = 0;
    cont_comparator = 0;
    if (load_factor <= 0)
        m_max_load_factor = 1.0;
    else
        m_max_load_factor = load_factor;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::size() const
{
    return m_number_of_elements;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::empty() const
{
    return m_number_of_elements == 0;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::bucket_count() const
{
    return m_table_size;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::bucket_size(size_t n) const
{
    return m_table.at(n).size();
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::bucket(const Key &k) const
{
    return hash_code(k);
}

template <typename Key, typename Value, typename Hash>
float ChainedHashTable<Key, Value, Hash>::load_factor() const
{
    return static_cast<float>(m_number_of_elements) / m_table_size;
}

template <typename Key, typename Value, typename Hash>
float ChainedHashTable<Key, Value, Hash>::max_load_factor() const
{
    return m_max_load_factor;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::clear()
{
    m_table.clear();
    m_table.resize(m_table_size);
    cont_collisions = 0;
    cont_comparator = 0;
    m_number_of_elements = 0;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::add(const Key &k, const Value &v)
{
    if (load_factor() >= m_max_load_factor)
        rehash(m_table_size/m_max_load_factor);
    size_t slot = hash_code(k);

    if(!m_table[slot].empty())
        cont_collisions++;

    for (auto p : m_table[slot])
        if (p.first == k && cont_comp())
            return false;

    m_table[slot].push_back({k, v});
    m_number_of_elements++;
    return true;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::contains(const Key &k)
{
    size_t slot = hash_code(k);
    for (auto p : m_table[slot])
        if (p.first == k)
            return true;
    return false;
}

template <typename Key, typename Value, typename Hash>
Value &ChainedHashTable<Key, Value, Hash>::at(const Key &k)
{
    size_t slot = hash_code(k);
    for (auto &p : m_table[slot])
        if (p.first == k)
            return p.second;

    throw std::invalid_argument("Invalid key");
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::rehash(size_t m)
{
    size_t new_table_size = get_next_prime(m);
    if (new_table_size > m_table_size)
    {
        std::vector<std::list<std::pair<Key, Value>>> old_vec = m_table;
        m_table.clear();
        m_number_of_elements = 0;
        m_table_size = new_table_size;
        m_table.resize(new_table_size);
        for (size_t i = 0; i < old_vec.size(); i++)
        {
            for (auto par : old_vec[i])
                add(par.first, par.second);
            old_vec[i].clear();
        }
    }
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::remove(const Key &k)
{
    size_t slot = hash_code(k);
    for (auto it = m_table[slot].begin(); it != m_table[slot].end(); ++it)
    {
        if (it->first == k && cont_comp())
        {
            m_table[slot].erase(it);
            m_number_of_elements--;
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::reserve(size_t n)
{
    if (n > m_table_size * m_max_load_factor)
    {
        rehash(n / m_max_load_factor);
    }
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::set_max_load_factor(float lf)
{
    if (lf <= 0)
        throw std::out_of_range("invalid load factor");

    max_load_factor = lf;
    reserve(m_number_of_elements);
}

template <typename Key, typename Value, typename Hash>
Value &ChainedHashTable<Key, Value, Hash>::operator[](const Key &k)
{
    size_t slot = hash_code(k);
    for (auto &par : m_table[slot])
        if (par.first == k)
            return par.second;

    m_table[slot].push_back({k, Value()});
    return m_table[slot].back().second;
}

template <typename Key, typename Value, typename Hash>
const Value &ChainedHashTable<Key, Value, Hash>::operator[](const Key &k) const
{
    return at(k);
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::get_cont_comparator() const
{
    return cont_comparator;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::get_cont_collisions() const
{
    return cont_collisions;
}

template <typename Key, typename Value, typename Hash>
ChainedHashTable<Key, Value, Hash>::~ChainedHashTable()
{
    m_table.clear();
    m_table_size = 0;
    m_number_of_elements = 0;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::cont_comp()
{
    cont_comparator++;
    return true;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::get_next_prime(size_t x)
{
    if (x <= 2)
        return 3;
    x = (x % 2 == 0) ? x + 1 : x;
    bool not_prime = true;
    while (not_prime)
    {
        not_prime = false;
        for (int i = 3; i <= sqrt(x); i += 2)
        {
            if (x % i == 0)
            {
                not_prime = true;
                break;
            }
        }
        x += 2;
    }
    return x - 2;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::hash_code(const Key &k) const
{
    return m_hashing(k) % m_table_size;
}

#endif
