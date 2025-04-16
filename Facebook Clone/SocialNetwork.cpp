#include<iostream>
#include<fstream>
using namespace std;

//-------------------------------------- Classes-----------------------------------------
class SocialNetwork;
class Users;
class Pages;
class Helper;
class Object;
class Date;
class Posts;
class Activity;
class Memory;
class Comments;

//-------------------------------------Helper Class--------------------------------------

class Helper
{
public:
	static int StringLenght(char const* str)                  //String Length
	{
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}
	static char* StringCopy(char* temp)                       //String Copy
	{
		int size = StringLenght(temp);
		char* arrayptr = new char[size + 1];
		int i = 0;
		for (i = 0; temp[i] != '\0'; i++)
		{
			arrayptr[i] = temp[i];
		}
		arrayptr[i] = '\0';

		return arrayptr;
	}
	static char* GetStringFromBuffer(char* buffer)            //Get String From Buffer
	{
		int s = (StringLenght(buffer)) + 2;
		char* String = 0;

		if (s > 0)
		{
			String = new char[s];

			char* temp = String;

			int i = 0;
			for (i = 0; buffer[i] != '\0'; i++)
			{
				temp[i] = buffer[i];
			}
			temp[i] = '\0';
		}
		return String;
	}
	static void StringConcatenate(char*& _String1, char* _String2)        //String Concatenate
	{
		if (_String1 != 0 && _String2 != 0)
		{
			int size1 = StringLenght(_String1);
			int size2 = StringLenght(_String2);

			int size = size1 + size2 + 2;

			char* temp = new char[size];

			for (int i = 0; _String1[i] != '\0'; i++)
			{
				temp[i] = _String1[i];
			}

			temp[StringLenght(_String1)] = ' ';

			int i = StringLenght(_String1) + 1;
			for (int j = 0; _String2[j] != '\0'; j++, i++)
			{
				temp[i] = _String2[j];
			}
			temp[i] = '\0';


			delete[] _String1;

			_String1 = temp;									//Point String1 to data in temp

		}
	}
	static bool StringCompare(char* array1, const char* array2)
	{
		if (StringLenght(array1) != StringLenght(array2))
			return 0;
		else
		{
			for (int i = 0; i < array1[i] != '\0' && array2[i] != '\0'; i++)
			{
				if (array1[i] != array2[i])
					return 0;
			}
		}
		return 1;
	}
};

//------------------------------------Date Class------------------------------

class Date
{
private:
	int Day;
	int Month;
	int Year;

	static Date CurrentDate;
public:
	Date(int, int, int);
	~Date() {}

	void ReadDatesFromFile(ifstream&);

	int GetDay();
	int GetMonth();
	int GetYear();

	static void SetCurrentDate(int, int, int);
	static Date GetCurrentDate();

	void PrintDate();
	static void PrintCurrentDate();
};

Date::Date(int d = 0, int m = 0, int y = 0)
{
	Day = d;
	Month = m;
	Year = y;
}

void Date::ReadDatesFromFile(ifstream& fin)
{
	fin >> Day;
	fin >> Month;
	fin >> Year;
}

int Date::GetDay()
{
	return Day;
}
int Date::GetMonth()
{
	return Month;
}
int Date::GetYear()
{
	return Year;
}

Date Date::GetCurrentDate()
{
	return CurrentDate;
}
void Date::SetCurrentDate(int d = 0, int m = 0, int y = 0)
{
	Date temp(d, m, y);
	CurrentDate = temp;
}

void Date::PrintDate()
{
	cout << "(" << Day << "/" << Month << "/" << Year << ")" << endl;
}
void Date::PrintCurrentDate()
{
	CurrentDate.PrintDate();
}

Date Date::CurrentDate;


//-------------------------------------Object Class--------------------------------------
class Object
{
private:
	char* ID;
public:
	Object();
	virtual ~Object();

	void SetID(char*);
	char* GetID();

	virtual void PrintName() {}
	virtual void PrintListView() {}
};

Object::Object()
{
	ID = 0;
}
Object::~Object()
{
	if (ID)
		delete[] ID;
}

void Object::SetID(char* id)
{
	ID = id;
}
char* Object::GetID()
{
	return ID;
}



//----------------------------------Comments Class-----------------------------------------
class Comments
{
private:
	char* ID;
	char* Message;

	Object* CommentBy;
public:
	Comments();
	~Comments();

	Comments& operator=(const Comments&);

	void SetID(char*);
	void SetMessage(char*);
	void SetCommentBy(Object*);

