#ifndef RBT_HPP
#define RBT_HPP

#define RED true
#define BLACK false
#include <utility>
#include <iostream>
#include <stack>
#include <exception>

template <typename Key, typename Value>
struct Node_RBT
{
    std::pair<Key, Value> value; // Guarda o valor e a chave do nó
    bool color;                  // Cor do nó (Preta ou Vermelha)
    Node_RBT<Key, Value> *right; // Ponteiro para o filho direito
    Node_RBT<Key, Value> *left;  // Ponteiro para o filho esquerdo
    Node_RBT<Key, Value> *p;     // Ponteiro para o pai

    Node_RBT(Key key, Value value, bool color, Node_RBT<Key, Value> *right, Node_RBT<Key, Value> *left, Node_RBT<Key, Value> *p)
    {
        this->value.first = key;
        this->value.second = value;
        this->color = color;
        this->right = right;
        this->left = left;
        this->p = p;
    }

    Node_RBT<Key, Value> &operator=(const Node_RBT<Key, Value> &node)
    {
        this->value.first = node.value.first;
        this->value.second = node.value.second;
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->p = node.p;

        return *this;
    }
};

template <typename Key, typename Value>
class RBT
{
public:
    // Construtor da RBT
    RBT();

    // Construtor de cópia de RBT
    RBT(const RBT<Key, Value> &rbt);

    // Recebe chave k e valor v
    // Insere um novo nó(k,v) vermelho na posição correta da RBT,
    // Aciona o balanceamento com fixup_node() para preservar as propriedades
    // da árvore após a inserção
    void add(Key key, Value value);

    // Recebe chave k
    // Remove um nó(k) da RBT.
    // Navega até a chave a ser removida, depois chama a função auxiliar
    // deletion(), que promete remover o nó preservando as propriedades da
    // árvore após a remoção
    void remove(Key key);

    // Recebe uma chave k e um valor v
    // Atualiza o valor por v associado a chave k,
    // caso não exista um nó(k), lança uma excessão
    void update(Key key, Value value);

    // Verifica se a árvore RBT está vazia.
    // Retorna true se não houver elementos, false caso contrário.
    bool empty();

    // Exibe a árvore RBT em formato textual.
    // Mostra a estrutura da árvore, útil para depuração
    void show_tree();

    // Imprime os elementos da árvore RBT em ordem simétrica (in-order).
    // A travessia é feita de forma iterativa, utilizando uma pilha para simular
    // a recursão e visitar os nós na ordem: esquerda -> raiz -> direita.
    void show();

    // Recebe uma key
    // Retorna true se e somente se a chave consta na árvore
    // Retorna false caso contrário
    bool contains(Key key);

    // Sobrecarga de operador de indexação.
    // Se k corresponder a chave de um elemento da árvore , a funcao
    // retorna uma referencia ao seu valor mapeado. Caso contrario,
    // se k nao corresponder a chave de nenhum elemento da árvore,
    // a funcao insere um novo elemento com essa chave e retorna um
    // referencia ao seu valor mapeado. Caso ocorra um erro durante a inserção
    // lança uma excessão de runtime_error
    Value &operator[](const Key &key);

    // Limpa a árvore
    void clear();

    // Retorna o contador de comparações de chave
    size_t get_cont_comparator() const;

    // Retorna o contador de rotaçãoes
    size_t get_cont_rotation() const;

    // Destrutor da RBT
    ~RBT();

private:
    // Raiz do nó
    Node_RBT<Key, Value> *m_root;
    // Nó NIL
    Node_RBT<Key, Value> *nil;

    // Contador de comparações, durante a inserção
    size_t cont_comparator;

    // Contador de rotações
    size_t cont_rotation;

    // Realiza uma rotação simples à esquerda.
    // Utilizada para rebalancear a árvore após inserções ou remoções.
    Node_RBT<Key, Value> *left_rotation(Node_RBT<Key, Value> *node);

    // Realiza uma rotação simples à direita.
    // Utilizada para rebalancear a árvore após inserções ou remoções.
    Node_RBT<Key, Value> *right_rotation(Node_RBT<Key, Value> *node);

    // Corrige o balanceamento da altura negra de um nó após inserção.
    // Aplica rotações simples ou duplas, e também, pinta os nós
    // conforme necessário.
    void fixup_node(Node_RBT<Key, Value> *node);

