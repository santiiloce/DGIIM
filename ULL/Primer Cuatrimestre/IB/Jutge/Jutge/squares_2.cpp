/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief Programa que imprime cuadrados n × n, dibujando cada cuadrado 
 *        de forma independiente y llenandolo con 0, 1,…, 9, 0, etc.
 * The program takes directly the input and prints the output
 *
 **/
#include <iostream>

int main() {
  int input;
  int contador = 0;
  bool aux = false; //Variable auxiliar para contar impresiones de bloque

  while (std::cin >> input) {
  	contador = 0;	// Reinicio los valores a mostrar	
  	if ((input < 1) || (input > 9)) //Verificacion de datos
  		return 1;
  		
    if (aux) {
      std::cout << std::endl;  // Línea en blanco entre bloques
    }

    // Defino la matriz mediante bucles
    for (int i = 0; i < input; i++) {
      for (int j = 0; j < input; j++) {
        std::cout << contador;
        contador++;
        if (contador == 10)  // Validacion de rango 
          contador = 0;
      }
      std::cout << std::endl;
    }

      aux = true;  // Contamos la primera impresion de bloque
  }
  

  return 0;
}
