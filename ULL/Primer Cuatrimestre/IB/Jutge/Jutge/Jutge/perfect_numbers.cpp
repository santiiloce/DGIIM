/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Informatica Basica
 *
 * @author Santiago Lopez Cerro
 * @date Nov 08 2024
 * @brief Funcion que determina si un numero dado es perfecto
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <vector>

void HallaDivisores(std::vector<int>& divisores, int& contador, int n){
  contador = 0;
  int  divisor = 1;
  while (divisor < n){
    if (n % divisor == 0){
      divisores[contador] = divisor;
      contador++;
    }
    divisor++;
  }
}

bool is_perfect(int n){
  if ( n == 0) // Excepcion
    return false;
  std::vector<int> divisores(n);
  int num_divisores;
  int total = 0;
  HallaDivisores(divisores, num_divisores, n);
  for (int i = 0; i <= num_divisores; i++){
  	total += divisores[i];
  }
  if (total == n)
    return true;
  else 
    return false;
}

int main(){
  int n;
  std::cin >> n;
  std::cout << is_perfect(n) << std::endl;
  return 0;
}

