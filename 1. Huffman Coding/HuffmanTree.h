#pragma once // Директива препроцессора, которая предотвращает многократное включение файла

#include <string> // Подключение библиотеки для работы со строками
#include <set> // Подключение библиотеки для работы с множествами
#include <vector> // Подключение библиотеки для работы с векторами

class HuffmanTree { // Объявление класса HuffmanTree
public:
    class Node; // Вложенный класс Node

    HuffmanTree(); // Конструктор класса HuffmanTree

    ~HuffmanTree(); // Деструктор класса HuffmanTree
    void removal(); // Метод для удаления дерева

    void build(const std::string& text); // Метод для построения дерева Хаффмана

    double encode(const std::string& text, std::vector<bool>& encodedBits); // Метод для кодирования текста

    bool decode(const std::vector<bool>& encodedBits, std::string& decodedText) const; // Метод для декодирования текста

private:
    Node* m_root; // Указатель на корень дерева

private:
    void removalAuxiliary(Node* node); // Вспомогательный метод для удаления дерева
};

class HuffmanTree::Node { // Объявление вложенного класса Node
public:
    Node(); // Конструктор класса Node
    Node(Node* first, Node* second); // Конструктор класса Node с параметрами

    Node*& getLeft(); // Метод для получения левого потомка
    Node*& getRight(); // Метод для получения правого потомка
    int& getFrequency(); // Метод для получения частоты символов
    std::set<char> getSymbols(); // Метод для получения множества символов

    void setSymbols(const char symbol); // Метод для установки символов

private:
    Node* m_left; // Указатель на левого потомка
    Node* m_right; // Указатель на правого потомка
    int m_frequency; // Частота символов
    std::set<char> m_symbols; // Множество символов
};