	void PrintListView();
};

Comments& Comments::operator=(const Comments& rhs)
{
	if (this != &rhs)
	{
		if (ID)
			delete[] ID;
		if (Message)
			delete[] Message;

		ID = Helper::GetStringFromBuffer(rhs.ID);
		Message = Helper::GetStringFromBuffer(rhs.Message);
		CommentBy = rhs.CommentBy;

	}
	return *this;
}

Comments::Comments()
{
	ID = 0;
	Message = 0;
	CommentBy = 0;
}
Comments::~Comments()
{
	if (ID)
		delete[] ID;
	if (Message)
		delete[] Message;
	if (CommentBy)
		delete[] CommentBy;
}

void Comments::SetID(char* id)
{
	ID = Helper::GetStringFromBuffer(id);
}
void Comments::SetMessage(char* m)
{
	Message = Helper::GetStringFromBuffer(m);
}
void Comments::SetCommentBy(Object* Ptr)
{
	CommentBy = Ptr;
}

void Comments::PrintListView()
{
	CommentBy->PrintName();
	cout << " wrote: \"" << Message << "\"" << endl;
}

//-------------------------------------Activity Class--------------------------------------

class Activity
{
private:
	int Type;
	char* Value;
public:
	Activity();
	~Activity();

	void ReadActivityFromFile(ifstream&);

	void PrintListView();
};

Activity::Activity()
{
	Type = 0;
	Value = 0;
}
Activity::~Activity()
{
	if (Value)
		delete[] Value;
}

void Activity::ReadActivityFromFile(ifstream& fin)
{
	char TempBuffer[100];
	fin >> Type;

	fin.getline(TempBuffer, 100);
	Value = Helper::GetStringFromBuffer(TempBuffer);
}

void Activity::PrintListView()
{
	switch (Type)
	{
	case 1:
		cout << " is feeling ";
		break;
	case 2:
		cout << " is thinking about ";
		break;
	case 3:
		cout << " is making ";
		break;
	case 4:
		cout << " is celebrating ";
		break;
	}
	cout << Value << endl;
}

//-------------------------------------Posts Class--------------------------------------
class Posts
{
private:
	int Type;
	int NumberofLikes;

	char* description;
	char* ID;

	Object* SharedBy;
	Object** LikedBy;

	Date SharedDate;

	Activity Post_Activity;

	Comments** CommentsList;
public:
	Posts();
	~Posts();

	void ReadPostsFromFile(ifstream&);

	void SetSharedBy(Object*);
	void SetLikedBy(Object*, int&);
	int Get_i_LikedBy();
	Date GetSharedDate();
	Object* GetSharedBy();

	int IsMemoryPosts();
	bool Is_to_be_Printed();
	bool CompareID(const char*);

	void UpdateCommentsList(Comments*);

	void PrintLikedBy();
	void PrintListView();
};

Posts::Posts()
{
	Type = NumberofLikes = 0;
	ID = description = 0;
	SharedBy = 0;
	LikedBy = new Object * [10];
	CommentsList = new Comments * [10];
	for (int i = 0; i < 10; i++)
	{
		CommentsList[i] = 0;
	}
}
Posts::~Posts()
{
	if (ID)
		delete[] ID;
	if (description)
		delete[] description;
	if (LikedBy)
		delete[] LikedBy;
	if (CommentsList)
		delete[] CommentsList;

}

void Posts::ReadPostsFromFile(ifstream& fin)
{
	char TempBuffer[100];

	fin >> Type;

	fin >> TempBuffer;
	ID = Helper::GetStringFromBuffer(TempBuffer);

	SharedDate.ReadDatesFromFile(fin);

	fin.ignore();
	fin.getline(TempBuffer, 100);
	description = Helper::GetStringFromBuffer(TempBuffer);

	if (Type == 2)
		Post_Activity.ReadActivityFromFile(fin);
}

void Posts::SetSharedBy(Object* Ptr)
{
	SharedBy = Ptr;
}
void Posts::SetLikedBy(Object* Ptr, int& i)
{
	LikedBy[i] = Ptr;
}
int Posts::Get_i_LikedBy()
{
	int i = 0;
	while (LikedBy[i])
	{
		i++;
	}
	return i;
}
Date Posts::GetSharedDate()
{
	return SharedDate;
}
Object* Posts::GetSharedBy()
{
	return SharedBy;
}

