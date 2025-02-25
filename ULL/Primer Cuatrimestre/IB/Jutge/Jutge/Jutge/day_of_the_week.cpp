/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Informatica Basica
 *
 * @author Santiago Lopez Cerro
 * @date Nov 08 2024
 * @brief Funcion que dada una fecha determina el tipo de dia que era 
 * The program takes directly the input and prints the output
 */
#include <string>
#include <iostream>
#include <cmath>

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


std::string day_of_the_week (int d, int m, int y){
  if(!is_valid_date(d, m, y)) // Compruebo que sea una fecha valida
    return "Fecha Inválida";
  //Aplico la congruencia de Zeller
  if ( m == 1){
    y--;
    m = 13;
  }
  if ( m == 2){
  	y--;
  	m = 14;
  }
  
  int j = floor(y / 100.0); // siglo 
  int k = y % 100;  // anio del siglo
  int resultado = d + (((m+1)*26)/10) + k + k/4 + j/4 + 5*j;
  resultado = resultado % 7;
  switch (resultado){
  	case 0:
  	  return "Saturday";
  	  break;
  	case 1:
  	  return "Sunday";
  	  break;
  	case 2:
  	  return "Monday";
  	  break;
  	case 3:
  	  return "Tuesday";
  	  break;
  	case 4:
  	  return "Wednesday";
  	  break;
  	case 5:
  	  return "Thursday";
  	  break;
  	case 6:
  	  return "Friday";
  	  break;
  }
}
  	  
 