    // Corrige o balanceamento da altura negra da árvore após a remoção
    // de um nó. Aplica rotações para manter e pinta nós para manter
    // as propriedades da RBT
    void fixup_deletion(Node_RBT<Key, Value> *node);

    // Remove um nó da Red-Black Tree substituindo-o pelo sucessor
    // apropriado e executa correção se necessário para manter as
    // propriedades da árvore após a remoção.
    void deletion(Node_RBT<Key, Value> *node);

    // Remove todos os nós da árvore a partir de um nó dado.
    // Libera a memória utilizada pela subárvore.
    Node_RBT<Key, Value> *clear(Node_RBT<Key, Value> *node);

    // Realiza a cópia profunda de uma subárvore RBT a partir de um nó dado.
    // Cria novos nós replicando as chaves e alturas da estrutura original,
    // preservando o formato e os valores da árvore.
    Node_RBT<Key, Value> *copy(Node_RBT<Key, Value> *node, Node_RBT<Key, Value> *nil_);

    // Incrementa o contador de comparações durante as operações da árvore.
    // Retorna verdadeiro para permitir seu uso dentro de expressões condicionais
    // sem interferir na lógica de decisão.
    bool cont_comp();

    // Recebe um nó n, e retorna o menor filho de n.
    Node_RBT<Key, Value> *minimum(Node_RBT<Key, Value> *node);

    // Exibe a estrutura da árvore a partir de um nó.
    // Mostra visualmente os ramos e subárvores.
    void show_tree(Node_RBT<Key, Value> *node, std::string heranca);
};

template <typename Key, typename Value>
RBT<Key, Value>::RBT()
{
    nil = new Node_RBT<Key, Value>(Key(), Value(), BLACK, nullptr, nullptr, nullptr);
    nil->left = nil->right = nil->p = nil;
    m_root = nil;
    m_root->p = nil;
    cont_rotation = 0;
    cont_comparator = 0;
}

template <typename Key, typename Value>
RBT<Key, Value>::RBT(const RBT &rbt)
    : cont_comparator{rbt.cont_comparator}, cont_rotation{rbt.cont_rotation}
{
    nil = new Node_RBT<Key, Value>(Key(), Value(), BLACK, nullptr, nullptr, nullptr);
    nil->left = nil->right = nil->p = nil;
    m_root = copy(rbt.m_root, rbt.nil);
    if (m_root != nil)
        m_root->p = nil;
}

template <typename Key, typename Value>
void RBT<Key, Value>::add(Key key, Value value)
{
    Node_RBT<Key, Value> *pai = nil;
    Node_RBT<Key, Value> *node = m_root;
    while (node != nil)
    {
        pai = node;
        if (cont_comp() && key < node->value.first)
            node = node->left;
        else if (cont_comp() && key > node->value.first)
            node = node->right;
        else
            return;
    }
    Node_RBT<Key, Value> *aux = new Node_RBT<Key, Value>(key, value, RED, nil, nil, nil);
    if (pai == nil)
    {
        m_root = aux;
        aux->p = nil;
    }
    else
    {
        aux->p = pai;

        if (cont_comp() && key < pai->value.first)
            pai->left = aux;
        else
            pai->right = aux;
    }

    fixup_node(aux);
}

template <typename Key, typename Value>
void RBT<Key, Value>::remove(Key key)
{
    Node_RBT<Key, Value> *atual = m_root;
    while (atual != nil && cont_comp() && atual->value.first != key)
    {
        if (cont_comp() && key < atual->value.first)
            atual = atual->left;
        else
            atual = atual->right;
    }
    if (atual != nil)
        deletion(atual);
}

template <typename Key, typename Value>
void RBT<Key, Value>::update(Key key, Value value)
{
    Node_RBT<Key, Value> *atual = m_root;

    while (atual != nil)
    {
        if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else if (cont_comp() && atual->value.first < key)
            atual = atual->right;
        else
        {
            atual->value.second = value;
            break;
        }
    }

    if (atual == nil)
    {
        throw std::invalid_argument("invalid key on update");
    }
}

template <typename Key, typename Value>
bool RBT<Key, Value>::empty()
{
    return m_root == nil;
}

template <typename Key, typename Value>
void RBT<Key, Value>::show_tree()
{
    show_tree(m_root, "");
}