int Posts::IsMemoryPosts()
{
	Date D = Date::GetCurrentDate();
	if (SharedDate.GetDay() == D.GetDay() && SharedDate.GetMonth() == D.GetMonth())
	{
		return (D.GetYear() - SharedDate.GetYear());
	}
	return 0;
}
bool Posts::Is_to_be_Printed()
{
	Date D = Date::GetCurrentDate();
	if (SharedDate.GetDay() == D.GetDay() || SharedDate.GetDay() == D.GetDay() - 1)
	{
		return 1;
	}
	return 0;
}
bool Posts::CompareID(const char* id)
{
	return(Helper::StringCompare(ID, id));
}

void Posts::UpdateCommentsList(Comments* Ptr)
{
	int i = 0;
	while (CommentsList[i])
	{
		i++;
	}
	CommentsList[i] = Ptr;
}

void Posts::PrintLikedBy()
{
	for (int i = 0; LikedBy[i] != 0; i++)
	{
		LikedBy[i]->PrintListView();
		cout << "\n";
	}
}
void Posts::PrintListView()
{
	SharedBy->PrintName();
	if (Type == 2)
	{
		Post_Activity.PrintListView();
	}
	else
	{
		cout << " shared ";
	}
	cout << "\" " << description << " \"";
	SharedDate.PrintDate();
	cout << endl;
	for (int i = 0; CommentsList[i] != 0 && i < 3; i++)
	{
		cout << "                  ";
		CommentsList[i]->PrintListView();
	}
}

//------------------------------------Memory Class----------------------------------------

class Memory
{
private:
	int TotalYears;
	char* Text;
	bool IsShared;
	Posts* Post;
	Date SharedDate;
public:
	Memory();
	~Memory();

	void SetMemory(Posts*);
	void SetTotalYear(int);
	int GetIsShared();
	Date GetSharedDate();
	Posts* GetMemoryPost();

	void ShareMemory(char*);

	void PrintListView();
};
Memory::Memory()
{
	Text = 0;
	IsShared = 0;
	TotalYears = 0;
	Post = 0;
}
Memory::~Memory()
{
	if (Text)
		delete[] Text;
	if (Post)
		delete[] Post;
}


void Memory::SetMemory(Posts* Ptr)
{
	Post = Ptr;
}
void Memory::SetTotalYear(int y)
{
	TotalYears = y;
}
int Memory::GetIsShared()
{
	return IsShared;
}
Date Memory::GetSharedDate()
{
	return SharedDate;
}
Posts* Memory::GetMemoryPost()
{
	return Post;
}

void Memory::ShareMemory(char* text)
{
	IsShared++;
	Text = Helper::GetStringFromBuffer(text);
	SharedDate = Date::GetCurrentDate();
}

void Memory::PrintListView()
{
	if (Text)
	{
		cout << "\"" << Text << "\"" << endl;
	}
	cout << "(" << TotalYears << " Years Ago)" << endl;
	Post->PrintListView();
}
//-----------------------------------Pages Class----------------------------------------

class Pages : public Object
{
private:
	char* Title;
	int PostCount;
	Posts** posts;
public:
	Pages();
	~Pages();

	void ReadPagesfromFile(ifstream&);

	bool CompareID(const char*);
	void SetPostCount(int&);
	void AddPosts(Posts*, int&);

	void ViewPost();
	void PrintName();
	void PrintListView();
	void PrintPosts();
};

Pages::Pages()											      //Default Constructor
{
	Title = 0;
	PostCount = 0;
	posts = 0;
}
Pages::~Pages()													       //Destructor
{
	if (Title)
		delete Title;
	if (PostCount)
		delete[] posts;
}

void Pages::ReadPagesfromFile(ifstream& fin)
{
	char TempBuffer[100];

	fin >> TempBuffer;
	SetID(Helper::GetStringFromBuffer(TempBuffer));

	fin.getline(TempBuffer, 100);
	Title = Helper::GetStringFromBuffer(TempBuffer);
}

bool Pages::CompareID(const char* id)
{
	return (Helper::StringCompare(GetID(), id));
}
void Pages::SetPostCount(int& p)
{
	PostCount = p;
	if (p)
	{
		posts = new Posts * [p];
	}
}
void Pages::AddPosts(Posts* Ptr, int& i)
{
	posts[i] = Ptr;
}

