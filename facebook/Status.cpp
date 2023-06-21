#include "Status.h"

using namespace std;

#pragma warning(disable: 4996)

//Prints text status
void Status::printStatus() const
{
	cout << "Status: " << text << "\n" << "Date: " << ctime(&date) << endl;
}

//Adds new status to arr
void addStatus(vector<Status*>& arr, Status* stat)
{
	arr.push_back(stat);
}

//Gets status array and print them acorrding to num of status to print.
void printStatuses(const vector<Status*>& board, int numOfStatusToPrint)
{
	int numToPrint = numOfStatusToPrint;
	if (numOfStatusToPrint >= (int)board.size())
		numToPrint = (int)board.size();
	for (int i = (int)board.size() - 1; i >= (int)board.size() - numToPrint; i--)
		board[i]->printStatus();
}

//Prints image status
void PicStatus::printStatus() const
{
	Status::printStatus();
	string command = "start " + picName;
	system(command.c_str());
}

//Prints video status
void VideoStatus::printStatus() const
{
	Status::printStatus();
	string command = "start " + videoName;
	system(command.c_str());
}

//operator Status==Status
bool Status::operator== (Status*& s) const
{
	return (text == s->text && dynamic_cast<PicStatus*>(s)==nullptr && dynamic_cast<VideoStatus*>(s) == nullptr);
}

//operator PicStatus==PicStatus
bool PicStatus::operator== (Status*& s) const
{
	return (this->getText() == s->getText() && dynamic_cast<PicStatus*>(s) != nullptr);
}

//operator VideoStatus==VideoStatus
bool VideoStatus::operator== (Status*& s) const
{
	return (this->getText() == s->getText() && dynamic_cast<VideoStatus*>(s) != nullptr);
}

//operator Status!=Status
bool Status::operator!= (Status*& s) const
{
	return (text != s->text || dynamic_cast<PicStatus*>(s) != nullptr || dynamic_cast<VideoStatus*>(s) != nullptr);
}

//operator PicStatus!=PicStatus
bool PicStatus::operator!= (Status*& s) const
{
	return (this->getText() != s->getText() || dynamic_cast<PicStatus*>(s) == nullptr);
}

//operator VideoStatus!=VideoStatus
bool VideoStatus::operator!= (Status*& s) const
{
	return (this->getText() != s->getText() || dynamic_cast<VideoStatus*>(s) == nullptr);
}