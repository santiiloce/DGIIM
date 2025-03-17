// AUTOR: Santiago López Cerro 
// FECHA: 12/02/2025
// EMAIL: alu0101763613@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 1
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html

// pauta de estilo [92]: comentarios multilínea usando solo "//"

#include "rational_t.hpp"

/**
 * @brief Metodo privado para calcular el maximo comun divisor entre dos numeros
 * 
 * @param a primer numero
 * @param b segundo numero
 * @return int mcd de ambos numeros
 */
int rational_t::mcd(int a, int b){
  if ( a < 0 || b < 0 || (a == 0 && b == 0))
    return -1;
  if (b > a){
        int aux = a;
        a = b;
        b = aux;
  }
  if (b == 0) // Excepcion del cero
        return a;
  int diferencia = a % b;
  while(diferencia != 0){
        a = b;
        b = diferencia;
    diferencia = a % b;
  }
  return b;
}

/**
 * @brief Metodo para calcular el minimo comun multiplo entre dos numeros
 * 
 * @param num1 primer numero
 * @param num2 segundo numero
 * @return int mcm de ambos numeros
 */
int rational_t::mcm(int const num1, int const num2){
  long int mcm;
  if (mcd(num1,num2) == 1)
    mcm = num1*num2;    // Si su mcd == 1 entoces su mcd sera su producto
  else
    mcm = (num1/mcd(num1,num2))*num2;
  return mcm;
}

// Maximo comun divisor sin ser funcion de tipo constante
int rational_t::mcd(int a, int b) const{
  if ( a < 0 || b < 0 || (a == 0 && b == 0))
    return -1;
  if (b > a){
        int aux = a;
        a = b;
        b = aux;
  }
  if (b == 0) // Excepcion del cero
        return a;
  int diferencia = a % b;
  while(diferencia != 0){
        a = b;
        b = diferencia;
    diferencia = a % b;
  }
  return b;
}

// Minimo comun multiplo sin ser de tipo constante
int rational_t::mcm(int const num1, int const num2) const{
  long int mcm;
  if (mcd(num1,num2) == 1)
    mcm = num1*num2;    // Si su mcd == 1 entoces su mcd sera su producto
  else
    mcm = (num1/mcd(num1,num2))*num2;
  return mcm;
}

// Dado dos numeros halla su version simplificada
void rational_t::simplifica(){
  int aux = mcd(den_, num_);
  num_ /= aux;
  den_ /= aux;
}

/**
 * @brief SObrecarga del operador -
 * 
 * @param r operador de la resta
 * @return rational_t resultado de la resta
 */
rational_t rational_t::operator - (const rational_t &r) const{
  rational_t sol;
  sol.set_den(mcm(den_, r.den_));
  sol.set_num(num_ * (sol.get_den() / den_) - r.get_num() * (sol.get_den() / r.get_den()));
  sol.simplifica();
  return sol;
}

/**
 * @brief Sobrecarga del operador +
 * 
 * @param r operador de la suma
 * @return rational_t resultado de la suma
 */
rational_t rational_t::operator + (const rational_t &r) const{
  rational_t sol;
  sol.set_den(mcm(den_, r.den_));
  sol.set_num(num_ * (sol.get_den() / den_) + r.get_num() * (sol.get_den() / r.get_den()));
  sol.simplifica();
  return sol;
}

/**
 * @brief Sobrecarga del operador asignación
 * 
 * @param r rational_r de copia
 */
void rational_t::operator = (const rational_t &r){
  den_ = r.get_den();
  num_ = r.get_num();
}

/**
 * @brief Construct a new rational t::rational t object
 * 
 * @param n numerador
 * @param d denominador
 */
rational_t::rational_t(const int n, const int d)
{
  assert(d != 0);
  num_ = n, den_ = d;
}

/**
 * @brief Getter del numerador
 * 
 * @return int numerador
 */
int rational_t::get_num() const
{
  return num_;
}

/**
 * @brief Getter del denominador
 * 
 * @return int denominador
 */
int rational_t::get_den() const
{
  return den_;
}

/**
 * @brief Setter del numerador
 * 
 * @param n valor nuevo
 */
void rational_t::set_num(const int n)
{
  num_ = n;
}


/**
 * @brief Setter del denominador
 * 
 * @param d nuevo valor
 */
void rational_t::set_den(const int d)
{
  assert(d != 0);
  den_ = d;
}


/**
 * @brief Division entre numerador y denominador
 * 
 * @return double 
 */
double rational_t::value() const
{ 
  return double(get_num()) / get_den();
}


/**
 * @brief Comprueba si dos numeros son iguales
 * 
 * @param r numero a comparar
 * @param precision cota limite
 * @return true 
 * @return false 
 */
bool rational_t::is_equal(const rational_t& r, const double precision) const
{ 
  rational_t aux = *this - r;
  double division = static_cast<double>(aux.get_num()) / static_cast<double>(aux.get_den());
  if(fabs(division) < precision){
    return true;
  }
  return false;
}


/**
 * @brief Comprueba si es mayor que otro valor dado
 * 
 * @param r numero a comparar
 * @param precision cota de comparacion
 * @return true 
 * @return false 
 */
bool rational_t::is_greater(const rational_t& r, const double precision) const
{
  rational_t aux = *this - r;
  double division = static_cast<double>(aux.get_num()) / static_cast<double>(aux.get_den());
  if(division > precision){
    return true;
  }
  return false;
}

/**
 * @brief Comprueba si es menor que otro numero
 * 
 * @param r Otro numero
 * @param precision cota limite para la comparacion
 * @return true 
 * @return false 
 */
bool rational_t::is_less(const rational_t& r, const double precision) const
{
  rational_t aux = r - *this;
  double division = static_cast<double>(aux.get_num()) / static_cast<double>(aux.get_den());
  if(division > precision){
    return true;
  }
  return false;
}


// operaciones
// Metodo para la operacion suma
rational_t rational_t::add(const rational_t& r)
{
  rational_t sol = *this + r;
  return sol;
}


// Metodo para operacion resta
rational_t rational_t::substract(const rational_t& r)
{
  rational_t sol = *this - r;
  return sol;
}


// Metodo para la operacion multiplicacion
rational_t rational_t::multiply(const rational_t& r)
{
  rational_t sol;
  sol.set_num(num_ * r.get_num());
  sol.set_den(den_ * r.get_den());
  sol.simplifica();
  return sol;
}


// Metodo para la operacion division
rational_t rational_t::divide(const rational_t& r)
{
  rational_t aux, sol;
  aux.num_ = r.den_;
  aux.den_ = r.num_;
  sol = multiply(aux);
  return sol;
}



// E/S
// Metodo de escritura 
void rational_t::write(ostream& os) const
{
  os << get_num() << "/" << get_den() << "=" << value() << endl;
}


// Metodo de lectura
void rational_t::read(istream& is)
{
  cout << "Numerador? ";
  is >> num_;
  cout << "Denominador? ";
  is >> den_;
  assert(den_ != 0);
}

/**
 * @brief Calcula inverso a la propia instancia de la clase
 * 
 * @return rational_t 
 */
rational_t rational_t::inverso(){
  rational_t aux;
  aux.den_ = num_;
  aux.num_ = den_;
  return aux;
}

/**
 * @brief Calcula inverso a cualquier isntancia de la clase
 * 
 * @param numero 
 * @return rational_t 
 */
rational_t rational_t::inverso(rational_t numero){
  rational_t aux;
  aux.den_ = numero.num_;
  aux.num_ = numero.den_;
  return aux;
}
