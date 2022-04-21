#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Fecha_mayor.h" 



int main(){
  int dia,mes,anio,f1,f2;
  Fecha_mayor p1(f1,f2);
  p1.pedirDatos();
  p1.mayor();
  p1.mostrar();
  system("pause");
  return 0;
}