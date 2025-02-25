/*Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Oct 16 2024
 * @brief Programa diseñado para que inicialice variables de tipos aritméticos e
 * imprima en pantalla el resultado de operar esas variables con todos los
 * operadores posibles 
 *        Jutge problem P97139
 *        The program takes directly the input and prints the output
 * @see https://jutge.org/problems/P97139
 * @see
 * http://www.interior.gob.es/web/servicios-al-ciudadano/dni/calculo-del-digito-de-control-del-nif-nie
 */
#include <iostream>
#include <cmath>

int main(){
  double num1, num2;
  // Inicializacion de variables
  std::cout<<"Numero 1: ";
  std::cin>>num1;
  std::cout<<"Numero 2: ";
  std::cin>>num2;
  // Operaciones a realizar
  std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
  std::cout << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
  std::cout << num1 << " / " << num2 << " = " << num1 / num2 << std::endl;
  std::cout << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
  std::cout << num1 << " % " << num2 << " = " << 
  static_cast<int>(num1) % static_cast<int>(num2) << std::endl;
  long double num3=pow(num1,num2);
  std::cout << num1 << " ^ " << num2 << " = " << num3 << std::endl;
  std::cout << num1 << " es igual a " << num2 << " : " << 
  (num1 == num2) << std::endl;
  std::cout << num1 << " es distinto a " << num2 << " : " << 
  (num1 != num2) << std::endl;
  
  return 0;
}
