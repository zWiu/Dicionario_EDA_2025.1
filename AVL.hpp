#ifndef AVL_HPP
#define AVL_HPP
#include <iostream>
#include <stack>

template <typename T>
struct Node
{
    T key;       // Chave do tipo T do nó
    int height;  // Altura do nó
    Node *left;  // Filho esquerdo do nó, menor
    Node *right; // Filho direito do nó, maior

    Node(T key, int height, Node<T> *left, Node<T> *right)
    {
        this->key = key;
        this->height = height;
        this->left = left;
        this->right = right;
    }

    Node<T> &operator=(const Node<T> &node)
    {
        this->key = node.key;
        this->height = node.height;
        this->left = node.left;
        this->right = node.right;

        return *this;
    }
};

template <typename T>
class AVL
{
public:
    // Construtor da AVL
    AVL();

    // Construtor de cópia da AVL
    AVL(const AVL<T> &avl);

    // Insere uma chave na árvore AVL.
    // A chave é posicionada de forma a manter a ordem e o balanceamento da árvore.
    void insert(T key);

    // Remove uma chave da árvore AVL.
    // Caso a chave não esteja presente, nenhuma operação é realizada.
    void erase(T key);

    // Verifica se a árvore está vazia.
    // Retorna true se não houver elementos, false caso contrário.
    bool empty();

    // Exibe a árvore AVL em formato textual.
    // Mostra a estrutura da árvore, útil para depuração
    void show_tree();

    // Imprime os elementos da árvore AVL em ordem simétrica (in-order).
    // A travessia é feita de forma iterativa, utilizando uma pilha para simular
    // a recursão e visitar os nós na ordem: esquerda → raiz → direita.
    void show();

    // Destrutor da AVL
    ~AVL();

private:
    // Raiz do nó
    Node<T> *m_root;

    // Contador de comparações, durante a inserção
    size_t cont_comparator;

    // Contador de rotações
    size_t cont_rotation;
    // Retorna a altura de um nó.
    // Nós nulos têm altura 0.
    int _height(Node<T> *node);

    // Calcula o fator de balanceamento de um nó.
    // É a diferença entre a altura da subárvore direita e da esquerda.
    int balance(Node<T> *node);

    // Realiza uma rotação simples à esquerda.
    // Utilizada para rebalancear a árvore após inserções ou remoções.
    Node<T> *left_rotation(Node<T> *p);

    // Realiza uma rotação simples à direita.
    // Utilizada para rebalancear a árvore após inserções ou remoções.
    Node<T> *right_rotation(Node<T> *p);

    // Corrige o balanceamento de um nó após inserção.
    // Aplica rotações simples ou duplas conforme necessário.
    Node<T> *fixup_node(Node<T> *node, T key);

    // Insere uma chave na árvore a partir de um nó dado.
    // Reorganiza os nós e corrige o balanceamento após a inserção
    Node<T> *insert(Node<T> *node, T key);

    // Corrige o balanceamento da árvore após a remoção de um nó.
    // Aplica rotações para manter a propriedade AVL
    Node<T> *fixup_deletion(Node<T> *node);

    // Remove o sucessor in-order de um nó na árvore.
    // Substitui o nó removido pelo menor valor da subárvore direita.
    Node<T> *remove_successor(Node<T> *p, Node<T> *node);

    // Remove uma chave da árvore a partir de um nó dado.
    // Reorganiza os nós e corrige o balanceamento após a remoção.
    Node<T> *erase(Node<T> *node, T key);

    // Remove todos os nós da árvore a partir de um nó dado.
    // Libera a memória utilizada pela subárvore.
    Node<T> *clear(Node<T> *node);

    // Realiza a cópia profunda de uma subárvore AVL a partir de um nó dado.
    // Cria novos nós replicando as chaves e alturas da estrutura original,
    // preservando o formato e os valores da árvore.
    Node<T> *copy(Node<T> *node);

    // Incrementa o contador de comparações durante as operações da árvore.
    // Retorna verdadeiro para permitir seu uso dentro de expressões condicionais
    // sem interferir na lógica de decisão.
    bool cont_comp();

    // Exibe a estrutura da árvore a partir de um nó.
    // Mostra visualmente os ramos e subárvores.
    void show_tree(Node<T> *node, std::string heranca);
};

template <typename T>
AVL<T>::AVL() 
:m_root{nullptr}, cont_comparator{0}, cont_rotation{0} {}

template <typename T>
AVL<T>::AVL(const AVL<T> &avl) 
:m_root{copy(avl.m_root)}, cont_comparator{avl.cont_comparator}, cont_rotation{avl.cont_rotation} {}

template <typename T>
void AVL<T>::insert(T key)
{
    m_root = insert(m_root, key);
}

template <typename T>
void AVL<T>::erase(T key)
{
    m_root = erase(m_root, key);
}

template <typename T>
bool AVL<T>::empty()
{
    return m_root == nullptr;
}

template <typename T>
void AVL<T>::show_tree()
{
    show(m_root, "");
}

