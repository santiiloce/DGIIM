/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 03 2024
 * @brief  Escriba un programa que imprima cuadrados con n^2 n's.
 * The program takes directly the input and prints the output
 *
 **/
#include <iostream>

int main() {
  int input;
  bool aux = false; //Variable auxiliar para contar impresiones de bloque

  while (std::cin >> input) {
  	if ((input < 1) || (input > 9)) //Verificacion de datos
  		return 1;
  		
    if (aux) {
      std::cout << std::endl;  // L�nea en blanco entre bloques
    }

    // Imprimir el bloque de n�meros input veces
    for (int i = 0; i < input; i++) {
      for (int j = 0; j < input; j++) {
        std::cout << input;
      }
      std::cout << std::endl;
    }

    aux = true;  // Contamos la primera impresion de bloque
  }

  return 0;
}

  	    
