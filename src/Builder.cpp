#include "Builder.h"

Figure* Builder::build_object()
{
	Figure* figure = nullptr;
	std::string str = get_data();
	switch (str[0])
	{
	case '1': figure = new Circle(); break;
	case '2': figure = new Ellipse(); break;
	case '3': figure = new Triangle(); break;
	case '4': figure = new Rectangle(); break;
	case '5': figure = new Star(); break;
	case '6': figure = new Hexagon(); break;
	}
	figure->from_string(str);
	return figure;
}

std::string Builder::get_data()
{
	std::string str;
	std::cout << "Enter the parametres of a new figure:";
	std::cout <<"<Type*> <Width> <Height> <Color**> <Position.X> <Position.Y>\n";
	std::cout << "* - Available types: Circle, Ellipse, Triangle, Rectangle, Star, Hexagon\n";
	std::cout << "** - Available colors: Red, Green, Blue, Cyan, Yellow, Magenta\n";
	std::cout << "Example: Rectangle 200 100 Yellow 600 700\n\n";
	std::getline(std::cin, str, '\n');

	str = input_to_valid_string(str);

	while (str == "")
	{
		std::cout << "Invalid data, try again!\n";
		std::getline(std::cin, str, '\n');
		str = input_to_valid_string(str);
	}

	return str;
}

std::string Builder::input_to_valid_string(std::string str)
{
	std::string valid = "";
	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	
	char* pch;
	std::string type;
	int width;
	int height;
	std::string color;
	int position_x;
	int position_y;

	pch = strtok(cstr, " ");
	if (wrong_string(pch))
		return "";
	else type = pch;

	pch = strtok(nullptr, " ");
	if (wrong_string(pch))
		return "";
	else width = atoi(pch);

	pch = strtok(nullptr, " ");
	if (wrong_string(pch))
		return "";
	else height = atoi(pch);

	pch = strtok(nullptr, " ");
	if (wrong_string(pch))
		return "";
	else color = pch;

	pch = strtok(nullptr, " ");
	if (wrong_string(pch))
		return "";
	else position_x = atoi(pch);

	pch = strtok(nullptr, "\n");
	if (wrong_string(pch))
		return "";
	else position_y = atoi(pch);

	delete[] cstr;

	if (type == "Circle")
		valid += "1-" + std::to_string(width / 2) + "-";
	else if (type == "Ellipse")
		valid += "2-" + std::to_string(width) + "-" + std::to_string(height) + "-";
	else if (type == "Triangle")
		valid += "3-" + std::to_string(width) + "-" + std::to_string(height) + "-";
	else if (type == "Rectangle")
		valid += "4-" + std::to_string(width) + "-" + std::to_string(height) + "-";
	else if (type == "Star")
		valid += "5-" + std::to_string(width / 2) + "-";
	else if (type == "Hexagon")
		valid += "6-" + std::to_string(width) + "-" + std::to_string(height) + "-";
	else return "";

	if (color == "Red")
		valid += "255,0,0";
	else if (color == "Green")
		valid += "0,255,0";
	else if (color == "Blue")
		valid += "0,0,255";
	else if (color == "Cyan")
		valid += "0,255,255";
	else if (color == "Yellow")
		valid += "255,255,0";
	else if (color == "Magenta")
		valid += "255,0,255";
	else return "";

	valid += "-" + std::to_string(position_x) + "," + std::to_string(position_y);
	return valid;
}

bool Builder::wrong_string(char* pch)
{
	if (pch == NULL)
		return true;
	else
		return false;
}
