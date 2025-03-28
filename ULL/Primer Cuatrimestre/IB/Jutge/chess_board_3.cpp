/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief  Consiste en calcular la cantidad total de monedas en las casillas 
 *         que se encuentran en ambas diagonales en un tablero de ajedrez 
 *         representado como una cuadrícula de caracteres. Cada
 * 		   casilla del tablero puede contener un número de monedas que
 *		   varía entre 0 y 9, y se indica mediante caracteres en una cadena.
 * The program takes directly the input and prints the output
 *
 **/
#include <iostream> 
#include <string>
#include <vector>

int main(){
  int size;
  int total = 0;
  std::cin >> size;
  std::vector<std::string> coins(size);
  // Entrada de monedas por cuadrado
  for (int i = 0; i < size; i++)
    std::cin >> coins.at(i);
   
  for ( int i = 0; i < size; i++){
  	for (int j = 0; j < size; j++){
  	  std::string aux = coins.at(i);
  	  if ((aux[j] - '0' < 0) || (aux[j] - '0' > 9)){  // Validacion de datos
  	  	return 1;
  	  }
	  if( (i == j) or (i == (-j + (size - 1)) ))
	    total += aux[j] - '0'; // Paso a numeros y sumo

    }
  }
  std::cout << total << std::endl;
  return 0;
}

