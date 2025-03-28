/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Programa que calcula el mcd de dos numeros naturales usando el 
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

int main(){
  int num1, num2;
  while(std::cin >> num1 >> num2)
    std::cout << gcd(num1, num2) << std::endl;	
  return 0;
}


