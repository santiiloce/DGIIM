	/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 08 2024
 * @brief Programa que que lee un car�cter y dice si es letra, si es vocal, si 
 *                es consonante, si es may�scula, si es min�scula y si es un 
 *                d�gito.
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <string>     
#include <cctype>

void print_line(char c, std::string s, bool b){
  std::cout << s << "('" << c << "') = ";
        if (b) std::cout << "true" << std::endl;
        else std::cout << "false" << std::endl;
    
}

bool EsVocal (char letter){
  bool vocal = false;
  if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U')
    vocal = true;
  return vocal;
}

int main(){
  char caracter, mayuscula;
  std::cin >> caracter;
  mayuscula = toupper(caracter);
  print_line (caracter, "letter", (mayuscula >= 'A' && mayuscula <= 'Z'));
  print_line (caracter,"vowel", (mayuscula >= 'A' && mayuscula <= 'Z') && EsVocal(mayuscula));
  print_line (caracter,"consonant", (mayuscula >= 'A' && mayuscula <= 'Z') && !EsVocal(mayuscula));
  print_line (caracter,"uppercase", (mayuscula >= 'A' && mayuscula <= 'Z') && caracter == mayuscula); 
  print_line (caracter,"lowercase", (mayuscula >= 'A' && mayuscula <= 'Z') && caracter != mayuscula); 
  print_line (caracter,"digit", (caracter >= '0' && mayuscula <= '9')); 
  return 0;
}
  
   
  
