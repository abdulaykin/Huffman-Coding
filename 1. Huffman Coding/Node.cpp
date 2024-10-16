#include <iostream> 
#include "HuffmanTree.h"

using std::cout; 

// Конструктор класса Node по умолчанию
HuffmanTree::Node::Node() {
    m_left = nullptr; 
    m_right = nullptr; 
    m_frequency = 0;
}

// Конструктор класса Node с параметрами
HuffmanTree::Node::Node(Node* first, Node* second) {
    m_left = first; 
    m_right = second; 
    m_frequency = first->m_frequency + second->m_frequency; 
    m_symbols.insert(first->m_symbols.begin(), first->m_symbols.end()); 
    m_symbols.insert(second->m_symbols.begin(), second->m_symbols.end()); 
}

// Метод для получения левого потомка
HuffmanTree::Node*& HuffmanTree::Node::getLeft() {
    return m_left; 
}

// Метод для получения правого потомка
HuffmanTree::Node*& HuffmanTree::Node::getRight() {
    return m_right; 
}

// Метод для получения частоты символов
int& HuffmanTree::Node::getFrequency() {
    return m_frequency; 
}

// Метод для получения множества символов
std::set<char> HuffmanTree::Node::getSymbols() {
    return m_symbols; 
}

// Метод для установки символов
void HuffmanTree::Node::setSymbols(const char symbol) {
    m_symbols.insert(symbol); 
}