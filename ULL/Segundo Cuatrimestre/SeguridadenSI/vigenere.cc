/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguridad en Sistemas Informáticos 2024-2025
  *
  * @author Santiago Lopez Cerro alu0101763613@ull.edu.es
  * @brief Encriptado de Vigenere
  * @bug Therea are no known bugs
  * @see https://www.cs.cmu.edu/~410/doc/doxygen.html
  */

 #include <iostream>
 #include <string>
 #include <cstdlib>
 #include <fstream>
 #include <cmath>
/**
 * @brief Transforma el texto de extrada en el texto claro necesario para el cifrado
 * 
 * @param text 
 * @return std::string texto claro
 */
std::string AdaptText(std::string text){
    std::string adapted_text = "";
    for(int i = 0; i < text.size(); i++){
        char value = text.at(i);
        char carac = std::toupper(value);
        if( carac >= 'A' && carac <= 'Z'){
            adapted_text.push_back(carac);
        }
        else{
            adapted_text.push_back('A'); // Caracter comodin
        }
    }
    return adapted_text;
}

/**
 * @brief Cifra el texto claro mediante la suma de los caracteres de la clav
 * 
 * @param text 
 * @param key 
 * @return std::string 
 */
std::string EncriptaVigenere(std::string text,std::string key){
    std::string encrypted = "";
    int counter = 0;
    for(int i = 0; i < text.size(); i++){
        int aux = text.at(i);
        if(text.at(i) >= 'A' && text.at(i) <= 'Z'){
            aux = (aux + (key.at(counter) - 'A') - 'A') % 26;
            encrypted.push_back(static_cast<char>(aux + 'A'));
            counter = (counter + 1) % key.size();
        }
        else{
            aux = (aux + (key.at(counter) - 'a') - 'a') % 26;
            encrypted.push_back(static_cast<char>(aux + 'a'));
        }
    }
    return encrypted;
}

std::string DesencriptaVigenere(std::string text, std::string key){
    std::string encrypted = "";
    int counter = 0;
    for(int i = 0; i < text.size(); i++){
        int aux = text.at(i);
        if(text.at(i) >= 'A' && text.at(i) <= 'Z'){
            aux = (aux - (key.at(counter) - 'A') - 'A') % 26;
            if(aux < 0){
                aux = 26 + aux;
            }
            encrypted.push_back(static_cast<char>(aux + 'A'));
            counter = (counter + 1) % key.size();
        }
        else{
            aux = (aux - (key.at(counter) - 'a') - 'a') % 26;
            if(aux < 0){
                aux = 26 + aux;
            }
            encrypted.push_back(static_cast<char>(aux + 'a'));
            counter = (counter + 1) % key.size();
        }
    }
    return encrypted;
}

 int main(){
    std::string key, text = "", encripted_text;
    std::string name_file = "vigenere.txt";
    std::ifstream archivo(name_file);
    if(!archivo.is_open()){
        std::cerr << "Error al abrir el fichero" << std::endl;
        return 1;
    }
    std::string aux;
    while(archivo >> aux){
        text += aux;
    }
    std::cout << "Palabra clave: ";
    std::cin >> key;
    std::cout << "Texto original: " << text << std::endl;
    key = AdaptText(key);
    text = AdaptText(text);
    std::cout << "Texto claro: " << text << std::endl;
    std::cout << "Clave: " << key << std::endl;
    int option;
    std::cout << "Encriptar - Desencriptar 0 / 1: ";
    std::cin >> option;
    if(option == 0)
        encripted_text = EncriptaVigenere(text, key);
    else if(option == 1){
        encripted_text = DesencriptaVigenere(text, key);
    }
    else{
        std::cerr << "Opcion invalida" << std::endl;
        return 2;
    }
    std::cout << "Texto cifrado: " << encripted_text << std::endl;
    return 0;
 }