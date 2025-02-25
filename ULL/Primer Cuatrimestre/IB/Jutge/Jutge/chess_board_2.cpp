/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 03 2024
 * @brief  Consiste en calcular la cantidad total de monedas en las casillas 
 *         blancas en un tablero de ajedrez representado como una cuadr�cula de 
 * 		   caracteres. Cada casilla del tablero puede contener un n�mero de 
 *		   monedas que var�a entre 0 y 9, y se indica mediante caracteres en una 
 *		   cadena.
 * The program takes directly the input and prints the output
 *
 **/
#include <iostream> 
#include <string>
#include <vector>

int main(){
  int rows, cols;
  int total = 0;
  std::cin >> rows >> cols;
  std::vector<std::string> coins(rows);
  // Entrada de monedas por cuadrado
  for (int i = 0; i < rows; i++)
    std::cin >> coins.at(i);
   
  for ( int i = 0; i < rows; i++){
  	for (int j = 0; j < cols; j++){
  	  std::string aux = coins.at(i);
	  if( (i % 2 == 0 and j % 2 != 0) or (i % 2 != 0 and j % 2 == 0))
	    continue;
  	  if ((aux[j] - '0' < 0) || (aux[j] - '0' > 9)){  // Validacion de datos
  	  	return 1;
  	  }
  	  total += aux[j] - '0'; // Paso a numeros y sumo
    }
  }
  std::cout << total << std::endl;
  return 0;
}
  
