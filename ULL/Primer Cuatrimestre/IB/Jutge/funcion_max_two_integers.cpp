/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Funcion que devuelve mayor numero entre dos dados
 * The program takes directly the input and prints the output
 */
#include <iostream>
int max2(int a, int b){
  int max = a;
  if(b > a)
    max = b;
  return max;
}
