/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @brief Programa que calcula si un numero es primo eperfecto
 * The program takes directly the input and prints the output
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

bool EsPrimo(int n){
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
    return es_primo;
}

bool EsPrimoPerfecto(int n){
    bool perfect = true;
    std::string num = std::to_string(n);
    while(perfect && num.size() != 1){
        int suma = 0;
        for(int i = 0; i < num.size(); i++){
            suma += num.at(i) - '0';
        }
        if(!EsPrimo(suma)){
            perfect = false;
        }

        num = std::to_string(suma);
    }
    if(std::stoi(num) > 1)
        return EsPrimo(std::stoi(num));
    else 
        return false;
}

int main(){
    int num;
    while(std::cin >> num){
        if(num == 0){
            break;
        }
        if(EsPrimoPerfecto(num)){
            std::cout << "yes" << std::endl;
        }
        else{
            std::cout << "no"  << std::endl;
        }      
    }
    return 0;
}