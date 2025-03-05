/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Generador C/A usado en GPS
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */
#include <iostream>
#include <vector>
#include <string>

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
        bool operation;
        std::cout << " First Operation: " << "1111111111" << std::endl;
        for (size_t i = 0; i < size_; i++) {
            first.push_back(aux.back());
            if (aux.size() > 9) { 
                operation = aux[2] ^ aux[9];
                InsertElement(operation, aux);
                std::string cadena = "";
                for(int i = 0; i < aux.size(); i++){
                    cadena.push_back(aux.at(i) + '0');
                }
                std::cout << "First Operation: " << cadena << " real. : " << operation << std::endl;
            }
        }
    }

    void SecondOperation(std::vector<bool>& second) {
        std::cout << "Second Operation: " << "1111111111" << std::endl;
        std::vector<bool> aux = init;
        bool realimentacion;
        second.push_back(aux[2 - 1] ^ aux[6 - 1]);
        for (size_t i = 0; i < size_ - 1; i++) {
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
               i = rand() % 10 + 1;
               do{
                 j = rand() % 10 + 1;
               }while(i == j);
               second.push_back(aux[i - 1] ^ aux[j - 1]);
               second.push_back(aux[i - 1] ^ aux[j - 1]);
            }
         for(int i = 0; i < aux.size(); i++){
            cadena.push_back(aux.at(i) + '0');
        }   
        std::cout << "Second Operation: " << cadena << " real. :" << xor5 << std::endl;
        }
    }

    void GeneratorCA() {
        std::vector<bool> first, second;
        std::string aux = "";
        FirstOperation(first);
        for(int i = 0; i < first.size(); i++){
            aux.push_back(first.at(i) + '0');
        }
        //std::cout << "First Solution: " << aux << std::endl;
        aux = "";
        SecondOperation(second);
        for(int i = 0; i < second.size(); i++){
            aux.push_back(second.at(i) + '0');
        }
        //std::cout << "Second Solution: " << aux << std::endl;
        aux = "";

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
