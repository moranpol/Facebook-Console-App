#include "facebook.h"

using namespace std;

#pragma warning(disable: 4996)

//Creates new member and adds him to members arr.
void Facebook::createAndAddMember() 
{
	string name;
	struct tm birth;
	cout << "Enter your name: " << endl;
	cin.ignore();
	getline(cin, name);
	if (findMemberInArray(name, members) != NOT_FOUND)
		throw ExistException();
	cout << "Enter your birth year, month, day: " << endl;
	cin >> birth.tm_year >> birth.tm_mon >> birth.tm_mday;
	if (birth.tm_year < MIN_YEAR || birth.tm_year> MAX_YEAR || birth.tm_mon < MIN_MONTH || birth.tm_mon > MAX_MONTH || birth.tm_mday < MIN_DAY || birth.tm_mday > MAX_DAY)
		throw DateException();
	birth.tm_mon--;
	Member* newMem = new Member(name, birth);
	addMemberToArr(members, newMem);
}

//Creates new fans page and adds him to pages arr.
void Facebook::createAndAddFansPage()
{
	string name;
	cout << "Enter your fans page name" << endl;
	cin.ignore();
	getline(cin, name);
	if (findFansPageInArray(name, pages) != NOT_FOUND)
		throw ExistException();
	fansPage* newPage = new fansPage(name);
	addfansPageToArr(pages, newPage);
}

//Prints all the fans pages of facebook.
void Facebook::printAllFansPages() const
{
	for (int i = 0; i < (int)pages.size(); i++)
		cout << "#" << i + 1 << " Fans page's name: " << pages[i]->getName() << endl;
}

//choose which type you are (member or fans page)
int Facebook::returnType() const
{
	int type;
	cout << "Enter 1 if you are a member and 2 if you are a fans page" << endl;
	cin >> type;
	if (type != MEMBER && type != FANS_PAGE)
		throw ChoiceException();
	return type;
}

//choose which member you are
int Facebook::chooseUser() const
{
	int memberIndex;
	printMembers(members);
	cin >> memberIndex;
	if (memberIndex < 1 || memberIndex >(int)members.size())
		throw ChoiceException();
	return memberIndex;
}

//choose which page you are
int Facebook::choosePage() const
{
	int pageIndex;
	printAllFansPages();
	cin >> pageIndex;
	if (pageIndex < 1 || pageIndex >(int)pages.size())
		throw ChoiceException();
	return pageIndex;
}

//choose which page you are
int Facebook::chooseStatusType() const
{
	int type;
	cout << "choose: \n1- text status\n2- image and text status\n3- video and text status" << endl;
	cin >> type;
	if ((StatusType)type < StatusType::TEXT || (StatusType)type >StatusType::VIDEO)
		throw ChoiceException();
	return type;
}

//Adds new status to member or fans page.
void Facebook::addNewStatus() 
{
	int type, memberIndex, pageIndex, statusType;
	string newStatus;
	type = returnType();
	if (type == MEMBER) {
		cout << "Enter your user's index:" << endl;
		memberIndex = chooseUser();
		statusType = chooseStatusType();
		members[memberIndex - 1]->addStatusToPage(statusType);
	}
	else {
		cout << "Enter your fans page's index:" << endl;
		pageIndex = choosePage();
		statusType = chooseStatusType();
		pages[pageIndex - 1]->addStatusToPage(statusType);
	}
}

//Prints all statuses of member or fans page.
void Facebook::printAllStatuses() const {
	int type, memberIndex, pageIndex;
	type = returnType();
	if (type == MEMBER) {
		cout << "Enter your user's index:" << endl;
		memberIndex = chooseUser();
		members[memberIndex - 1]->printAllBoard();
	}
	else {
		cout << "Enter your fans page's index:" << endl;
		pageIndex = choosePage();
		pages[pageIndex - 1]->printAllBoard();
	}
}

//Prints 10 statuses of member's friends.
void Facebook::printTenStatuses() const {
	int memberIndex;
	cout << "Enter your user's index:" << endl;
	memberIndex = chooseUser();
	members[memberIndex - 1]->printTenStatusesOfFriends();
}

