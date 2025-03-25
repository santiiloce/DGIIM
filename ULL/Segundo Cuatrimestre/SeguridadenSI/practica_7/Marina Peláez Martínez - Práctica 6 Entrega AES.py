def hex_to_bytes(hex_string):
    return bytes.fromhex(hex_string)

def bytes_to_hex(byte_array):
    return byte_array.hex()

def xor_bytes(a, b):
    return bytes(x ^ y for x, y in zip(a, b))

# S-Box table 
S_BOX = (
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,
)

# Round Constant Word Array
RCON = (
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A
)

def sub_bytes(state):
    return bytes(S_BOX[b] for b in state)

def shift_rows(state):
    """Realiza la operación de ShiftRows en AES reorganizando correctamente la matriz."""

    matrix = [[state[row + (col * 4)] for col in range(4)] for row in range(4)]
    

    matrix[1] = matrix[1][1:] + matrix[1][:1]  
    matrix[2] = matrix[2][2:] + matrix[2][:2]  
    matrix[3] = matrix[3][3:] + matrix[3][:3]  

    # Convertir la matriz de vuelta a una lista de bytes en formato columna por columna
    result = []
    for col in range(4):  # Iteramos en columnas
        for row in range(4):
            result.append(matrix[row][col])  # Reensamblamos en orden de columnas

    return bytes(result)  # Convertir a formato de bytes nuevamente


def multiply_by_2(byte):
    """Multiplicar un byte por 2 en el campo GF(2^8)"""
    result = (byte << 1) & 0xFF
    if byte & 0x80:
        result ^= 0x1B  # XOR con el polinomio de reducción x^8 + x^4 + x^3 + x + 1
    return result

def multiply_by_3(byte):
    """Multiplicar un byte por 3 en el campo GF(2^8)"""
    return multiply_by_2(byte) ^ byte

def mix_columns(state):
    result = bytearray(16)
    
    for col in range(4):
        s0 = state[col * 4]
        s1 = state[col * 4 + 1]
        s2 = state[col * 4 + 2]
        s3 = state[col * 4 + 3]
        
        # Matriz de multiplicación, cada columna es multiplicada por:
        # [ 2 3 1 1 ]
        # [ 1 2 3 1 ]
        # [ 1 1 2 3 ]
        # [ 3 1 1 2 ]
        result[col * 4] = multiply_by_2(s0) ^ multiply_by_3(s1) ^ s2 ^ s3
        result[col * 4 + 1] = s0 ^ multiply_by_2(s1) ^ multiply_by_3(s2) ^ s3
        result[col * 4 + 2] = s0 ^ s1 ^ multiply_by_2(s2) ^ multiply_by_3(s3)
        result[col * 4 + 3] = multiply_by_3(s0) ^ s1 ^ s2 ^ multiply_by_2(s3)
    
    return bytes(result)

def key_expansion(key, nb=4, nr=10):
    nk = len(key) // 4 
    w = []
    
    for i in range(nk):
        w.append(key[4*i:4*(i+1)])
    
    for i in range(nk, nb * (nr + 1)):
        temp = w[i-1]
        
        if i % nk == 0:
            # RotWord: 
            temp = temp[1:] + temp[:1]
            # SubWord: 
            temp = bytes(S_BOX[b] for b in temp)
            # XOR:
            temp = bytes([temp[0] ^ RCON[i // nk]]) + temp[1:]
        
        w.append(xor_bytes(w[i-nk], temp))
    
    round_keys = []
    for i in range(nr + 1):
        round_key = b''
        for j in range(nb):
            round_key += w[i*nb + j]
        round_keys.append(round_key)
    
    return round_keys

def add_round_key(state, round_key):
    return xor_bytes(state, round_key)

def rijndael_encrypt(plaintext, key):
    """
    Algoritmo Rijndael/AES con una clave de 16-bytes.
    """

    nr = 10
    

    round_keys = key_expansion(key, nb=4, nr=nr)
    

    state = plaintext
    

    results = []
    
    # Ronda inicial
    results.append(("R0 (Subclave = " + round_keys[0].hex() + ")", state.hex()))
    state = add_round_key(state, round_keys[0])
    
    # Rondas principales
    for round_num in range(1, nr):
        state = sub_bytes(state)
        state = shift_rows(state)
        state = mix_columns(state)
        

        state_before_key = state
        
        state = add_round_key(state, round_keys[round_num])
        

        results.append((f"R{round_num} (Subclave = {round_keys[round_num].hex()})", state.hex()))
    
    # Ronda final
    state = sub_bytes(state)
    state = shift_rows(state)
    state = add_round_key(state, round_keys[nr])
    
    # Resultado final
    results.append((f"R{nr} (Subclave = {round_keys[nr].hex()})", state.hex()))
    
    return results, state, round_keys

def main():
    print("Implementación del Algoritmo Rijndael (AES)")
    print("===========================================")
    
    key_hex = input("Clave (16 bytes en hexadecimal): ").strip()
    plaintext_hex = input("Bloque de Texto Original (16 bytes en hexadecimal): ").strip()
    
    try:
        key = hex_to_bytes(key_hex)
        plaintext = hex_to_bytes(plaintext_hex)
        
        if len(key) != 16:
            raise ValueError("La clave debe ser de 16 bytes (32 caracteres hexadecimales)")
        if len(plaintext) != 16:
            raise ValueError("El bloque de texto debe ser de 16 bytes (32 caracteres hexadecimales)")
    
    except ValueError as e:
        print(f"Error: {e}")
        return
    
    results, ciphertext, round_keys = rijndael_encrypt(plaintext, key)
    
    print("\nSubclaves:")
    for i, key in enumerate(round_keys):
        print(f"Subclave {i}: {key.hex()}")
    
    print("\nResultados de cada iteración:")
    for round_info, state in results:
        print(f"{round_info} = {state}")
    
    print("\nBloque de Texto Cifrado:", ciphertext.hex())

if __name__ == "__main__":
    main()

# TEST:
# Clave: 000102030405060708090a0b0c0d0e0f  
# Bloque de Texto Original: 00112233445566778899aabbccddeeff 

# RESULTADO:
# Bloque de Texto Cifrado: 69c4e0d86a7b0430d8cdb78070b4c55a 
