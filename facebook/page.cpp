#include "page.h"

using namespace std;

//Adds status to page
void Page::addStatusToPage(int type)
{
	Status* newStat = nullptr;
	string text, image, video;
	cout << "Enter your status: ";
	cin.ignore();
	getline(cin, text);
	switch ((StatusType)type)
	{
	case(StatusType::TEXT):
		newStat = new Status(text);
		break;
	case(StatusType::IMAGE):
		cout << "Enter image full path: ";
		getline(cin, image);
		newStat = new PicStatus(text, image);
		break;
	case(StatusType::VIDEO):
		cout << "Enter video full path: ";
		getline(cin, video);
		newStat = new VideoStatus(text, video);
		break;
	}
	if (newStat != nullptr)
		addStatus(board, newStat);
}

//Prints all fans page board
void Page::printAllBoard() const
{
	cout << name << ": \n" << endl;
	printStatuses(board, (int)board.size());
}