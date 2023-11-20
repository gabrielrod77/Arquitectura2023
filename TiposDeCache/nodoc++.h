#include <iostream>
#ifndef NODO_H
#define NODO_H

template <typename Elemento>
class Nodo{
	private:
		Elemento info;
		Nodo<Elemento> *prox;
	public:
		void setInfo(Elemento n);
		void setProx(Nodo<Elemento>* P);
		Nodo<Elemento>* getProx();
		Elemento getInfo();
		void construir();
		void destruir();
};

#endif


template <typename Elemento>
Elemento Nodo<Elemento>::getInfo(){
	return info;
}

template <typename Elemento>
void Nodo<Elemento>::setInfo(Elemento n){
	info = n;
}

template <typename Elemento>
void Nodo<Elemento>::setProx(Nodo<Elemento>* P){
	prox = P;
}

template <typename Elemento>
Nodo<Elemento>* Nodo<Elemento>::getProx(){
	return prox;
}


