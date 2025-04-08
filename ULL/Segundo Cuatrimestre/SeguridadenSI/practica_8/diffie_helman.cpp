
/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Encriptado de Diffie Helman
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */

  #include <iostream>
  #include <string>
  #include <bitset>
  #include <cmath>
  #include <unistd.h> 
  #include <stdlib.h>
  #include <cstdlib>
  
  std::bitset<8> DecimalToBinary(int num){
    std::bitset<8> binary_aux;
    int counter = 0;
    while( (num / 2 >= 1) ){
      binary_aux[counter] = (num % 2);
      num /= 2;
      counter++;
    }
    if(num == 1){
      binary_aux[counter] = 1;
    }
    if(binary_aux.size() < 8){
      int diference = 8 - binary_aux.size();
      for(int i = 0; i < diference; i++){
        binary_aux[counter] = 0;
      }
    }
    return binary_aux;
  }
  
  class DiffieHelman{
      private:
        int prime_;
        int base_;
        int secret_key_;
        int public_key_;
      public:
        DiffieHelman(): prime_(0), base_(0), secret_key_(0), public_key_(0){}
  
        DiffieHelman(int base, int secret_key, int prime): 
          prime_ (prime), 
          base_ (base), 
          secret_key_(secret_key),
          public_key_(ExponentiationFast(prime_, secret_key_, base_)) {}
  
        long long ExponentiationFast(int module, int exponent, int base){
          std::bitset<8> bin_exponent = DecimalToBinary(exponent);
          std::cout << std::endl << std::endl << "---------------------------------------------------------" << std::endl;
          std::cout << "bin exponent: " << bin_exponent <<std::endl;
          int x = 1;
          int index;
          for(int i{bin_exponent.size() - 1 }; i >= 0; --i){
            if(bin_exponent[i] == 1){
              index = i;
              break;
            }
          }
          for(int i{index}; i >= 0; --i){
            if(bin_exponent[i] == 0){
              std::cout << "i = " << i <<std::endl;
              std::cout << "bi = " << bin_exponent[i] << std::endl;
              std::cout << "x = " << x << std::endl;
              std::cout << "(x * x) % module = ";
              x = (x * x) % module;
              std::cout << x << std::endl;
            }
            else{
              std::cout << "i = " << i << std::endl;
              std::cout << "bi = " << bin_exponent[i] << std::endl;
              std::cout << "x = " << x << std::endl;
              std::cout << "(x * x * base) % module = ";
              x = (x * x * base) % module;
              std::cout << x << std::endl;
            }
          }
          std::cout << std::endl << std::endl << "---------------------------------------------------------" << std::endl;
          return x;
        }
  
        int GetPublicKey(){
          return public_key_;
        }
  
        int CheckPublicKey(int another_key){
          return ExponentiationFast(prime_, secret_key_, another_key);
        }
      };
        bool isPrime(int n) {
            if (n < 2) return false;
            if (n == 2 || n == 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;

            for (int i = 5; i * i <= n; i += 6) {
                if (n % i == 0 || n % (i + 2) == 0) {
                    return false;
                }
            }
            return true;
        }


  
  int main(){
      int prime_b, base_b, secret_key_Bob;
      std::cout << "Hi, Im Bob and this is the number prime and the base that I acorded with Alice:" << std::endl;
      std::cout << "number prime = ";
      std::cin >> prime_b;
      while(!isPrime(prime_b)){
        std::cin >> prime_b;
      }
      std::cout << "base = ";
      std::cin >> base_b;
      std::cout << "And now this is my secret key, but be caution...It is a secret ->";
      std::cin >> secret_key_Bob;
      DiffieHelman Bob(base_b, secret_key_Bob, prime_b);
      std::cout << "So this is my public key: " << Bob.GetPublicKey() << std::endl;
      std::string action;
      if(std::cin>>action)
        system("clear");
      int prime_a, base_a, secret_key_Alice;
      std::cout << "Hi, Im Alice and this is the number prime and the base that I acorded with Alice:" << std::endl;
      std::cout << "number prime = ";
      std::cin >> prime_a;
      while(prime_a != prime_b){
          std::cout << "No!! This is not the number prime that I accorded with Bob, try again: " << std::endl;
          std::cin >> prime_a;
      }
      std::cout << "base = ";
      std::cin >> base_a;
      while(base_a != base_b){
          std::cout << "No!! This is not the base that I accorded with Bob, try again: " << std::endl;
          std::cin >> base_a;
      }
      std::cout << "And now this is my secret key, but be caution...It is a secret ->";
      std::cin >> secret_key_Alice;
      DiffieHelman Alice(base_a, secret_key_Alice, prime_a);
      std::cout << "So this is my public key: " << Alice.GetPublicKey() << std::endl;
      if(std::cin>>action)
        system("clear");
      int resultBob = Bob.CheckPublicKey(Alice.GetPublicKey());
      int resultAlice = Alice.CheckPublicKey(Bob.GetPublicKey());
      std::cout << "Final message for Bob: " << resultBob << std::endl;
      std::cout << "Final message for Alice: " << resultAlice << std::endl;
      return 0;
  }
