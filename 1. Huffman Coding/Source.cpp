#include <iostream> 
#include <fstream> 
#include <algorithm>
#include <vector> 

#include "HuffmanTree.h" 

using std::cout; 
using std::endl; 

int main() {
    setlocale(LC_ALL, "Russian"); 

    std::ifstream inputFile("input.txt"); 
    std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>()); 

    HuffmanTree huffmanTree; 
    huffmanTree.build(text); 
    std::vector<bool> encodedBits; 

    double compressionRatio = huffmanTree.encode(text, encodedBits); 
    cout << "Сжатие данных: " << compressionRatio << endl; 

    std::ofstream encodedFile("encoded.bin", std::ios::binary); 
    for (bool bit : encodedBits) {
        encodedFile.put(bit ? '1' : '0'); 
    }
    encodedFile.close(); 

    std::ifstream encodedInputFile("encoded.bin", std::ios::binary); 
    std::vector<bool> encodedInputBits; 
    char bit;
    while (encodedInputFile.get(bit)) {
        encodedInputBits.push_back(bit == '1'); 
    }
    encodedInputFile.close(); 

    std::string decodedText; 
    huffmanTree.decode(encodedInputBits, decodedText); 
    std::ofstream decodedFile("decoded.txt"); 
    decodedFile << decodedText; 
    decodedFile.close(); 

    // Проверка успешности декодирования
    if (text == decodedText) {
        cout << "Декодирование данных выполнено успешно!" << endl; 
    }
    else {
        cout << "Декодирование данных выполнено неудачно!" << endl;}

    return 0;
}