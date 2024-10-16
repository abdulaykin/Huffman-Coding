#include <iostream> 
#include "HuffmanTree.h"

using std::cout; 

// ����������� ������ Node �� ���������
HuffmanTree::Node::Node() {
    m_left = nullptr; 
    m_right = nullptr; 
    m_frequency = 0;
}

// ����������� ������ Node � �����������
HuffmanTree::Node::Node(Node* first, Node* second) {
    m_left = first; 
    m_right = second; 
    m_frequency = first->m_frequency + second->m_frequency; 
    m_symbols.insert(first->m_symbols.begin(), first->m_symbols.end()); 
    m_symbols.insert(second->m_symbols.begin(), second->m_symbols.end()); 
}

// ����� ��� ��������� ������ �������
HuffmanTree::Node*& HuffmanTree::Node::getLeft() {
    return m_left; 
}

// ����� ��� ��������� ������� �������
HuffmanTree::Node*& HuffmanTree::Node::getRight() {
    return m_right; 
}

// ����� ��� ��������� ������� ��������
int& HuffmanTree::Node::getFrequency() {
    return m_frequency; 
}

// ����� ��� ��������� ��������� ��������
std::set<char> HuffmanTree::Node::getSymbols() {
    return m_symbols; 
}

// ����� ��� ��������� ��������
void HuffmanTree::Node::setSymbols(const char symbol) {
    m_symbols.insert(symbol); 
}