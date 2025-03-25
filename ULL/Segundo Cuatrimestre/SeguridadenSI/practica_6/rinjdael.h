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

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "matrix_t.hpp"

class AES{
    private:
      std::vector<std::string> kRcon;
      matrix_t<std::string> kMatrixMixColumn;
      matrix_t<std::string> kSBox;
      matrix_t<std::string> solution_;
      matrix_t<std::string> key_;
      std::vector<matrix_t<std::string>> sub_keys_;
      matrix_t<std::string> text_;
    private: 
      void InitializeSol();
      void InitializeSubKeys();
      void LoadRcon();
      void AddRoundKey(matrix_t<std::string> &sol,matrix_t<std::string> key, matrix_t<std::string> &text);
      void ShiftRows(matrix_t<std::string> &data);
      void MixColumns(matrix_t<std::string> data, matrix_t<std::string> &solution);
      void SubBytes(matrix_t<std::string> &data); 
      void RotWords(matrix_t<std::string> &data);
    public:
      AES();
      AES(matrix_t<std::string> key, matrix_t<std::string> text);
      std::bitset<8> StringHexToBinary(const std::string& hex);
      std::string DecimalToHex(int num);
      std::string BinaryToStringHex(std::bitset<8>& binary);
      int StringHexToDecimal(const std::string& hex);
      int CharHexToDecimal(const char& hex);
      void ExpansionKey();
      void AlgorithmRijndael();
      std::string GetSolution();
      static void FinalResult();
};