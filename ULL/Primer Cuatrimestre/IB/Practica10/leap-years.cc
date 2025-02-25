/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief Programa que determina si un año es bisiesto
 * The program takes directly the input and prints the output
 */
#include <iostream>
/*
void PrintProgramPurpose(){
  std::cout << "Programa que determina si un año es bisiesto";
  std::cout << std::endl;
}
*/
void IsLeapYear (const int year){
  bool leap = false;
  if (year % 400 == 0){
    leap = true;
  }
  else if (year % 100 == 0){
    leap = false;
  }
  else if (year % 4 == 0){
    leap = true;
  }

  if(leap)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

int main(){
  int year;
  //PrintProgramPurpose();
  while (std::cin >> year){
    IsLeapYear (year);
  }
  return 0;
}

