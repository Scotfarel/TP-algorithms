//
//  Created by izakharov on 12/05/20
//
//  2_1. Порядок обхода in-order.
//  Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
//  Требуется построить бинарное дерево, заданное наивным порядком вставки.
//  Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в
//  правое поддерево root; иначе в левое поддерево root.
//  Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
//
//  Выведите элементы в порядке in-order (слева направо).
//


#include <iostream>
#include <stack>
#include <vector>

template<class Value, class Comparator=std::less<Value>>
class BST {
    struct Node {
        explicit Node(const Value& value) : left(nullptr), right(nullptr), value(value) {};
        Node* left;
        Node* right;
        Value value;
    };
public:
    explicit BST(Comparator comp = Comparator()) : root(nullptr), comp(comp), size(0) {}
    ~BST();
    void addNode(const Value& value);
    std::vector<int> inOrder();

    bool isEmpty() { return size == 0; }

private:
    size_t size;
    Node* root;
    Comparator comp;
};

template<class Value, class Comparator>
void BST<Value, Comparator>::addNode(const Value &value) {
    bool added = false;

    Node* node = root;
    if (isEmpty()) {
        root = new Node(value);
        root->value = value;
        added = true;
        size++;
    }

    while (!added) {
        if (comp(value, node->value)) {
            if (!node->left) {
                node->left = new Node(value);
                added = true;
                size++;
            } else {
                node = node->left;
            }
        } else {
            if (!node->right) {
                node->right = new Node(value);
                added = true;
                size++;
            } else {
                node = node->right;
            }
        }
    }
}

template<class Value, class Comparator>
std::vector<int> BST<Value, Comparator>::inOrder() {
    std::stack<Node*> stackOfNodes;
    std::vector<int> vectorForPrint;
    Node* node = root;

    while (!stackOfNodes.empty() or node) {
        while (node) {
            stackOfNodes.push(node);
            node = node->left;
        }
        node = stackOfNodes.top();
        vectorForPrint.push_back(node->value);
        stackOfNodes.pop();
        node = node->right;
    }
    return vectorForPrint;
}

template<class Value, class Comparator>
BST<Value, Comparator>::~BST() {
    std::stack<Node*> stackOfNodes;
    Node* node = root;

    while (!stackOfNodes.empty() or node) {
        while (node) {
            stackOfNodes.push(node);
            node = node->left;
        }
        node = stackOfNodes.top();
        Node* delNode = node;
        stackOfNodes.pop();
        node = node->right;
        delete delNode;
    }
}


int main()
{
    int n = 0;
    std::cin >> n;
    BST<int> BST;
    for (int i = 0; i < n; i++)
    {
        int key = 0;
        std::cin >> key;
        BST.addNode(key);
    }

    std::vector<int> values = BST.inOrder();
    for (const auto& i: values) {
        std::cout << i << ' ';
    }
    return 0;
}
