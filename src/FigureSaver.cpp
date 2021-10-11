#include "FigureSaver.h"

FigureSaver::FigureSaver()
{
	memento = Memento();
}

FigureSaver::FigureSaver(std::string str)
{
	memento.state = str;
}

void FigureSaver::save_state(Figure* figure)
{
	figure->set_memento(memento);
}

void FigureSaver::load_state(Figure*& figure_ptr)
{
	switch (memento.state[0])
	{
	case '0': figure_ptr = new Composite(); break;
	case '1': figure_ptr = new Circle(); break;
	case '2': figure_ptr = new Ellipse(); break;
	case '3': figure_ptr = new Triangle(); break;
	case '4': figure_ptr = new Rectangle(); break;
	case '5': figure_ptr = new Star(); break;
	case '6': figure_ptr = new Hexagon(); break;
	}
	figure_ptr->get_memento(memento);
}

std::string FigureSaver::to_string()
{
	return memento.state + "\n";
}
