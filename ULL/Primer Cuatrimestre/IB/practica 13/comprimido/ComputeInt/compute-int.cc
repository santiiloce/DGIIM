/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @brief Clase que permite realizar diferentes cálculos con numeros enteros
 * The program takes directly the input and prints the output
 */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class ComputeInt{
public:
/**
 * @brief Calcula el factorial de un numero
 * 
 * @param num numero a calcular el factorial
 * @return double resultado
 */
    double Factorial(double num){
        int n = static_cast<int>(num);
        int factorial = 1;
        for (int i = 1; i <= n; i++){
            factorial *= i;
        }
        return factorial;
    }

    /**
     * @brief Calcula la suma de los primeros n términos de la serie 
     * 
     * @param num numero maximo del que calcular la serie
     * @return int suma de la serie
     */
    int SumSerie(double num){
        int n = static_cast<int>(num);
        int sum = 0;
        for(int i = 1; i <= n; i++){
            sum += i;
        }
        return sum;
    }

    /**
     * @brief Determina si un numero es primo
     * 
     * @param n 
     * @return true 
     * @return false 
     */
    bool IsPrime(int n){
            std::vector<int> primos;

            for(int i = 2; i <= n; i++){
                primos.push_back(i);
            }
            bool es_primo = true;
            bool fin = false;
            int contador = 0;
            while(es_primo || !fin ){
                while(primos.at(contador) == -1 && (contador < primos.size())){ //Evito seleccionar numeros marcados como no primos
                    contador++;
                }
                int nuevo_primo = primos.at(contador);
                for(int i = contador + 1; i < primos.size(); i++){
                    if(primos.at(i) % nuevo_primo == 0){
                        if (primos.at(i) == n){
                            es_primo = false;
                            break;
                        }
                        else{
                            primos.at(i) = -1;
                        }
                    }
                }

                if(nuevo_primo * nuevo_primo >= n){
                    break;
                }
                contador++;
    }
    if (n > 1)
        return es_primo;
    else   
        return true;
}

    /**
     * @brief Determina si un numero es un primo perfecto
     * 
     * @param n 
     * @return true 
     * @return false 
     */
    bool IsPerfectPrime(int n){
        bool perfect = true;
        std::string num = std::to_string(n);
        while(perfect && num.size() != 1){
            int suma = 0;
            for(int i = 0; i < num.size(); i++){
                suma += num.at(i) - '0';
            }
            if(!IsPrime(suma)){
                perfect = false;
            }
            num = std::to_string(suma);
        }
        if(std::stoi(num) > 1)
            return IsPrime(std::stoi(num));
        else 
            return false;
    }

    /**
     * @brief Calcula el mcd de dos numeros dados
     * 
     * @param a numero 1
     * @param b numero 2
     * @return int mcd de los dos numeros dados
     */
    int gcd(int a, int b){
        if ( a < 0 || b < 0 || (a == 0 && b== 0))
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
     * @brief Determina si dos números son mutuamente primos
     * 
     * @param num1 primer numero
     * @param num2 segundo numero
     * @return true 
     * @return false 
     */
    bool AreRelativePrimes(int num1, int num2){
        return (gcd(num1, num2) == 1);
    }

};


int main(int argc, char* argv[]) {
  if(argc != 3){
    std::cerr << "./compute-int.cc num1 num2" << std::endl;
  }
  ComputeInt compute_integer; 
  double num1 = std::stoi(argv[1]);
  double num2 = std::stoi(argv[2]);
  std::cout << compute_integer.Factorial(num1) << std::endl; 
  std::cout << compute_integer.SumSerie(num1) << std::endl; 
  if(compute_integer.IsPrime(num1)){
    std::cout << "Es primo" << std::endl;
  }
  else{
    std::cout << "No es primo" << std::endl;
  }
  if(compute_integer.AreRelativePrimes(num1, num2)){
    std::cout << "Son primos relativos" << std::endl;
  }
  else{
    std::cout << "No son primos relativos" << std::endl;
  }
  return 0;
}