void Pages::ViewPost()		//for User
{
	for (int i = 0; i < PostCount; i++)
	{
		posts[i]->PrintListView();
		cout << endl;
	}
}
void Pages::PrintName()
{
	cout << Title;
}
void Pages::PrintListView()
{
	cout << GetID() << " - " << Title << endl;
}
void Pages::PrintPosts()		//For friends and liked pages
{
	for (int i = 0; i < PostCount; i++)
	{
		if (posts[i]->Is_to_be_Printed())
		{
			posts[i]->PrintListView();
			cout << endl;
		}
	}
}

//-----------------------------------Users Class---------------------------------------

class Users : public Object
{
private:
	char* FirstName;
	char* LastName;

	Pages** LinkedPages;
	Users** Friends;
	Posts** posts;
	Memory** memories;

	int PageCount;
	int UserCount;
	int PostCount;
	int MemoriesCount;

public:
	Users();
	~Users();

	void ReadUsersfromFile(ifstream&);

	void LikePages(Pages*&);
	void AddFriend(Users*&);
	void AddPosts(Posts*, int&);
	void AddMemories();

	void SetPostCount(int);
	bool CompareID(const char*);
	Posts* SearchPostbyID(char* str);
	void ShareMemory(char* str, char* des);

	void ViewHome();
	void ViewMemories();
	void ViewFriendList();
	void ViewLikedPages();
	void ViewTimeline();

	void PrintID();
	void PrintName();
	void PrintDetailView();
	void PrintListView();
	void PrintPosts();
	void PrintSharedMemories();
	void PrintPostsOfFriends();
	void PrintPostsOfLikedPages();
};

Users::Users()											      //Default Constructor
{
	PageCount = 0;
	UserCount = 0;
	PostCount = 0;
	MemoriesCount = 0;
	FirstName = 0;
	LastName = 0;
	LinkedPages = 0;
	Friends = 0;
	LinkedPages = new Pages * [10];
	for (int i = 0; i < 10; i++)
	{
		LinkedPages[i] = 0;
	}
	Friends = new Users * [10];
	for (int i = 0; i < 10; i++)
	{
		Friends[i] = 0;
	}
	posts = 0;
	memories = 0;
}
Users::~Users()											               //Destructor
{
	if (FirstName)
		delete FirstName;
	if (LastName)
		delete LastName;
	if (LinkedPages)
	{
		delete[] LinkedPages;
	}
	if (Friends)
	{
		delete[] Friends;
	}
	if (posts)
	{
		for (int i = 0; i < PostCount; i++)
		{
			delete[] posts[i];
		}
		delete[] posts;
	}
}

void Users::ReadUsersfromFile(ifstream& fin)
{
	char TempBuffer[100];

	fin >> TempBuffer;
	SetID(Helper::GetStringFromBuffer(TempBuffer));

	fin >> TempBuffer;
	FirstName = Helper::GetStringFromBuffer(TempBuffer);

	fin >> TempBuffer;
	LastName = Helper::GetStringFromBuffer(TempBuffer);
}

void Users::LikePages(Pages*& p)
{
	if (PageCount < 10)
	{
		LinkedPages[PageCount] = p;
		PageCount++;
		LinkedPages[PageCount] = NULL;
	}
}
void Users::AddFriend(Users*& u)
{
	if (UserCount < 10)
	{
		Friends[UserCount] = u;
		UserCount++;
		Friends[UserCount] = NULL;
	}
}
void Users::AddPosts(Posts* Ptr, int& i)
{
	posts[i] = Ptr;
}
void Users::AddMemories()
{
	for (int i = 0; i < PostCount; i++)
	{
		if (posts[i]->IsMemoryPosts())
			MemoriesCount++;
	}

	if (MemoriesCount)
	{
		memories = new Memory * [MemoriesCount];

		int j = 0;
		for (int i = 0; i < PostCount; i++)
		{
			int k = posts[i]->IsMemoryPosts();

			if (k)
			{
				memories[j] = new Memory;
				memories[j]->SetTotalYear(k);
				memories[j]->SetMemory(posts[i]);
				j++;
			}
		}

	}
}

void Users::SetPostCount(int p)
{
	PostCount = p;
	if (p)
		posts = new Posts * [p];
}
bool Users::CompareID(const char* id)
{
	return (Helper::StringCompare(GetID(), id));
}
Posts* Users::SearchPostbyID(char* str)
{
	for (int i = 0; i < PostCount; i++)
	{
		if (posts[i]->CompareID(str))
		{
			return posts[i];
		}
	}
	return 0;
}
void Users::ShareMemory(char* str, char* des)
{
	Posts* ptr = SearchPostbyID(str);
	for (int i = 0; i < MemoriesCount && !memories[i]->GetIsShared(); i++)
	{
		if (ptr == memories[i]->GetMemoryPost())
		{
			memories[i]->ShareMemory(des);
		}
	}
}

