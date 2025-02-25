#include <iostream>
#include <string>
#include <fstream>
#include "Racional.cc"

int main(int argc, char* argv[]){
    if(argc == 1){
        std::cerr << "./racionales -- Números Racionales" << std::endl;
        std::cerr << "Modo de uso: ./racionales fichero_entrada fichero_salida" << std::endl;
        std::cerr << "Pruebe ./racionales --help para más información" << std::endl;
        return 1;
    }
    if(argv[1] == "--help"){
        std::cerr << "./racionales -- Números Racionales" << std::endl;
        std::cerr << "Modo de uso: ./racionales fichero_entrada fichero_salida" << std::endl;
        std::cerr << "fichero_entrada: Fichero de texto conteniendo líneas con un par de números racionales: a/b c/d separados por un espacio" << std::endl;
        std::cerr << "fichero_salida:  Fichero de texto que contendrá líneas con las operaciones realizadas: a/b + c/d = n/m" << std::endl;
        return 2;
    }
    if(argc != 3){
        std::cerr << "Modo de uso: ./racionales fichero_entrada fichero_salida" << std::endl;
        return 3;
    }
    
    std::ifstream lectura(argv[1]);
    if(!lectura.is_open()){
        std::cerr << "Error al abrir el archivo de lectura" << std::endl;
        return 1;
    }
    std::ofstream escritura(argv[2],std::ios::app);
    if(!escritura.is_open()){
        std::cerr << "Error al abrir el archivo de escritura" << std::endl;
        return 2;
    }
    std::string new_num1;
    std::string new_num2;
    while(lectura >> new_num1 && lectura >> new_num2){
        Racional num1;
        num1.PutNumberString(new_num1);
        Racional num2;
        num2.PutNumberString(new_num2);
        escritura << num1.EjemplificaOperaciones(num2);
        escritura << std::endl;
        escritura << "***********************************************************************" << std::endl;
    }
    lectura.close();
    escritura.close();
    return 0;
}