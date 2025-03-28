/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Programa que calcula el mcd de 4 numeros naturales usando el 
 *        algoritmo de euclides
 * The program takes directly the input and prints the output
 */
#include <iostream> 

int gcd(int a, int b){
  if ( a < 0 || b < 0 || (a == 0 && b== 0))
    return -1;
  if (b > a){
  	int aux = a;
  	a = b;
  	b = aux;
  }
  if (b == 0) // Excepcion del cero
  	return a;
  int diferencia = a % b;
  while(diferencia != 0){
   	a = b;
   	b = diferencia;
    diferencia = a % b;
  }
  return b;
}

int gcd4(int a, int b, int c, int d){
  if ( a == 0 && b == 0 && c == 0 && d == 0)
    return -1;
  int mcd1 = gcd (a,b);
  int mcd2 = gcd (c,mcd1);
  int mcd3 = gcd (d, mcd2);
  return mcd3;
}
