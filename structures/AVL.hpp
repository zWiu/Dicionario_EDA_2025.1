#ifndef AVL_HPP
#define AVL_HPP
#include <iostream>
#include <stack>
#include <utility>
#include <exception>

template <typename Key, typename Value>
struct Node
{
    std::pair<Key, Value> value; // Par com chave e valor do nó
    int height;                  // Altura do nó
    Node *left;                  // Filho esquerdo do nó, menor
    Node *right;                 // Filho direito do nó, maior

    Node(Key k, Value v, int height, Node<Key, Value> *left, Node<Key, Value> *right)
    {
        this->value.first = k;
        this->value.second = v;
        this->height = height;
        this->left = left;
        this->right = right;
    }

    Node<Key, Value> &operator=(const Node<Key, Value> &node)
    {
        this->value = node.value;
        this->height = node.height;
        this->left = node.left;
        this->right = node.right;

        return *this;
    }
};

template <typename Key, typename Value>
class AVL
{
public:
    // Construtor da AVL
    AVL();

    // Construtor de cópia da AVL
    AVL(const AVL<Key, Value> &avl);

    // Insere um valor na árvore AVL.
    // A chave é posicionada de forma a manter a ordem e o balanceamento da árvore.
    void add(Key key, Value value);

    // Remove uma chave da árvore AVL.
    // Caso a chave não esteja presente, nenhuma operação é realizada.
    void remove(Key key);

    // Recebe uma key
    // Atualiza o valor associado a key, caso não exista, lança uma excessão
    void update(Key key, Value value);

    // Verifica se a árvore está vazia.
    // Retorna true se não houver elementos, false caso contrário.
    bool empty();

    // Exibe a árvore AVL em formato textual.
    // Mostra a estrutura da árvore, útil para depuração
    void show_tree();

    // Imprime os elementos da árvore AVL em ordem simétrica (in-order).
    // A travessia é feita de forma iterativa, utilizando uma pilha para simular
    // a recursão e visitar os nós na ordem: esquerda -> raiz -> direita.
    void show();

    // Recebe uma key
    // Retorna true se e somente se a chave consta na árvore
    // Retorna false caso contrário
    bool contains(Key key);

    // Retorna o tamanho do árvore
    size_t size();

    // Sobrecarga de operador de indexação.
    // Se k corresponder a chave de um elemento da árvore , a funcao
    // retorna uma referencia ao seu valor mapeado. Caso contrario,
    // se k nao corresponder a chave de nenhum elemento da árvore,
    // a funcao insere um novo elemento com essa chave e retorna um
    // referencia ao seu valor mapeado. Caso ocorra um erro durante a inserção
    // lança uma excessão de runtime_error
    Value &operator[](const Key &key);

    // Recebe uma chave referência constante de chave e retorna uma referência
    // ao seu valor associado, caso não encontre retorna uma excessão
    Value &at(const Key &key);

    // Limpa a árvore
    void clear();

    // Retorna o contador de comparações de chave
    size_t get_cont_comparator() const;

    // Retorna o contador de rotaçãoes
    size_t get_cont_rotation() const;

    // Destrutor da AVL
    ~AVL();

private:
    // Raiz do nó
    Node<Key, Value> *m_root;

    // Contador de comparações, durante a inserção
    size_t cont_comparator;

    // Contador de rotações
    size_t cont_rotation;

    // Retorna a altura de um nó.
    // Nós nulos têm altura 0.
    int _height(Node<Key, Value> *node);

    // Calcula o fator de balanceamento de um nó.
    // É a diferença entre a altura da subárvore direita e da esquerda.
    int balance(Node<Key, Value> *node);

    // Realiza uma rotação simples à esquerda.
    // Utilizada para rebalancear a árvore após inserções ou remoções.
    Node<Key, Value> *left_rotation(Node<Key, Value> *p);

    // Realiza uma rotação simples à direita.
    // Utilizada para rebalancear a árvore após inserções ou remoções.
    Node<Key, Value> *right_rotation(Node<Key, Value> *p);

    // Corrige o balanceamento de um nó após inserção.
    // Aplica rotações simples ou duplas conforme necessário.
    Node<Key, Value> *fixup_node(Node<Key, Value> *node, Key key);

    // Insere uma chave na árvore a partir de um nó dado.
    // Reorganiza os nós e corrige o balanceamento após a inserção
    Node<Key, Value> *add(Node<Key, Value> *node, Key key, Value value);

    // Corrige o balanceamento da árvore após a remoção de um nó.
    // Aplica rotações para manter a propriedade AVL
    Node<Key, Value> *fixup_deletion(Node<Key, Value> *node);

    // Remove o sucessor in-order de um nó na árvore.
    // Substitui o nó removido pelo menor valor da subárvore direita.
    Node<Key, Value> *remove_successor(Node<Key, Value> *p, Node<Key, Value> *node);

