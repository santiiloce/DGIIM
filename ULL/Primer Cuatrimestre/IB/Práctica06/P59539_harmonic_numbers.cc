/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date 28 Oct 2024
* @brief Programa que dado un numero imprime el enésimo numero armónico
 *
 * @see http://www.cplusplus.com/doc/tutorial/program_structure/
 * @see http://cpp.sh/2dd
 */
#include <iostream>
#include <iomanip>

int main(){
  int numero;
  double numero_armonico = 0.0;
  std::cin >> numero;
  for(int i = 1; i <= numero; i++){
    numero_armonico += 1.0/i;
  }
  std::cout << std::fixed << std::setprecision(4);
  std::cout << numero_armonico << std::endl;
  return 0;
}

