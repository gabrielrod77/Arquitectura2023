#include <iostream>
#include <fstream>

using namespace std;

int main(){
	int secuencia[32],i,bloque[5], longSec,dir, ultEnc[12], j, k, ultDir[12], bloq;
	bool encont;
	bloque[0] = -1;
	bloque[1] = -1;
	bloque[2] = -1;
	bloque[3] = -1;
	ultEnc[0] = 0;
	ultEnc[1] = -1;
	ultEnc[2] = 2;
	ultEnc[3] = -1;
	ifstream entrada;
	ofstream salida;
	entrada.open("entradacpp.txt");
	salida.open("salidacpp.txt");
	i = 0;
	while(entrada >> secuencia[i]){
		//cout << secuencia[i] << endl;
		i++;
	}
	longSec = i;
	salida << "DBMA AF      CBC" << endl;
	salida << "          B0 B1 B2 B3" << endl;
	for(i=0;i<=longSec-1;i++){
		dir = secuencia[i]%4;
		salida << secuencia[i] << " ";
		if(bloque[dir] == secuencia[i]){
			salida << "acierto ";
		} else {
			salida << "fallo   ";
		}
		bloque[dir] = secuencia[i];
		salida << bloque[0] << " " << bloque[1] << " " << bloque[2] << " " << bloque[3] << endl;
		//cout << dir << endl;
	}
	salida << endl;
	bloque[0] = -1;
	bloque[1] = -1;
	bloque[2] = -1;
	bloque[3] = -1;
	salida << "DBMA AF      CBC" << endl;
	salida << "          C0 C0 C1 C1" << endl;
	for(i=0;i<=longSec-1;i++){
		dir = (secuencia[i]%2) * 2;
		//cout << dir << endl;
		salida << secuencia[i] << " ";
		if(bloque[dir] == secuencia[i]){
			salida << "acierto ";
			ultEnc[dir] = dir + 1; 
		} else
		if(bloque[dir + 1] == secuencia[i]){
			salida << "acierto ";
			ultEnc[dir] = dir; 
		} else {
			salida << "fallo   ";
			bloque[ultEnc[dir]] = secuencia[i];
			if(ultEnc[dir]%2 == 1){
				ultEnc[dir] -= 1;
			} else {
				ultEnc[dir] += 1;
			}
		}
		salida << bloque[0] << " " << bloque[1] << " " << bloque[2] << " " << bloque[3] << endl;
		//cout << dir << endl;
	}
	salida << endl;
	bloque[0] = -1;
	bloque[1] = -1;
	bloque[2] = -1;
	bloque[3] = -1;
	for(i=0;i<=7;i++){
		ultEnc[i] = -1;
		ultDir[i] = -1;
	}
	dir = 0;
	salida << "DBMA AF      CBC" << endl;
	salida << "          B0 B1 B2 B3" << endl;
	for(i=0;i<=longSec-1;i++){
		salida << secuencia[i] << " ";
		encont = false;
		j = 0;
		while(!(encont)){
			if(bloque[j] == secuencia[i]){
				salida << "acierto ";
				bloq = j;
				encont = true;
			}
			if(bloque[j] == -1){
				salida << "fallo   ";
				if(j <= 3){
					bloque[j] = secuencia[i];
					bloq = j;
				}  else {
					bloque[ultDir[0]] = secuencia[i];
					bloq = ultDir[0];
					ultEnc[0] = secuencia[i]; 				
				}
				encont = true;
			}
			j++;
		}
		encont = false;
		j = 0;
		while(!(encont)){
			if(ultEnc[j] == -1){
				ultEnc[j] = secuencia[i];
				ultDir[j] = bloq;
				encont = true;
			} else if(ultEnc[j] == secuencia[i]){
				k = j;
				while(ultEnc[k+1] != -1){
					ultEnc[k] = ultEnc[k+1];
					ultDir[k] = ultDir[k+1];
					k++; 
				}
				ultEnc[k] = secuencia[i];
				ultDir[k] = bloq;
				encont = true;
			}
			j++;
		}
		salida << bloque[0] << " " << bloque[1] << " " << bloque[2] << " " << bloque[3] << endl;
		//cout << dir << endl;
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
