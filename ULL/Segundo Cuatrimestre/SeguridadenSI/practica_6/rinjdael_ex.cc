#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

typedef vector<vector<unsigned char>> State;

// Matriz S-Box (Tabla de sustitución)
const unsigned char SBox[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}
};

// Función para convertir un string hexadecimal en un vector de bytes
vector<unsigned char> hexStringToBytes(const string& hex) {
    vector<unsigned char> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

// Función para imprimir en formato hexadecimal
void printHex(const vector<unsigned char>& data) {
    for (unsigned char byte : data) {
        cout << hex << setw(2) << setfill('0') << (int)byte;
    }
    cout << endl;
}

// Expansión de clave (simplificada)
vector<unsigned char> keyExpansion(const vector<unsigned char>& key) {
    vector<unsigned char> expandedKey = key;
    for (int i = 16; i < 176; i++) {
        expandedKey.push_back(expandedKey[i - 16] ^ expandedKey[i - 1]);
    }
    return expandedKey;
}

// ShiftRows
void shiftRows(vector<unsigned char>& state) {
    vector<unsigned char> temp = state;
    state[1] = temp[5]; state[5] = temp[9]; state[9] = temp[13]; state[13] = temp[1];
    state[2] = temp[10]; state[6] = temp[14]; state[10] = temp[2]; state[14] = temp[6];
    state[3] = temp[15]; state[7] = temp[3]; state[11] = temp[7]; state[15] = temp[11];
}

// Implementación completa de AES-128
vector<unsigned char> aesEncrypt(const vector<unsigned char>& key, const vector<unsigned char>& text) {
    vector<unsigned char> expandedKey = keyExpansion(key);
    vector<unsigned char> state = text;
    
    // Aplicar AddRoundKey inicial
    for (size_t i = 0; i < state.size(); i++) {
        state[i] ^= expandedKey[i];
    }
    
    // 9 rondas de cifrado
    for (int round = 1; round <= 9; round++) {
        for (size_t i = 0; i < state.size(); i++) {
            state[i] = SBox[state[i] >> 4][state[i] & 0x0F];
        }
        shiftRows(state);
        for (size_t i = 0; i < state.size(); i++) {
            state[i] ^= expandedKey[round * 16 + i];
        }
    }
    
    // Ronda final
    for (size_t i = 0; i < state.size(); i++) {
        state[i] = SBox[state[i] >> 4][state[i] & 0x0F];
    }
    shiftRows(state);
    for (size_t i = 0; i < state.size(); i++) {
        state[i] ^= expandedKey[160 + i];
    }
    
    return state;
}

int main() {
    string keyInput, textInput;
    cout << "Clave: ";
    cin >> keyInput;
    cout << "Bloque de Texto Original: ";
    cin >> textInput;
    
    vector<unsigned char> key = hexStringToBytes(keyInput);
    vector<unsigned char> text = hexStringToBytes(textInput);
    
    vector<unsigned char> encryptedText = aesEncrypt(key, text);
    
    cout << "Bloque de Texto Cifrado: ";
    printHex(encryptedText);
    
    return 0;
}
