/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Encriptado de Chacha
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */
 #include <iostream>
 #include <cmath>
 #include <cstdint>
 #include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdint>


template< std::size_t N >
class bitset;
#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) ( \
    a += b, d ^= a, d = ROTL(d, 16), \
    c += d, b ^= c, b = ROTL(b, 12), \
    a += b, d ^= a, d = ROTL(d, 8),  \
    c += d, b ^= c, b = ROTL(b, 7)   \
)

#define ROUNDS 20

void chacha_block(uint32_t out[16], uint32_t const in[16]) {
    int i;
    uint32_t x[16];

    for (i = 0; i < 16; ++i)
        x[i] = in[i];

    // 20 loops = 2 rounds/loop = 20 rounds
    for (i = 0; i < ROUNDS; i += 2) {
        // Odd round
        QR(x[0], x[4], x[8], x[12]);  // column 0
        QR(x[1], x[5], x[9], x[13]);  // column 1
        QR(x[2], x[6], x[10], x[14]); // column 2
        QR(x[3], x[7], x[11], x[15]); // column 3

        // Even round
        QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
        QR(x[1], x[6], x[11], x[12]); // diagonal 2
        QR(x[2], x[7], x[8], x[13]);  // diagonal 3
        QR(x[3], x[4], x[9], x[14]);  // diagonal 4
    }
    std::ofstream escritura("estado_final.txt");
    for( i = 0; i < 16; ++i){
        escritura << out[i] << " ";
    }
    for ( i = 0; i < 16; ++i)
        out[i] = x[i] + in[i];
    
    std::ofstream escritura2("estado_salida.txt");
    for( i = 0; i < 16; ++i){
        escritura2 << out[i] << " ";
    }
}

uint32_t word_to_bytes(const std::string& byte_str) {
    uint32_t word = 0;
    std::stringstream ss(byte_str);
    std::string byte;

    // Leer cada byte separado por ':'
    int shift = 0;
    while (std::getline(ss, byte, ':')) {
        // Convertir el byte de string a entero
        uint32_t byte_value = std::stoul(byte, nullptr, 16);
        // Agregar el byte a la palabra, en little-endian
        word |= (byte_value << (shift * 8));
        shift++;
    }

    return word;
}

int main(){
    std::ifstream lectura("datos.txt");
    std::string clave, contador, nonce;
    uint32_t in[16], out[16];
    in[0] = 0x61707865;
    in[1] = 0x3320646e;
    in[2] = 0x79622d32;
    in[3] = 0x6b206574;
    int i = 4;
    for( i = 4; i < 12; i++){
        lectura >> clave;
        in[i] = word_to_bytes(clave);
    }
    lectura >> contador;
    in[i] = word_to_bytes(contador);
    while(i < 16){
        lectura >> nonce;
        in[i] = word_to_bytes(nonce);
        i++;
    }
    std::cout << "Estado inicial: " << std::endl;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++){
            std::cout << in[j] << " ";
            i++; 
        }
        std::cout << std::endl;
    }
    chacha_block(out, in);
    std::cout << "Estado final tras 20 iteraciones: " << std::endl;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++){
            std::cout << in[j] << " ";
            i++; 
        }
        std::cout << std::endl;
    }

}


 