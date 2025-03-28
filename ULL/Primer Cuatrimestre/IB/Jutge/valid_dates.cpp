/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Informatica Basica
 *
 * @author Santiago Lopez Cerro
 * @date Nov 08 2024
 * @brief Funcion que determina si una fecha es valida
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

bool is_valid_date(int d, int m, int y){
  bool valid = true;
  
  if (m < 1 || m > 12)
    return false;
    
  if (m > 7) // Aniado uno para que se siga cumpliendo la alternancia
    m++; 	 // Habiendo comprobado anteriormente que es un mes valido
  if (m % 2 != 0){
  	if (d < 1 || d > 31)
  	  return false;
  }
  else{ 
    if (m == 2){
      if (is_leap_year(y)){
        if (d < 1 || d > 29)
      	  return false;
      }
      else{ 
        if (d < 1 || d > 28)
      	  return false;
      }
    }
    else{ 
      if (d < 1 || d > 30)
      	  return false;
    }
  }
      	  
  return true;
         
}
