// AUTOR: Santiago López Cerro 
// FECHA: 12/02/2025
// EMAIL: alU0101763613@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 1
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html

// pauta de estilo [92]: comentarios multilínea usando solo "//"

#pragma once

#include <iostream>
#include <cassert>
#include <cmath>

# define EPSILON 1e-6

using namespace std;

class rational_t
{
public:
  // Constructor
  rational_t(const int = 0, const int = 1);
  // Destructor
  ~rational_t() {}
  
  // Getter del numerador
  int get_num() const;
  // Getter del denominador
  int get_den() const;
  
  // Setter del numerador
  void set_num(const int);
  // Setter del denominador
  void set_den(const int);

  double value(void) const;

  // FASE II

  bool is_equal(const rational_t&, const double precision = EPSILON) const;
  bool is_greater(const rational_t&, const double precision = EPSILON) const;
  bool is_less(const rational_t&, const double precision = EPSILON) const;
  
  // FASE III
  rational_t add(const rational_t&);
  rational_t substract(const rational_t&);
  rational_t multiply(const rational_t&);
    rational_t divide(const rational_t&);
  
  // Metodo de escritura a pantalla
  void write(ostream& = cout) const;
  // Metodo de lectura desde teclado
  void read(istream& = cin);

  rational_t inverso();
  static rational_t inverso(rational_t numero);
  
  rational_t operator - (const rational_t &r) const;
  rational_t operator + (const rational_t &r) const ;

  void operator = (const rational_t &r);
private:
  // pauta de estilo [11]: nombre de los atributos seguido de "_"
  int num_, den_;
  int mcd(int a, int b);
  int mcm(int num1, int num2);
  int mcd(int a, int b) const;
  int mcm(int num1, int num2) const;
  void simplifica();
};
