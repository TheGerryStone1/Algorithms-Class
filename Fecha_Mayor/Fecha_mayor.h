#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class Fecha_mayor {
	private:
		struct Fecha{
			int dia,mes,anio;
			}f1,f2, mayorFecha;

	public: 
		Fecha_mayor(int,int);
    	void pedirDatos();
    	void mayor();
    	void mostrar(); 
};

Fecha_mayor::Fecha_mayor
( int _f1, int _f2){
}

void Fecha_mayor::pedirDatos(){
	cout<<"Digite la Fecha1: "<<endl;
	cout<<"Dia: "; cin>>f1.dia;
	cout<<"Mes: "; cin>>f1.mes;
	cout<<"Anio: "; cin>>f1.anio;
	
	cout<<"\n\nDigite la Fecha2: "<<endl;
	cout<<"Dia: "; cin>>f2.dia;
	cout<<"Mes: "; cin>>f2.mes;
	cout<<"Anio: "; cin>>f2.anio;
}

void Fecha_mayor::mayor(){
	//Fecha mayorFecha;
    if(f1.anio == f2.anio){
		//Ahora, comprobamos los meses
		if(f1.mes ==f2.mes){
			//Por ultimo comprobamos los dias
			if(f1.dia == f2.dia){
				cout<<"\nAmbas fechas son iguales";
			}
			else if(f1.dia > f2.dia){
				mayorFecha = f1;
			}
			else{
				mayorFecha = f2;
			}
		}
		else if(f1.mes > f2.mes){
			mayorFecha = f1;
		}
		else{
			mayorFecha = f2;
		}
	}
	else if(f1.anio > f2.anio){
		mayorFecha = f1;
	}
	else{
		mayorFecha = f2;
	}
}

void Fecha_mayor::mostrar(){
	cout<<"\nMostrando fecha mayor: "<<mayorFecha.dia<<"/"<<mayorFecha.mes<<"/"<<mayorFecha.anio<<endl;
}