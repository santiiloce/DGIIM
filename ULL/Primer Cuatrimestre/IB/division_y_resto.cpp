/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Oct 16 2024
 * @brief Programa diseñado para que lea dos números naturales a y b, con b>0,
 *        e imprime la división de entero d y el resto r de una dividida por
 *        lea dos números naturales a y b, con b 0, e imprime la división de
 *        entero d y el resto r de una dividida por b
 *        Jutge problem P48107
 *        The program takes directly the input and prints the output
 * @see https://jutge.org/problems/P97139
 */

#include <iostream>
#include <string>

int main(){
  int cociente, dividendo, resto, divisor;
  cociente = dividendo = resto = divisor = 0; // Inicializo las variables

  // Leo los datos
  std::cin >> dividendo >> divisor;

  // Determino que el divisor no sea negativo
  if( divisor < 0 or divisor == 0 )
    return 1;
  
  // Realizo las operaciones
  cociente = dividendo / divisor;
  resto = dividendo % divisor;

  // Muestro los resultados por pantalla
  std::cout << cociente << " " << resto << std::endl;

  return 0;
}
