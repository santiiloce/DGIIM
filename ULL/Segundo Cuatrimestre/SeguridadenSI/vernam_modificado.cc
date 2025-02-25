/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Encriptado de Vernam
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */
 #include <iostream>
 #include <fstream>
 #include <string> 
 #include <sstream>
 #include <cctype>
 #include <vector>
 #include <cmath>


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

int BinaryToDecimal(std::string binary){
  int num = 0;
  for(int i = binary.size() - 1; i >= 0; i--){
    int bit = (binary.at(i) - '0');
    num += bit * pow(2, binary.size() - 1 - i );
  }
  return num;
}

std::string TextToBinary(std::string word){
  std::string binary;
  for(char value: word) {
    int num = value;
    binary += DecimalToBinary(num);
  }
  return binary;
}

std::string BinaryToText(std::string binary){
  std::string word = "";
  std::string binary_aux = "";
  if(binary.size() % 8 != 0){   // Me aseguro que la palabra este compuesta por caracteres
    int size = 8 - (binary.size() % 8);
    for(int i = 0; i < size; i++){
      binary_aux.push_back('0');
    }
    for(int i = 0; i < binary.size(); i++){
      binary_aux.push_back(binary.at(i));
    }
  }
  else{
    binary_aux = binary;
  }
  int counter = binary_aux.size() - 1;
  std::string letra = "";
  for(int i = 0; i < binary_aux.size(); i++){
    letra.push_back(binary_aux.at(i));
    if(letra.size() == 8){
      char value = static_cast<char>(BinaryToDecimal(letra));
      // Compruebo que sea un caracter imprimible
      if(value < 32 || value > 126){
        std::cout << value << " es un caracter ASCII no imprimible." << std::endl;
        value = 'a';
      }
      word.push_back(value);
      letra = "";
    }
  }
  return word;
}

std::string processKey(const std::string& key) {
    std::string processed_key = key;
    for (char& c : processed_key) {
        c = c ^ 128;  
    }
    return processed_key;
}

//Como es el mismo proceso para encriptar como desencriptar solo defino una funcion
 std::string EncryptXOR(std::string cadena, std::string key){
    //std::string processed_key = processKey(key);
    size_t key_length = key.size();
    std::string encript = "";

    for(int i = 0; i < cadena.size(); i++){
      int aux = ((cadena.at(i) - '0') + (key.at(i % key_length) - '0')) % 2;
      encript += std::to_string(aux);
    }

    return encript;
}

bool IsBinary(std::string key){
    for(int i = 0; i < key.size(); i++){
        if(key.at(i) != 0  && key.at(i) != 1){
            return false;
        }
    }
    return true;
}

std::string GenerateKey(){
    srand (time(NULL));
    std::string key = "";
    int size = pow(2,7);
    for(int i = 0; i < size; i++){
     int num = rand() % 2; 
     key.push_back(num + '0');
    }
    return key;
}


 int main( int argc, char* argv[]){
  std::cout << "Encriptar / Desencriptar (0/1)" << std::endl;
  int option;
  std::cin >> option;
  if(option != 0 && option != 1){
    std::cerr << "Opcion no admitida. Ha de ser 0 o 1." << std::endl;
    return 0;
  }
  std::string mensaje_original, original_binario, cifrado, cifrado_binario, clave;
  if(option == 0){
    std::cout << "Mensaje original: ";
    std::cin >> mensaje_original;
    original_binario = TextToBinary(mensaje_original);
    std::cout << "Mensaje original en binario: " << original_binario << std::endl;
    std::cout << "Longitud del mensaje binario: " << original_binario.size() << std::endl;
    std::cout << "Clave aleatoria: ";
    std::cout << "Manual o aleatoria 0/1: ";
    std::cin >> option;
    if(option == 0)
      std::cin >> clave;
    else
      clave = GenerateKey();
    cifrado_binario= EncryptXOR(original_binario, clave);
    cifrado = BinaryToText(cifrado_binario);
    std::cout << "Mensaje cifrado en binario: " << cifrado_binario << std::endl;
    std::cout << "Mensaje cifrado: " << cifrado << std::endl;
  }
  else{
    std::cout << "Mensaje cifrado: " << std::endl;
    std::cin >> cifrado;
    cifrado_binario = TextToBinary(cifrado);
    std::cout << "Mensaje cifrado en binario: " << cifrado_binario << std::endl;
    std::cout << "Longitud del mensaje binario: " << cifrado_binario.size() << std::endl;
    std::cout << "Clave aleatoria: ";
    std::cout << "Manual o aleatoria 0/1: ";
    std::cin >> option;
    if(option == 0)
      std::cin >> clave;
    else
      clave = GenerateKey();
    original_binario = EncryptXOR(cifrado_binario,clave);
    mensaje_original = BinaryToText(original_binario);
    std::cout << "Mensaje original en binario: " << original_binario << std::endl;
    std::cout << "Mensaje original: " << mensaje_original << std::endl;
  }
  return 0;
 }