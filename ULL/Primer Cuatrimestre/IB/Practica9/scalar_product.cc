/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2022-2023
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @date Nov 17 2024
  * @brief El programa que ejecuta una funcion matematica de tres variables
  * @bug Therea are  no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */
#include <iostream>
#include <vector>
#include <string>

std::vector<double> StringToVector (std::string cadena){
  std::vector<double> resultado;
  std::string numero;
  for (int i = 0; i < cadena.size(); i++){
    
}

double ScalarProduct (std::vector<double> num1, std::vector<double> num2){
  if (num1.size() != num2.size()){
    std::cerr << "Invalid numbers";
    return 0;
  }
  int resultado = 0;
  for (int i = 0; i < num1.size(); i++){
    resultado += num1.at(i) * num2.at(i);
  }
  return resultado;
}

int main(int argc, char* argv[]){
    if (argc != 3){
      std::cerr << "Ejemplo de ejecucion: ./scalar_product 3,7,8 8,9,10 ";
    return 1;
  }
  std::string num1, num2;
  num1 = argv[1];
  num2 = argv[2];
  int cont1, cont2;
  cont1 = 0;
  cont2 = 0;
  std::vector<double> convertido1 = StringToVector(num1); // Inicializo los vectores con su tamanio correspondiente
  std::vector<double> convertido2 = StringToVector(num2);

  std::cout << ScalarProduct(convertido1,convertido2) << std::endl;
  return 0;
}