template <typename T>
void AVL<T>::show()
{
    std::cout << "AVL: ";
    Node<T> *aux = m_root;
    std::stack<Node<T> *> p;
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
            std::cout << aux->key;
            aux = aux->right;
            if (!p.empty() || aux != nullptr)
                std::cout << ", ";
            else 
                std::cout << std::endl;
        }
    }
}

template <typename T>
AVL<T>::~AVL()
{
    m_root = clear(m_root);
}

template <typename T>
int AVL<T>::_height(Node<T> *node)
{
    if (node == nullptr)
        return 0;
    else
        return node->height;
}

template <typename T>
int AVL<T>::balance(Node<T> *node)
{
    return _height(node->right) - _height(node->left);
}

template <typename T>
Node<T> *AVL<T>::left_rotation(Node<T> *pai)
{
    Node<T> *filho = pai->right;
    pai->right = filho->left;
    filho->left = pai;

    pai->height = 1 + std::max(_height(pai->left), _height(pai->right));
    filho->height = 1 + std::max(_height(filho->left), _height(filho->right));
    cont_rotation++;
    return filho;
}

template <typename T>
Node<T> *AVL<T>::right_rotation(Node<T> *pai)
{
    Node<T> *filho = pai->left;
    pai->left = filho->right;
    filho->right = pai;

    pai->height = 1 + std::max(_height(pai->left), _height(pai->right));
    filho->height = 1 + std::max(_height(filho->left), _height(filho->right));
    cont_rotation++;
    return filho;
}

template <typename T>
Node<T> *AVL<T>::fixup_node(Node<T> *node, T key)
{
    int bal = balance(node);
    if (bal == -2 && key < node->left->key && cont_comp())
        return right_rotation(node);
    // Rotação dupla à direita
    else if (bal == -2 && key > node->left->key && cont_comp())
    {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }
    // Rotação à esquerda
    else if (bal == 2 && key > node->right->key && cont_comp())
        return left_rotation(node);
    // Rotação dupla à esquerda
    else if (bal == 2 && key < node->right->key && cont_comp())
    {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    node->height = 1 + std::max(_height(node->left), _height(node->right));

    return node;
}

template <typename T>
Node<T> *AVL<T>::insert(Node<T> *node, T key)
{
    if (node == nullptr)
        return new Node<T>(key, 1, nullptr, nullptr);
    if (key == node->key && cont_comp())
        return node;
    if (key < node->key && cont_comp())
        node->left = insert(node->left, key);
    else if(cont_comp())
        node->right = insert(node->right, key);

    node = fixup_node(node, key);

    return node;
}

template <typename T>
Node<T> *AVL<T>::fixup_deletion(Node<T> *node)
{
    int bal = balance(node);
    // Rotação à esquerda
    if (bal == 2 && balance(node->right) >= 0 && cont_comp())
        return left_rotation(node);
    // Rotação dupla à esquerda
    else if (bal == 2 && balance(node->right) < 0 && cont_comp())
    {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }
    // Rotação à direita
    else if (bal == -2 && balance(node->left) <= 0 && cont_comp())
        return right_rotation(node);
    // Rotação dupla à direita
    else if (bal == -2 && balance(node->left) < 0 && cont_comp())
    {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    return node;
}

template <typename T>
Node<T> *AVL<T>::remove_successor(Node<T> *p, Node<T> *node)
{
    if (node->left == nullptr)
    {
        p->key = node->key;
        Node<T> *aux = node->right;
        delete node;
        return aux;
    }
    node->left = remove_successor(p, node->left);
    node = fixup_deletion(node);

    return node;
}

template <typename T>
Node<T> *AVL<T>::erase(Node<T> *node, T key)
{
    if (node == nullptr)
        return nullptr;
    if (key < node->key && cont_comp())
        node->left = erase(node->left, key);
    else if (key > node->key && cont_comp())
        node->right = erase(node->right, key);
    else if (node->right == nullptr)
    {
        Node<T> *aux = node->left;
        delete node;
        return aux;
    }
    else
        node->right = remove_successor(node, node->right);

    node = fixup_deletion(node);
    return node;
}

template <typename T>
Node<T> *AVL<T>::clear(Node<T> *node)
{
    if (node != nullptr)
    {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }

    return nullptr;
}

template <typename T>
Node<T> *AVL<T>::copy(Node<T> *node)
{
    if (node == nullptr)
        return nullptr;

    Node<T> *aux = new Node<T>(node->key, node->height, nullptr, nullptr);
    aux->left = copy(node->left);
    aux->right = copy(node->right);

    return aux;
}

template <typename T>
bool AVL<T>::cont_comp()
{
    cont_comparator++;
    return true;
}

template <typename T>
void AVL<T>::show_tree(Node<T> *node, std::string heranca)
{
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        show(node->right, heranca + "r");
    for (int i = 0; i < (int)heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if (heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if (node == nullptr)
    {
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        show(node->left, heranca + "l");
}

#endif