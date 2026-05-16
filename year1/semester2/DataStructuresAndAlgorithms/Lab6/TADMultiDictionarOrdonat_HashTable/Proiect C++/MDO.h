#pragma once
#include <vector>
#include <utility>
#include <list>
using namespace std;

typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

struct Pereche
{
	TCheie cheie;
	vector<TValoare> valori;
};

class MDO {
	friend class IteratorMDO;
    private:

	int m;
	list<Pereche>* l;
	Relatie relatie;

	/**
	 * Theta (1)
	 * @param c Cheia
	 * @return locatia unde se vor dispersa elementele cu cheia c
	 * pre: m > 0, c este o cheie valida
	 * post: hash(TCheie c) este locatia unde se vor dispersa elementele cu cheia c
	 */
	int hash(TCheie c) const;

    public:

	/**
	 * Theta (1)
	 * constructorul implicit al MultiDictionarului Ordonat
	 * @param r Relatia dupa care sunt ordonate elementele dictionarului
	 * pre: r este o relatie, r: TCheie x TValoare -> {adevarat, fals}
	 * post: s-a creat MDO cu relatia r, MDO este vid
	 */
	MDO(Relatie r);

	/**
	 * BC: O (1), WC: O (n), AC: O (1)
	 * adauga o pereche (cheie, valoare) in MDO
	 * @param c Cheia
	 * @param v Valoarea
	 * Adauga perechea <c, v> in dictionar
	 * pre: mdo - MDO
	 * post:  mdo' = mdo + <c, v>, perechea <c, v> este adaugata in multidictionarul cu relatia r
	 */
	void adauga(TCheie c, TValoare v);

	/**
	 * BC: O (1), WC: O (n), AC: O (1)
	 * cauta o cheie si returneaza vectorul de valori asociate
	 * @param c Cheia
	 * @return Vectorul de elemente cu cheia c
	 * pre: mdo - MDO
	 * post: Vector: TValoare - lista de valori asociate cheii c in multidictionarul ordonat mdo
	 */
	vector<TValoare> cauta(TCheie c) const;

	/**
	 * BC: O (1), WC: O (n), AC: O (1)
	 * sterge o cheie si o valoare
	 * returneaza adevarat daca s-a gasit cheia si valoarea de sters
	 * @param c Cheia
	 * @param v Valoarea
	 * @return true daca stergerea s-a realizat cu succes, false daca nu s-a realizat stergerea (nu s-a gasit elementul cu cheia c si valoarea v)
	 * pre: mdo - MDO
	 * post: mdo' - perechea <c, v> este eliminata din multidictionar
	 */
	bool sterge(TCheie c, TValoare v);

	/**
	 * Theta (n + m)
	 * returneaza numarul de perechi (cheie, valoare) din MDO
	 * @return Dimensiunea dictionarului
	 * pre: mdo - MDO
	 * post: mdo.dim() este dimensiunea multi-dictionarului ordonat
	 */
	int dim() const;

	//alpha = n/m -> factorul de incarcare al tabelei = nr mediu de elemente memorate intr-o inlantuire
	/**
	 * BC: O (1), WC: O (m), AC: O (1 + m/n)
	 * verifica daca MultiDictionarul Ordonat e vid
	 * @return True/False daca dictionarul este/nu este vid
	 * pre: mdo - MDO
	 * post: mdo.vid() este True/False daca dictionarul este/nu este vid
	 */
	bool vid() const;

	/**
	 * Theta (1)
	 * se returneaza iterator pe MDO
	 * iteratorul va returna perechile in ordine in raport cu relatia de ordine
	 * @return Iteratorul pe MDO
	 * pre: mdo - MDO
	 * post: it este un iterator pe mdo
	 */
	IteratorMDO iterator() const;

	/**
	 * Theta (1)
	 * destructorul
	 */
	~MDO();

};
