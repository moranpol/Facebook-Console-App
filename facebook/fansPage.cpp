#include "fansPage.h"
#include "Member.h"

using namespace std;

//Addnew fan to fans page
void fansPage::addMemberToPage(Member* mem)
{
	addMemberToArr(fans, mem);
}

//Gets name and remove member from member array.
void fansPage::removeMemberFromPage(const string& memberName)
{
	int i = findMemberInArray(memberName, fans);
	removeMemberFromArray(fans, i);
}

//Prints friends
void fansPage::printFans() const
{
	cout << getName() << "'s fans: " << endl;
	printMembers(fans);
}

//Gets pointer to new fans page and insert him to fans page pointers array.
void addfansPageToArr(vector <fansPage*>& arr, fansPage* newPage)
{
	arr.push_back(newPage);
}

//Gets array of fans page and a name. Return the name index.
int findFansPageInArray(const string& name, const vector <fansPage*>& arr)
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

//operator +=
fansPage& fansPage::operator+=(Member& m)
{
	m.addFansPageToMember(this);
	return *this;
}

//operator >
bool fansPage::operator>(const Member& m) const
{
	if ((int)fans.size() > m.getFriendsSize())
		return true;
	return false;
}

//operator >
bool fansPage::operator>(const fansPage& f) const
{
	if ((int)fans.size() > (int)f.fans.size())
		return true;
	return false;
}