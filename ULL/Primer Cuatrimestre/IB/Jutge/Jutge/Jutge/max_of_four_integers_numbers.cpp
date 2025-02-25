/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Funcion que devuelve mayor numero entre cuatro dados
 * The program takes directly the input and prints the output
 */
#include <iostream>
int max4(int a, int b, int c, int d){
  int max = a;
  if(b >= a && b >= c && b >= d)
    max = b;
  else if( c >= a && c >= b && c >= d)
    max = c;
  else if ( d > a )
    max = d;
  return max;
}
