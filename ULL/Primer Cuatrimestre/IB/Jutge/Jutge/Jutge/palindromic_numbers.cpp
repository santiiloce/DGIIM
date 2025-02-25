/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Funcion que determina si un numero es un palindromo o no
 * The program takes directly the input and prints the output
 */

#include <cmath>
#include <iostream>
#include <string>
 
int number_of_digits(int n){
  if (n < 0) // Control de excepciones
    return -1;
  else if(n == 0)
    return 1;
  int size = 0;
  while (n != 0){
  	size++;
  	n /= 10;
  }
  return size;
}

bool is_palindromic(int n){
  int size = number_of_digits(n);
  bool palindromo = true;
  std::string s_number = std::to_string(n);
  for (int i = 0; i < size/2 && palindromo; i++){
  	if (s_number[i] - s_number[size - 1 - i])
	  palindromo = false;   
  }
  return palindromo;
}

  	
  
