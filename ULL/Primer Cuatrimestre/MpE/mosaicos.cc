/**
 * @file mpe_ej1.cc
 * @author Julia Pereda Vivo y Santiago López Cerro
 * @brief Este codigo calcula todas las posibilidades de unir mosaicos regulares entorno a un vértice
 * @version 0.1
 * @date 2024-12-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>


const int kSize = 27;


void HallaValores(int n, double sol, std::vector<int>& sol1, std::vector<int>& sol2, std::vector<int>& sol3, std::vector<int>& sol4, std::vector<int>& sol5) {
    switch (n) {
    case 3:
        #pragma omp parallel for collapse(3)
        for (int i = 3; i <= kSize; i++) {
            for (int j = i; j <= kSize; j++) {
                for (int k = j; k <= kSize; k++) {
                    double aux = j * k + i * k + i * j;
                    sol = 0.5 * i * j * k;
                    if (aux == sol) {
                        #pragma omp critical
                        {
                            sol1.push_back(i);
                            sol2.push_back(j);
                            sol3.push_back(k);
                        }
                    }
                }
            }
        }
        break;
    case 4:
        #pragma omp parallel for collapse(4)
        for (int i = 3; i <= kSize; i++) {
            for (int j = i; j <= kSize; j++) {
                for (int k = j; k <= kSize; k++) {
                    for (int x = k; x <= kSize; x++) {
                        double aux = j*k*x + i*k*x + i*j*x + i*j*k;
                        if (aux == (i * j * k * x )) {
                            #pragma omp critical
                            {
                                sol1.push_back(i);
                                sol2.push_back(j);
                                sol3.push_back(k);
                                sol4.push_back(x);
                            }
                        }
                    }
                }
            }
        }
        break;
    case 5:
        #pragma omp parallel for collapse(5)
        for (int i = 3; i <= kSize; i++) {
            for (int j = i; j <= kSize; j++) {
                for (int k = j; k <= kSize; k++) {
                    for (int x = k; x <= kSize; x++) {
                        for (int y = x; y <= kSize; y++) {
                            double aux = 1.0 / static_cast<double>(i) + 1.0 / static_cast<double>(j) + 1.0 / static_cast<double>(k) + 1.0 / static_cast<double>(x) + 1.0 / static_cast<double>(y);
                            if (aux == sol) {
                                #pragma omp critical
                                {
                                    sol1.push_back(i);
                                    sol2.push_back(j);
                                    sol3.push_back(k);
                                    sol4.push_back(x);
                                    sol5.push_back(y);
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
}

int main(){
    std::vector<std::vector<int>> sols(5);
    double sol = 0.0;
    int contador = 3;
    std::ofstream archivo("patron.txt");
    if (!archivo.is_open()) {
       std::cerr << "Error al abrir el archivo" << std::endl;
       return 1;
    }
    archivo << "Estas son las distintas posibilidades de unir mosaicos regulares entorno a un vértice:  " << std::endl << std::endl;
    for(int i = 3; i <= 5; i++){
        sol += 0.5;
        HallaValores(i, sol, sols.at(0), sols.at(1), sols.at(2), sols.at(3), sols.at(4));
        archivo << "________________________________k = " << i << "______________________________" << std::endl;
        std::cout << "Tamanio " << i << " : " << sols.at(i-1).size() << std::endl;
            for (int k = 0; k < sols.at(i - 1).size(); k++) {
                switch (i)
                {
                case 3:
                    archivo << "nº "<< k + 1 << " : " << sols.at(0).at(k) << " " << sols.at(1).at(k) << " " << sols.at(2).at(k) << std::endl; 
                    break;
                case 4:
                    archivo << "nº "<< k + 1 << " : " << sols.at(0).at(k) << " " << sols.at(1).at(k) << " " << sols.at(2).at(k) << " " << sols.at(3).at(k) << std::endl; 
                    break;
                case 5:
                    archivo << "nº "<< k + 1 << " : " << sols.at(0).at(k) << " " << sols.at(1).at(k) << " " << sols.at(2).at(k) << " " << sols.at(3).at(k) << " " << sols.at(4).at(k) << std::endl; 
                    break;

                }
            }
        contador++;
        sols.at(0).clear();
        sols.at(1).clear();
        sols.at(2).clear();
        sols.at(3).clear();
        sols.at(4).clear();
    }
    archivo.close();
    return 0;
}