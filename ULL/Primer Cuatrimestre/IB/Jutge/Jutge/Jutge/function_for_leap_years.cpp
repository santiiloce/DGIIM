/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 08 2024
 * @brief Funcion que determina si un año es bisiesto
 * The program takes directly the input and prints the output
 */
bool is_leap_year(int year){
  bool bisiesto = false;
  if (year % 4 == 0)
     bisiesto = true;
     
  if (year % 100 == 0 && year % 400 != 0) // Considero excepcion
    bisiesto = false;
  return bisiesto;
}
