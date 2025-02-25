/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Oct 16 2024
 * @brief Programa diseñado para que dada las horas, minutos y segundos
 *        devuelve lo mismo en formato hora con un segundo adicional 
 *        si esta es mayuscula y viceversa.
 *        Jutge problem P98960
 *        The program takes directly the input and prints the output
 */




#include <iostream>

// Funcion que dado un parametro lo ajusta al formato
void Conversion (int cantidad, char tipo){
  if (tipo != 's'){ 
    if (cantidad < 10 ){
      std::cout << "0" << cantidad << ":";
    }
    else{
      std::cout << cantidad << ":";
    }
  }
  else{
    if (cantidad < 9){
      std::cout  << "0" << (cantidad + 1) << std::endl;
    }
    else if (cantidad == 59){
      std::cout  << "00" << std::endl;
    }
    else{
      std::cout << (cantidad + 1) << std::endl;
    } 
  }
}

int main(){
  int h, m, s, hora_final;
  std::cin >> h;
  std::cin >> m;
  std::cin >> s;
  if (h > 24 || m > 60 || s > 60){
    std::cerr << "Numeros invalidos";
    return 1;
  }
  if (s == 59){
    if (m == 59){
      h = (h + 1) % 24;
      m = 0;
    }
    else{
      m++;
    }
  }  
  Conversion(h, 'h');
  Conversion(m, 'm');
  Conversion(s, 's');
  return 0;
}
    

    