    // Remove uma chave da árvore a partir de um nó dado.
    // Reorganiza os nós e corrige o balanceamento após a remoção.
    Node<Key, Value> *remove(Node<Key, Value> *node, Key key);

    // Remove todos os nós da árvore a partir de um nó dado.
    // Libera a memória utilizada pela subárvore.
    Node<Key, Value> *clear(Node<Key, Value> *node);

    // Realiza a cópia profunda de uma subárvore AVL a partir de um nó dado.
    // Cria novos nós replicando as chaves e alturas da estrutura original,
    // preservando o formato e os valores da árvore.
    Node<Key, Value> *copy(Node<Key, Value> *node);

    // Incrementa o contador de comparações durante as operações da árvore.
    // Retorna verdadeiro para permitir seu uso dentro de expressões condicionais
    // sem interferir na lógica de decisão.
    bool cont_comp();

    // Exibe a estrutura da árvore a partir de um nó.
    // Mostra visualmente os ramos e subárvores.
    void show_tree(Node<Key, Value> *node, std::string heranca);
};

template <typename Key, typename Value>
AVL<Key, Value>::AVL()
    : m_root{nullptr}, cont_comparator{0}, cont_rotation{0} {}

template <typename Key, typename Value>
AVL<Key, Value>::AVL(const AVL<Key, Value> &avl)
    : m_root{copy(avl.m_root)}, cont_comparator{avl.cont_comparator}, cont_rotation{avl.cont_rotation} {}

template <typename Key, typename Value>
void AVL<Key, Value>::add(Key key, Value value)
{
    m_root = add(m_root, key, value);
}

template <typename Key, typename Value>
void AVL<Key, Value>::remove(Key key)
{
    m_root = remove(m_root, key);
}

template <typename Key, typename Value>
void AVL<Key, Value>::update(Key key, Value value)
{
    Node<Key, Value> *atual = m_root;

    while (atual != nullptr)
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

    if (atual == nullptr)
    {
        throw std::invalid_argument("invalid key on update");
    }
}

template <typename Key, typename Value>
bool AVL<Key, Value>::empty()
{
    return m_root == nullptr;
}

template <typename Key, typename Value>
void AVL<Key, Value>::show_tree()
{
    show_tree(m_root, "");
}

template <typename Key, typename Value>
void AVL<Key, Value>::show()
{
    std::cout << "AVL: ";
    Node<Key, Value> *aux = m_root;
    std::stack<Node<Key, Value> *> p;
    while (!p.empty() || aux != nullptr)
    {
        if (aux != nullptr)
        {
            p.push(aux);
            aux = aux->left;
        }
        else
        {
            aux = p.top();
            p.pop();
            std::cout << "(" << aux->value.first << ", " << aux->value.second << ")";
            aux = aux->right;
            if (!p.empty() || aux != nullptr)
                std::cout << ", ";
            else
                std::cout << std::endl;
        }
    }
}

