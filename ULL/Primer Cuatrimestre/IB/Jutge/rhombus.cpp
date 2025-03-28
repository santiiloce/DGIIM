/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief  Programa que, dado un número n, imprime un "rombo de tamaño n".
 * The program takes directly the input and prints the output
 *
 **/
#include <iostream>
#include <string>

int main(){
  int size;
  std::string rhombus = "";
  std::cin >> size;
  if(size < 1){	// Validacion de datos
  	return 1;
  }
  int mitad = (2*size - 1)/2;
  // Inicio del rombo
  for(int i = 0; i <= mitad; i++){
  	if ( i == mitad)
      rhombus += "*";
  	else
  	  rhombus += " ";
  }
  // Comprobación de rombo no nulo
  if( size != 0)
    std::cout << rhombus << std::endl;
    
  // Impresion hasta la mitad del rombo
  for(int i = 1; i <= mitad; i++){
  	rhombus[mitad - i] = '*';
    rhombus += '*';
    std::cout << rhombus << std::endl;
  }
  // Impresion del resto
  for(int i = 0; i < mitad; i++){
  	int aux = (2*size - 2) - i;
  	rhombus[aux] -= '*';
    rhombus[i] = ' ';
    std::cout << rhombus << std::endl;
  }
  
  return 0;
}
