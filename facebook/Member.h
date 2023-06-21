#pragma once
#include "page.h"

class fansPage;

const int NOT_FOUND = -1;
const int NUM_STATUSES_TO_PRINT = 10;

class FriendshipException2 : public std::exception
{
	std::string str;

public:
	FriendshipException2()
	{
		str = "Your already friends.";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class NotFoundException : public std::exception
{
	std::string str;

public:
	NotFoundException()
	{
		str = "Member not found.";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class PageException1 : public std::exception
{
	std::string str;

public:
	PageException1()
	{
		str = "Your already a fan!!!!!";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class PageException2 : public std::exception
{
	std::string str;

public:
	PageException2()
	{
		str = "Your are not a fan!!!!!";
	}

	const char* what() const
	{
		return str.c_str();
	}
};

class Member : public Page
{
	struct tm date;
	std::vector <Member*> friends;
	std::vector <fansPage*> pages;

public:
	Member(const std::string _name, struct tm _date) : Page(_name), date(_date) {}

	Member(const Member& m) = delete;

	Member& operator=(const Member& m)
	{
		this->setName(m.getName());
		this->getBoard().assign(const_cast<Member&>(m).getBoard().begin(), const_cast<Member&>(m).getBoard().end());
		date = m.date;
		friends.assign(m.friends.begin(), m.friends.end());
		pages.assign(m.pages.begin(), m.pages.end());
		return *this;
	}

	Member& operator+= (Member& m);
	Member& operator+=(fansPage& f);
	bool operator>(const Member& m) const;
	bool operator>(const fansPage& f) const;

	void addFansPageToMember(fansPage* newPage);
	void removeFansPageFromMember(const std::string& pageName);
	void printTenStatusesOfFriends() const;
	void printMember() const;
	void printFriends() const;
	void addNewFriend(Member* newFriend);
	void removeFriends(const std::string& friendName);
	void printPagesOfMember() const;
	friend void printMembers(const std::vector <Member*>& members);
	friend int findMemberInArray(const std::string& name, const std::vector <Member*>& arr);
	friend void addMemberToArr(std::vector <Member*>& arr, Member* newMem);
	friend void removeMemberFromArray(std::vector <Member*>& arr, int indexToRemove);

	int getFriendsSize() const
	{
		return (int)friends.size();
	}

	std::vector<Member*>& getFriends()
	{
		return friends;
	}

	int getPagesSize() const
	{
		return (int)pages.size();
	}

	const std::vector<fansPage*>& getPages()
	{
		return pages;
	}

	struct tm getDate() const
	{
		return date;
	}
};