void Users::ViewHome()
{
	PrintName();
	cout << "-----Home Page\n\n";

	PrintPostsOfFriends();
	PrintPostsOfLikedPages();

}
void Users::ViewMemories()
{
	if (MemoriesCount)
	{
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\nOn This Day\n";

		for (int i = 0; i < MemoriesCount; i++)
		{
			memories[i]->PrintListView();
		}
	}
	else
	{
		cout << "No Memories\n";
	}
}
void Users::ViewFriendList()
{
	cout << FirstName << " " << LastName << " - Friend List" << endl;
	for (int i = 0; Friends[i] != NULL; i++)
	{
		Friends[i]->PrintListView();
	}
}
void Users::ViewLikedPages()
{
	cout << FirstName << " " << LastName << " - Liked Pages" << endl;
	for (int i = 0; LinkedPages[i] != NULL; i++)
	{
		LinkedPages[i]->PrintListView();
	}
}
void Users::ViewTimeline()
{
	PrintName();
	cout << "-----Time Line\n\n";
	PrintSharedMemories();
	for (int i = 0; i < PostCount; i++)
	{
		posts[i]->PrintListView();
		cout << endl;
	}
}

void Users::PrintID()
{
	char* id = GetID();
	cout << id;
}
void Users::PrintName()
{
	cout << FirstName << " " << LastName;
}
void Users::PrintListView()
{
	cout << GetID() << " - " << FirstName << " " << LastName << endl;
}
void Users::PrintDetailView()
{
	PrintListView();
	cout << "FriendList: \n";
	int i = 0;
	while (Friends[i])
	{
		Friends[i]->PrintListView();
		i++;
	}
	i = 0;
	cout << "Liked pages: \n";
	while (LinkedPages[i])
	{
		LinkedPages[i]->PrintListView();
		cout << endl;
		i++;
	}
}
void Users::PrintPosts()
{
	for (int i = 0; i < PostCount; i++)
	{
		if (posts[i]->Is_to_be_Printed())
		{
			posts[i]->PrintListView();
			cout << endl;
		}
	}
}
void Users::PrintSharedMemories()
{
	if (MemoriesCount)
	{
		for (int i = 0; i < MemoriesCount; i++)
		{
			if (memories[i]->GetIsShared())
			{
				cout << "~~~";
				PrintName();
				cout << " shared a memory~~~~........(";
				memories[i]->GetSharedDate().PrintDate();
				cout << ")\n";
				memories[i]->PrintListView();
			}
		}
	}
}
void Users::PrintPostsOfFriends()
{
	int i = 0;
	while (Friends[i])
	{
		Friends[i]->PrintSharedMemories();
		Friends[i]->PrintPosts();
		i++;
	}
}
void Users::PrintPostsOfLikedPages()
{
	int i = 0;
	while (LinkedPages[i])
	{
		LinkedPages[i]->PrintPosts();
		i++;
	}
}


//-----------------------------------Template------------------------------

template<class T>
void DeAllocation(T** Ptr, int Total)
{
	for (int i = 0; i < Total; i++)
	{
		delete[] Ptr[i];
	}
	delete[] Ptr;
}

//-----------------------------------SocialNetwork Class------------------------------

class SocialNetwork
{
private:
	Pages** PageList;
	Users** Userlist;
	Posts** PostList;
	Comments** CommentList;

	int TotalPages;
	int TotalUsers;
	int TotalPosts;
	int TotalComments;

public:
	SocialNetwork();
	~SocialNetwork();

	void Link_PostsandUsers();
	void Link_PostsandPages();

	void LoadPagesfromFile(ifstream&);
	void LoadUsersfromFile(ifstream&);
	void LoadPostsfromFile(ifstream&);
	void LoadCommentsfromFile(ifstream&);

	void Load();
	void Run();

	Pages* SearchPagebyID(char*);
	Users* SearchUserbyID(char*);
	Posts* SearchPostbyID(char*);

	Comments* PostComment(char*, char*, Object*);
	void LikePost(char*, Object*);

	void ViewPost(char*);
	void ViewLikedList(char*);
	void ViewPage(char* str);
};

