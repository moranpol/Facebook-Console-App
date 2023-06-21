#include "facebook.h"

int main()
{
	Facebook* f = new Facebook();
	f->readDataFromFile();
	f->play();
	f->saveDataToFile();
	f->checkOperators();
	delete f;
}