template <typename Key, typename Value>
void RBT<Key, Value>::show()
{
    std::cout << "RBT: ";
    Node_RBT<Key, Value> *aux = m_root;
    std::stack<Node_RBT<Key, Value> *> pilha;
    while (!pilha.empty() || aux != nil)
    {
        if (aux != nil)
        {
            pilha.push(aux);
            aux = aux->left;
        }
        else
        {
            aux = pilha.top();
            pilha.pop();

            std::cout << (aux->color == RED ? "\033[31m" : "\033[30m") << "(" << aux->value.first << ", " << aux->value.second << ")" << "\033[0m";
            aux = aux->right;
            if (!pilha.empty() || aux != nil)
                std::cout << ", ";
            else
                std::cout << std::endl;
        }
    }
}

template <typename Key, typename Value>
bool RBT<Key, Value>::contains(Key key)
{
    Node_RBT<Key, Value> *atual = m_root;

    while (atual != nil)
    {
        if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else if (cont_comp() && atual->value.first < key)
            atual = atual->right;
        else
            return true;
    }

    return false;
}

template <typename Key, typename Value>
Value &RBT<Key, Value>::operator[](const Key &key)
{
    Node_RBT<Key, Value> *atual = m_root;
    while (atual != nil)
    {
        if (cont_comp() && atual->value.first == key)
            return atual->value.second;
        else if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else
            atual = atual->right;
    }

    if (atual == nil)
        add(key, Value());

    atual = m_root;
    while (atual != nil)
    {
        if (cont_comp() && atual->value.first == key)
            return atual->value.second;
        else if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else
            atual = atual->right;
    }

    throw std::runtime_error("Erro durante a operação de indexação da RBT");
}

template <typename Key, typename Value>
void RBT<Key, Value>::clear()
{
    cont_comparator = 0;
    cont_rotation = 0;
    m_root = clear(m_root);
}

template <typename Key, typename Value>
size_t RBT<Key, Value>::get_cont_comparator() const
{
    return cont_comparator;
}

template <typename Key, typename Value>
size_t RBT<Key, Value>::get_cont_rotation() const
{
    return cont_rotation;
}

template <typename Key, typename Value>
RBT<Key, Value>::~RBT()
{
    clear();
}

template <typename Key, typename Value>
Node_RBT<Key, Value> *RBT<Key, Value>::left_rotation(Node_RBT<Key, Value> *node)
{
    Node_RBT<Key, Value> *aux = node->right;
    node->right = aux->left;
    if (aux->left != nil)
        aux->left->p = node;
    aux->p = node->p;
    if (node->p == nil)
        m_root = aux;
    else if (node == node->p->left)
        node->p->left = aux;
    else
        node->p->right = aux;
    aux->left = node;
    node->p = aux;

    cont_rotation++;

    return aux;
}

template <typename Key, typename Value>
Node_RBT<Key, Value> *RBT<Key, Value>::right_rotation(Node_RBT<Key, Value> *node)
{
    Node_RBT<Key, Value> *aux = node->left;
    node->left = aux->right;
    if (aux->right != nil)
        aux->right->p = node;
    aux->p = node->p;
    if (node->p == nil)
        m_root = aux;
    else if (node == node->p->right)
        node->p->right = aux;
    else
        node->p->left = aux;
    aux->right = node;
    node->p = aux;

    cont_rotation++;

    return aux;
}

