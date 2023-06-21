#pragma once
#include "page.h"

class Member;

class fansPage: public Page
{
	std::vector <Member*> fans;

public:
	fansPage(const std::string _name) : Page(_name){}

	fansPage(const fansPage& f) = delete;

	fansPage& operator=(const fansPage& f)
	{
		this->setName(f.getName());
		this->getBoard().assign(const_cast<fansPage&>(f).getBoard().begin(), const_cast<fansPage&>(f).getBoard().end());
		fans.assign(f.fans.begin(), f.fans.end());
		return *this;
	}

	fansPage& operator+=(Member& m);
	bool operator>(const Member& m) const;
	bool operator>(const fansPage& f) const;

	void addMemberToPage(Member* mem);
	void removeMemberFromPage(const std::string& memberName);
	void printFans() const;
	friend void addfansPageToArr(std::vector <fansPage*>& arr, fansPage* newPage);
	friend int findFansPageInArray(const std::string& name, const std::vector <fansPage*>& arr);
	
	int getFansSize() const
	{
		return (int)fans.size();
	}

	const std::vector<Member*>& getFans()
	{
		return fans;
	}
};
