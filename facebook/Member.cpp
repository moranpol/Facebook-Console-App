#include "Member.h"
#include "fansPage.h"

using namespace std;

//Gets new fans page and adds fans page to member.
void Member::addFansPageToMember(fansPage* newPage) {
	if (findFansPageInArray(newPage->getName(), pages) != NOT_FOUND)
		throw PageException1();
	addfansPageToArr(pages, newPage);
	newPage->addMemberToPage(this);
}

//Gets name and remove fans page from member pages array.
void Member::removeFansPageFromMember(const string& pageName) {
	int i = findFansPageInArray(pageName, pages);
	if (i == NOT_FOUND)
		throw PageException2();
	pages[i]->removeMemberFromPage(getName());
	pages[i] = pages[(int)pages.size() - 1];
	pages.resize((int)pages.size() - 1);
}

//Prints 10 statuses of friends.
void Member::printTenStatusesOfFriends() const{
	for (int i = 0; i < (int)friends.size(); i++) {
		cout << friends[i]->getName() << ": \n" << endl;
		printStatuses(friends[i]->getBoard(), NUM_STATUSES_TO_PRINT);
	}
}

//Prints member
void Member::printMember() const {
	cout << "Member's name: " << getName();
	cout << ", Birth date: " << date.tm_mday << "/" << date.tm_mon + 1 << "/" << date.tm_year << endl;
}

//Prints friends
void Member::printFriends() const {
	cout << getName() << "'s friends: " << endl;
	printMembers(friends);
}

//Adds new friend to both friends array.
void Member::addNewFriend(Member* newFriend) {
	if (findMemberInArray(newFriend->getName(), friends) != NOT_FOUND) 
		throw FriendshipException2();
	addMemberToArr(friends, newFriend);
	addMemberToArr(newFriend->friends, this);
}

//Removes friendship between 2 friends.
void Member::removeFriends(const string& friendName) {
	int i;
	Member* memToRemove;
	i = findMemberInArray(friendName, friends);
	if (i == NOT_FOUND)
		throw NotFoundException();
	memToRemove = friends[i];
	removeMemberFromArray(friends, i);
	i = findMemberInArray(getName(), memToRemove->friends);
	removeMemberFromArray(memToRemove->friends, i);
}

// Print pages of member
void Member::printPagesOfMember() const
{
	cout << getName() << "'s pages: " << endl;
	for (int i = 0; i < (int)pages.size(); i++)
		cout << "#" << i + 1 << " Name: " << pages[i]->getName() << endl;
}

//Gets members array and prints her members.
void printMembers(const vector <Member*>& members)
{
	for (int i = 0; i < (int)members.size(); i++)
	{
		cout << "#" << i + 1 << " ";
		members[i]->printMember();
	}
}

//Gets array of members and a name. Return the name index.
int findMemberInArray(const string& name, const vector <Member*>& arr)
{
	bool stop = false;
	int res = NOT_FOUND;
	for (int i = 0; i < (int)arr.size() && !stop; i++)
	{
		if (name == arr[i]->getName())
		{
			stop = true;
			res = i;
		}
	}
	return res;
}

//Adds new member to arr
void addMemberToArr(vector <Member*>& arr, Member* newMem)
{
	arr.push_back(newMem);
}

//Gets index of member and remove him from member array.
void removeMemberFromArray(vector <Member*>& arr, int indexToRemove)
{
	arr[indexToRemove] = arr[(int)arr.size() - 1];
	arr.resize((int)arr.size() - 1);
}

//operator >
Member& Member::operator+= (Member& m)
{
	addNewFriend(&m);
	return *this;
}

//operator >
Member& Member::operator+=(fansPage& f)
{
	addFansPageToMember(&f);
	return *this;
}

//operator >
bool Member::operator>(const Member& m) const
{
	if ((int)friends.size() > (int)m.friends.size())
		return true;
	return false;
}

//operator >
bool Member::operator>(const fansPage& f) const
{
	if ((int)friends.size() > f.getFansSize())
		return true;
	return false;
}

