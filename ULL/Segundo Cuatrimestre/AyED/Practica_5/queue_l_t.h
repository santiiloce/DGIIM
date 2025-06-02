// AUTOR: Santiago López Cerro 
// FECHA: 24/04/2025
// EMAIL: alu0101763613@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase TAD cola implementada con una lista

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <cassert>
#include <vector>

#include "dll_t.h"

// Clase TAD cola implementada con una lista
template <class T> class queue_l_t {
 private:
  dll_t<T>    l_;

 public:
  // constructor
  queue_l_t(void) : l_() {}

  // destructor
  ~queue_l_t(void) {}

  // operaciones
  bool empty(void) const;
  int size(void) const;
  void push(const T& dato);
  void pop(void);
  const T& front(void) const;
  const T& back(void) const;
  void invert();
  void erase_odds();
  void fuze(queue_l_t<T>& one, queue_l_t<T>& two, queue_l_t<T>& fuze);
  void erase_repetition();

  // E/S
  std::ostream& write(std::ostream& os = std::cout) const;
};


// operaciones
template<class T> bool queue_l_t<T>::empty(void) const {
  return l_.empty();
}

template<class T> int queue_l_t<T>::size(void) const {
  return l_.get_size();	
}

template<class T> void queue_l_t<T>::push(const T& dato) {
  dll_node_t<T>* node = new dll_node_t<T>(dato);
  assert(node != NULL);
  l_.push_front(node);
}

template<class T> void queue_l_t<T>::pop(void) {
  assert(!empty());
  delete l_.pop_back();
}

template<class T> const T& queue_l_t<T>::front(void) const {
  assert(!empty());
  return (l_.get_tail()->get_data());
}

template<class T> const T& queue_l_t<T>::back(void) const {
  assert(!empty());
  return (l_.get_head()->get_data());
}

 // E/S
template<class T> std::ostream& queue_l_t<T>::write(std::ostream& os) const {
  dll_node_t<T>* aux = l_.get_head();
  while (aux != NULL) {
    os << aux->get_data() << " ";
    aux = aux->get_next();
  }
  os << std::endl;
  return os;
}

template<class T> std::ostream& operator<<(std::ostream& os,
					   const queue_l_t<T>& q) {
  q.write(os);
  return os;
}

// Ejercicio 1 (comprobado)
template<class T>
void queue_l_t<T>::invert(){
  stack_l_t<T> pila;
  // Sacamos los elementos y los guardamos en una pila
  while(!empty()){
    T aux = front();
    pop();
    pila.push(aux);
  }
  // Los volvemos a guardar
  while(!pila.empty()){
    T aux = pila.top();
    pila.pop();
    push(aux);
  }
}

// Ejercicio 2 (comprobado)
template<class T>
void queue_l_t<T>::erase_odds(){
  int sz = this->size();
  if(sz % 2 != 0 && !empty()){
    pop(); // Ya tenemos una cola de tamanio par
  }
  queue_l_t<T> cola_aux;
  //std::cout << "Inicialmente esta vacia" << cola_aux.empty() << std::endl;
  while(!empty()){  // Como la cola es de tamanio par saco los elementos de dos en dos
    T aux = front();
    std::cout << "Salvamos " << aux << std::endl;
    pop();
    cola_aux.push(aux);
    pop();
  }
  // Paso los elemento impares a la cola original
  while(!cola_aux.empty()){
    T aux = cola_aux.front();
    cola_aux.pop();
    push(aux);
  }
}

// Ejercicio 3 (comprobado)
template<class T>
void queue_l_t<T>::fuze(queue_l_t<T>& one, queue_l_t<T>& two, queue_l_t<T>& fuze){
  int min_sz = std::min(one.size(), two.size());
  T aux1, aux2;
  for(int i{0}; i < min_sz; ++i){
    aux1 = one.front();
    one.pop();
    aux2 = two.front();
    two.pop();
    fuze.push(aux1);
    fuze.push(aux2);
  }
  while(!one.empty()){
    aux1 = one.front();
    one.pop();
    fuze.push(aux1);
  }
  while(!two.empty()){
    aux2 = two.front();
    two.pop();
    fuze.push(aux2);
  }
}

// Ejercicio 4 
template<class T>
bool belongs(std::vector<T> aux, T k){ // Cuidado con el std
  for(T valor: aux){
    if( valor == k){
      return true;
    } 
  }
  return false;
}

template<class T>
void queue_l_t<T>::erase_repetition(){
  std::vector<T> v;
  T aux;
  while(!empty()){
    aux = front();
    pop();
    if(!belongs(v, aux)){
      v.push_back(aux);
    }
  }
  for(int i{0}; i < v.size(); ++i){
    push(v.at(i));
  }
}

#endif  // QUEUE_H_
