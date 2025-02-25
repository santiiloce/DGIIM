/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Funcion que devuelve el doble factorial de un numero dado de la 
 *        forma --> n!! = n × (n - 2) × (n - 4) × …. 
 * The program takes directly the input and prints the output
 */

int double_factorial (int x){
  int factorial = 1;
  if (x < 0 && x > 12)
    return -1;
  for (int i = x; i > 0; i -= 2){
  	factorial *= i;
  }
  return factorial;
}

