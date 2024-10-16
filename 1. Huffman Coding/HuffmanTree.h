#pragma once // ��������� �������������, ������� ������������� ������������ ��������� �����

#include <string> // ����������� ���������� ��� ������ �� ��������
#include <set> // ����������� ���������� ��� ������ � �����������
#include <vector> // ����������� ���������� ��� ������ � ���������

class HuffmanTree { // ���������� ������ HuffmanTree
public:
    class Node; // ��������� ����� Node

    HuffmanTree(); // ����������� ������ HuffmanTree

    ~HuffmanTree(); // ���������� ������ HuffmanTree
    void removal(); // ����� ��� �������� ������

    void build(const std::string& text); // ����� ��� ���������� ������ ��������

    double encode(const std::string& text, std::vector<bool>& encodedBits); // ����� ��� ����������� ������

    bool decode(const std::vector<bool>& encodedBits, std::string& decodedText) const; // ����� ��� ������������� ������

private:
    Node* m_root; // ��������� �� ������ ������

private:
    void removalAuxiliary(Node* node); // ��������������� ����� ��� �������� ������
};

class HuffmanTree::Node { // ���������� ���������� ������ Node
public:
    Node(); // ����������� ������ Node
    Node(Node* first, Node* second); // ����������� ������ Node � �����������

    Node*& getLeft(); // ����� ��� ��������� ������ �������
    Node*& getRight(); // ����� ��� ��������� ������� �������
    int& getFrequency(); // ����� ��� ��������� ������� ��������
    std::set<char> getSymbols(); // ����� ��� ��������� ��������� ��������

    void setSymbols(const char symbol); // ����� ��� ��������� ��������

private:
    Node* m_left; // ��������� �� ������ �������
    Node* m_right; // ��������� �� ������� �������
    int m_frequency; // ������� ��������
    std::set<char> m_symbols; // ��������� ��������
};