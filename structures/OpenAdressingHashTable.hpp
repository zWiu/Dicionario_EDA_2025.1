#ifndef OPENADRESSINGHASHTABLE_HPP
#define OPENADRESSINGHASHTABLE_HPP

#include <iostream>
#include <exception>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>

#define EMPTY 0
#define DELETED 1
#define ACTIVE 2

template <typename Key, typename Value>
struct Element
{
    std::pair<Key, Value> value; // Guarda o valor e a chave do elemento
    int status;                  // Guarda o status do item, se ele é EMPTY, DELETED ou ACTIVE

    Element()
    : value{Key(), Value()}, status{EMPTY} {}

    Element(Key key, Value value, int status)
    {
        this->value.first = key;
        this->value.second = value;
        this->status = status;
    }
};

// Classe que implementa uma tabela hash com tratamento de
// colisão por endereçamento aberto

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAdressingHashTable
{
public:
    // Construtor: cria uma tabela hash com um numero primo de slot
    OpenAdressingHashTable(size_t size_table = 19, float load_factor = 1.0);

    // Retorna o número de elemento da tabela hash
    size_t size() const;

    // Se a tabela for vazia retorna true, senão retorna vazia
    bool empty() const;

    // Retorna o número de slots da OpenAdressingHashTable, ou seja, o tamanho dela
    // Slots são os campos que um valor ocupar dentro da tabela,
    // essa função retorna tanto os vazios quanto ocupados.
    size_t bucket_count() const;

    // Retorna o fator de carga atual da tabela
    float load_factor() const;

    // Retorna o maior valor que o fator de carga pode ter
    float max_load_factor() const;

    // A tabela é limpa, ou seja, todos os seus valores são deletados
    // e seus atributos renicializados
    void clear();

    // Insere um novo elemento na tabela hash.
    // Usa a função aux_search(), para procurar a chave, caso ela já esteja sendo usada
    // atualiza o valor dela, se não tiver na tabela uma nova busca é realizada para inserir nela.
    bool add(const Key &k, const Value &v);

    // Recebe uma chave e atualiza o valor associada aquela chave
    // Caso a operação dê certo retorna true,
    // caso a operação falhe retorna false
    bool update(const Key &k, const Value &v);

    // Recebe como entrada uma chave k e retorna true
    // se e somente se a chave k estiver presente na tabela hash.
    bool contains(const Key &k);

    // Recebe a referência de uma chave constante k
    // Procura a chave, caso encontre retorna o valor associado
    // se não lança uma excessão
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
    // referencia ao seu valor mapeado. caso a inserção não funcione
    // Chama o rehash para duas vezes o tamanho atual
    // tenta a inserção de novo
    // Caso funcione continua.
    // Caso não lança uma excessão
    // Observe que isso sempre aumenta o tamanho da tabela em um,
    //  mesmo se nenhum valor mapeado for atribuido ao elemento
    //(o elemento eh construido usando seu construtor padrao)
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

    // Guarda todos os valores da hash table num vector
    // ordena ele, e mostra ele no terminal.
    void show() const;

    // Destrutor da OpenAdressingHashTable
    ~OpenAdressingHashTable();

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
    std::vector<Element<Key, Value>> m_table;

    // Referencia para a funcao de codificacao
    Hash m_hashing;

    // Contador de comparações de chave
    size_t cont_comparator;

    // Contador de colisões
    size_t cont_collisions;

    // A função aux_search realiza sondagem linear para encontrar a posição
    // de uma chave específica dentro da tabela hash. Se a chave estiver
    // presente em um slot ativo, retorna seu índice; caso contrário,
    // lança exceção indicando que a chave não foi encontrada.
    size_t aux_search(Key k);

    // Incrementa o contador de comparações durante as operações da tabela.
    // Retorna verdadeiro para permitir seu uso dentro de expressões condicionais
    // sem interferir na lógica de decisão.
    bool cont_comp();

    // Retorna o menor numero primo que eh maior que ou igual
    // a x e maior que 2.
    size_t get_next_prime(size_t x);

    // Retorna um inteiro no intervalo [0 ... m_table_size-1].
    // Esta funcao recebe uma chave k e um indice i faz o seguinte:
    // Realiza dois modelos de hashing:
    //      h1 = m_hashing(k)%m_table_size
    //      h2 = 1+(m_hashing(k)%(m_table_size-1))
    // Juntando as duas num modelo de hashing duplo, tal que:
    //      hash_duplo: (h1+i*h2)%m_table_size
    size_t hash_code(const Key &k, size_t i) const;
};

