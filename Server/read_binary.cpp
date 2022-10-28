//
// Created by devem on 10/1/22.
//

#include "read_binary.h"

void read_binary::read(std::string name) {
    ifstream binary("../Client/Data.txt", ios::in | ios::binary | ios::app);
    ofstream image(name, ios::out | ios::app);

    char ch;
    while(!binary.eof()){
        ch = binary.get();
        image.put(ch);

    }
    image.clear();
    binary.close();
}