template <typename Key, typename Value>
void RBT<Key, Value>::fixup_node(Node_RBT<Key, Value> *node)
{
    while (node->p->color == RED)
    {
        if (node->p == node->p->p->left)
        {
            Node_RBT<Key, Value> *tio = node->p->p->right;
            if (tio->color == RED)
            {
                node->p->color = BLACK;
                tio->color = BLACK;
                node->p->p->color = RED;
                node = node->p->p;
            }
            else
            {
                if (node == node->p->right)
                {
                    node = node->p;
                    left_rotation(node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                right_rotation(node->p->p);
            }
        }
        else
        {
            Node_RBT<Key, Value> *tio = node->p->p->left;

            if (tio->color == RED)
            {
                node->p->color = BLACK;
                tio->color = BLACK;
                node->p->p->color = RED;
                node = node->p->p;
            }
            else
            {
                if (node == node->p->left)
                {
                    node = node->p;
                    right_rotation(node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                left_rotation(node->p->p);
            }
        }
    }
    m_root->color = BLACK;
}

template <typename Key, typename Value>
void RBT<Key, Value>::fixup_deletion(Node_RBT<Key, Value> *node)
{
    while (node != m_root && node->color == BLACK)
    {
        if (node == node->p->left)
        {
            Node_RBT<Key, Value> *irmao = node->p->right;
            if (irmao->color == RED)
            {
                irmao->color = BLACK;
                node->p->color = RED;
                left_rotation(node->p);
                irmao = node->p->right;
            }
            if (irmao->left->color == BLACK && irmao->right->color == BLACK)
            {
                irmao->color = RED;
                node = node->p;
            }
            else
            {
                if (irmao->right->color == BLACK)
                {
                    irmao->left->color = BLACK;
                    irmao->color = RED;
                    right_rotation(irmao);
                    irmao = node->p->right;
                }
                irmao->color = node->p->color;
                node->p->color = BLACK;
                irmao->right->color = BLACK;
                left_rotation(node->p);
                node = m_root;
            }
        }
        else
        {
            Node_RBT<Key, Value> *irmao = node->p->left;
            if (irmao->color == RED)
            {
                irmao->color = BLACK;
                node->p->color = RED;
                right_rotation(node->p);
                irmao = node->p->left;
            }
            if (irmao->left->color == BLACK && irmao->right->color == BLACK)
            {
                irmao->color = RED;
                node = node->p;
            }
            else
            {
                if (irmao->left->color == BLACK)
                {
                    irmao->left->color = BLACK;
                    irmao->color = RED;
                    left_rotation(irmao);
                    irmao = node->p->left;
                }
                irmao->color = node->p->color;
                node->p->color = BLACK;
                irmao->left->color = BLACK;
                right_rotation(node->p);
                node = m_root;
            }
        }
    }
    node->color = BLACK;
}

template <typename Key, typename Value>
void RBT<Key, Value>::deletion(Node_RBT<Key, Value> *node)
{
    Node_RBT<Key, Value> *aux = nullptr, *_aux = nullptr;
    if (node->left == nil || node->right == nil)
        aux = node;
    else
        aux = minimum(node->right);
    if (aux->left != nil)
        _aux = aux->left;
    else
        _aux = aux->right;
    _aux->p = aux->p;
    if (aux->p == nil)
        m_root = _aux;
    else
    {
        if (aux == aux->p->left)
            aux->p->left = _aux;
        else
            aux->p->right = _aux;
    }
    if (aux != node)
    {
        node->value.first = aux->value.first;
        node->value.second = aux->value.second;
    }
    if (aux->color == BLACK)
        fixup_deletion(_aux);

    delete aux;
}

template <typename Key, typename Value>
Node_RBT<Key, Value> *RBT<Key, Value>::clear(Node_RBT<Key, Value> *node)
{
    if (node != nil)
    {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }

    return nil;
}

template <typename Key, typename Value>
Node_RBT<Key, Value> *RBT<Key, Value>::copy(Node_RBT<Key, Value> *node, Node_RBT<Key, Value> *nil_)
{
    if (node == nil_)
        return nil;

    Node_RBT<Key, Value> *aux = new Node_RBT<Key, Value>(node->value.first, node->value.second, node->color, nil, nil, nullptr);
    aux->left = copy(node->left, nil_);
    if (aux->left != nil)
        aux->left->p = aux;
    aux->right = copy(node->right, nil_);
    if (aux->right != nil)
        aux->right->p = aux;

    return aux;
}

template <typename Key, typename Value>
bool RBT<Key, Value>::cont_comp()
{
    cont_comparator++;
    return true;
}

template <typename Key, typename Value>
Node_RBT<Key, Value> *RBT<Key, Value>::minimum(Node_RBT<Key, Value> *node)
{
    if (node == nil)
        throw std::invalid_argument("invalid argument on minimum");
    Node_RBT<Key, Value> *atual = node;
    if (atual->left != nil)
        atual = atual->left;

    return atual;
}

template <typename Key, typename Value>
void RBT<Key, Value>::show_tree(Node_RBT<Key, Value> *node, std::string heranca)
{
    if (node != nil && (node->left != nil || node->right != nil))
        show_tree(node->right, heranca + "r");
    for (int i = 0; i < (int)heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if (heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if (node == nil)
    {
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << (node->color == RED ? "\033[31m" : "\033[30m") << node->value.first << ", " << node->value.second << "\033[0m" << std::endl;
    if (node != nil && (node->left != nil || node->right != nil))
        show_tree(node->left, heranca + "l");
}
#endif