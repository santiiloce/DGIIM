#include <iostream>
#include <string>

int main(){
  std::string entrada;
  int suma = 0;
  std::cin >> entrada;
  for (int i = 0; entrada[i] != '\0'; i++){
    suma += entrada[i] - '0';
  }
  std::cout << suma << std::endl;
  return 0;
}
