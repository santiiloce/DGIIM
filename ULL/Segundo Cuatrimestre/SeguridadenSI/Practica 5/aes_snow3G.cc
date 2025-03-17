/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Encriptado de Snow3G & AES
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <sstream>

  std::string DecimalToBinary(int num){
  std::string binary_aux, binary;
  while( (num / 2 >= 1) ){
    binary_aux += std::to_string(num % 2);
    num /= 2;
  }
  if(num == 1){
    binary_aux += std::to_string(1);
  }
  if(binary_aux.size() < 8){
    int diference = 8 - binary_aux.size();
    for(int i = 0; i < diference; i++){
      binary_aux.push_back('0');
    }
  }
  for(int i = 0; i < binary_aux.size(); i++){
    binary.push_back(binary_aux.at(binary_aux.size() - 1 - i));
  }
  return binary;
}


std::string hexToBinary(const std::string& hex) {
    std::stringstream ss;
    ss << std::hex << hex;  // Convertir string hexadecimal a número
    unsigned int num;
    ss >> num;  // Almacenar el número en una variable

    std::bitset<8> bin(num);  // Convertir a binario (8 bits)
    
    return bin.to_string();  // Devolver la representación en binario
}

 enum class Encription{
    Snow3G,
    AES
  };

  class AES_3G{
    private:
      std::bitset<8> KSnow3g{"10101001"};
      std::bitset<8> kAes{"00011011"};
      size_t size_ = 8; // Tamanio de un byte

    public:
      void Module(std::bitset<8> &byte, const Encription choosen) const{
        // Selecciono la la clave apropiada
        std::bitset<8> key;
        switch(choosen){
          case Encription::Snow3G:
            key = KSnow3g;
            break;
          case Encription::AES:
            key = kAes;
            break;
        }
        std::bitset<8> aux = byte;
        // Realizo la operacion XOR entre la clave y el byte pasado por parametro
        for(int i{0}; i < size_; ++i){
          byte[i] = aux[i] ^ key[i];
        }
      }

      std::bitset<8> Multiplication(std::bitset<8>& byte1, std::bitset<8> byte2, const Encription choosen) const{
        std::bitset<8> sol{"00000000"};
        if(byte2.none()){
          return sol;
        }
        for(int i{0}; i < size_; ++i){
          bool carry = false;
          //std::cout << i << " byte[end]-> " << byte1[size_ - 1] << std::endl;
          if(byte1[size_ - 1]){
            carry = true;
          }
          if(byte2[i]){
            for(int i{0}; i < size_; ++i){
              sol[i] = byte1[i] ^ sol[i];
            }
            //std::cout << "State solution: " << sol.to_string() << std::endl;
          }
          byte1 <<= 1;
          //std::cout << "After carry " << i << " :" << byte1.to_string() << std::endl;
          if(carry){
            Module(byte1, choosen);
            //std::cout << "After module " << i << " :" << byte1.to_string() << std::endl;
          }
        }
        return sol;
      }
  };

int main(){
   std::ifstream file("data.txt");
   //Compruebo si se ha abierto correctamente
   if(!file.is_open()){
    std::cerr << "Error to open the file" << std::endl;
    return 1;
   }
   //Lectura de 
   std::string aux1, aux2;
   file >> aux1 >> aux2;
   std::cout << "First number: " << aux1 << std::endl;
   std::cout << "Second number: " << aux2 << std::endl;
   std::bitset<8> byte1{hexToBinary(aux1)};
   std::cout <<"First byte: "<< byte1.to_string() <<std::endl;
   std::bitset<8> byte2{hexToBinary(aux2)};
   std::cout <<"Second byte: "<< byte2.to_string() <<std::endl;
   int option;
   std::cout << "Choose one method to encrypt: SNOW 3G(0) / AES(1): ";
   std::cin >> option;
   if(!(option == 1 or option == 0)){
    std::cerr << "Invalid option have been choosen" << std::endl;
    return 1;
   }
   Encription choosen;
   if(option)
    choosen = Encription::AES;
   else
    choosen = Encription::Snow3G;
   
   AES_3G solution;
   std::cout << "Multiplication: " << solution.Multiplication(byte1, byte2, choosen).to_string() << std::endl;
   return 0;
  }
