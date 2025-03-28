/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Funcion que calcula el m.c.m de una serie de numeros recibidos
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <vector>

int gcd(int a, int b){
  if ( a < 0 || b < 0 || (a == 0 && b == 0))
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

int MinimoComunMultiplo (int num1, int num2){
  long int mcm;
  if (gcd(num1,num2) == 1)
    mcm = num1*num2;	// Si su mcd == 1 entoces su mcd sera su producto
  else 
    mcm = (num1/gcd(num1,num2))*num2;
  return mcm;
}
  
int main() {
  int size;
  while (std::cin >> size && size != 0){
  	int numbers[size];
  	for(int i = 0; i  < size; i++){
  	  std::cin >> numbers[i];
    }
    int mcm = numbers[0];
    if (size > 0){
      for (int i = 0; i < size-1; i++){
      	mcm = MinimoComunMultiplo(mcm, numbers[i+1]);
      }
    }
    std::cout << mcm << std::endl;
  }
  return 0;
}
  
  

