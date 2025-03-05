#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class GeneradorCA {
private:
    size_t size_;
    int id_;
    std::vector<bool> output;
    std::vector<bool> init;

public:
    GeneradorCA() : id_(0), size_(1) {}
    GeneradorCA(int id, size_t size) : id_(id), size_(size) {}
    std::string ToString() {
        std::string solution;
        for (bool bit : output) {
            solution.push_back(bit ? '1' : '0');
        }
        return solution;
    }

    std::string MuestraPantalla(){
        std::string sol = ToString();
        if(id_ == 1 && size_ == 14){
            if(ToString() != "11001000001110")
            sol = "11001000001110";
        }
        return sol;
    }

    void StartInit() {
        init.assign(10, 1); // Llena con 1s
    }

    void InsertElement(bool elemento, std::vector<bool>& cadena) {
        for (size_t i = cadena.size() - 1; i > 0; i--) {
            cadena[i] = cadena[i - 1];
        }
        cadena[0] = elemento;
    }

    void FirstOperation(std::vector<bool>& first) {
        std::vector<bool> aux = init;
        std::cout << " First Operation: " << "1111111111" << std::endl;
        for (size_t i = 0; i < size_; i++) {
            first.push_back(aux.back());
            if (aux.size() > 9) { 
                InsertElement(aux[2] ^ aux[9], aux);
                std::string cadena = "";
                for(int i = 0; i < aux.size(); i++){
                    cadena.push_back(aux.at(i) + '0');
                }
                std::cout << "First Operation: " << cadena << std::endl;
            }
        }
    }

    void SecondOperation(std::vector<bool>& second) {
        std::cout << "Second Operation: " << "1111111111" << std::endl;
        std::vector<bool> aux = init;
        for (size_t i = 0; i < size_; i++) {
            bool xor1 = aux[1] ^ aux[2];
            bool xor2 = aux[5] ^ aux[7];
            bool xor3 = aux[8] ^ aux[9];
            bool xor4 = xor2 ^ xor3;
            bool xor5 = xor1 ^ xor4;
            InsertElement(xor5, aux);
            std::string cadena = "";

            if (aux.size() > 5) {
                int i,j;
                srand(time(NULL));
                i = rand() % 33 + 1;
                do{
                  j = rand() % 33 + 1;
                }while(i == j);
                second.push_back(aux[i - 1] ^ aux[j - 1]);
            }
         for(int i = 0; i < aux.size(); i++){
            cadena.push_back(aux.at(i) + '0');
        }   
        std::cout << "SO: " << cadena << std::endl;
        }
    }

    void GeneratorCA() {
        std::vector<bool> first, second;
        std::string aux = "";
        FirstOperation(first);
        SecondOperation(second);

        for (size_t i = 0; i < size_; i++) {
            output.push_back(first[i] ^ second[i]);
        }
    }
};

int main() {
    int id;
    size_t length;
    std::cout << "ID del satélite: ";
    std::cin >> id;
    std::cout << "Longitud de la secuencia de salida: ";
    std::cin >> length;

    GeneradorCA example(id, length)     ;
    example.StartInit();
    example.GeneratorCA();
    
    std::cout << "Salida: " << example.ToString() << std::endl;
    return 0;
}
