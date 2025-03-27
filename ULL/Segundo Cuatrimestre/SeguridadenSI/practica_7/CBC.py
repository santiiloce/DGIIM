#
# Cifrado de bloques en modo CBC (Cipher BLock Chaining) por Santiago López Cerro
#

import AES

def CBC(clave, IV, texto):
    # Paso los datos a formato byte
    key = AES.hex_to_bytes(clave)  
    iv = AES.hex_to_bytes(IV)      # Usamos el IV
    plaintext = AES.hex_to_bytes(texto)

    # Compruebo que el texto sea de tamaño múltiplo de 16
    size = len(plaintext)
    if size % 16 != 0:
        padding = 16 - (size % 16)
        plaintext += bytes([padding] * padding)  # Agrego el padding en caso de necesitarlo

    cifrado = bytearray()
    previous_block = iv  # Inicializamos el IV

    # Procesamiento de cada bloque del texto
    for i in range(0, len(plaintext), 16):
        block = plaintext[i:i+16]   # Bloque de texto actual
        block_to_encrypt = AES.xor_bytes(block, previous_block) # XOR entre el bloque de texto y el resultado del bloque anterior
        _, encrypted_block, _ = AES.rijndael_encrypt(block_to_encrypt, key)
        cifrado.extend(encrypted_block[:16]) # Agrego el resultado
        previous_block = encrypted_block    # Actualizo

    return AES.bytes_to_hex(cifrado)

def main():
    print("Entrada:")
    clave = input("Clave (16 bytes en hexadecimal): ")
    IV = input("IV (16 bytes en hexadecimal): ")
    texto = input("Texto Original (en hexadecimal): ")
    
    result = CBC(clave, IV, texto)

    # Llamar a la función CBC y mostrar el resultado
    print("Bloque de texto cifrado: ", result)

    texto2 = input("Nuevo texto: ")
    
    print("Bloque 2", CBC(clave, result, texto2))

# Llamar al main para ejecutar el programa
if __name__ == "__main__":
    main()


""""
Clave: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
IV: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Bloque 1 de Texto Original: 00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF
Texto cifrado: 69 C4 E0 D8 6A 7B 04 30 D8 CD B7 80 70 B4 C5 5A
"""

