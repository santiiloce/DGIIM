/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 03 2024
 * @brief Programa que devuelve el producto de las cifras de cada numero
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <string>

int main(){
  std::string entrada;
  int producto = 1;
  while ( std::cin >> entrada){
  	while (producto != 0){
  	  producto = 1; // Lo inicializo por el elemento identidad 
      for (int i = 0; entrada[i] != '\0'; i++){
        producto *= entrada[i] - '0';
      }
      std::cout << "The product of the digits of " << entrada << " is "<< producto << "." << std::endl;
      entrada =  std::to_string(producto);
      
    }
  }
  return 0;
}
