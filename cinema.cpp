/*
                       __
	                 .'  '.
	             _.-'/  |  \
	,        _.-"  ,|  /  0 `-.
	|\    .-"       `--""-.__.'=====================-,
	\ '-'`        .___.--._)=========================|
	 \            .'      |                          |
	  |     /,_.-'        |  CODIFICADO POR:         |
	_/   _.'(             |                          |
	/  ,-'\  \            |          Jairo Medrano   |
	\  \   `-'            |  ⌨                       |
	 `-'                  '--------------------------'
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ios;
using std::ofstream;
using std::ifstream;
using std::string;
using std::setfill;
using std::setw;

string nombreArchivo = "data.txt";

typedef struct{
	int space;
	int listNumber;
	string idMovie;
	string nameMovie;
	int ticketSales;
	double recaudation;
	string launchDate;
}Peliculas;

typedef struct{
	int numeroFila;
	int tamanoEspacio;
}Disponibles;

vector <Peliculas> pelis;
vector <Disponibles> listaDisponibles;

void pausarSistema(){
	cout<<"\nPresione la tecla <ENTER> para continuar....";
	getchar();
}

string validarIngreso(int maximoCaracteres, string text){
	string datoIngreso = "";
	cout<<text;
	cin>>datoIngreso;
	cout<<endl;
	if(datoIngreso.length() > maximoCaracteres){
			cout<<"Error: Ha ingresado mas caracteres de los permitidos. Intentelo nuevamente";
			pausarSistema();
			return validarIngreso(maximoCaracteres, text);
	}
	return datoIngreso;
}

bool lineaDisponible(int fileNumber){
		if(listaDisponibles.size()>0){
			for(int i = 0; i < listaDisponibles.size(); i++){
				if(fileNumber == listaDisponibles[i].numeroFila){
					return true;
				}
			}
		}
		return false;
}

void ingresarNuevaData(){
	string linea = "";
	string new_idMovie = "";
	string new_nameMovie = "";
	string new_ticketSales = "";
	string new_recaudation = "";
	string new_launchDate = "";
	system("clear");
	cout<<"################################################################################"<<endl;
	cout<<"#                                    CINEMAXAD                                 #"<<endl;
	cout<<"################################################################################"<<endl<<endl;
	cout<<"                             INGRESANDO NUEVA PELICULA                          \n";
	new_idMovie = validarIngreso(4, "        Ingrese el identificador de la nueva Pelicula (4): ");
	new_nameMovie = validarIngreso(20, "        Ingrese el nombre (20): ");
	new_ticketSales = validarIngreso(8, "        Ingrese la cantidad de boletos vendidos: ");
	new_recaudation = validarIngreso(13, "        Ingrese cuanto se ha recaudado: ");
	new_launchDate = validarIngreso(11, "        Ingrese la fecha de estreno (dd-mmm-aaaa): ");	

	bool nuevoAlmacenado = false;
	bool archivado = false;
	ofstream archivoDatos(nombreArchivo);
	int totalLines = (pelis.size()+listaDisponibles.size());

	for(int i = 0; i < totalLines; i++){
		archivado = false;
		if(lineaDisponible(i+1)){
			if(!nuevoAlmacenado){
				archivoDatos<<"|"<<setfill('0')<<setw(2)<<"00"<<"|"<<setfill('0')<<setw(3)<<(i+1)<<"|"<<setfill(' ')<<setw(4)<<new_idMovie<<"|"<<setfill(' ')<<setw(20)<<new_nameMovie<<"|"<<setfill('0')<<setw(8)<<new_ticketSales<<"|"<<setfill('0')<<setw(13)<<new_recaudation<<"|"<<setfill(' ')<<setw(11)<<new_launchDate<<"|"<<endl;
				nuevoAlmacenado = true;
				archivado = true;
				listaDisponibles.pop_back();
			}else{
				archivoDatos<<"|"<<setfill('0')<<setw(2)<<"62"<<"|"<<setfill('0')<<setw(3)<<(i+1)<<"|(empty)..."<<endl;
				archivado = true;
			}
		}else{
			for(int j = 0; j<pelis.size(); j++){
				if(pelis[j].listNumber == (i+1)){
					archivoDatos<<"|"<<setfill('0')<<setw(2)<<pelis[j].space<<"|"<<setfill(' ')<<setw(3)<<pelis[j].listNumber<<"|"<<pelis[j].idMovie<<"|"<<pelis[j].nameMovie<<"|"<<setfill(' ')<<setw(8)<<pelis[j].ticketSales<<"|"<<setfill(' ')<<setw(13)<<pelis[j].recaudation<<"|"<<pelis[j].launchDate<<"|"<<endl;
					archivado = true;
				}
			}
		}
		if(!archivado){
			archivoDatos<<"|"<<setfill('0')<<setw(2)<<"62"<<"|"<<setfill('0')<<setw(3)<<(i+1)<<"|(empty)..."<<endl;
		}
	}
	if(!nuevoAlmacenado){
		archivoDatos<<"|"<<setfill('0')<<setw(2)<<"00"<<"|"<<setfill('0')<<setw(3)<<totalLines<<"|"<<setfill(' ')<<setw(4)<<new_idMovie<<"|"<<setfill(' ')<<setw(20)<<new_nameMovie<<"|"<<setfill('0')<<setw(8)<<new_ticketSales<<"|"<<setfill('0')<<setw(13)<<new_recaudation<<"|"<<setfill(' ')<<setw(11)<<new_launchDate<<"|"<<endl;	
	}

	cout<<"\n     Nuevo registro almacenado exitosamente."<<endl;
	pausarSistema();
	archivoDatos.close();
}

void mostrarData(){
	cout<<"---------------------------------------------------------------------"<<endl;
	cout<<"|sp|nli|  id| Nombre Pelicula    |Vendidos| Recaudacion | Estreno   |"<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
	if(pelis.size()>0){
		for(int i = 0; i<pelis.size(); i++){
			cout<<"|"<<setfill(' ')<<setw(2)<<pelis[i].space<<"|"<<setfill(' ')<<setw(3)<<pelis[i].listNumber<<"|"<<pelis[i].idMovie<<"|"<<pelis[i].nameMovie<<"|"<<setfill(' ')<<setw(8)<<pelis[i].ticketSales<<"|"<<setfill(' ')<<setw(13)<<pelis[i].recaudation<<"|"<<pelis[i].launchDate<<"|"<<endl;
			cout<<"---------------------------------------------------------------------"<<endl;
		}
	}else{
		cout<<"No hay datos para mostrar";
	}
}

Disponibles crearDisponible(int numeroFila, int espacioDisponible){
	Disponibles disp = {
		numeroFila ,
		espacioDisponible
	};
	return disp;
}

Peliculas crearPelicula(string linea){
	Peliculas peli = {
		stoi(linea.substr(1,2)),
		stoi(linea.substr(4,3)),
		linea.substr(8,4),
		linea.substr(13,20),
		stoi(linea.substr(34,8)),
		stod(linea.substr(43,13)),
		linea.substr(57,11)
	};
	return peli;
}

void mostrarListaDisponibles(){
	if(listaDisponibles.size()<1){
		cout<<"\nNo hay registros vacios en el fichero de guardado.\n";
	}
	for(int i = 0; i < listaDisponibles.size(); i++){
		cout<<"Posicion en pila: "<<i<<"\nNumero de linea en fichero: "<<listaDisponibles[i].numeroFila<<"\nEspacio disponible: "<<listaDisponibles[i].tamanoEspacio<<endl<<endl;
	}
}

void almacenarData(string linea){
	string spaceInLine = linea.substr(1,2);
	int availableSpace = stoi(spaceInLine);
	int numberLine = stoi(linea.substr(4,3));
	if(spaceInLine == "00"){
		pelis.push_back(crearPelicula(linea));
	}else{
		listaDisponibles.push_back(crearDisponible(numberLine, availableSpace));
	}
}

bool yesno(string text){
	system("clear");
	int seleccion = 0;
	bool resp = false;
	while(seleccion != 1 && seleccion != 2){
		cout<<text<<endl;
		cout<<"1.Si\n2.No\n\nIngrese una opcion: ";
		cin>>seleccion;
		getchar();
		if(seleccion == 1){
			resp = true;
		}else if(seleccion == 2){
			resp = false;
		}else{
			cout<<"\nError: la opcion ingresada es invalida. Intente nuevamente.\n\n";
		}
	}
	return resp;
}

void leerData(){
	pelis.clear();
	listaDisponibles.clear();
	string linea = "";
	ifstream archivoDatos(nombreArchivo);

	if(archivoDatos.is_open()){
		while(getline(archivoDatos, linea)){
			almacenarData(linea);
		}
		archivoDatos.close();
	}else{
		cout<<"Error: No se pudo leer el archivo";
	}

	cout<<"Cantidad elementos existentes: "<<pelis.size()<<endl;
	cout<<"Cantidad de registros vacios: "<<listaDisponibles.size()<<endl<<endl;

	mostrarData();
	pausarSistema();
	system("clear");
	if(yesno("Desea desplegar los registros vacios?")){
		cout<<endl;
		mostrarListaDisponibles();
	}
}

void readData(){
	pelis.clear();
	listaDisponibles.clear();
	string linea = "";
	ifstream archivoDatos(nombreArchivo);

	if(archivoDatos.is_open()){
		while(getline(archivoDatos, linea)){
			almacenarData(linea);
		}
		archivoDatos.close();
	}else{
		cout<<"Error: No se pudo leer el archivo";
	}
}
void menu(){
	int opcionMenu = 0;
	system("clear");
	cout<<"################################################################################"<<endl;
	cout<<"#                                    CINEMAXAD                                 #"<<endl;
	cout<<"################################################################################"<<endl<<endl;
	cout<<"                                    Bienvenido                               \n"
		<<"                  Que desea realizar?\n\n"
		<<"                        1. Ver los registros existentes.\n"
		<<"                        2. Ver los detalles de un registro.\n"
		<<"                        3. Agregar un nuevo registro.\n"
		<<"                        4. Eliminar un registro.\n"
		<<"                        5. Salir.\n\n"
		<<"                  Ingrese una opcion: ";
		cin>>opcionMenu;
		getchar();
	switch(opcionMenu){
		case 1:
			system("clear");
			leerData();
			pausarSistema();
		break;
		case 2:
			cout<<"Aun estamos trabajando en ello."<<endl;
			pausarSistema();
		break;
		case 3:
			system("clear");
			ingresarNuevaData();
		break;

		case 4:
			cout<<"Aun estamos trabajando en ello."<<endl;
                        pausarSistema();
		break;

		case 5:
			if(yesno("?Desea abandonar la aplicacion?")){
				cout<<"Saliendo...\n";
				pausarSistema();
				exit(0);
			}
		break;
	}
}

int main(){
	readData();
	while(true){
		menu();
	}
	return 0;
}
