#include "Memento.h"

Memento::Memento()
{
	state = "";
}

Memento::Memento(std::string st)
{
	state = st;
}