//Makes a new friendship between 2 members.
void Facebook::newFriendship() {
	int newFriendIndex, memberIndex;
	cout << "Enter your user's index:" << endl;
	memberIndex = chooseUser();
	cout << "Enter friend's index to add:" << endl;
	newFriendIndex = chooseUser();
	if (memberIndex == newFriendIndex)
		throw FriendshipException1();
	*members[memberIndex - 1] += *members[newFriendIndex - 1];
}

//Removes friendship between 2 friends.
void Facebook::cancelFrienship() {
	int removeFriendIndex, memberIndex;
	cout << "Enter your user's index:" << endl;
	memberIndex = chooseUser();
	cout << "Enter friend's index to remove from your friends list:" << endl;
	removeFriendIndex = chooseUser();
	members[memberIndex - 1]->removeFriends(members[removeFriendIndex - 1]->getName());
}

//Adds fan to fans page
void Facebook::addFanToPage() {
	int pageIndex, memberIndex;
	cout << "Enter your user's index:" << endl;
	memberIndex = chooseUser();
	cout << "Enter fans page's index to add to your pages:" << endl;
	pageIndex = choosePage();
	*members[memberIndex - 1] += *(pages[pageIndex - 1]);
}

//Removes fan to fans page
void Facebook::removeFanFromPage() {
	int pageIndex, memberIndex;
	cout << "Enter your user's index:" << endl;
	memberIndex = chooseUser();
	cout << "Enter fans page's index to remove from your pages:" << endl;
	pageIndex = choosePage();
	members[memberIndex - 1]->removeFansPageFromMember(pages[pageIndex - 1]->getName());
}

//Prints all members and all fans pages.
void Facebook::printAllEntities() const {
	cout << "Members:" << endl;
	printMembers(members);
	cout << "Fans pages:" << endl;
	printAllFansPages();
}

//Prints all members of user or fans page.
void Facebook::showAllMembers() const {
	int type, memberIndex, pageIndex;
	type = returnType();
	if (type == MEMBER) {
		cout << "Enter your user's index:" << endl;
		memberIndex = chooseUser();
		members[memberIndex - 1]->printFriends();
	}
	else {
		cout << "Enter your fans page's index:" << endl;
		pageIndex = choosePage();
		pages[pageIndex - 1]->printFans();
	}
}

//Menu + errors
void Facebook::play() {
	int ans;
	bool stop = false;
	while (!stop) 
	{
		cout << "Enter your action:" << endl;
		cout << "#1 Add new member to facebook." << endl;
		cout << "#2 Add new fans page to facebook." << endl;
		cout << "#3 Add new status to member/ fans page." << endl;
		cout << "#4 Show all statuses of member/ fans page." << endl;
		cout << "#5 Show 10 statuses of friends of member." << endl;
		cout << "#6 New friendship." << endl;
		cout << "#7 Cancel friendship." << endl;
		cout << "#8 Add fan to fans page." << endl;
		cout << "#9 Remove fan from fans page." << endl;
		cout << "#10 Show all Members and Fans pages of facebook." << endl;
		cout << "#11 Show all fans of fans page or friends of member." << endl;
		cout << "#12 Logout." << endl;
		cin >> ans;
		try
		{
			switch (ans) 
			{
			case (NEW_MEM):
				createAndAddMember();
				break;
			case(NEW_PAGE):
				createAndAddFansPage();
				break;
			case(NEW_STAT):
				addNewStatus();
				break;
			case(PRINT_ALL_STAT):
				printAllStatuses();
				break;
			case(PRINT_10_STAT):
				printTenStatuses();
				break;
			case(NEW_FRIENDSHIP):
				newFriendship();
				break;
			case(CANCEL_FRIENDSHIP):
				cancelFrienship();
				break;
			case(ADD_FAN):
				addFanToPage();
				break;
			case(REMOVE_FAN):
				removeFanFromPage();
				break;
			case(PRINT_ALL):
				printAllEntities();
				break;
			case(ALL_MEMBERS):
				showAllMembers();
				break;
			case(LOG_OUT):
				cout << "Byeeeeee." << endl;
				stop = true;
				break;
			}
		}
		catch (const ExistException& m1)
		{
			cout << m1.what() << endl;
		}
		catch (const DateException& d1)
		{
			cout << d1.what() << endl;
		}
		catch (const ChoiceException& c1)
		{
			cout << c1.what() << endl;
		}
		catch (const FriendshipException1& f1)
		{
			cout << f1.what() << endl;
		}
		catch (const FriendshipException2& f2)
		{
			cout << f2.what() << endl;
		}
		catch (const NotFoundException& n1)
		{
			cout << n1.what() << endl;
		}
		catch (const PageException1& p1)
		{
			cout << p1.what() << endl;
		}
		catch (const PageException2& p2)
		{
			cout << p2.what() << endl;
		}
		cout << endl;
	}
}

