#include "nodoc++.h"
#include <iostream>
#ifndef LISTA_H
#define LISTA_H

template <typename Elemento>
class Lista{
	private:
		int longitud;
		Nodo<Elemento> *primero;
		Nodo<Elemento> *ultimo;
	public:
		void construir();
		void setLongitud(int n);
		void setPrimero(Nodo<Elemento>* prim);
		void setUltimo(Nodo<Elemento>* ult);
		int getLongitud();
		Nodo<Elemento>* getPrimero();
		Nodo<Elemento>* getUltimo();
		void invertir();
		void modificar(Elemento elem, int pos);
		void eliminar(int pos);
		Elemento consultar(int pos);
		void insertar(Elemento elem, int pos);
		void mediaMovil(int vent);
		void ordenar(int asc);
		void vaciar();
		void destruir();
};

#endif



using namespace std;

template <typename Elemento>
void Lista<Elemento>::construir(){
	longitud = 0;
	primero = NULL;
	ultimo = NULL;
}

template <typename Elemento>
void Lista<Elemento>::setLongitud(int n){
	longitud = n;
}

template <typename Elemento>
void Lista<Elemento>::setPrimero(Nodo<Elemento>* prim){
	primero = prim;
}

template <typename Elemento>
void Lista<Elemento>::setUltimo(Nodo<Elemento>* ult){
	ultimo = ult;
}

template <typename Elemento>
int Lista<Elemento>::getLongitud(){
	return longitud;
}

template <typename Elemento>
Elemento Lista<Elemento>::consultar(int pos){
	int i;
	Elemento valor;
	Nodo<Elemento> *aux;
	if (longitud >= 1) {
		aux = primero;
		for(i = 2; i <= pos; i++){
			aux = aux->getProx();
		}
		valor = aux->getInfo();
	} else {
	valor = -1;
	}
	return(valor);
}

template <typename Elemento>
void Lista<Elemento>::insertar(Elemento elem, int pos){
	int i;
	if(pos > 0 && pos <= longitud + 1){
		Nodo<Elemento> *nuevo;
		Nodo<Elemento> *actual;
		actual = primero;
		nuevo = new Nodo<Elemento>();
		nuevo->setInfo(elem);
		if(pos == 1){
			if(longitud >= 1){
				nuevo->setProx(primero);
			}
			primero = nuevo;
		} else {
		for(i=3;i<=pos;i++){
			actual = actual->getProx();
		}
		if(pos < longitud + 1){
			nuevo->setProx(actual->getProx());
		}
		actual->setProx(nuevo);
		}
		if(pos == longitud + 1){
			ultimo = nuevo;
		}
		longitud = longitud + 1;
	}
}

template <typename Elemento>
void Lista<Elemento>::modificar(Elemento elem, int pos){
	int i;
	if(pos > 0 && pos <= longitud){
		Nodo<Elemento> *actual;
		actual = primero;
		for(i=2;i<=pos;i++){
			actual = actual->getProx();
		}
		actual->setInfo(elem);
	}
}

template <typename Elemento>
void Lista<Elemento>::eliminar(int pos){
	int i;
	if(pos > 0 && pos <= longitud){
		Nodo<Elemento> *actual;
		Nodo<Elemento> *posterior;
		actual = primero;
		if(pos == 1){
			if(longitud >= 2){
				actual = actual->getProx();
			}
			delete primero;
			primero = actual;
		} else {
		posterior = actual->getProx();
		for(i=3;i<=pos;i++){
			actual = actual->getProx();
			posterior = actual->getProx();
		}
		posterior = posterior->getProx();
		delete actual->getProx();
		actual->setProx(posterior);
		}
		longitud = longitud - 1;
	}
}

template <typename Elemento>
void Lista<Elemento>::mediaMovil(int vent){
	int sumas,i,j;
	float result = 0;
	sumas = longitud - vent + 1;
	for(i=1;i<=sumas;i++){
		for(j=i;j<=vent+i-1;j++){
			result = consultar(j) + result;
			//cout << result << endl;
		}
		result = result/vent;
		cout << result << endl;
		result = 0;
	}

}

template <typename Elemento>
void Lista<Elemento>::invertir(){
	Elemento valA,valB;
	int i,mitadL;
	if(longitud >= 2){
		mitadL = longitud/2;
		for(i=1;i<=mitadL;i++){
			valA = consultar(i);
			valB = consultar(longitud - i + 1);
			modificar(valB,i);
			modificar(valA,longitud - i + 1);
		}
	}
}

template <typename Elemento>
void Lista<Elemento>::vaciar(){
	int i;
	for(i=1;i<=longitud;i++){
		eliminar(1);
	}
}

template <typename Elemento>
void Lista<Elemento>::ordenar(int asc){
	int i,j; 
	Elemento valor;
	for(i=1;i<=longitud-1;i++){
		for(j=i+1;j<=longitud;j++){
			if(consultar(i) < consultar(j)){
				valor = consultar(i);
				modificar(consultar(j),i);
				modificar(valor,j);
			}
		}
	}
	if(asc == 1){
		invertir();
	}		
}
