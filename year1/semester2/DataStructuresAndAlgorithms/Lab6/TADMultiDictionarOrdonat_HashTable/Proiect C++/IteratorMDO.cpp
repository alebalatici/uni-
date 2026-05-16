#include "IteratorMDO.h"
#include <algorithm>
#include <stdexcept>
#include "MDO.h"
/*
void IteratorMDO::deplasare()
{
	while (pozCurent < dict.m && dict.l[pozCurent].empty())
	{
		pozCurent++;
	}
	if (pozCurent < dict.m)
	{
		itLista = dict.l[pozCurent].begin();
		indexVector = 0;
	}
}
*/
IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	for (int i = 0; i < dict.m; i++)
	{
		for (auto const& pereche : dict.l[i])
		{
			for (auto const& val : pereche.valori)
			{
				elem_sortate.emplace_back(pereche.cheie, val);
			}
		}
	}
	sort(elem_sortate.begin(), elem_sortate.end(),
		[this](const TElem& a, const TElem& b) -> bool
		{
			return dict.relatie(a.first, b.first);
		});
	pozCurent = 0;
}

void IteratorMDO::prim(){
	pozCurent = 0;
}

void IteratorMDO::urmator(){
	if (!valid())
	{
		throw exception();
	}
	pozCurent++;
}

bool IteratorMDO::valid() const{
	return pozCurent < (int)elem_sortate.size();
}

TElem IteratorMDO::element() const{
	if (!valid())
	{
		throw exception();
	}
	return elem_sortate[pozCurent];
}


