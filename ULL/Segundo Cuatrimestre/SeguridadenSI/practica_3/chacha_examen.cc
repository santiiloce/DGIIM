/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Encriptado de Chacha con la modificación del examen
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */ 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <stdlib.h>     
#include <time.h>       
#include <iomanip>

std::vector<int> desplazamiento = {7,8,12,16};

int EligeDesplazamiento(){
    srand(time(NULL));
    int sol;
    do{
        int pos = rand() % 4;
        sol = desplazamiento.at(pos);
        desplazamiento.at(pos) = -1;
    }while(sol != -1);
    return sol;
}

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) ( \
    a += b, d ^= a, d = ROTL(d, EligeDesplazamiento()), \
    c += d, b ^= c, b = ROTL(b, EligeDesplazamiento()), \
    a += b, d ^= a, d = ROTL(d, EligeDesplazamiento()),  \
    c += d, b ^= c, b = ROTL(b, EligeDesplazamiento())   \
)

#define ROUNDS 20

void chacha_block(uint32_t out[16], const uint32_t in[16]) {
    uint32_t x[16];
    for (int i = 0; i < 16; ++i)
        x[i] = in[i];

    // 20 rounds (10 double-rounds)
    for (int i = 0; i < ROUNDS; i += 2) {
        // Odd round
        QR(x[0], x[4], x[8], x[12]);
        QR(x[1], x[5], x[9], x[13]);
        QR(x[2], x[6], x[10], x[14]);
        QR(x[3], x[7], x[11], x[15]);

        // Even round
        QR(x[0], x[5], x[10], x[15]);
        QR(x[1], x[6], x[11], x[12]);
        QR(x[2], x[7], x[8], x[13]);
        QR(x[3], x[4], x[9], x[14]);
    }

    // Guardar estado final en archivo
    std::ofstream estado_final("estado_final.txt");
    for (int i = 0; i < 16; ++i)
        estado_final << std::hex << std::setfill('0') << std::setw(8) << x[i] << " ";
    estado_final.close();

    // Estado de salida del generador: suma con el estado inicial
    for (int i = 0; i < 16; ++i)
        out[i] = x[i] + in[i];

    // Guardar estado de salida en archivo
    std::ofstream estado_salida("estado_salida.txt");
    for (int i = 0; i < 16; ++i)
        estado_salida << std::hex << std::setfill('0') << std::setw(8) << out[i] << " ";
    estado_salida.close();
}

uint32_t word_to_bytes(const std::string& byte_str) {
    uint32_t word = 0;
    std::stringstream ss(byte_str);
    std::string byte;
    int shift = 0;

    while (std::getline(ss, byte, ':')) { // Defino delimitador ":"
        uint32_t byte_value = std::stoul(byte, nullptr, 16); // Sirve para pasar cadena unsigned long en base xx
        word |= (byte_value << (shift * 8));
        shift++; // Incremento el desplazamiento
    }
    return word;
}

uint32_t random_counter(){
    srand (time(NULL));
    std::string sol = "";
    for(int i = 0; i < 8; i++){
        int num = rand() % 16;
        switch (num)
        {
        case 10:
            sol.push_back('a');
            break;
        case 11:
            sol.push_back('b');
            break;
        case 12:
            sol.push_back('c');
            break;
        case 13:
            sol.push_back('d');
            break;
        case 14:
            sol.push_back('e');
            break;
        case 15:
            sol.push_back('f');
            break;
        
        default:
            sol.push_back(num + '0');
            break;
        }
        if(i != 7 && (i % 2 == 1)){
            sol += ":";
        }
    }
    uint32_t hex = word_to_bytes(sol);
    return hex;
}

int main() {
    std::ifstream lectura("datos.txt");
    if (!lectura) {
        std::cerr << "Error al abrir el archivo datos.txt\n";
        return 1;
    }

    std::string clave, contador, nonce;
    uint32_t in[16], out[16];

    // Cadena constante de ChaCha20
    in[0] = 0x61707865;
    in[1] = 0x3320646e;
    in[2] = 0x79622d32;
    in[3] = 0x6b206574;

    // Clave
    for (int i = 4; i < 12; i++) {
        lectura >> clave;
        in[i] = word_to_bytes(clave);
    }

    // Contador
    lectura >> contador;
    in[12] = word_to_bytes(contador);

    // Nonce
    for (int i = 13; i < 16; i++) {
        lectura >> nonce;
        in[i] = word_to_bytes(nonce);
    }

    // Mostrar estado inicial
    std::cout << "Estado inicial:\n";
    for (int i = 0; i < 16; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << in[i] << " ";
        if ((i + 1) % 4 == 0) std::cout << std::endl;
    }

    // Ejecutar ChaCha20
    chacha_block(out, in);

    // Mostrar estado final tras 20 iteraciones
    std::cout << "\nEstado final tras 20 iteraciones:\n";
    std::ifstream final("estado_final.txt");
    if(!final.is_open()){
        std::cerr << "Error al abrir el archivo";
        return 1;
    }
    std::string word_final = "";
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++){
            final >> word_final;
            std::cout << word_final << " ";
            i++;
        }
        std::cout << std::endl;
    }

    // Muestro estado salida
    std::cout << " Estado de salida del generador: " << std::endl;
    std::ifstream salida("estado_salida.txt");
    if(!salida.is_open()){
        std::cerr << "Error al abrir el archivo";
        return 1;
    }
    std::string word_salida = "";
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++){
            salida >> word_salida;
            std::cout << word_salida << " ";
            i++;
        }
        std::cout << std::endl;
    }
    return 0;
}