template <typename Key, typename Value, typename Hash>
OpenAdressingHashTable<Key, Value, Hash>::OpenAdressingHashTable(size_t size_table, float load_factor)
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
size_t OpenAdressingHashTable<Key, Value, Hash>::size() const
{
    return m_number_of_elements;
}

template <typename Key, typename Value, typename Hash>
bool OpenAdressingHashTable<Key, Value, Hash>::empty() const
{
    return m_number_of_elements == 0;
}

template <typename Key, typename Value, typename Hash>
size_t OpenAdressingHashTable<Key, Value, Hash>::bucket_count() const
{
    return m_table_size;
}

template <typename Key, typename Value, typename Hash>
float OpenAdressingHashTable<Key, Value, Hash>::load_factor() const
{
    return static_cast<float>(m_number_of_elements) / m_table_size;
}

template <typename Key, typename Value, typename Hash>
float OpenAdressingHashTable<Key, Value, Hash>::max_load_factor() const
{
    return m_max_load_factor;
}

template <typename Key, typename Value, typename Hash>
void OpenAdressingHashTable<Key, Value, Hash>::clear()
{
    m_table.clear();
    m_table.resize(m_table_size);
    cont_collisions = 0;
    cont_comparator = 0;
    m_number_of_elements = 0;
}

template <typename Key, typename Value, typename Hash>
bool OpenAdressingHashTable<Key, Value, Hash>::add(const Key &k, const Value &v)
{
    try
    {
        size_t m = aux_search(k);
        m_table[m].value.second = v;
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        size_t i = 0;
        do
        {
            size_t j = hash_code(k, i);
            if (cont_comp() && m_table[j].status != ACTIVE)
            {
                m_table[j].value.first = k;
                m_table[j].value.second = v;
                m_table[j].status = ACTIVE;
                m_number_of_elements++;
                return true;
            }
            cont_collisions++;
            i++;
        } while (i < m_table_size);
        return false;
    }
}

template <typename Key, typename Value, typename Hash>
bool OpenAdressingHashTable<Key, Value, Hash>::update(const Key &k, const Value &v)
{
    try
    {
        size_t m = aux_search(k);
        m_table[m].value.second = v;
        return true;
    }
    catch(const std::invalid_argument &e)
    {
        return false;
    }
}

