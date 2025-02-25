/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 08 2024
 * @brief Programa que calcula el mcd de dos numeros naturales usando el 
 *        algoritmo de euclides
 * The program takes directly the input and prints the output
 */
#include <iostream>

int gcd (int a, int b){
  int mcd;
  if (b > a){
  	int aux = a;
  	a = b;
  	b = aux;
  }
  if (b == 0) // Excepcion del cero
  	return a;
  int diferencia = a - b;
  while(diferencia != 0){
  	while (diferencia > 0){
  	  if(diferencia - b < 0)
  	    break;	// No cuenta la ultima iteracion que genera el resto
  	  diferencia -= b;
    }
    if (diferencia != 0){ // Si no es cero permito entonces que siga ejecut�ndose
   	  a = b;
   	  b = diferencia;
      diferencia = a - b;
    }
  }
  return b;
}

int main();
 int a;
 int b;
 std::cin>>a>>b;
 std::cout<<gcd(a,b)<<std::endl;
 return 0;
}

