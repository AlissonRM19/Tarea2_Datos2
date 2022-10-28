//
// Created by devem on 10/1/22.
//

#include "convert_to_binary.h"

void convert_to_binary::convert(std::string name) {
    ifstream image(name, ios::in | ios::binary);
    ofstream binary ("Data.txt", ios::out | ios::app);
    char ch;

    while(!image.eof()){
        ch = image.get();
        binary.put(ch);
    }

    image.close();
    binary.close();
    return;
}