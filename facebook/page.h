#pragma once
#include "Status.h"

class Page
{
	std::string name;
	std::vector <Status*> board;

public:
	Page(const std::string _name) :
		name(_name)
	{}

	Page(const Page& f) = delete;

	~Page()
	{
		int i;
		for (i = 0; i < (int)board.size(); i++)
			delete board[i];
	}

	void addStatusToPage(int type);
	void printAllBoard() const;

	const std::string& getName() const
	{
		return name;
	}

	std::vector <Status*>& getBoard() 
	{
		return board;
	}

	const Status& getFirstStatus() const
	{
		return *board[0];
	}

	void setName(const std::string& _name)
	{
		name = _name;
	}
};