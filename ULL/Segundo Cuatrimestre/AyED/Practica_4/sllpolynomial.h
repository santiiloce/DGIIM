// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  SllPolynomial();
  for(int i{v.get_size() - 1 }  ; i >= 0; --i){
    if(IsNotZero(v.at(i))){
      pair_double_t monomio(v.get_val(i), i);
      SllPolyNode* aux = new SllPolyNode(monomio);   // Asigno puntero
      push_front(aux);
    }
  }
}


// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0}; 
  //std::cout << "4" << std::endl;
  if(this->get_head() != NULL){
    int index;
    double coefficient;
    sll_node_t<pair_double_t>* aux = (this->get_head());
      while(aux != nullptr){
        index = aux->get_data().get_inx();
        coefficient = aux->get_data().get_val();
        result += pow(x, index) * coefficient;
        aux = aux->get_next();
        //std::cout << std::endl << "bucle" << std::endl;
      }
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol, const double eps) const {
  bool differents = false;
  if(this != NULL){
    int index1, index2;
    double coefficient1, coefficient2;
    sll_node_t<pair_double_t>* node1 = this->get_head();
    sll_node_t<pair_double_t>* node2 = sllpol.get_head();
    do{
      index1 = node1->get_data().get_inx();
      coefficient1 = node1->get_data().get_val();
      index2 = node2->get_data().get_inx();
      coefficient2 = node2->get_data().get_val();
      if(node2->get_next() == NULL || index1 != index2 || (coefficient1 - coefficient2) > eps){
        differents = true;
        break;
      }
      node1 = node1->get_next();
      node2 = node2->get_next();
    }while(node1->get_next() != NULL);
    // Se comprueba que el polinomio segundo no sea mas grande que el primero
    if(node2->get_next() != NULL)
      differents = true;
  }
  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol, SllPolynomial& sllpolsum, const double eps){
  if(this->get_head() != NULL){   // Compruebo no trabajar con un polinomio vacio
    int index1, index2;
    SllPolynomial aux;
    double coefficient1, coefficient2;
    sll_node_t<pair_double_t>* node1 = this->get_head();
    sll_node_t<pair_double_t>* node2 = sllpol.get_head();
    while(node1 != nullptr){
      index1 = node1->get_data().get_inx();
      coefficient1 = node1->get_data().get_val();
      index2 = node2->get_data().get_inx();
      coefficient2 = node2->get_data().get_val();
      if(index1 < index2){
        for(int i{index1}; i < index2; ++i){
          SllPolyNode* node_aux = new sll_node_t<pair_double_t>(node1->get_data());    
          aux.push_front(node_aux);
          node1 = node1->get_next();
        }
      }
      else if(index1 > index2){
        for(int i{index2}; i < index1; ++i){
          SllPolyNode* node_aux = new sll_node_t<pair_double_t>(node2->get_data());    
          aux.push_front(node_aux);
          node2 = node2->get_next();
        }
      }
      else{
        double sume = coefficient1 + coefficient2;
        // En caso de ser la suma cero no añado el monomio resultante
        if(IsNotZero(sume)){  
          pair_double_t value(sume, index2); // Creo el value del nodo
          SllPolyNode* node_aux = new SllPolyNode(value); // Reservo espacio de memoria
          aux.push_front(node_aux);  // Añado el nuevo nodo a la lista enlazada
        }
        node1 = node1->get_next();
        node2 = node2->get_next();
      }
    }
    // Se comprueba que el polinomio segundo no sea mas grande que el primero
      while(node2 != nullptr){
        SllPolyNode* node_aux = new sll_node_t<pair_double_t>(node2->get_data());    
        aux.push_front(node_aux);
        node2 = node2->get_next();
      }
      SllPolyNode* node3 = aux.get_head();
      // Usando un polinomio auxiliar invierto el orden de los valores del polinomio solucion
      while(node3 != nullptr){
        SllPolyNode* node_aux = new SllPolyNode(node3->get_data());
        sllpolsum.push_front(node_aux);
        node3 = node3->get_next();
      }
  }
}


#endif  // SLLPOLYNOMIAL_H_
