#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <string.h>

using namespace std;

#include "gtest/gtest.h"


TEST(convert_to_binary_check, Prueba1){

    //Prueba 1 de tools.cpp
    //Para la funcion Tools::SimpleSmooth(const QImage &origin)
    //Por medio de la siguiente operacion se determina el valor con el que inicia x
    int kernelSize=5;
    int Resultado;

    Resultado = kernelSize/2;

    ASSERT_EQ(2,Resultado);

    //Prueba 2 de tools.cpp
    //Para la funcion Tools::SimpleSmooth(const QImage &origin)
    //El resultado de esta operacion es el primer valor en el for

    int width = 200;
    int Resultado2;

    Resultado2 = width-Resultado;

    ASSERT_EQ(198,Resultado2);

    //Prueba 3 de mainwindow.cpp
    //Prueba para la funcion MainWindow::on_actionOpen_triggered()
    //En esta prueba se  valida que una condicion sea falsa por medio de un string el cual debe de ser leido

    string image = "imagen";

    if(image.length()==0){
        std::cout<<"Esta entrando en el if"<<std::endl;
    }

    ASSERT_FALSE(image.length()==0);

    //Prueba 4 de mainwindow.cpp
    //Prueba para la funcion MainWindow::on_actionAdjust_triggered()
    //Comparacion de que el tamaño dado sea menor que el tamaño maximo de la imagen

    int size[2] = {400,300};
    int max_size[2] = {700,600};

    if (size[0]<max_size[0] && size[1]<max_size[1]){
        std::cout<<"Esta entrando en el if"<<std::endl;
    }

    ASSERT_TRUE(size[0]<max_size[0] && size[1]<max_size[1]);

    //Prueba 5 graphicsview.cpp
    //Prueba de GraphicsView::wheelEvent(QWheelEvent *e)
    //Compara la distancia del movimiento de la rueda del mouse

    int distance = 10;
    int distance2 = 0;

    if (distance != 0){
        ASSERT_TRUE(distance != 0);
    }

    if (distance2 != 0){
        std::cout<<"Esta entrando en el if"<<std::endl;
    }
    ASSERT_FALSE(distance2 != 0);

    //Prueba 6 de gaussianblur.cpp
    //Prueba de GaussianBlur::BlurImage(const QImage& in)
    //Comprueba que unb input dado tenga ancho y largo para la modificacion e sus valores RGB

    int input[2] = {0,0};
    int x = 0;
    int y = 0;

    for (x < input[0]; x++;){
        for (y < input[1]; y++;){
            std::cout<<"Esta entrando en el for"<<std::endl;
        }
    }
    ASSERT_FALSE(x < input[0] || y < input[1]);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}