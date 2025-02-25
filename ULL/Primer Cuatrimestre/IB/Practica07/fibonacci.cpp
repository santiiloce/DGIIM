#include <iostream>

int main(){
  int iteraciones;
  int num1, num2, num3;
  num1 = 0;
  num2 = 1;
  num3 = 1;
  std::cin >> iteraciones;
  //Comprueba las posibles excepciones que pueden ocurrir
  switch(iteraciones){
    case 0:
       return 0;
    case 1:
      std::cout << num1;
      return 0;
      break;
    case 2:
      std::cout << num2;
      return 0;
      break;
    case 3:
      std::cout << num3;
      return 0;
    default:
      std::cout << "";
  }


  iteraciones -= 3;
  std::cout << num1 << " " << num2 << " " << num3;
  for(int i = 0; iteraciones > 0 && i < iteraciones; i++){
    num1 = num2;
    num2 = num3;
    num3 = num1 + num2;
    std::cout << " " << num3;
  } 
  std::cout << std::endl;
  return 0;
}
