/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 08 2024
 * @brief Funcion que devuelve el factorial de un numero dado
 * The program takes directly the input and prints the output
 */
int factorial (int n){
  int factorial = 1;
  if (n < 0 && n > 19)
    return -1;
  for (int i = 1; i <= n; i++){
  	factorial *= i;
  }
  return factorial;
}
