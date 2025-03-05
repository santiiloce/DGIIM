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
#include <fstream>
#include <bitset>
#include <string>
#include <stdlib.h>
#include <vector>

 class Generador_ca{
    private:
        size_t size_;
        int id_;
        std::vector<bool> output;
        std::vector<bool> init;
    public:
        Generador_ca(): id_(0), size_(1){};
        Generador_ca(int id, size_t size): id_(id), size_(size){};
        
        void StartInit(){
            for(int i = 0; i < size_; i++){
                init.push_back(1);
            }
        }

        void InsertElement(bool elemento, std::vector<bool> &cadena){
            std::vector<bool> aux = cadena;
            for(size_t i = 2; i < size_ ;i++){
                cadena.at(i) = aux.at(i - 1);
            }
            cadena.at(0) = elemento;
        }

        void FirstOperation(std::vector<bool> &first){
            std::vector<bool> aux = this->init;
            for(size_t i = 0; i < size_; i++){
                first.push_back(aux.at(aux.size() - 1));
                InsertElement(init.at(2) ^ init.at(9), aux);
            }
        }

        void SecondOperation(std::vector<bool> &second){
            std::vector<bool> aux = init;
            bool xor1, xor2, xor3, xor4, xor5, xor_end;
            for(size_t i = 0; i < size_; i++){
                xor1 = init.at(1) ^ init.at(2);
                xor2 = init.at(5) ^ init.at(7);
                xor3 = init.at(8) ^ init.at(9);
                xor4 = xor2 ^ xor3;
                xor5 = xor1 ^ xor4;
                InsertElement(xor5, aux);
                xor_end = init.at(1) ^ init.at(5);
                second.push_back(xor_end);
            }
        }

        void GeneratorCA(){
            std::cout << "1" << std::endl;
            std::vector<bool> first;
            std::vector<bool> second;
            std::cout << "2" << std::endl;
            FirstOperation(first);
            for(int i = 0; i < size_; i++)
                std::cout << first.at(i) << std::endl;
            std::cout << "3" << std::endl;
            SecondOperation(second);
            std::cout << "4" << std::endl;
            for(size_t i = 0; i < size_; i++){
                output.push_back(first.at(i) ^ second.at(i));
            }
        }

        std::string ToString(){
            std::string solution = "";
            for(int i = 0; i < size_; i++){
                solution.push_back(output.at(i) + '0');
            }
            return solution;
        }
 };

 int main(){
    int id;
    size_t lenght;
    std::cout << "ID del satelite: ";
    std::cin >> id;
    std::cout << "Longitud de la secuencia de salida: ";
    std::cin >> lenght;
    Generador_ca example(id, lenght);
    example.StartInit();
    example.GeneratorCA();
    std::cout << "Salida: " << example.ToString() << std::endl;
    return 0;
 }