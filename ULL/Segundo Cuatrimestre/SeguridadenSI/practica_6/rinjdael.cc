/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Implementation AES 
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */


#include "rinjdael.h"

AES::AES(){
    key_(4,4);
    text_(4,4);
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 4; j++){
            key_.at(i,j) = "00";
            text_.at(i,j) = "00";
        }
    }
    std::ifstream file("KMatrixMixColumn");
    std::string aux;
    while(file >> aux){
        kMatrixMixColumn.read(file);
    }
    file.close();
    std::ifstream file2("kSBolx.txt");
    while(file2 >> aux){
        kMatrixMixColumn.read(file2);
    }
    file2.close();
}

AES::AES(matrix_t<std::string> key, matrix_t<std::string> text){
    assert(key.get_m() == key.get_n());
    assert(text.get_n() == text.get_m());
    assert(text.get_m() == key.get_n());
    size_t rows = key.get_m();
    size_t cols = key.get_n();
    key_ = key;
    text_ = text;
    for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= cols; j++){
            key_.at(i,j) = key.at(i,j);
            text_.at(i,j) = text.at(i,j);
        }
    }
    std::ifstream file("KMatrixMixColumn");
    std::string aux;
    while(file >> aux){
        kMatrixMixColumn.read(file);
    }
    file.close();
    std::ifstream file2("kSBolx.txt");
    while(file2 >> aux){
        kMatrixMixColumn.read(file2);
    }
    file2.close();
}

std::bitset<8> AES::StringHexToBinary(const std::string& hex) {
    std::stringstream ss;
    ss << std::hex << hex;  // Convertir string hexadecimal a número
    unsigned int num;
    ss >> num;  // Almacenar el número en una variable

    std::bitset<8> bin(num);  // Convertir a binario (8 bits)
    
    return bin;  // Devolver la representación en binario
}

std::string AES::DecimalToHex(int num) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << num; // Convertimos a hexadecimal en mayúsculas
    return ss.str();
}

std::string AES::BinaryToStringHex(std::bitset<8> &binary){
    std::string solution;
    unsigned long number_sol = binary.to_ulong();
    std::stringstream ss;
    ss << std::hex << number_sol;
    ss >> solution;
    return solution;
}

int AES::CharHexToDecimal(const char& hex){
    std::stringstream ss;
    ss << std::hex << hex;  // Convertir string hexadecimal a número
    int num;
    ss >> num;  // Almacenar el número en una variable
    return num;
}

int AES::StringHexToDecimal(const std::string& hex){
  std::bitset<8> value = StringHexToBinary(hex);
  return value.to_ulong();
}

void AES::InitializeSol() {
    size_t sol_size = key_.get_m();
    solution_.resize(sol_size, sol_size); // Asegúrate de que esté dimensionada
    for (int i = 1; i <= sol_size; i++) {
        for (int j = 1; j <= sol_size; j++) {
            solution_.at(i, j) = "00";
        }
    }
}

//PRE: sol size have to be the same as key and text
void AES::AddRoundKey(matrix_t<std::string> &sol, matrix_t<std::string> key, matrix_t<std::string> &text){
  for(int i = 1; i <= key.get_m(); i++){
    for(int j = 1; j <= text_.get_n(); j++){
        std::bitset<8> aux;
        aux = StringHexToBinary(key.at(i,j)) ^ StringHexToBinary(text.at(i,j));
        sol.at(i,j) = aux.to_string();
    }
  }  
}

void AES::SubBytes(matrix_t<std::string> &data){
  for(int i = 1; i <= data.get_m(); ++i){
    for(int j = 1; j <= data.get_n(); ++j){
        int row = CharHexToDecimal(data.at(i,j).at(0));
        int col = CharHexToDecimal(data.at(i,j).at(1));
        data.at(i,j) = kSBox.at(row, col);
    }
  }
}

void AES::ShiftRows(matrix_t<std::string> &data){
  matrix_t<std::string> aux;
  for(int i = 1; i <= data.get_m(); i++){
      for(int j = 1; j <= data.get_n(); j++){
        aux.at(i,j) = data.at(i,j);
      }
    }
    
  for(int i = 2; i <= data.get_m(); ++i){
    for(int j = 1; j <= data.get_n(); ++j){
      data.at(i,j) = aux.at(i,(j - i + data.get_n()) % data.get_n());
    }
  }
}

void AES::MixColumns(matrix_t<std::string> data, matrix_t<std::string> &solution){
  std::bitset<8> sol; 
  for(int y = 1; y <= data.get_m(); y++){
    for(int i = 1; i <= data.get_m(); ++i){
        std::vector<std::bitset<8>> aux;
        for(int j = 1; j <= data.get_n(); ++j){
            aux.push_back(StringHexToBinary(DecimalToHex(StringHexToDecimal(data.at(j,y)) * StringHexToDecimal(kMatrixMixColumn.at(i,j)))));
        }
        sol = aux.at(0);
        for(int k = 1; k <= aux.size(); k++){
            sol = sol ^ aux.at(k);
        }
        solution.at(i,y) = BinaryToStringHex(sol);
    }
  }
}

void AES::InitializeSubKeys(){
    for(int i = 0; i < 11; ++i){
        sub_keys_.push_back(key_);
    }
}

void AES::LoadRcon(){
    kRcon = {
        "01000000","02000000","04000000","08000000",
        "10000000","20000000","40000000","80000000",
        "1B000000","36000000"
    };
}

void AES::RotWords(matrix_t<std::string> &data){
  std::string aux = data.at(0,3);
  data.at(0,3) = data.at(3,3);
  data.at(3,3) = aux;
}

void AES::ExpansionKey(){
    for(int i = 1; i <= 11; i++){
        RotWords(sub_keys_.at(i));
        matrix_t<std::string> byte(1,4);
        byte.at(0,0) = (key_(3,0));
        byte.at(0,1) = (key_(3,1));
        byte.at(0,2) = (key_(3,2));
        byte.at(0,3) = (key_(3,3));
        SubBytes(byte);
        std::string sub_key = "";
        for(int i = 0; i < 4; i++){
            sub_key += (byte.at(0,i));
        }
        std::bitset sol_xor_bin = StringHexToBinary(sub_key) ^ StringHexToBinary(kRcon.at(i));
        std::string sol_xor_string = BinaryToStringHex(sol_xor_bin);
        int counter = 0;
        for(int i = 0; i < 4; i++){
            byte.at(0,i) = sol_xor_string.at(counter) + sol_xor_string.at(counter + 1);
            counter += 2;
        }
        for(int k = 0; k < 4; k++){
            sub_keys_.at(i).at(0,k) = byte.at(0,k);
        }
    }
}

void AES::AlgorithmRijndael(){
    InitializeSol();
    InitializeSubKeys();
    AddRoundKey(solution_, sub_keys_.at(0), text_);
    for(int i = 1; i < 10; ++i){
        SubBytes(solution_);
        ShiftRows(solution_);
        MixColumns(solution_, solution_);
        AddRoundKey(solution_,solution_, sub_keys_.at(i));
    }
    SubBytes(solution_);
    ShiftRows(solution_);
    AddRoundKey(solution_, solution_, sub_keys_.at(10));
}

std::string AES::GetSolution(){
    std::string solution;
    for (int i = 0; i < solution_.get_m(); i++) {
        for (int j = 0; j < solution_.get_n(); j++) {
            solution += solution_.at(i, j);
        }
    }
    return solution;
}


