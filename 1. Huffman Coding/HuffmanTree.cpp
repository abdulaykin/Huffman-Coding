#include <iostream> 
#include <string> 
#include <list>
#include <set> 

#include "HuffmanTree.h"

using std::cout; 

// ����������� ������ HuffmanTree
HuffmanTree::HuffmanTree() {
    m_root = nullptr; 
}

// ���������� ������ HuffmanTree
HuffmanTree::~HuffmanTree() {
    removal(); 
}

// ����� ��� �������� ������
void HuffmanTree::removal() {
    removalAuxiliary(m_root); 
    m_root = nullptr; 
}

// ��������������� ����� ��� �������� ������
void HuffmanTree::removalAuxiliary(Node* node) {
    if (node == nullptr) { 
        return;
    }

    removalAuxiliary(node->getLeft()); 
    removalAuxiliary(node->getRight()); 

    delete node; 
}

// ����� ��� ���������� ������ ��������
void HuffmanTree::build(const std::string& text) {
    removal(); 

    int frequencies[256] = {}; 

    // ������� ������ �������� � ������
    for (int i = 0; i < text.length(); i++) {
        frequencies[text[i]]++;
    }

    std::list<Node*> nodes; 

    // �������� ����� ��� ������� ������� � ��������� ��������
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] == 0) {
            continue;
        }

        Node* newNode = new Node; 

        newNode->getFrequency() = frequencies[i]; 
        newNode->setSymbols(i); 

        nodes.push_back(newNode); 
    }

    // ���������� ������ ��������
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

// ����� ��� ����������� ������
double HuffmanTree::encode(const std::string& text, std::vector<bool>& encodedBits) {
    if (m_root == nullptr) { 
        build(text);
    }

    encodedBits.clear(); 

    // ����������� ������� ������� � ������
    for (int i = 0; i < text.length(); i++) {
        char huffmanChar = text[i]; 
        std::set<char> symbols = m_root->getSymbols();

        // ���� ������ �� ������ � ������, ���������� -1
        if (symbols.find(huffmanChar) == symbols.end()) {
            return -1;
        }

        // ���� � ����� ������ ������ ���� ������, ��������� '0'
        if (symbols.size() == 1) {
            encodedBits.push_back(false);
            continue;
        }

        Node* node = m_root; 

        // ����� ���� ������� � ������
        while ((node->getSymbols().size()) > 1) {
            Node* left = node->getLeft(); 

            if (left == nullptr) { 
                continue;
            }

            std::set<char> leftSymbols = left->getSymbols(); 

            // ���� ������ ������ � ����� �������, ��������� '0'
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

    // ���������� ����������� ������
    return double(encodedBits.size()) / double(text.size() * 8);
}

// ����� ��� ������������� ������
bool HuffmanTree::decode(const std::vector<bool>& encodedBits, std::string& decodedText) const {
    decodedText = ""; 

    Node* node = m_root; 

    // ���� ������ ������ �����������, ���������� false
    if (node == nullptr) {
        return false;
    }

    // ������������� ������� ���� � �������������� ������
    for (bool bit : encodedBits) {
        if (m_root->getSymbols().size() == 1) { 
            if (bit != false) { 
                return false;
            }

            decodedText += *(node->getSymbols().begin());
            continue;
        }

        // ����������� �� ������ � ����������� �� ���� '0' ��� '1'
        if (bit == false) {
            node = node->getLeft(); 
        }
        else if (bit == true) {
            node = node->getRight(); 
        }
        else {
            return false; 
        }

        // ���� ���� �����������, ���������� false
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