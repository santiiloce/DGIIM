/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
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