//Check operators
void Facebook::checkOperators()const
{
	cout << "Now we are checking our operators :)." << endl;
	cout << "We used operator += in our functions, let's check the other operators." << endl;
	
	cout << "\nIs Adi > Ofir? ";
	if (*members[2] > *members[0])
		cout << "Yes, ";
	else
		cout << "No, ";
	cout<<"Adi has " << members[2]->getFriendsSize() << " friends, Ofir has " << members[0]->getFriendsSize() << " friends." << endl;
	
	cout << "\nIs Adi > hapshuta? ";
	if (*members[2] > *pages[1])
		cout << "Yes, ";
	else
		cout << "No, ";
	cout << "Adi has " << members[2]->getFriendsSize() << " friends, hapshuta has " << pages[1]->getFansSize() << " fans." << endl;
	
	cout << "\nIs food lovers > Moran? ";
	if (*pages[0] > *members[1])
		cout << "Yes, ";
	else
		cout << "No, ";
	cout << "food lovers has " << pages[0]->getFansSize() << " fans, Moran has " << members[1]->getFriendsSize() << " friends." << endl;

	cout << "\nIs food lovers > sport lovers? ";
	if (*pages[0] > *pages[2])
		cout << "Yes, ";
	else
		cout << "No, ";
	cout << "food lovers has " << pages[0]->getFansSize() << " fans, sport lovers has " << pages[2]->getFansSize() << " fans." << endl;

	cout << "\nIs Moran's first status == Ofir's first status? ";
	if (&(members[1]->getFirstStatus()) == &(members[0]->getFirstStatus()))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << "\nMoran's first status: ";
	members[1]->getFirstStatus().printStatus();
	cout << "Ofir's first status: ";
	members[0]->getFirstStatus().printStatus();

	cout << "Is food lovers's first status != hapshuta's first status? ";
	if (&(pages[0]->getFirstStatus()) != &(pages[1]->getFirstStatus()))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << "\nfood lovers's first status: ";
	pages[0]->getFirstStatus().printStatus();
	cout << "hapshuta's first status: ";
	pages[1]->getFirstStatus().printStatus();
}

//save statuses to file
void saveStatusesToFile(ofstream& file, const vector<Status*>& board, int size)
{
	file << size << "\n";
	for (int i = 0; i < size; i++)
	{
		if (dynamic_cast<PicStatus*>(board[i]) != nullptr)
			file << (int)StatusType::IMAGE << " " << dynamic_cast<PicStatus*>(board[i])->getPicName() << "\n";
		else if (dynamic_cast<VideoStatus*>(board[i]) != nullptr)
			file << (int)StatusType::VIDEO << " " << dynamic_cast<VideoStatus*>(board[i])->getVideoName() << "\n";
		else
			file << (int)StatusType::TEXT << "\n";
		file << board[i]->getText() << "\n";
		struct tm* timeinfo;
		char buffer[80];
		timeinfo = localtime(&(board[i]->getDate()));
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
		file << buffer << "\n";
	}
}

