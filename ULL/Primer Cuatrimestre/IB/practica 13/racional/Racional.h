
#include <iostream>
#include <string>
#include <fstream>

class Racional{
public:
    /**
     * @brief Construct a default new Racional object
     * 
     */
    Racional(): num(0), denom(1) {}

    /**
     * @brief Construct a new Racional object
     * 
     * @param new_num 
     * @param new_denom 
     */
    Racional(int new_num, int new_denom): num(new_num), denom(new_denom){}

    /**
     * @brief Get the Num object
     * 
     * @return int 
     */
    int GetNum(){ return num; }

    /**
     * @brief Get the Denom object
     * 
     * @return int 
     */
    int GetDenom(){ return denom; }

    /**
     * @brief Cambia el valor de num
     * 
     * @param new_num 
     */
    void PutNum(int new_num){ this->num = new_num; }

    /**
     * @brief Cambia el valor de denom
     * 
     * @param new_denom 
     */
    void PutDenom(int new_denom){ this->denom = new_denom; }

    /**
     * @brief Get the Number object being a string type
     * 
     * @return std::string 
     */
    std::string GetNumber();

    std::string GetNumber(Racional other);

    void Print(Racional other);
    /**
     * @brief Muestra por pantalla la instancia de la clase
     * 
     */
    void Print();

    /**
     * @brief Get the To File object
     * 
     * @param file 
     */
    void GetToFile(std::string file);

    /**
     * @brief Cambia los valores de la clase apartir del numerador y denominador
     *        dados
     * 
     * @param new_num 
     * @param new_denom 
     */
    void PutNumberInt(int new_num, int new_denom);
    
    /**
     * @brief Cambia los valores de la clase apartir de un racional de tipo
     *        string
     * 
     * @param number 
     */
    void PutNumberString(std::string number);

    /**
     * @brief Cambia los valores mediante los valores de un archivo
     * 
     * @param file 
     */
    void PutNumberStringFile(std::string file);

    /**
     * @brief Simplifica el racional dado pasándolo a la forma irreducible
     * 
     */
    void Simplifica();

    /**
     * @brief Redefine el operador +
     * 
     * @param other 
     * @return Racional 
     */
    Racional operator+(Racional other);

    /**
     * @brief Redefine el operador -
     * 
     * @param other 
     * @return Racional 
     */
    Racional operator-(Racional other);

    /**
     * @brief Redefine el operador *
     * 
     * @param other 
     * @return Racional 
     */
    Racional operator*(Racional other);
    
    /**
     * @brief Redefine el operador /
     * 
     * @param other 
     * @return Racional 
     */
    Racional operator/(Racional other);

    /**
     * @brief Redefine el operador ==
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==( Racional other);

    /**
     * @brief Redefine el operador =
     * 
     * @param other 
     */
    void operator=( Racional other);

    /**
     * @brief Muestra todas las posibles operaciones que se pueden realizar junto
     *        a otra variable de tipo racional
     * 
     * @param other 
     */
    std::string EjemplificaOperaciones(Racional other);

private:
    int num;
    int denom;

    /**
     * @brief Calcula el mcd de los numeros a y b
     * 
     * @param a 
     * @param b 
     * @return int 
     */
    int gcd(int a, int b);

    /**
     * @brief Calcula el mcm de los numeros num1 y num2
     * 
     * @param num1 
     * @param num2 
     * @return int 
     */
    int MinimoComunMultiplo(int num1, int num2);
};