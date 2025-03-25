#include "rinjdael.cc"


int main(){
    std::cout << "Valores de entrada: " <<std::endl; 
    std::string key = "000102030405060708090a0b0c0d0e0f";
    std::string text = "00112233445566778899aabbccddeeff";
    matrix_t<std::string> mkey(4,4), mtext(4,4);
    int counter = 0;
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 4; j++){
            mkey.at(j,i) = key.at(counter) + key.at(counter + 1);
            mtext.at(j,i) = text.at(counter) + text.at(counter + 1);
            counter += 2;
        }
    }
    AES aes(mkey, mtext);
    aes.AlgorithmRijndael();
    return 0;
}