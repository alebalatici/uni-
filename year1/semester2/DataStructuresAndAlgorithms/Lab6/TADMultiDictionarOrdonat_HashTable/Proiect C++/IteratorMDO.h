#pragma once

#include "MDO.h"


class IteratorMDO{
	friend class MDO;
private:

	/**
	 * O (m + nlogn)
	 * constructorul primeste o referinta catre Container
	 * iteratorul va referi primul element din container
	 * @param dictionar MDO-ul de iterat
	 */
	IteratorMDO(const MDO& dictionar);

	/**
	 * contine o referinta catre containerul pe care il itereaza
	 */
	const MDO& dict;
	int pozCurent; //pozitia in lista principala (cea cu m pozitii)

	//list<Pereche>::iterator itLista; //pozitia in lista de dispersie, itLista - TCHeie, TValoare(vector)

	std::vector<TElem> elem_sortate;
	//int indexVector{}; //iterator in vectorul cu elemente care au cheia c


	/**
	 * BC: O (1), WC: O (m), AC: O (1 + m/n)
	 * pre: i - iterator container
	 * post: incrementam pozCurent cat timp nu s-a epuizat tabela si lista de la pozitia pozCurent e vida
	 */
	//void deplasare();
	//ex: daca la pozCurent = 5 am cheile {18, 31, 44} => itLista ma ajuta sa trec de la 18 la 31
	//inzexVector ajuta sa parcurgem valorile de la cheia 18 spre exemplu
public:

	/**
	 * Theta (1)
	 * reseteaza pozitia iteratorului la inceputul containerului
	 * pre: mdo - MDO
	 * post: iteratorul pointeaza la prima pozitie din dictionar
	 */
	void prim();

	/**
	 * Theta (1)
	 * muta iteratorul in container
	 * arunca exceptie daca iteratorul nu e valid
	 * pre: mdo - MDO
	 * post: iteratorul pointeaza la urmatoarea pozitie din dictionar
	 */
	void urmator();

	/**
	 * Theta (1)
	 * verifica daca iteratorul e valid (indica un element al containerului)
	 * @return True/False daca elementul curent e/nu e
	 * pre: mdo - MDO
	 * post: valid este True/False daca pozitia curenta este/nu este valida
	 */
	bool valid() const;

	/**
	 * Theta (1)
	 * returneaza valoarea elementului din container referit de iterator
	 * arunca exceptie daca iteratorul nu e valid
	 * @return elementul curent
	 * pre: mdo - MDO
	 * post: it.element() este elementul cu cheia si valoarea <TCheie, TValoare> din dictionar
	 */
	TElem element() const;
};

