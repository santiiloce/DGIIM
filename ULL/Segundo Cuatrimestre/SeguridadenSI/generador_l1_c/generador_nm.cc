#include <iostream>
#include <vector>
#include <string>

// Clase que implementa el Generador C/A
class GeneradorCA {
private:
    std::vector<bool> G1, G2;
    int id;
    size_t sequence_length;
    
    // Mapa de taps de G2 según el ID del satélite
    const int taps[32][2] = {
        {2, 6}, {3, 7}, {4, 8}, {5, 9}, {1, 9}, {2, 10}, {1, 8}, {2, 9}, {3, 10}, {2, 3},
        {3, 4}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {1, 4}, {2, 5}, {3, 6}, {4, 7},
        {5, 8}, {6, 9}, {1, 3}, {4, 6}, {5, 7}, {6, 8}, {7, 9}, {8, 10}, {1, 6}, {2, 7},
        {3, 8}, {4, 9}
    };

    // Desplaza los registros y devuelve el nuevo bit
    bool shiftRegister(std::vector<bool>& reg, std::vector<int> feedback_taps) {
        bool feedback = 0;
        for (int tap : feedback_taps) {
            feedback ^= reg[tap - 1]; // XOR de los taps
        }
        bool last_bit = reg.back(); // Guardamos el último bit
        reg.pop_back();             // Desplazamos
        reg.insert(reg.begin(), feedback);
        return last_bit;
    }

public:
    // Constructor
    GeneradorCA(int sat_id, size_t length) : id(sat_id), sequence_length(length) {
        G1.assign(10, 1); // Inicializar con todos 1s
        G2.assign(10, 1);
    }

    // Genera la secuencia C/A
    std::string generateCA() {
        std::string ca_sequence;
        
        // Obtener taps específicos de G2 para el satélite
        std::vector<int> G1_taps = {3, 10};       // Siempre los mismos
        std::vector<int> G2_taps = {taps[id - 1][0], taps[id - 1][1]}; 

        // Generar la secuencia
        for (size_t i = 0; i < sequence_length; i++) {
            bool G1_bit = shiftRegister(G1, G1_taps);
            bool G2_bit = shiftRegister(G2, G2_taps);
            ca_sequence.push_back((G1_bit ^ G2_bit) ? '1' : '0'); // XOR final
        }

        return ca_sequence;
    }
};

int main() {
    int id;
    size_t length;
    
    std::cout << "ID del satélite (1-32): ";
    std::cin >> id;
    if (id < 1 || id > 32) {
        std::cerr << "Error: ID fuera de rango (1-32)." << std::endl;
        return 1;
    }
    
    std::cout << "Longitud de la secuencia de salida: ";
    std::cin >> length;

    GeneradorCA generator(id, length);
    std::string ca_code = generator.generateCA();

    std::cout << "Secuencia C/A: " << ca_code << std::endl;

    return 0;
}