SocialNetwork::SocialNetwork()								      //Default Constructor
{
	PageList = 0;
	Userlist = 0;
	PostList = 0;
	CommentList = 0;

	TotalPages = 0;
	TotalUsers = 0;
	TotalPosts = 0;
	TotalComments = 0;
}
SocialNetwork::~SocialNetwork()								      //Default Constructor
{
	if (PageList)
	{
		DeAllocation(PageList, TotalPages);
	}
	if (Userlist)
	{
		DeAllocation(Userlist, TotalUsers);
	}
	if (PostList)
	{
		DeAllocation(PostList, TotalPosts);
	}
	if (CommentList)
	{
		DeAllocation(CommentList, TotalComments);
	}

}

void SocialNetwork::Link_PostsandUsers()
{
	int count = 0;
	for (int i = 0; i < TotalUsers; i++)
	{
		count = 0;
		for (int j = 0; j < TotalPosts; j++)
		{
			if (Userlist[i] == PostList[j]->GetSharedBy())
				count++;
		}
		Userlist[i]->SetPostCount(count);
	}

	count = 0;

	for (int i = 0; i < TotalUsers; i++)
	{
		count = 0;
		for (int j = 0; j < TotalPosts; j++)
		{
			if (Userlist[i] == PostList[j]->GetSharedBy())
			{
				Userlist[i]->AddPosts(PostList[j], count);
				count++;
			}
		}
		Userlist[i]->AddMemories();
	}
}
void SocialNetwork::Link_PostsandPages()
{
	int count = 0;

	for (int i = 0; i < TotalPages; i++)
	{
		count = 0;
		for (int j = 0; j < TotalPosts; j++)
		{
			if (PageList[i] == PostList[j]->GetSharedBy())
				count++;
		}
		PageList[i]->SetPostCount(count);
	}

	count = 0;

	for (int i = 0; i < TotalUsers; i++)
	{
		count = 0;
		for (int j = 0; j < TotalPosts; j++)
		{
			if (PageList[i] == PostList[j]->GetSharedBy())
			{
				PageList[i]->AddPosts(PostList[j], count);
				count++;
			}
		}
	}
}

void SocialNetwork::LoadPagesfromFile(ifstream& fin)
{
	int total = 0;
	fin >> total;
	TotalPages = total;
	PageList = new Pages * [total + 1];

	int i = 0;
	for (i = 0; i < total; i++)
	{
		PageList[i] = new Pages;
		PageList[i]->ReadPagesfromFile(fin);
	}
	PageList[total] = NULL;
}
void SocialNetwork::LoadUsersfromFile(ifstream& fin)
{
	char TempBuffer[100];
	fin >> TotalUsers;
	Userlist = new Users * [TotalUsers + 1];

	char*** temp_Friends = new char** [TotalUsers + 1];
	for (int i = 0; i < TotalUsers; i++)
	{
		temp_Friends[i] = new char* [10];
	}
	temp_Friends[TotalUsers] = NULL;

	for (int i = 0; i < TotalUsers; i++)
	{
		Userlist[i] = new Users;
		Userlist[i]->ReadUsersfromFile(fin);

		int j = 0, flag = 1;
		for (j = 0; j < 10 && flag == 1; j++)
		{
			fin >> TempBuffer;
			if (TempBuffer[0] == '-')
				flag = 0;
			temp_Friends[i][j] = new char[4];
			temp_Friends[i][j] = Helper::GetStringFromBuffer(TempBuffer);
		}

		for (j = 0; j < 10 && flag == 0; j++)
		{
			fin >> TempBuffer;
			if (TempBuffer[0] == '-')
				flag = 1;
			if (flag == 0)
			{
				Pages* pagePtr = SearchPagebyID(TempBuffer);
				Userlist[i]->LikePages(pagePtr);
			}
		}
	}

	for (int i = 0; i < TotalUsers; i++)
	{
		int j = 0, flag = 1;
		for (j = 0; j < 10 && flag == 1; j++)
		{
			if (temp_Friends[i][j][0] == '-')
				flag = 0;
			if (flag == 1)
			{
				Users* userPtr = SearchUserbyID(temp_Friends[i][j]);
				Userlist[i]->AddFriend(userPtr);
			}
		}
	}

	for (int i = 0; i < TotalUsers; i++)
	{
		delete[] temp_Friends[i];
	}
	delete[] temp_Friends;
}
void SocialNetwork::LoadPostsfromFile(ifstream& fin)
{
	char TempBuffer[100];
	Object* Ptr = 0;

	fin >> TotalPosts;

	PostList = new Posts * [TotalPosts + 1];
	for (int i = 0; i < TotalPosts; i++)
	{
		PostList[i] = new Posts;
		PostList[i]->ReadPostsFromFile(fin);

		fin >> TempBuffer;		//SharedBy

		if (TempBuffer[0] == 'u')
			Ptr = SearchUserbyID(TempBuffer);
		else
			Ptr = SearchPagebyID(TempBuffer);

		PostList[i]->SetSharedBy(Ptr);

		fin >> TempBuffer;		//Likedby

		int j = 0;
		for (j = 0; TempBuffer[0] != '-'; j++)
		{
			if (TempBuffer[0] == 'u')
			{
				PostList[i]->SetLikedBy(SearchUserbyID(TempBuffer), j);
			}
			else
			{
				PostList[i]->SetLikedBy(SearchPagebyID(TempBuffer), j);
			}

			fin >> TempBuffer;
		}

		PostList[i]->SetLikedBy(NULL, j);
	}
	PostList[TotalPosts] = NULL;

	Link_PostsandUsers();
	Link_PostsandPages();
}
void SocialNetwork::LoadCommentsfromFile(ifstream& fin)
{
	char TempBuffer[100];

	fin >> TotalComments;

	CommentList = new Comments * [TotalComments];
	for (int i = 0; i < TotalComments; i++)
	{
		CommentList[i] = new Comments;

		fin >> TempBuffer;
		CommentList[i]->SetID(Helper::GetStringFromBuffer(TempBuffer));

		fin >> TempBuffer;
		Posts* Ptr = SearchPostbyID(TempBuffer);
		Ptr->UpdateCommentsList(CommentList[i]);

		fin >> TempBuffer;
		if (TempBuffer[0] == 'u')
			CommentList[i]->SetCommentBy(SearchUserbyID(TempBuffer));
		else
			CommentList[i]->SetCommentBy(SearchPagebyID(TempBuffer));

		fin.getline(TempBuffer, 100);
		CommentList[i]->SetMessage(Helper::GetStringFromBuffer(TempBuffer));
	}

}

