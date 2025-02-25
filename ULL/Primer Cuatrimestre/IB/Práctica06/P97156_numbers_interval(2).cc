/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date 28 Oct 2024
 * @brief Programa que imprime todos los numeros naturales comprendidos entre
 *        dos numeros naturales dados
 * @see http://www.cplusplus.com/doc/tutorial/program_structure/
 * @see http://cpp.sh/2dd
 */
#include <iostream>
int main(){
  int init, fin;
  std::cin >> init;
  std::cin >> fin;

  if (init > fin){
    std::cout << std::endl;
  }
  
  for(int i = init; i <= fin; i ++){
    if(i == fin){
      std::cout << i << std::endl;
    }
    else{
      std::cout << i << ",";
    }
  }

  return 0;
}
    

     
