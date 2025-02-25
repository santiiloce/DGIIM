/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Oct 16 2024
 * @brief Programa diseñado para que lea una letra y la exprese en minuscula
 *        si esta es mayuscula y viceversa.
 *        Jutge problem P98960
 *        The program takes directly the input and prints the output
 */

#include <iostream>

int main() {
  char letra_inicial, letra_convertida;
  std::cin >> letra_inicial;

  if ('A' <= letra_inicial && letra_inicial <= 'Z'){
    letra_convertida = letra_inicial + ('a' - 'A');
  }
  else if ('a' <= letra_inicial && letra_inicial <= 'z'){
    letra_convertida = letra_inicial - ('a' - 'A');
  }
  else{
    std::cerr << "Error con la letra introducida";
    return 1;
  }
    
  std::cout << letra_convertida << std::endl;

  return 0;
 }
  
