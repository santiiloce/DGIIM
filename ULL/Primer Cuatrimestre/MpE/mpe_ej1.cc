/**
 * @file mpe_ej1.cc
 * @author Julia Pereda Vivo y Santiago López Cerro
 * @brief Este codigo
 * @version 0.1
 * @date 2024-12-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

const int kSize = 27;

class Patron {
private:
    std::vector<int> sol1;
    std::vector<int> sol2;
    std::vector<int> sol3;

public:
    void RealizaCalculos(int n1, int n2, int n3) {
        int k1 = n2 * n3;
        int k2 = n1 * n3;
        int k3 = n1 * n2;
        int sol = (n1 * n2 * n3) / 2;

        if ((k1 + k2 + k3) == sol) {
            #pragma omp critical  // Evitar conflictos de acceso a vectores
            {
                sol1.push_back(n1);
                sol2.push_back(n2);
                sol3.push_back(n3);
            }
        }
    }

    void HallaSolucion() {
        #pragma omp parallel for collapse(3)  // Paralelizar los tres bucles anidados
        for (int i = 1; i <= kSize; i++) {
            for (int j = i; j <= kSize; j++) {
                for (int k = j; k <= kSize; k++) {
                    RealizaCalculos(i, j, k);  // Calcular y almacenar solución si se cumple la condición
                }
            }
        }
    }

    void ObtenerSoluciones() {
        std::ofstream archivo("patron.txt");
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo" << std::endl;
            return;
        }
        for (size_t i = 0; i < sol1.size(); i++) {
            archivo << i + 1 << ": " << sol1.at(i) << " " << sol2.at(i) << " " << sol3.at(i) << std::endl;
        }
        archivo.close();
    }
};

int main() {
    Patron patron;
    std::cout << "Inicio de los cálculos" << std::endl;
    patron.HallaSolucion();
    std::cout << "Fin de los cálculos. La solución se encuentra en patron.txt" << std::endl;
    patron.ObtenerSoluciones();
    return 0;








    CalculaIgualdad(int n, int sol){
        for(int i = 0; ç)
    }
}
