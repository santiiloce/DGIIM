// AUTOR: Santiago López Cerro 
// FECHA: 24/04/2025
// EMAIL: alu0101763613@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase RPN (Reverse Polish Notation)

#ifndef RPNT_H_
#define RPNT_H_

#include <iostream>
#include <cctype>
#include <cmath>
//#include <cstdlib>

#include "queue_l_t.h"

// Clase RPN (Reverse Polish Notation)
template <class T> class rpn_t {
 public:
  // constructor
 rpn_t(void) : stack_() {}

  // destructor
  ~rpn_t() {}

  // operaciones
  const int evaluate(queue_l_t<char>&);

 private: 
  T stack_;
  void operate_(const char operador);
};


// operaciones
template<class T> const int rpn_t<T>::evaluate(queue_l_t<char>& q) {
  while (!q.empty()) 	{
    char c = q.front();
    
    q.pop();
    std::cout << "Sacamos de la cola un carácter: " << c;

    if (isdigit(c)) {
      int num = c -'0';
      std::cout << " (es un dígito) " << std::endl
		<< "   Lo metemos en la pila..." << std::endl;
      stack_.push(num);
    } else {
      std::cout << " (es un operador)" << std::endl;
      operate_(c);
    }
  }
  return stack_.top();
}

template<class T> void rpn_t<T>::operate_(const char c) {
  assert(c == '+' || c == '-' || c == '*' || c == '/' || c == 'c' || c == '<' ||
  c == '^' || c == 'r' || c == 'l');
  int result = 0;
  int num1 = stack_.top();
  stack_.pop();
  std::cout << "   Sacamos de la pila un operando: " << num1 << std::endl;
  if(c == 'l' || c == 'c' || c == 'r'){   // Operadores unitarios
    switch(c){
      case('l'):
        result = log2(num1);
        break;
      case('c'):
        result = num1 * num1;
        break;
      case('r'):
        result = sqrt(num1);
        break;
      default: 
        std::cerr << "Caracter no valido " << c << std::endl;
        exit(EXIT_SUCCESS);
    }
  }
  else{   // Operadores binarios
    int num2 = stack_.top();
    stack_.pop();
    std::cout << "  Sacamos de la pila otro operando: " << num2 << std::endl;
    switch(c) {
      case '+':
        result = num1 + num2;
        break;
      case '-':
        result = num2 - num1;
        break;
      case '*':
        result = num2 * num1;
        break;
      case '/':
        result = num2 / num1 ;
        break;
      case '<':
         result = num2 < num1;
         std::cout << num2 <<" es menor que " << num1 <<" : " << result;
         break;
      case '^':
        result = pow(num2, num1);
        break;
      default:
        std::cerr << "Caracter no válido " << c << std::endl;
        exit(EXIT_SUCCESS);
    }
  }

  std::cout << "   Metemos en la pila el resultado: " << result << std::endl;
  stack_.push(result);
}

 
#endif  // RPNT_H_
