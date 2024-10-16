#include <iostream> 
#include <string> 
#include <list>
#include <set> 

#include "HuffmanTree.h"

using std::cout; 

// Конструктор класса HuffmanTree
HuffmanTree::HuffmanTree() {
    m_root = nullptr; 
}

// Деструктор класса HuffmanTree
HuffmanTree::~HuffmanTree() {
    removal(); 
}

// Метод для удаления дерева
void HuffmanTree::removal() {
    removalAuxiliary(m_root); 
    m_root = nullptr; 
}

// Вспомогательный метод для удаления дерева
void HuffmanTree::removalAuxiliary(Node* node) {
    if (node == nullptr) { 
        return;
    }

    removalAuxiliary(node->getLeft()); 
    removalAuxiliary(node->getRight()); 

    delete node; 
}

// Метод для построения дерева Хаффмана
void HuffmanTree::build(const std::string& text) {
    removal(); 

    int frequencies[256] = {}; 

    // Подсчет частот символов в тексте
    for (int i = 0; i < text.length(); i++) {
        frequencies[text[i]]++;
    }

    std::list<Node*> nodes; 

    // Создание узлов для каждого символа с ненулевой частотой
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] == 0) {
            continue;
        }

        Node* newNode = new Node; 

        newNode->getFrequency() = frequencies[i]; 
        newNode->setSymbols(i); 

        nodes.push_back(newNode); 
    }

    // Построение дерева Хаффмана
    while (nodes.size() > 1) {
        nodes.sort([](Node* first, Node* second) {
            return (first->getFrequency()) < (second->getFrequency());
            });

        Node* first;
        Node* second;

        first = *(nodes.begin()); 
        nodes.pop_front(); 

        second = *(nodes.begin()); 
        nodes.pop_front(); 

        Node* root = new Node(first, second); 

        nodes.push_back(root); 
    }

    m_root = *(nodes.begin()); 
}

// Метод для кодирования текста
double HuffmanTree::encode(const std::string& text, std::vector<bool>& encodedBits) {
    if (m_root == nullptr) { 
        build(text);
    }

    encodedBits.clear(); 

    // Кодирование каждого символа в тексте
    for (int i = 0; i < text.length(); i++) {
        char huffmanChar = text[i]; 
        std::set<char> symbols = m_root->getSymbols();

        // Если символ не найден в дереве, возвращаем -1
        if (symbols.find(huffmanChar) == symbols.end()) {
            return -1;
        }

        // Если в корне дерева только один символ, добавляем '0'
        if (symbols.size() == 1) {
            encodedBits.push_back(false);
            continue;
        }

        Node* node = m_root; 

        // Поиск кода символа в дереве
        while ((node->getSymbols().size()) > 1) {
            Node* left = node->getLeft(); 

            if (left == nullptr) { 
                continue;
            }

            std::set<char> leftSymbols = left->getSymbols(); 

            // Если символ найден в левом потомке, добавляем '0'
            if (leftSymbols.find(huffmanChar) != leftSymbols.end()) {
                encodedBits.push_back(false);
                node = left; 
            }
            else { 
                encodedBits.push_back(true);
                node = node->getRight(); 
            }
        }
    }

    // Возвращаем коэффициент сжатия
    return double(encodedBits.size()) / double(text.size() * 8);
}

// Метод для декодирования текста
bool HuffmanTree::decode(const std::vector<bool>& encodedBits, std::string& decodedText) const {
    decodedText = ""; 

    Node* node = m_root; 

    // Если корень дерева отсутствует, возвращаем false
    if (node == nullptr) {
        return false;
    }

    // Декодирование каждого бита в закодированном тексте
    for (bool bit : encodedBits) {
        if (m_root->getSymbols().size() == 1) { 
            if (bit != false) { 
                return false;
            }

            decodedText += *(node->getSymbols().begin());
            continue;
        }

        // Перемещение по дереву в зависимости от бита '0' или '1'
        if (bit == false) {
            node = node->getLeft(); 
        }
        else if (bit == true) {
            node = node->getRight(); 
        }
        else {
            return false; 
        }

        // Если узел отсутствует, возвращаем false
        if (node == nullptr) {
            return false;
        }
        else if (node->getSymbols().size() == 1) { 
            decodedText += *(node->getSymbols().begin()); 
            node = m_root; 
        }
    }

    return true; 
}