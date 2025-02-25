/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @brief Clase que permite realizar diferentes cálculos con numeros racionales
 * The program takes directly the input and prints the output
 */

#include "Racional.h"
#include <string>
#include <iostream>

std::string Racional::GetNumber(){
    std::string numero = std::to_string(num) + "/" + std::to_string(denom);
    return numero;
}

std::string Racional::GetNumber(Racional other){
    std::string cadena = other.GetNumber();
    return cadena;
}

void Racional::Print(Racional other){
    std::cout << this->GetNumber(other) << std::endl;
}

void Racional::Print(){
    std::cout << this->GetNumber() << std::endl;
}



void Racional::GetToFile(std::string file){
    std::ofstream archivo(file);
    if(!archivo.is_open()){
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }
    archivo << this->GetNumber() << std::endl;
    archivo.close();
}

void Racional::PutNumberInt(int new_num, int new_denom){
    this->num = new_num;
    if(new_denom == 0){
        std::cerr << "Valor nulo inválido" << std::endl; 
        return;
    }
    this->denom = new_denom;
}

void Racional::PutNumberString(std::string number){
    //Inicialmente realizo una serie de comprobaciones de que sea un formáto valido
    int pos_i, pos_j;
    bool es_valido = true;
    for( pos_i = 0; pos_i < number.size() && number.at(pos_i) != '/'; pos_i++){ 
        char aux = number.at(pos_i);
        if(aux < '0' || aux > '9'){
            es_valido = false;
        }
    }
    if(pos_i == number.size() - 1){
        es_valido = false;
    }

    for(pos_j = pos_i + 1; pos_j < number.size(); pos_j++){
        char aux = number.at(pos_j);
        if(aux < '0' || aux > '9'){
            es_valido = false;
        }
    }

    if(!es_valido){
        std::cerr << "Formato invalido y/o caracter invalido" << std::endl;
        return;
    }

    bool num_found = false;
    for(int i = 0; i < number.size(); i++){
        std::string aux = "";
        while(i < number.size()){
            if(number.at(i) == '/'){
                break;
            } 
            aux +=number.at(i);
            i++;
        }
        if(!num_found){
          this->num = std::stoi(aux);
          num_found = true;
        }
        else{
            if(std::stoi(aux) == 0){
              std::cerr << "Valor nulo inválido" << std::endl; 
              return;
            }
            this->denom = std::stoi(aux);
        }
    }
}

void Racional::PutNumberStringFile(std::string file){
    std::ofstream archivo(file);
    if(!archivo.is_open()){
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }
    std::string numero;
    archivo << numero;
    this->PutNumberString(numero);
}

int Racional::gcd(int a, int b){
        if ( a < 0 || b < 0 || (a == 0 && b== 0))
            return -1;
        if (b > a){
            int aux = a;
            a = b;
            b = aux;
        }
        if (b == 0) // Excepcion del cero
            return a;
        int diferencia = a % b;
        while(diferencia != 0){
            a = b;
            b = diferencia;
            diferencia = a % b;
        }
        return b;
}

int Racional::MinimoComunMultiplo (int num1, int num2){
  long int mcm;
  if (this->gcd(num1,num2) == 1)
    mcm = num1*num2;	// Si su mcd == 1 entoces su mcd sera su producto
  else 
    mcm = (num1/gcd(num1,num2))*num2;
  return mcm;
}

void Racional::Simplifica(){
    int aux = gcd(this->num, this->denom);
    if(aux != 1){
        this->num /= aux;
        this->denom /= aux;
    }
}

Racional Racional::operator+(Racional other){
    Racional sol;
    int new_num = this->num * other.GetDenom() + other.GetNum() * this->denom;
    int new_denom = this->denom * other.GetDenom();
    sol.PutNumberInt(new_num, new_denom);
    sol.Simplifica();
    return sol;
}

Racional Racional::operator-(Racional other){
    Racional sol;
    int new_num = this->num * other.GetDenom() - other.GetNum() * this->denom;
    int new_denom = this->denom * other.GetDenom();
    sol.PutNumberInt(new_num, new_denom);
    sol.Simplifica();
    return sol;
}

Racional Racional::operator*(Racional other){
    Racional sol;
    int new_num = this->num * other.GetNum();
    int new_denom = this->denom * other.GetDenom();
    sol.PutNumberInt(new_num, new_denom);
    sol.Simplifica();
    return sol;
}

Racional Racional::operator/( Racional other){
    Racional aux(other.GetDenom(), other.GetNum());
    return (*this)*aux;
}

bool Racional::operator==(Racional other){
    Racional aux = *this;
    aux.Simplifica();
    other.Simplifica();
    bool num = (aux.GetNum() ==  other.GetNum());
    bool denom = (aux.GetDenom() == other.GetDenom());
    return ( num && denom ); 
}

void Racional::operator=(Racional other){
    this->num = other.GetNum();
    this->denom = other.GetDenom();
}

std::string Racional::EjemplificaOperaciones(Racional other){
    std::string solucion = "";
    Racional aux = *this;
    solucion += aux.GetNumber() + " + " + other.GetNumber() + " = ";
    solucion += (aux + other).GetNumber() + "\n";
    solucion += aux.GetNumber() + " - " + other.GetNumber() + " = ";
    solucion += (aux - other).GetNumber() + "\n";
    solucion += aux.GetNumber() + " * " + other.GetNumber() + " = ";
    solucion += (aux * other).GetNumber() + "\n";
    solucion += aux.GetNumber() + " / " + other.GetNumber() + " = ";
    solucion += (aux / other).GetNumber() + "\n";
    solucion += aux.GetNumber() + " == " + other.GetNumber() + " = ";
    if( aux == other){
        solucion += "true";
    }
    else{
        solucion += "false";
    }
    solucion += "\n";
    return solucion;
}

/*
int main(){
    Racional example;
    example.PutNumberString("9/8");
    example.Print();
    return 0;
}
*/







