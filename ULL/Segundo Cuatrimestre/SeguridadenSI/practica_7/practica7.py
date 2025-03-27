import AES

# PRÁCTICA 7 --> CBC

def aes_encrypt_block(plaintext, key):
    """ Función auxiliar para cifrar un solo bloque con AES. """
    _, ciphertext, _ = rijndael_encrypt(plaintext, key)
    return ciphertext

def cbc_encrypt(plaintext_blocks, key, iv):
    """ Implementación del modo CBC para cifrar bloques de texto. """
    ciphertext_blocks = []
    previous_block = iv
    
    for plaintext_block in plaintext_blocks:
        # XOR entre el bloque actual y el bloque cifrado anterior (o IV para el primer bloque)
        xored_block = AES.xor_bytes(plaintext_block, previous_block)
        
        # Cifrar el bloque resultante con AES
        cipher_block = AES.aes_encrypt_block(xored_block, key)
        
        # Almacenar el bloque cifrado
        ciphertext_blocks.append(cipher_block)
        
        # Actualizar el bloque anterior para la siguiente iteración
        previous_block = cipher_block
    
    return ciphertext_blocks

def format_hex_with_spaces(hex_string):
    """Formatea una cadena hexadecimal con espacios entre cada byte y en mayúsculas."""
    # Convierte a mayúsculas y luego inserta un espacio cada 2 caracteres
    return ' '.join(hex_string.upper()[i:i+2] for i in range(0, len(hex_string), 2))

def cbc_main():
    print("Implementación del Modo CBC usando AES")
    print("======================================")
    
    key_hex = input("Clave (16 bytes en hexadecimal): ").strip()
    iv_hex = input("Vector de inicialización (16 bytes en hexadecimal): ").strip()
    
    blocks = []
    block_count = int(input("Número de bloques a cifrar: "))
    
    for i in range(block_count):
        block_hex = input(f"Bloque {i+1} de Texto Original (16 bytes en hexadecimal): ").strip()
        blocks.append(AES.hex_to_bytes(block_hex))
    
    try:
        key = hex_to_bytes(key_hex)
        iv = hex_to_bytes(iv_hex)
        
        if len(key) != 16:
            raise ValueError("La clave debe ser de 16 bytes (32 caracteres hexadecimales)")
        if len(iv) != 16:
            raise ValueError("El IV debe ser de 16 bytes (32 caracteres hexadecimales)")
        
        for i, block in enumerate(blocks):
            if len(block) != 16:
                raise ValueError(f"El bloque {i+1} debe ser de 16 bytes (32 caracteres hexadecimales)")
    
    except ValueError as e:
        print(f"Error: {e}")
        return
    
    ciphertext_blocks = cbc_encrypt(blocks, key, iv)
    
    print("\nSalida:")
    for i, block in enumerate(ciphertext_blocks):
        # Formatea la salida con espacios entre cada byte y en mayúsculas
        formatted_hex = format_hex_with_spaces(block.hex())
        print(f"    Bloque {i+1} de Texto Cifrado: {formatted_hex}")

# PRÁCTICA 7 

if __name__ == "__main__":
    # Puedes elegir entre la implementación AES original o la nueva CBC
    choice = input("Selecciona modo (1: AES estándar, 2: CBC): ")
    
    if choice == "1":
        from practica7 import main as aes_main  # Función original de AES
    elif choice == "2":
        cbc_main()  # Nueva función CBC
    else:
        print("Opción no válida")