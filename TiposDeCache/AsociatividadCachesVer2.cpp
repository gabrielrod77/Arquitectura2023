#include <iostream>
#include <fstream>
#include "listac++.h"

using namespace std;

int main(){
	//int i,bloque[5], ultEnc[9], j, k, , bloq;
	int insert, i, longSec, dir, bloque[5], ultEnc[9], j, k , bloq, contFallos = 0, contAciertos = 0, mejorCache, masAciertos;
	Lista<int> secuencia, ultEncon, ultDir;
	bool encont;
	secuencia.construir();
	ultEncon.construir();
	ultDir.construir();
	for(i=0;i<=3;i++){
		bloque[i] = -1;
	}
	ultEnc[0] = 0;
	ultEnc[1] = -1;
	ultEnc[2] = 2;
	ultEnc[3] = -1;
	ifstream entrada;
	ofstream salida;
	entrada.open("entradacpp.txt");
	salida.open("salidacpp.txt");
	i = 0;
	while(entrada >> insert){
		secuencia.insertar(insert,1);
		//cout << secuencia.consultar(1) << endl;
	}
	secuencia.invertir();
	longSec = secuencia.getLongitud();
	salida << "DBMA AF      CBC" << endl;
	salida << "          B0 B1 B2 B3" << endl;
	for(i=1;i<=longSec;i++){                          // cache de correspondencia directa
		dir = secuencia.consultar(i) % 4;
		salida << secuencia.consultar(i) << " ";
		if(bloque[dir] == secuencia.consultar(i)){
			salida << "acierto ";
			contAciertos++;
		} else {
			salida << "fallo   ";
			contFallos++;
		}
		bloque[dir] = secuencia.consultar(i);
		salida << bloque[0] << " " << bloque[1] << " " << bloque[2] << " " << bloque[3] << endl;
		//cout << dir << endl;
	}
	salida << endl << "La cache de correspondencia directa produjo " << contFallos << " fallo(s) y " << contAciertos << " acierto(s)" << endl << endl;

	mejorCache = 1;
	masAciertos = contAciertos;
	
	for(i=0;i<=3;i++){
		bloque[i] = -1;
	}
	salida << "DBMA AF      CBC" << endl;
	salida << "          C0 C0 C1 C1" << endl;
	contFallos = 0;
	contAciertos = 0;
	for(i=1;i<=longSec;i++){           // cache asociativa por conjuntos
		insert = secuencia.consultar(i);
		dir = (insert % 2) * 2;
		//cout << dir << endl;
		salida << insert << " ";
		//cout << insert << "F" << endl;
		if(bloque[dir] == insert){
			salida << "acierto ";
			contAciertos++;
			ultEnc[dir] = dir + 1; 
		} else
		if(bloque[dir + 1] == insert){
			salida << "acierto ";
			contAciertos++;
			ultEnc[dir] = dir; 
		} else {
			salida << "fallo   ";
			contFallos++;
			j = ultEnc[dir];
			bloque[j] = insert;
			if((ultEnc[dir] % 2) == 1){
				ultEnc[dir] -= 1;
			} else {
				ultEnc[dir] += 1;
			}
		}
		salida << bloque[0] << " " << bloque[1] << " " << bloque[2] << " " << bloque[3] << endl;
		//cout << dir << endl;
	}
	salida << endl << "La cache asociativa por conjuntos produjo " << contFallos << " fallo(s) y " << contAciertos << " acierto(s)" << endl << endl;
	if(contAciertos > masAciertos){
		mejorCache = 2;
		masAciertos = contAciertos;
	} else if(contAciertos == masAciertos){
		mejorCache = 4;
	}	


	for(i=0;i<=3;i++){
		bloque[i] = -1;
	}
	
	dir = 0;
	salida << "DBMA AF      CBC" << endl;
	salida << "          B0 B1 B2 B3" << endl;
	contFallos = 0;
	contAciertos = 0;
	for(i=1;i<=longSec;i++){                       // cache completamente asociativa
		salida << secuencia.consultar(i) << " ";
		encont = false;
		j = 0;
		while(!(encont)){
			if(bloque[j] == secuencia.consultar(i)){
				salida << "acierto ";
				contAciertos++;
				bloq = j;
				encont = true;
			}
			if(bloque[j] == -1){
				salida << "fallo   ";
				contFallos++;
				if(j <= 3){
					bloque[j] = secuencia.consultar(i);
					bloq = j;
				}  else {
					bloque[ultDir.consultar(1)] = secuencia.consultar(i);
					bloq = ultDir.consultar(1);
					ultEncon.modificar(secuencia.consultar(i),1); 				
				}
				encont = true;
			}
			j++;
		}
		encont = false;
		j = 1;
		while(!(encont)){
			if(ultEncon.getLongitud() < j){
				ultEncon.insertar(secuencia.consultar(i),j);
				ultDir.insertar(bloq,j);
				encont = true;
			} else if(ultEncon.consultar(j) == secuencia.consultar(i)){
				k = ultEncon.consultar(j);
				insert = ultDir.consultar(j);
				ultEncon.eliminar(j);
				ultDir.eliminar(j);
				ultEncon.insertar(secuencia.consultar(i),ultEncon.getLongitud() + 1);
				ultDir.insertar(bloq, ultDir.getLongitud() + 1);
				encont = true;
			}
			j++;
		}
		salida << bloque[0] << " " << bloque[1] << " " << bloque[2] << " " << bloque[3] << endl;
		//cout << dir << endl;
	}
	salida << endl << "La cache completamente asociativa produjo " << contFallos << " fallo(s) y " << contAciertos << " acierto(s)" << endl << endl;
	if(contAciertos > masAciertos){
		mejorCache = 3;
		masAciertos = contAciertos;
	} else if(contAciertos == masAciertos){
		if(mejorCache == 1){
			mejorCache = 5;
		}
		if(mejorCache == 2){
			mejorCache = 6;
		}
		if(mejorCache == 4){
			mejorCache = 0;
		}
	}
	
	switch(mejorCache){
		case 0:
			salida << "las tres caches producen la misma cantidad de fallos y aciertos" << endl << endl;
		break;
		case 1:
			salida << "la cache de correspondencia directa tiene la menor cantidad de fallos" << endl << endl;
		break;
		case 2:
			salida << "la cache asociativa por conjuntos tiene la menor cantidad de fallos" << endl << endl;
		break;
		case 3:
			salida << "la cache completamente asociativa tiene la menor cantidad de fallos" << endl << endl;
		break;
		case 4:
			salida << "tanto la cache de correspondencia directa como la cache asociativa por conjuntos tienen la menor cantidad de fallos" << endl << endl;
		break;
		case 5:
			salida << "tanto la cache de correspondencia directa como la cache completamente asociativa tienen la menor cantidad de fallos" << endl << endl;
		break;
		case 6:
			salida << "tanto la cache completamente asociativa como la cache asociativa por conjuntos tienen la menor cantidad de fallos" << endl << endl;
		break;
		default:
		break;
	}
	

	salida << endl << "DBMA= direccion de bloque de memoria accedido" << endl;
	salida << "AF= Acierto o Fallo" << endl;
	salida << "CBC= contenido de los bloques de cache despues de cada acceso" << endl;
	salida << "Bn= bloque n" << endl;
	salida << "Cn= Conjunto n" << endl;
	salida << "-1= Bloque no contiene nada" << endl;
	salida << "* lo que esta en cada bloque de cache es memoria[n], NO es n" << endl;
	entrada.close();
	salida.close();
}
