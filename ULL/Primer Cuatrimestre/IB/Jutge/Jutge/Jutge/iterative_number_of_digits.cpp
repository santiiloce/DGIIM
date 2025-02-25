/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 08 2024
 * @brief Funcion que devuelve el numero de cifras de un numero
 * The program takes directly the input and prints the output
 */
#include <string>
#include <iostream>
 
int number_of_digits(int n){
 if(n == 0) // Control de excepciones
    return 1;
  int size = 0;
  while (n != 0){
  	size++;
  	n /= 10;
  }
  return size;
}
  
	
