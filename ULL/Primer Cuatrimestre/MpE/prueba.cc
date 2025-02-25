#include <iostream>

int main(){
    int contador = 1;
    for(int i=1; i < 27; i++){
        for(int j=1; j<27; j++){
            for(int k = 1; k <27; k++){
                double aux = 1.0/i + 1.0/j + 1.0/k;
                double sol = 0.5;
                if( aux == sol){
                    std::cout << contador << " : " << i << " " << j << " " << k << " " << std::endl;
                    contador++;
                }
            }
        }
    }
    std::cout << 1.0/3.0 << std::endl;
    return 0;
}