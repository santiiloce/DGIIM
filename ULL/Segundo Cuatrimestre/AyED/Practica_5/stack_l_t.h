// AUTOR: Santiago López Cerro 
// FECHA: 24/04/2025
// EMAIL: alu0101763613@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// TEMA: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: 

#ifndef STACKL_H_
#define STACKL_H_

#include <iostream>
#include <iomanip>
#include <cassert>

#include "dll_t.h"

// Clase para pilas mediante estructura dinámica
template<class T> class stack_l_t {
 public:	
  // constructor
  stack_l_t(void) : l_() {}

  // destructor
  ~stack_l_t(void) {}

  // operaciones
  void push(const T&);
  void pop(void);
  const T& top(void) const;
  bool empty(void) const;
  void erase_odds();
  void swap12();
  void organize(T k, stack_l_t<T>& stack1, stack_l_t<T>& stack2);
  T max();

  // E/S	
  std::ostream& write(std::ostream& os = std::cout) const;

private:
  dll_t<T> l_;
};


// operaciones
template<class T> void stack_l_t<T>::push(const T& dato) {
  dll_node_t<T>* nodo = new dll_node_t<T>(dato);
  assert(nodo != NULL);
  l_.push_front(nodo);
}

template<class T> void stack_l_t<T>::pop(void) {
  assert(!empty());
  delete l_.pop_front();
}

template<class T> const T& stack_l_t<T>::top(void) const {
  assert(!empty());
  return l_.get_head()->get_data();
}

template<class T> bool stack_l_t<T>::empty(void) const {
  return l_.empty();
}

// E/S
template<class T> std::ostream& stack_l_t<T>::write(std::ostream& os) const {
  dll_node_t<T>* aux = l_.get_head();
  while (aux != NULL) { 
    os << " │ " << std::setw(2) << aux->get_data() << "  │" << std::endl;
    aux = aux->get_next();
  }
  os << " └─────┘" << std::endl;
  return os;
}

// Ejercicio 1
template<class T>
void stack_l_t<T>::swap12(){
  T uno = top();
  pop();
  if(empty()){
    push(uno);
  }
  else{
    T dos = top();
    pop();
    push(uno);
    push(dos);
  }
}

// Ejercicio 3
template<class T> 
void stack_l_t<T>::erase_odds(){
  stack_l_t<T> other;
  while(!empty()){
    T aux = top();
    pop();
    other.push(aux);
  }
  
  while(!other.empty()){
    other.pop();
    if(!other.empty()){
      T aux = other.top();
      push(aux);
      other.pop();
    }
  }
}

// Ejercicio 4
template<class T>
void stack_l_t<T>::organize(T k, stack_l_t<T>& stack1, stack_l_t<T>& stack2){
  while(!empty()){
    T aux = top();
    pop();
    (aux > k) ? stack1.push(aux) : stack2.push(aux);
  }
  stack1.write();
  stack2.write();
}

// Ejercicio 5
template<class T>
T stack_l_t<T>::max(){
  while(!empty()){
    T uno = top();
    pop();
    if(empty()){
      push(uno);
      break;
    }
    T dos = top();
    pop();
    T max = std::max(uno,dos);
    push(max);
  }
  return top();
} 

#endif  // STACKL_H_
