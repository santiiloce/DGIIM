#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>

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

    bool TestPrimalidad(){
        bool esprimo = true;
        for(int value: valoresLH){
            if(p % value == 0){
                esprimo = false;
                break;
            }
        }
        std::srand(std::time({}));
        int a;
        int size = (p - 1) / 2;
        for(int i{1}; i <= 40; ++i){
          a = rand() % (p - 1) + 2; 
          if(abs(pow(a, size)) % p == 1){
            esprimo = true;
            break;
          }
        }
        return esprimo;
    }

    // Implementación del algoritmo de Euclides
    static int MCD(int a, int b){
      std::vector<int>  x, z;
      int resto, i = 2;
      z.push_back(0);
      z.push_back(1);
      x.push_back(-1);
      x.push_back(a);
      x.push_back(b);   
      do{
        resto = x.at(i-1) % x.at(i);
        x.push_back(resto);
        int new_z = -(x.at(i-1) / x.at(i))*z.at(i-1) + z.at(i-2);
        z.push_back(new_z % a);
        i++;
      }while(resto != 0);
      return x.at(i-1);
    }

    static bool EsPrimoRelativo(int a, int b){
      int mcd = MCD(a,b);
      return ((mcd == 1) ? true: false);
    }

};

int main(){
    /*
    int p, q, d;
    std::cout << "Introduzca los parámetros: " << std::endl;
    std::cout << "p: ";
    std::cin >> p;
    std::cout << "q: ";
    std::cin >> q;
    std::cout << "d :";
    std::cin >> q; 
    */
   RSA a;
   std::cout << a.MCD(16,32) << std::endl;
   return 0;

}