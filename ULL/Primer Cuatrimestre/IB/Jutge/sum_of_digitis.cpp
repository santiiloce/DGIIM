/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief Programa que devuelve la suma de las cifras de cada numero
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <string>

int main(){
  std::string entrada;
  int suma;
  while ( std::cin >> entrada){
    suma = 0;
    for (int i = 0; entrada[i] != '\0'; i++){
      suma += entrada[i] - '0';
    }
    std::cout << "The sum of the digits of " << entrada << " is "<< suma << "." << std::endl;
  }
  return 0;
}
