#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <string.h>

using namespace std;

#include "gtest/gtest.h"


TEST(convert_to_binary_check, Prueba1){

    //Prueba 1 para la funcion SimpleSmooth
    //Por medio de la siguiente operacion se determina el valor con el que inicia x
    int kernelSize=5;
    int Resultado;

    Resultado = kernelSize/2;

    ASSERT_EQ(2,Resultado);

    //Prueba 2 para la funcion SimpleSmooth
    //El resultado de esta operacion es el primer valor en el for

    int width = 200;
    int Resultado2;

    Resultado2 = width-Resultado;

    ASSERT_EQ(198,Resultado2);

    //Prueba 3 Open a image file and show it on canvas
    //prueba para la funcion MainWindow::on_actionOpen_triggered()
    //En esta prueba se  valida que una condicion sea falsa por medio de un string el cual debe de ser leido

    string image = "imagen";

    if(image.length()==0){
        std::cout<<"Esta entrando en el if"<<std::endl;
    }

    ASSERT_FALSE(image.length()==0);


}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}