Pages* SocialNetwork::SearchPagebyID(char* id)
{
	for (int i = 0; i < TotalPages; i++)
	{
		if (PageList[i]->CompareID(id))
			return PageList[i];
	}
	return NULL;
}
Users* SocialNetwork::SearchUserbyID(char* id)
{
	for (int i = 0; i < TotalUsers; i++)
	{
		if (Userlist[i]->CompareID(id))
			return Userlist[i];
	}
	return NULL;
}
Posts* SocialNetwork::SearchPostbyID(char* id)
{
	for (int i = 0; i < TotalPosts; i++)
	{
		if (PostList[i]->CompareID(id))
			return PostList[i];
	}
	return NULL;
}

Comments* SocialNetwork::PostComment(char* str, char* content, Object* commentedBy)
{
	char id[4] = "c14";

	Comments* newComment = new Comments;

	newComment->SetID(Helper::GetStringFromBuffer(id));
	newComment->SetMessage(Helper::GetStringFromBuffer(content));
	newComment->SetCommentBy(commentedBy);

	Posts* ptr = SearchPostbyID(str);
	if (ptr)
	{
		ptr->UpdateCommentsList(newComment);
	}
	return newComment;
}
void SocialNetwork::LikePost(char* str, Object* like)
{
	Posts* ptr = SearchPostbyID(str);
	if (ptr)
	{
		int i = ptr->Get_i_LikedBy();
		ptr->SetLikedBy(like, i);
		i++;
		ptr->SetLikedBy(0, i);
	}
	else
	{
		cout << "No Result Found\n";
	}
}

void SocialNetwork::ViewPost(char* str)
{
	Posts* ptr = SearchPostbyID(str);
	if (ptr)
	{
		ptr->PrintListView();
	}
	else
	{
		cout << "No results Found\n";
	}
}
void SocialNetwork::ViewLikedList(char* str)
{
	Posts* ptr = SearchPostbyID(str);
	if (ptr)
	{
		ptr->PrintLikedBy();
	}
	else
	{
		cout << "No Result Found\n";
	}
}
void SocialNetwork::ViewPage(char* str)
{
	Pages* ptr = SearchPagebyID(str);
	if (ptr)
	{
		ptr->ViewPost();
	}
	else
	{
		cout << "No Result Found\n";
	}
}