//save data to file
void Facebook::saveDataToFile()
{
	ofstream myFile("facebookData.txt");
	myFile << (int)members.size() << "\n";
	//friends data
	for (int i = 0; i < (int)members.size(); i++)
	{
		myFile << members[i]->getName() << "\n" << members[i]->getDate().tm_year << " ";
		myFile << members[i]->getDate().tm_mon << " " << members[i]->getDate().tm_mday << "\n";
		saveStatusesToFile(myFile, members[i]->getBoard(), (int)members[i]->getBoard().size());
	}
	//pages data
	myFile << (int)pages.size() << "\n";
	for (int i = 0; i < (int)pages.size(); i++)
	{
		myFile << pages[i]->getName() << "\n";
		saveStatusesToFile(myFile, pages[i]->getBoard(), (int)pages[i]->getBoard().size());
	}
	//members friends
	for (int i = 0; i < (int)members.size(); i++)
	{
		myFile << members[i]->getFriendsSize() << " ";
		for (int j = 0; j < members[i]->getFriendsSize(); j++)
			myFile << members[i]->getFriends()[j]->getName() << "\n";
	}
	//members pages
	for (int i = 0; i < (int)members.size(); i++)
	{
		myFile << members[i]->getPagesSize() << " ";
		for (int j = 0; j < members[i]->getPagesSize(); j++)
			myFile << members[i]->getPages()[j]->getName() << "\n";
	}
	myFile.close();
}

//read statuses from file 
void readStatusesFromFile(ifstream& myFile, vector<Status*>& board)
{
	int statSize, statType;
	string image, text, video, dateStr;
	struct tm tm = {};
	Status* newStat = nullptr;
	myFile >> statSize;
	myFile.get();
	for (int j = 0; j < statSize; j++)
	{
		myFile >> statType;
		myFile.get();
		switch (statType)
		{
		case((int)StatusType::IMAGE):
			getline(myFile, image);
			getline(myFile, text);
			newStat = new PicStatus(text, image);
			break;
		case((int)StatusType::VIDEO):
			getline(myFile, video);
			getline(myFile, text);
			newStat = new VideoStatus(text, video);
			break;
		case((int)StatusType::TEXT):
			getline(myFile, text);
			newStat = new Status(text);
			break;
		}
		getline(myFile, dateStr);
		istringstream ss(dateStr);
		ss >> get_time(&tm, "%d-%m-%Y %I:%M:%S");
		auto time_point = chrono::system_clock::from_time_t(std::mktime(&tm));
		time_t time_t_value = chrono::system_clock::to_time_t(time_point);
		newStat->setDate(time_t_value);
		addStatus(board, newStat);
	}
}

//read data from file
void Facebook::readDataFromFile()
{
	ifstream myFile("facebookData.txt");
	if (!myFile.is_open() || !myFile.good())
		return;
	string name;
	struct tm date;
	int memberSize, fansPageSize, friendsSize, pagesSize, index;
	myFile >> memberSize;
	myFile.get();
	//member data without friends and pages
	for (int i = 0; i < memberSize; i++)
	{
		getline(myFile, name);
		myFile >> date.tm_year >> date.tm_mon >> date.tm_mday;
		Member* newMem = new Member(name, date);
		addMemberToArr(members, newMem);
		myFile.get();
		readStatusesFromFile(myFile, members[i]->getBoard());
	}
	//pages data without fans
	myFile >> fansPageSize;
	myFile.get();
	for (int i = 0; i < fansPageSize; i++)
	{
		getline(myFile, name);
		fansPage* newPage = new fansPage(name);
		addfansPageToArr(pages, newPage);
		readStatusesFromFile(myFile, pages[i]->getBoard());
	}
	//members friends
	for (int i = 0; i < memberSize; i++)
	{
		myFile >> friendsSize;
		myFile.get();
		for (int j = 0; j < friendsSize; j++)
		{
			getline(myFile, name);
			index = findMemberInArray(name, members);
			addMemberToArr(members[i]->getFriends(),members[index]);
		}
	}
	//members pages
	for (int i = 0; i < memberSize; i++)
	{
		myFile >> pagesSize;
		myFile.get();
		for (int j = 0; j < pagesSize; j++)
		{
			getline(myFile, name);
			index = findFansPageInArray(name, pages);
			*members[i] += *(pages[index]);
		}
	}
	myFile.close();
}

