#pragma once
#include"Member.h"
#include"fansPage.h"
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>

enum {NEW_MEM=1, NEW_PAGE, NEW_STAT, PRINT_ALL_STAT, PRINT_10_STAT, NEW_FRIENDSHIP, CANCEL_FRIENDSHIP, ADD_FAN, 
REMOVE_FAN, PRINT_ALL, ALL_MEMBERS, LOG_OUT};
const int MAX_YEAR = 2023;
const int MIN_YEAR = 0;
const int MIN_MONTH = 0;
const int MAX_MONTH = 12;
const int MIN_DAY = 0;
const int MAX_DAY = 31;
const int MEMBER = 1;
const int FANS_PAGE = 2;

class ExistException: public std::exception
{
	std::string str;

public:
	ExistException()
	{
		str = "You already exist.";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class DateException : public std::exception
{
	std::string str;

public:
	DateException()
	{
		str = "Date is not valid.";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class ChoiceException : public std::exception
{
	std::string str;

public:
	ChoiceException()
	{
		str = "Input is not valid.";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class FriendshipException1 : public std::exception
{
	std::string str;

public:
	FriendshipException1()
	{
		str = "You cannot add yourself!!!!";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class Facebook
{
	std::vector <Member*> members;
	std::vector <fansPage*> pages;
	
public:
	Facebook(){}

	Facebook(const Facebook& f) = delete;

	Facebook& operator=(const Facebook& f)
	{
		members.assign(f.members.begin(), f.members.end());
		pages.assign(f.pages.begin(), f.pages.end());
		return *this;
	}

	~Facebook()
	{
		int i;
		for (i = 0; i < (int)members.size(); i++)
			delete members[i];
		for (i = 0; i < (int)pages.size(); i++)
			delete pages[i];
	}

	void createAndAddMember();
	void createAndAddFansPage();
	void printAllFansPages() const;
	void addNewStatus();
	void printAllStatuses() const;
	void printTenStatuses() const;
	void newFriendship();
	void cancelFrienship();
	void addFanToPage();
	void removeFanFromPage();
	void printAllEntities() const;
	void showAllMembers() const;
	void play();
	void checkOperators()const;
	void saveDataToFile();
	void readDataFromFile();

private:
	int returnType() const;
	int chooseUser() const;
	int choosePage() const;
	int chooseStatusType() const;
	friend void saveStatusesToFile(std::ofstream& file, const std::vector<Status*>& board, int size);
	friend void readStatusesFromFile(std::ifstream& myFile, std::vector<Status*>& board);
};