void SocialNetwork::Load()
{
	cout << endl;

	Date::SetCurrentDate(15, 11, 2017);
	Date::PrintCurrentDate();

	ifstream fin1("Pages.txt");
	LoadPagesfromFile(fin1);
	fin1.close();

	ifstream fin2("Users.txt");
	LoadUsersfromFile(fin2);
	fin2.close();

	ifstream fin3("Posts.txt");
	LoadPostsfromFile(fin3);
	fin3.close();

	ifstream fin4("Comments.txt");
	LoadCommentsfromFile(fin4);
	fin4.close();
}
void SocialNetwork::Run()
{
	cout << "\n---------------------------------------------------------------------------" << endl;

	Users* CurrentUser = 0;
	char Buffer[4] = "u7";
	char* bufferPtr = Buffer;
	CurrentUser = SearchUserbyID(bufferPtr);

	cout << "Command:		Set current user \"";
	CurrentUser->PrintID();
	cout << "\"" << endl;
	CurrentUser->PrintName();
	cout << " successfully set as Current User." << endl;

	cout << "\n---------------------------------------------------------------------------" << endl;
	cout << "\nCommand:		View Friend List" << endl;

	CurrentUser->ViewFriendList();

	cout << "\n---------------------------------------------------------------------------" << endl;
	cout << "\nCommand:		View Liked Pages" << endl;
	CurrentUser->ViewLikedPages();
	cout << "\n---------------------------------------------------------------------------" << endl;
	cout << "Command: ViewHome\n";
	cout << "-------------------------------------------------------------------\n";
	CurrentUser->ViewHome();
	cout << "-------------------------------------------------------------------\n";
	cout << "Command: ViewTimeLine\n";
	cout << "-------------------------------------------------------------------\n";
	CurrentUser->ViewTimeline();
	cout << "Command: ViewLikedList\n";
	cout << "-------------------------------------------------------------------\n";
	cout << "Post Liked By:\n";
	char id0[7] = "post5";
	ViewLikedList(id0);
	cout << "Command: LikePost\n";
	LikePost(id0, CurrentUser);
	cout << "Command: ViewLikedList\n";
	cout << "-------------------------------------------------------------------\n";
	cout << "Post Liked By:\n";
	ViewLikedList(id0);
	cout << "-------------------------------------------------------------------\n";
	cout << "Command: PostComment\n";
	char id1[7] = "post4";
	char text1[26] = "Good Luck For Your Result";
	Comments* comment = PostComment(id1, text1, CurrentUser);
	cout << "Command: ViewPost\n";
	cout << "-------------------------------------------------------------------\n";
	ViewPost(id1);
	cout << "-------------------------------------------------------------------\n";
	cout << "Command: PostComment\n";
	char id2[7] = "post8";
	char text2[22] = "Thanks for the wishes";
	Comments* comment1 = PostComment(id2, text2, CurrentUser);
	cout << "Command: ViewPost\n";
	cout << "-------------------------------------------------------------------\n";
	ViewPost(id2);
	cout << "Command: SeeMemories\n";
	cout << "-------------------------------------------------------------------\n";
	CurrentUser->ViewMemories();
	cout << "Command: ShareMemory\n";
	cout << "-------------------------------------------------------------------\n";
	char id3[7] = "post10";
	char text3[52] = "Never thought I will be specialist in this field...";
	CurrentUser->ShareMemory(id3, text3);
	cout << "-------------------------------------------------------------------\n";
	cout << "Command: ViewTimeLine\n";
	cout << "-------------------------------------------------------------------\n";
	CurrentUser->ViewTimeline();
	cout << "Command: ViewPage\n";
	cout << "-------------------------------------------------------------------\n";
	char id4[3] = "p1";
	ViewPage(id4);
	char Buffer2[4] = "u11";
	bufferPtr = Buffer2;
	CurrentUser = SearchUserbyID(bufferPtr);
	CurrentUser->PrintName();
	cout << " successfully set as current user\n";
	cout << "-------------------------------------------------------------------\n";
	cout << "Command: ViewHome\n";
	cout << "-------------------------------------------------------------------\n";
	CurrentUser->ViewHome();
	cout << "-------------------------------------------------------------------\n";
	cout << "Command: ViewTimeLine\n";
	cout << "-------------------------------------------------------------------\n";
	CurrentUser->ViewTimeline();
	delete[] comment1;
	delete[] comment;
}

int main()
{
	cout << "Project OOP" << endl;
	cout << "Name: Fatima Imran" << endl;
	cout << "RollNo: 22L-6946" << endl;

	SocialNetwork Facebook;
	Facebook.Load();
	Facebook.Run();

	cout << endl;
	system("pause");
	return 0;
}