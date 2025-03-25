// AUTOR: Santiao López Cerro
// FECHA: 19/12/2025
// EMAIL: alu0101763613@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "vector_t.h"
#include "sparse_vector_t.h"
#include <algorithm>    // std::max

// Clase para polinomios basados en vectores densos de doubles
class Polynomial : public vector_t<double> {
 public:
  // constructores
  Polynomial(const int n = 0) : vector_t<double>(n) {};
  Polynomial(const Polynomial& pol)
      : vector_t<double>(pol) {}; // constructor de copia

  // destructor
  ~Polynomial() {};

  // E/S
  void Write(std::ostream& = std::cout, const double eps = EPS) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
  int SumOfEvenDegrees() const;
 };


// Clase para polinomios basados en vectores dispersos
class SparsePolynomial : public sparse_vector_t {
 public:
  // constructores
  SparsePolynomial(const int n = 0) : sparse_vector_t(n) {};
  SparsePolynomial(const Polynomial& pol) : sparse_vector_t(pol) {};
  SparsePolynomial(const SparsePolynomial&);  // constructor de copia

  // destructor
  ~SparsePolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SparsePolynomial&, const double = EPS) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
};

// E/S
void Polynomial::Write(std::ostream& os, const double eps) const {
  os << get_size() << ": [ ";
  bool first{true};
  for (int i{0}; i < get_size(); i++)
    if (IsNotZero(at(i), eps)) {
      os << (!first ? " + " : "") << at(i)
	 << (i > 1 ? " x^" : (i == 1) ? " x" : "");
      if (i > 1)
	os << i;
      first = false;
    }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
  p.Write(os);
  return os;
}

// Operaciones con polinomios

// Evaluación de un polinomio representado por vector denso
double Polynomial::Eval(const double x) const {
  double result{0.0};
  for(int i = 0; i < get_size(); i++){
    result += at(i) * pow(x,i);
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por vectores densos
bool Polynomial::IsEqual(const Polynomial& pol, const double eps) const {
  bool differents = false;
  int mayor;
  if (get_size() - pol.get_size() < eps) {
    mayor = get_size();
    for(size_t i = get_size() + 1; i < pol.get_size(); i++){ // Compruebo que el resto del vector sean ceros
      if(pol.at(i) > eps)
        differents = true;
    }
  }
  else {
    mayor = pol.get_size();
    for(size_t i = pol.get_size() + 1; i < get_size(); i++){ // Compurebo que el resto del vector sean ceros
      if(at(i) > eps)
        differents = true;
    }
  }
  for (size_t i = 0; i < mayor; i++) {
      if ( fabs(get_val(i) - pol.get_val(i)) >= eps) {
        differents = true;
      }
  }
  return !differents;
}

int Polynomial::SumOfEvenDegrees() const{
  int result{0};
  for(int i = 0; i < get_size(); i++){
    if(at(i) > EPS && (i % 2) == 0){
      result += i;
    }
  }
  return result;
}

// constructor de copia
SparsePolynomial::SparsePolynomial(const SparsePolynomial& spol) {
  *this = spol;   // se invoca directamente al operator=
}

// E/S
void SparsePolynomial::Write(std::ostream& os) const {
  os << get_n() << "(" << get_nz() << "): [ ";
  bool first{true};
  for (int i{0}; i < get_nz(); i++) {
    int inx{at(i).get_inx()};
    os << (!first ? " + " : "") << at(i).get_val()
       << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SparsePolynomial& p) {
  p.Write(os);
  return os;
}

// Operaciones con polinomios

// Evaluación de un polinomio representado por vector disperso
double SparsePolynomial::Eval(const double x) const {
  double result{0.0};
  for(int i = 0; i < get_nz(); i++){
    pair_t aux = at(i);
    result += aux.get_val() * pow(x, aux.get_inx());
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por vectores dispersos
bool SparsePolynomial::IsEqual(const SparsePolynomial& spol, const double eps) const {
  bool equals = true;
  if(get_nz() == spol.get_nz()){
    for(int i = 0; i < get_nz(); i++){
      pair_t aux1 = at(i);
      pair_t aux2 = spol.at(i);
      if(!(aux1.get_inx() == aux2.get_inx() && fabs(aux1.get_val() -  aux2.get_val() < eps))){
        equals = false;
        break;
      }
    }
  }
  else{
    equals = false;
  }
  return equals;
}

// Comparación si son iguales dos polinomios representados por
// vector disperso y vector denso
bool SparsePolynomial::IsEqual(const Polynomial& pol, const double eps) const {
  bool differents = false;
    int mayor = 0;
  if((get_nz() - pol.get_size()) < 0){
    mayor = get_nz();
  }
  else{
    mayor = pol.get_size();
  }
  for(size_t i = 0; i < mayor; i++){
    if((at(i).get_val() - pol.at(at(i).get_inx())) >= eps){
      differents = true;
    }
  }
  return !differents;
}


#endif  // POLYNOMIAL_H_
