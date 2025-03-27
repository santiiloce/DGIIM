#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdint>

using namespace std;

// S-Box de AES
const uint8_t S_BOX[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    // ... (completar la S-Box)
};

// Función para convertir un string hexadecimal en vector de bytes
vector<uint8_t> hex_to_bytes(const string& hex) {
    vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

// Función para convertir un vector de bytes a hexadecimal
string bytes_to_hex(const vector<uint8_t>& bytes) {
    stringstream ss;
    for (uint8_t byte : bytes) {
        ss << hex << setw(2) << setfill('0') << (int)byte;
    }
    return ss.str();
}

// XOR entre dos arrays de bytes
vector<uint8_t> xor_bytes(const vector<uint8_t>& a, const vector<uint8_t>& b) {
    vector<uint8_t> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i];
    }
    return result;
}

// SubBytes
void sub_bytes(vector<uint8_t>& state) {
    for (size_t i = 0; i < state.size(); ++i) {
        state[i] = S_BOX[state[i]];
    }
}

// ShiftRows
void shift_rows(vector<uint8_t>& state) {
    vector<uint8_t> temp = state;
    state[1] = temp[5]; state[5] = temp[9]; state[9] = temp[13]; state[13] = temp[1];
    state[2] = temp[10]; state[6] = temp[14]; state[10] = temp[2]; state[14] = temp[6];
    state[3] = temp[15]; state[7] = temp[3]; state[11] = temp[7]; state[15] = temp[11];
}

// Multiplicación en GF(2^8)
uint8_t multiply_by_2(uint8_t byte) {
    return (byte << 1) ^ (byte & 0x80 ? 0x1B : 0);
}

uint8_t multiply_by_3(uint8_t byte) {
    return multiply_by_2(byte) ^ byte;
}

// MixColumns
void mix_columns(vector<uint8_t>& state) {
    vector<uint8_t> temp = state;
    for (int i = 0; i < 4; i++) {
        int col = i * 4;
        state[col] = multiply_by_2(temp[col]) ^ multiply_by_3(temp[col+1]) ^ temp[col+2] ^ temp[col+3];
        state[col+1] = temp[col] ^ multiply_by_2(temp[col+1]) ^ multiply_by_3(temp[col+2]) ^ temp[col+3];
        state[col+2] = temp[col] ^ temp[col+1] ^ multiply_by_2(temp[col+2]) ^ multiply_by_3(temp[col+3]);
        state[col+3] = multiply_by_3(temp[col]) ^ temp[col+1] ^ temp[col+2] ^ multiply_by_2(temp[col+3]);
    }
}

int main() {
    string plaintext_hex, key_hex;
    cout << "Introduce el texto en hexadecimal: ";
    cin >> plaintext_hex;
    cout << "Introduce la clave en hexadecimal: ";
    cin >> key_hex;

    vector<uint8_t> plaintext = hex_to_bytes(plaintext_hex);
    vector<uint8_t> key = hex_to_bytes(key_hex);
    
    sub_bytes(plaintext);
    shift_rows(plaintext);
    mix_columns(plaintext);

    cout << "Texto cifrado: " << bytes_to_hex(plaintext) << endl;
    return 0;
}
