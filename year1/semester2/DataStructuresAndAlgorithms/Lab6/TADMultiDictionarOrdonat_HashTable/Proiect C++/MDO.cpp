#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

using namespace std;

int MDO::hash(TCheie c) const
{
	return abs(c) % m;
}

MDO::MDO(Relatie r) {
	this->m = 13;
	this->relatie = r;
	this->l = new list<Pereche>[m];
}

void MDO::adauga(TCheie c, TValoare v) {
	//poz = indicele din lista unde se disperseaza c
	int poz = hash(c);
	bool gasit = false;
	//<7, x>, <20, y> sunt trimise in l[7]
	//verific daca la locatia poz exista elemente cu cheia c
	for (auto& p : this->l[poz])
	{
		if (p.cheie == c)
		{
			p.valori.push_back(v);
			gasit = true;
			break;
		}
	}
	//daca nu exista
	if (!gasit)
	{
		Pereche noua;
		noua.cheie = c;
		noua.valori.push_back(v);

		auto it = this->l[poz].begin();
		while (it != this->l[poz].end() && relatie(it->cheie, c))
		{
			++it;
		}
		this->l[poz].insert(it, noua);
	}
}

vector<TValoare> MDO::cauta(TCheie c) const {
	int poz = hash(c);
	for (auto& p : this->l[poz])
	{
		if (p.cheie == c)
		{
			return p.valori;
		}
	}
	return {};
}

bool MDO::sterge(TCheie c, TValoare v) {
	int poz = hash(c);
	//parcurg elementele care se disperseaza in l[poz] cu iterator
	for (auto it_lista = l[poz].begin(); it_lista != l[poz].end(); ++it_lista)
	{
		if (it_lista->cheie == c)
		{
			//gaseste perechea <c, v>
			auto it = find_if(it_lista->valori.begin(), it_lista->valori.end(),
				[v] (TValoare val) -> bool
				{
					return val == v;
				});
			//daca a gasit o
			if (it != it_lista->valori.end())
			{
				it_lista->valori.erase(it);
				//daca nu mai ramane niciun element in vecotrul de valori al cheii c
				if (it_lista->valori.empty())
				{
					l[poz].erase(it_lista);
				}
				return true;
			}
			return false;
		}
	}
	return false;
}

int MDO::dim() const {
	int size = 0;
	for (int i = 0; i < m; i++) //n
	{
		for (const auto& p : this->l[i]) //n
		{
			size += int(p.valori.size());
		}
	}
	return size;
}

bool MDO::vid() const {
	for (int i = 0; i < m; i++)
	{
		if (!this->l[i].empty())
		{
			return false;
		}
	}
	return true;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	delete[] l;
}
