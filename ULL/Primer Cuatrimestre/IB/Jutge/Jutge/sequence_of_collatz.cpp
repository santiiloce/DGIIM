/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief Programa que dado un numero devuelve el numero de pasos necesarios
          tomados para llegar a uno mediante la secuencia de Collatz
 * The program takes directly the input and prints the output
 */
#include <iostream>
bool Comprobacion( int input){
	return input == 1;
}

int main(){
  int input;
  int contador = 0;
  while (std::cin >> input){
  	contador = 0;
  	if (input < 0){
  		return 1;
  	}
   	while (!Comprobacion(input)){
  	  if (input % 2 == 0)
  	  	input /= 2;
  	  else{
  	  	input *= 3;
  	  	input++;
  	  }
  	  contador++;
    }
    std::cout << contador << std::endl;
  	
  }  
	return 0;
}
  	  	
  	  