template <typename Key, typename Value, typename Hash>
bool OpenAdressingHashTable<Key, Value, Hash>::contains(const Key &k)
{
    try
    {
        aux_search(k);
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}

template <typename Key, typename Value, typename Hash>
Value &OpenAdressingHashTable<Key, Value, Hash>::at(const Key &k)
{
    try
    {
        size_t m = aux_search(k);
        return m_table[m].value.second;
    }
    catch (const std::invalid_argument &e)
    {
        throw e;
    }
}

template <typename Key, typename Value, typename Hash>
void OpenAdressingHashTable<Key, Value, Hash>::rehash(size_t m)
{
    size_t new_table_size = get_next_prime(m);
    if (new_table_size > m_table_size)
    {
        std::vector<Element<Key, Value>> old_vec = m_table;
        m_number_of_elements = 0;
        m_table_size = new_table_size;
        m_table.resize(new_table_size);
        for (auto &elem : old_vec)
        {
            if (elem.status == ACTIVE)
                add(elem.value.first, elem.value.second);
        }
    }
}

template <typename Key, typename Value, typename Hash>
bool OpenAdressingHashTable<Key, Value, Hash>::remove(const Key &k)
{
    try
    {
        size_t m = aux_search(k);
        m_table[m].status = DELETED;
        m_number_of_elements--;
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}

template <typename Key, typename Value, typename Hash>
void OpenAdressingHashTable<Key, Value, Hash>::reserve(size_t n)
{
    if (n > m_table_size * m_max_load_factor)
    {
        rehash(n / m_max_load_factor);
    }
}

template <typename Key, typename Value, typename Hash>
void OpenAdressingHashTable<Key, Value, Hash>::set_max_load_factor(float lf)
{
    if (lf <= 0)
        throw std::out_of_range("invalid load factor");

    max_load_factor = lf;
    reserve(m_number_of_elements);
}

template <typename Key, typename Value, typename Hash>
Value &OpenAdressingHashTable<Key, Value, Hash>::operator[](const Key &k)
{
    try
    {
        size_t m = aux_search(k);
        return m_table[m].value.second;
    }
    catch (const std::invalid_argument &e)
    {
        if (!add(k, Value()))
        {
            rehash(2 * m_table_size);
            if (!add(k, Value()))
            {
                throw std::runtime_error("Erro durante a inserção de um elemento na hash de endereçamento aberto.");
            }
        }

        size_t m = aux_search(k);
        return m_table[m].value.second;
    }
}

template <typename Key, typename Value, typename Hash>
const Value &OpenAdressingHashTable<Key, Value, Hash>::operator[](const Key &k) const
{
    return at(k);
}

template <typename Key, typename Value, typename Hash>
size_t OpenAdressingHashTable<Key, Value, Hash>::get_cont_comparator() const
{
    return cont_comparator;
}

template <typename Key, typename Value, typename Hash>
size_t OpenAdressingHashTable<Key, Value, Hash>::get_cont_collisions() const
{
    return cont_collisions;
}

template <typename Key, typename Value, typename Hash>
void OpenAdressingHashTable<Key, Value, Hash>::show() const
{
    std::vector<std::pair<Key, Value>> elementos;

    for (size_t i = 0; i < m_table_size; i++){
        if (m_table[i].status == ACTIVE)
            elementos.push_back(m_table[i].value);
    }

    std::sort(elementos.begin(), elementos.end(), [](auto &a, auto &b)
              {
                  return a.first < b.first; // Método de ordenação(Por chaves em ordem crescente)
              });

    for (size_t i = 0; i < elementos.size(); i++)
    {
        const auto &par = elementos[i];
        std::cout << "(" << par.first << ", " << par.second << ")" << std::endl;
    }

}

template <typename Key, typename Value, typename Hash>
OpenAdressingHashTable<Key, Value, Hash>::~OpenAdressingHashTable()
{
    m_table.clear();
    m_table_size = 0;
    m_number_of_elements = 0;
}

template <typename Key, typename Value, typename Hash>
size_t OpenAdressingHashTable<Key, Value, Hash>::aux_search(Key k)
{
    size_t i = 0, j = 0;
    do
    {
        j = hash_code(k, i);
        if (m_table[j].status == ACTIVE and m_table[j].value.first == k)
            return j;
        i++;
    } while (m_table[j].status != EMPTY and i < m_table_size);

        throw std::invalid_argument("Chave não encontrada");
}

template <typename Key, typename Value, typename Hash>
bool OpenAdressingHashTable<Key, Value, Hash>::cont_comp()
{
    cont_comparator++;
    return true;
}

template <typename Key, typename Value, typename Hash>
size_t OpenAdressingHashTable<Key, Value, Hash>::get_next_prime(size_t x)
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
size_t OpenAdressingHashTable<Key, Value, Hash>::hash_code(const Key &k, size_t i) const
{
    return (m_hashing(k) % m_table_size) + i * (1 + (m_hashing(k) % (m_table_size - 1))) % m_table_size;
}

#endif
