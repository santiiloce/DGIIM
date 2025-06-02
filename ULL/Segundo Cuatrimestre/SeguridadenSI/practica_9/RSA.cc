#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <bitset>
#include <string>
#include <iomanip>
#include <cassert>
#include <cctype>
#include <unistd.h>
#include <limits>
#include <limits>

std::bitset<8> DecimalToBinary(int num) {
    std::bitset<8> binary;
    
    // Manejo de caso especial
    if (num == 0) return binary; // Ya está inicializado con ceros
    
    // Convertir a binario correctamente
    int pos = 0;
    while (num > 0 && pos < 8) {
        binary[pos] = (num % 2);
        num /= 2;
        pos++;
    }
    
    return binary;
}

int TextoToDecimal(std::string texto){
  int result = 0;
  for(int i{0}; i < texto.size(); i++){
    texto.at(i) = tolower(texto.at(i));
    int coeficiente = texto.at(i) - 'a';
    result += coeficiente * pow(26,texto.size() - 1 - i);
  }
  return result;
}

std::string filtrarAlfabeticos(const std::string& entrada) {
    std::string resultado;
    
    for (char c : entrada) {
        // Verificar si es una letra entre a-z, A-Z o ñ/Ñ
        if ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            c == 165 || c == 241) {
            resultado += c;
        }
    }
    
    return resultado;
}

class RSA{
  private:
    int n;
    int p;
    int q;
    int phi;
    int d;
    int e; 
    int valoresLH[5] = {2,3,5,7,11};
  public:
    RSA():n(0), p(0),q(0), phi(0), d(0),e(0){};
    RSA(int p_value, int q_value, int d_value):
       p(p_value),
       q(q_value),
       d(d_value)
       {
        n = p * q;
        phi = (p - 1) * (q - 1);
        std::pair<int,int> mcd = MCD(d, phi);
        if(mcd.first == 1){
          e = mcd.second;
        }
        else{
          e = -1;
        }
       }
    
    void SetP(int p_value){
      p = p_value;
    }

    int GetPhi(){
      return phi;
    }

    int GetE(){
      return e;
    }

    int GetN(){
      return n;
    }

    bool TestPrimalidad(int p){
        for(int value: valoresLH){
            if(p % value == 0){
                return false;
                break;
            }
        }
        std::srand(std::time(nullptr));  // Inicializar semilla aleatoria
        int hayMenosUno = 0;

        // Paso 2 y 3: probar 40 valores aleatorios de a
        for (int i = 0; i < 40; ++i) {
            int a = std::rand() % (p - 3) + 2;  // a pertenece [2, p - 2]
            int exp = (p - 1) / 2;
            int resultado = ExponentiationFast(a, exp, p);

            if (resultado != 1 && resultado != p - 1)
                return false;  // p es compuesto

            if (resultado == p - 1)
                hayMenosUno++;
        }

        // Si todos los resultados fueron 1, entonces p es compuesto
        if (hayMenosUno == 40)
            return false;

        return true;  // p tal vez es primo
  }


static std::pair<int, int> MCD(int a, int m) {
    // Aseguramos que a sea positivo inicialmente
    a = ((a % m) + m) % m;
    
    long long r1 = m, r2 = a; // 
    long long t1 = 0, t2 = 1;
    
    while (r2 > 0) {
        long long q = r1 / r2;
        long long temp_r = r1 - q * r2; // resto
        r1 = r2;
        r2 = temp_r;
        
        long long temp_t = t1 - q * t2;
        t1 = t2;
        t2 = temp_t;
    }
    
    // Si r1 > 1, entonces a no tiene inverso modular
    if (r1 > 1) {
        return {r1, -1};
    }
    
    // Aseguramos que el resultado sea positivo
    if (t1 < 0) {
        t1 += m;
    }
    
    return {1, static_cast<int>(t1)};
}

    static bool EsPrimoRelativo(int a, int b){
      std::pair<int,int> sol = MCD(a,b);
      int mcd = sol.first;
      return ((mcd == 1) ? true: false);
    }

long long ExponentiationFast(long long base, long long exponente, long long modulo) {
    // Caso base
    if (modulo == 1) return 0;
    
    // Inicialización
    long long resultado = 1;
    base = base % modulo;  // Reducir la base módulo m
    
    // Mientras el exponente sea mayor que 0
    while (exponente > 0) {
        // Si el bit menos significativo del exponente es 1
        if (exponente & 1) {
            resultado = (resultado * base) % modulo;
        }
        
        // Desplazar a la derecha el exponente (dividir por 2)
        exponente >>= 1;
        
        // Elevar la base al cuadrado
        base = (base * base) % modulo;
    }
    
    return resultado;
}

    int TamanioBloques(){
      int i = 1;
      int tamanio;
      bool encontrado = false;
      while(!encontrado){
        long long extremo_inferior = pow(26,i-1);
        long long extremo_superior = pow(26,i);
        //std::cout << "Extremos " << extremo_inferior << " " << n << " " << extremo_superior << std::endl;
        if(extremo_inferior< n && n < extremo_superior){
          return (i-1);
        }
        else
          i++;
      }
      return tamanio;
    }

};

int main(){
    int p, q, d;
    std::string cadena, cadena_sin_filtrar;
    RSA prev;
    std::cout << "Introduzca los parámetros: " << std::endl;
    std::cout << "p: ";
    std::cin >> p;
    std::cout << "q: ";
    std::cin >> q;
    if(!prev.TestPrimalidad(p) && !prev.TestPrimalidad(q)){
      std::cerr << "p y q no son primos" << std::endl;
      return 1;
    }
    else{
      std::cout << "p y q son primos" << std::endl;
    }
    std::cout << "d: ";
    std::cin >> d;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    RSA rsa(p,q,d);
    if(rsa.EsPrimoRelativo(d,rsa.GetPhi())){
      std::cout << "d y phi(n) son primos relativos" << std::endl;
    }
    else{
      std::cerr << "d y phi(n) no son primos relativos" << std::endl;
    }
    std::cout << "Texto Original: " ;
    std::getline(std::cin, cadena_sin_filtrar);
    cadena = filtrarAlfabeticos(cadena_sin_filtrar);

    int bloques = rsa.TamanioBloques();
    int i = 0;
    while(i < cadena.size()){
      std::string aux;
      int size = i + bloques;
      while(i < size){
        if((i + 1) >= cadena.size()){
          aux.push_back(cadena.at(i));
          i++;
          for(int j{i}; j < size; ++j){
            aux.push_back('X');
          }
        }
        else
          aux.push_back(cadena.at(i));
        i++;
      }
      int bloque_convertido = TextoToDecimal(aux);
      std::cout << "Bloque a decimal " << aux << " : " << bloque_convertido << std::endl;
      long long cifrado = rsa.ExponentiationFast(bloque_convertido,rsa.GetE(), rsa.GetN());
      std::cout << "Texto cifrado: " << cifrado << std::endl << std::endl;
    }

   return 0;

}