template <typename Key, typename Value>
bool AVL<Key, Value>::contains(Key key)
{
    Node<Key, Value> *atual = m_root;

    while (atual != nullptr)
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
size_t AVL<Key, Value>::size()
{
    size_t cont = 0;
    std::stack<Node<Key, Value> *> p;
    p.push(m_root);
    while(!p.empty())
    {
        Node<Key, Value> *aux = p.top();
        p.pop();
        cont++;

        if(aux->right != nullptr)
            p.push(aux->right);
        if(aux->left != nullptr)
            p.push(aux->left);
    }
    return cont;
}

template <typename Key, typename Value>
Value &AVL<Key, Value>::operator[](const Key &key)
{
    Node<Key, Value> *atual = m_root;
    while (atual != nullptr)
    {
        if (cont_comp() && atual->value.first == key)
            return atual->value.second;
        else if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else
            atual = atual->right;
    }

    if (atual == nullptr)
        add(m_root, key, Value());

    atual = m_root;
    while (atual != nullptr)
    {
        if (cont_comp() && atual->value.first == key)
            return atual->value.second;
        else if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else
            atual = atual->right;
    }

    throw std::runtime_error("Erro durante a operação de indexação da AVL");
}

template <typename Key, typename Value>
Value &AVL<Key, Value>::at(const Key &key)
{
    Node<Key, Value> *atual = m_root;
    while (atual != nullptr)
    {
        if (cont_comp() && atual->value.first == key)
            return atual->value.second;
        else if (cont_comp() && atual->value.first > key)
            atual = atual->left;
        else
            atual = atual->right;
    }

    throw std::invalid_argument("Essa chave não existe na AVL");
}

template <typename Key, typename Value>
void AVL<Key, Value>::clear()
{
    cont_comparator = 0;
    cont_rotation = 0;
    m_root = clear(m_root);
}

template <typename Key, typename Value>
size_t AVL<Key, Value>::get_cont_comparator() const
{
    return cont_comparator;
}

template <typename Key, typename Value>
size_t AVL<Key, Value>::get_cont_rotation() const
{
    return cont_rotation;
}

template <typename Key, typename Value>
AVL<Key, Value>::~AVL()
{
    m_root = clear(m_root);
}

template <typename Key, typename Value>
int AVL<Key, Value>::_height(Node<Key, Value> *node)
{
    if (node == nullptr)
        return 0;
    else
        return node->height;
}

template <typename Key, typename Value>
int AVL<Key, Value>::balance(Node<Key, Value> *node)
{
    return _height(node->right) - _height(node->left);
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::left_rotation(Node<Key, Value> *pai)
{
    Node<Key, Value> *filho = pai->right;
    pai->right = filho->left;
    filho->left = pai;

    pai->height = 1 + std::max(_height(pai->left), _height(pai->right));
    filho->height = 1 + std::max(_height(filho->left), _height(filho->right));
    cont_rotation++;
    return filho;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::right_rotation(Node<Key, Value> *pai)
{
    Node<Key, Value> *filho = pai->left;
    pai->left = filho->right;
    filho->right = pai;

    pai->height = 1 + std::max(_height(pai->left), _height(pai->right));
    filho->height = 1 + std::max(_height(filho->left), _height(filho->right));
    cont_rotation++;
    return filho;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::fixup_node(Node<Key, Value> *node, Key key)
{
    int bal = balance(node);
    if (cont_comp() && bal == -2 && key < node->left->value.first)
        return right_rotation(node);
    // Rotação dupla à direita
    else if (cont_comp() && bal == -2 && key > node->left->value.first)
    {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }
    // Rotação à esquerda
    else if (cont_comp() && bal == 2 && key > node->right->value.first)
        return left_rotation(node);
    // Rotação dupla à esquerda
    else if (cont_comp() && bal == 2 && key < node->right->value.first)
    {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    node->height = 1 + std::max(_height(node->left), _height(node->right));

    return node;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::add(Node<Key, Value> *node, Key key, Value value)
{
    if (node == nullptr)
        return new Node<Key, Value>(key, value, 1, nullptr, nullptr);
    if (cont_comp() && key == node->value.first)
        return node;
    if (cont_comp() && key < node->value.first)
        node->left = add(node->left, key, value);
    else
        node->right = add(node->right, key, value);

    node = fixup_node(node, key);

    return node;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::fixup_deletion(Node<Key, Value> *node)
{
    int bal = balance(node);
    // Rotação à esquerda
    if (cont_comp() && bal == 2 && balance(node->right) >= 0)
        return left_rotation(node);
    // Rotação dupla à esquerda
    else if (cont_comp() && bal == 2 && balance(node->right) < 0)
    {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }
    // Rotação à direita
    else if (cont_comp() && bal == -2 && balance(node->left) <= 0)
        return right_rotation(node);
    // Rotação dupla à direita
    else if (cont_comp() && bal == -2 && balance(node->left) < 0)
    {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    return node;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::remove_successor(Node<Key, Value> *p, Node<Key, Value> *node)
{
    if (node->left == nullptr)
    {
        p->value = node->value;
        Node<Key, Value> *aux = node->right;
        delete node;
        return aux;
    }
    node->left = remove_successor(p, node->left);
    node = fixup_deletion(node);

    return node;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::remove(Node<Key, Value> *node, Key key)
{
    if (node == nullptr)
        return nullptr;
    if (cont_comp() && key < node->value.first)
        node->left = remove(node->left, key);
    else if (cont_comp() && key > node->value.first)
        node->right = remove(node->right, key);
    else if (node->right == nullptr)
    {
        Node<Key, Value> *aux = node->left;
        delete node;
        return aux;
    }
    else
        node->right = remove_successor(node, node->right);

    node = fixup_deletion(node);
    return node;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::clear(Node<Key, Value> *node)
{
    if (node != nullptr)
    {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }

    return nullptr;
}

template <typename Key, typename Value>
Node<Key, Value> *AVL<Key, Value>::copy(Node<Key, Value> *node)
{
    if (node == nullptr)
        return nullptr;

    Node<Key, Value> *aux = new Node<Key, Value>(node->value.first, node->value.second, node->height, nullptr, nullptr);
    aux->left = copy(node->left);
    aux->right = copy(node->right);

    return aux;
}

template <typename Key, typename Value>
bool AVL<Key, Value>::cont_comp()
{
    cont_comparator++;
    return true;
}

template <typename Key, typename Value>
void AVL<Key, Value>::show_tree(Node<Key, Value> *node, std::string heranca)
{
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        show_tree(node->right, heranca + "r");
    for (int i = 0; i < (int)heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if (heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if (node == nullptr)
    {
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->value.first << ", " << node->value.second << std::endl;
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        show_tree(node->left, heranca + "l");
}

#endif