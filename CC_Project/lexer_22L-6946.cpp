#include<iostream>
#include <fstream>
#include<cstring>
#include <string>
#include <unordered_map>
#include<sstream>
#include<vector>
#include<algorithm>
#include <sstream>
#define IB_SIZE 25

using namespace std;


//------------------------CLEAN CODE-------------------------
string removeComments(const string& code) {
	string result;
	bool inMultiLine = false;
	istringstream iss(code);
	string line;

	while (getline(iss, line)) {
		string cleanedLine;
		bool skipLine = false;

		for (size_t i = 0; i < line.size(); ++i) {
			if (!inMultiLine && i + 1 < line.size() && line[i] == '/' && line[i + 1] == '*') {
				inMultiLine = true;
				i++;
			}
			else if (inMultiLine && i + 1 < line.size() && line[i] == '*' && line[i + 1] == '/') {
				inMultiLine = false;
				i++;
			}
			else if (!inMultiLine && i + 1 < line.size() && line[i] == '/' && line[i + 1] == '/') {
				break; 
			}
			else if (!inMultiLine) {
				cleanedLine += line[i]; 
			}
		}

		
		size_t start = cleanedLine.find_first_not_of(" \t");
		size_t end = cleanedLine.find_last_not_of(" \t");

		if (start != string::npos && end != string::npos) {
			cleanedLine = cleanedLine.substr(start, end - start + 1);
			result += cleanedLine + "\n";  
		}
	}

	return result;
}


void CleanCode(const string& filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cerr << "Could not open input file!" << endl;
	}

	stringstream buffer;
	buffer << inFile.rdbuf();
	inFile.close();

	string code = buffer.str();

	string cleanedCode = removeComments(code);
	
	ofstream outFile(filename); 
	if (!outFile.is_open()) {
		cerr << "Could not open output file!" << endl;
	}

	outFile << cleanedCode;
	outFile.close();
}


//--------------------------LEXER---------------------------

int findIndex(const vector<string>& vec, const string& target) {
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] == target) {
			return i;  // Return the index where it's found
		}
	}
	return -1;  // Not found
}

vector<string> SymbolTable;

class HashMap {
private:
	unordered_map<string, int> map;

public:
	
	void populateFromFile(const string& filename) {
		ifstream file(filename);
		string word;
		int id;

		if (!file) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		while (file >> id >> word) {
			map[word] = id;
		}

		file.close();
	}

	bool isKeyword(const string& word) {
		return map.find(word) != map.end();
	}

	int getValue(const string& word) {
		if (isKeyword(word)) {
			return map[word];
		}
		return -1; // Return -1 if not a keyword
	}

	void printMap() { // Debugging method
		for (const auto& pair : map) {
			cout << pair.first << " -> " << pair.second << endl;
		}
	}
};

int getchmap(char ch, const int& state) {
	if ((ch == 'e' || ch == 'E') && (state == 10 || state == 7))
		return 8;
	else if (state == 10 && !isdigit(ch))
		return 6;
	else if (isalpha(ch))
		return 0;
	else if (ch == '_')
		return 1;
	else if (isdigit(ch))
		return 2;
	else if (!isalnum(ch) && ch != '_' && (state == 3 || state == 2))
		return 3;	//other 1
	else if (ch == '+')
		return 4;
	else if (ch == '-')
		return 5;
	else if (ch == '.')
		return 7;
	else if (!isdigit(ch) && (state == 7 || state == 10 || state == 14)) 
		return 6; // Other 2
	else if (strchr("*[](){}", ch))
		return 9;
	else if (ch == ':')
		return 10;
	else if (ch == '=')
		return 11;
	else if (strchr("\"/%*", ch))
		return 12;
	else if (ch == '<')
		return 13;
	else if (ch == '>')
		return 14;
	else if (!strchr("<=>", ch) && state == 21)
		return 15;	//other 5
	else if (!strchr("=>", ch) && state == 26)
		return 16;	//other 6
	else if (ch == '|')
		return 17;
	else if (ch == '&')
		return 18;
	else if (ch == '!')
		return 19;
	else if (!isalpha(ch) && (state == 40 || state == 45 || state == 51 || state == 57 || state == 62 || state == 67 || state == 73 || state == 77 || state == 85 || state == 81))
		return 27;	//other 7
	else if ((isalnum(ch) || ch == '_') && (state == 40 || state == 45 || state == 51 || state == 57 || state == 62 || state == 67 || state == 73 || state == 77 || state == 85 || state == 81))
		return 23;	//other 8
	else if (state == 16 && ch == ' ')
		return 25;
	else
		return -1;	//error

}

void Scanner(const string &filename) {


	ifstream fin(filename);
	if (!fin) {
		cerr << "Error Opening the File!";
		return;
	}
	else {

		//-------------------Keywords--------------------

		HashMap keywordMap;
		keywordMap.populateFromFile("Keyword.txt");


		//-------------------Accept--------------------
		vector<int> Accept(91, 0);
		ifstream ac("Accept.txt");
		if (!ac) {
			cerr << "Error opening file: "<< endl;
			return;
		}

		int p = 0;
		while (ac >> p) {
			Accept[p] = 1;
		}
		ac.close();

		//-------------------Advance--------------------
		vector<vector<int>> Advance(91, vector<int>(46, -1));
		ifstream ad("Advance.txt");
		int b, c, d;
		while (ad >> b >> c >> d) Advance[b][c] = d;
		ad.close();

		//-----------------Transition Table--------------------
		vector<vector<int>> TT(91, vector<int>(46, -1));
		ifstream tt("TT.txt");
		while (tt >> b >> c >> d) TT[b][c] = d;
		tt.close();

		ofstream fout("Token.txt");
		ofstream s("Symbol_Table_22L-6946.txt");
		ofstream e("Error_22L-6946.txt");
		ofstream l("Literal_Table_22L-6946.txt");

		char IB1[IB_SIZE + 1] = { 0 };
		char IB2[IB_SIZE + 1] = { 0 };
		bool IB1or2 = true;
		string leftover = "";

		int id = 1;
		int lit = 1;
		char* IB;
		string toProcess;

		while (fin.read(IB1or2 ? IB1 : IB2, IB_SIZE) || fin.gcount()) {

			IB = IB1or2 ? IB1 : IB2;  
			
			IB[fin.gcount()] = '\0';
			int bufferSize = fin.gcount();
			IB[bufferSize] = '\0';
			size_t splitPos = 0;

			string chunk = leftover + string(IB, bufferSize);
			splitPos = chunk.find_last_of(" :\n", IB_SIZE - 1);
			string toProcess;
			toProcess = chunk.substr(0, splitPos + 1);
			leftover = chunk.substr(splitPos + 1);
			IB = const_cast<char*>(toProcess.c_str());
			

			if (bufferSize == 0) break;

			char ch = ' ';
			int state = 0; //start state
			int newstate = 0;
			int lb = 0;
			int fp = 0;
			bool error = false;

			while (fp < bufferSize && IB[fp]!='\0') {
				state = 0;
				error = false;

				if (IB[fp] == '\n') {
					fp++;
					lb = fp;
					fout << endl;
				}
				if (IB[fp] == ' ') {
					fp++;
					lb = fp;
				}
					

				ch = getchmap(IB[fp], state);
				if (ch == -1) { error = true; break; }
				while (ch == -2) { ch = getchmap(IB[++fp], state); ++lb;}

				if (IB[fp] == '"') {
					fout << "<lit," << lit << ">";
					fp++;

					while (fp < IB_SIZE && IB[fp] != '"') {
						l << IB[fp];
						fp++;
					}
					l << "\n";

					if (fp < IB_SIZE) {
						fp += 2;
						lb = fp;
					}
					else {
						e << "Error: Unclosed string literal\n";
					}
					lit++;
				}

				if (fp + 1 < IB_SIZE) {  
					if (IB[fp] == '+' && IB[fp + 1] == '+') {
						fout << "< ++ >";
						fp += 2;  
					}
					if (IB[fp] == '+' && IB[fp + 1] == '=') {
						fout << "< += >";
						fp += 2;
					}
					if (IB[fp] == '=' && IB[fp + 1] == '=') {
						fout << "< == >";
						fp += 2;
					}
					if (IB[fp] == ' ') {
						while (IB[fp] == ' ' && fp + 1 < IB_SIZE) {
							fp++;
							lb++;
						}
					}
					if (IB[fp] == '=') {
						fout << "<=>";
						fp += 2;
						lb = fp;
					}
					if (isdigit(IB[fp]) && IB[fp+1]==' ') {
						fout << "<"<<IB[fp] << ">";
						fp += 2;
						lb = fp;
					}
					if (isalpha(IB[fp]) && IB[fp + 1] == ' ') {
						fout << "<" << IB[fp] << ">";
						fp += 2;
						lb = fp;
					}
					if (isalpha(IB[fp]) && IB[fp + 1] == ' ') {
						fout << "<" << IB[fp] << ">";
						fp += 2;
						lb = fp;
					}
					
				}
				ch = getchmap(IB[fp], state);
				while (!Accept[state] && !error) {

					while (IB[fp] != '\0'){
						string token;
						int i = fp;
						int j = 0;

						while (IB[i] != ' ' && IB[i] != '\0' && IB[i]!='\n') {
							token += IB[i];
							i++;
							j++;
						}
						token.resize(j);

						bool flag = 0;
						

						for (int f = 0; f < j; f++) {
							if (token[f] == '_') {
								flag = 1;
								fp = i;
								break;
							}
						}

						int index = findIndex(SymbolTable, token);

						if (index!=-1) {
							fout << "<id," << index+1 << ">";
							

							for (int k = lb; k < fp; k++) {
								
							}

							if (fp == 25)
								continue;
							fp++;
							lb = fp;
							ch = getchmap(IB[fp], state);

						}
						else if (flag == 1)
						{
							string c;

							s << id << " ";

							for (int k = lb; k < fp; k++) {
								s << IB[k];
								c += IB[k];

							}
							
							SymbolTable.push_back(c);

							s << endl;



							fout << "<id," << id << ">";
							if (fp == 25)
								continue;
							fp++;
							id++;
							lb = fp;
							ch = getchmap(IB[fp], state);
							flag = 0;
						}
						
						else if (keywordMap.isKeyword(token)) {
							fout << "<keyword," << keywordMap.getValue(token) << ">";
							fp = i + 1;
							lb = i + 1;
							ch = getchmap(IB[fp], state);
						}
						else if (IB[fp] == '=' && IB[fp+1] == ' ') {
							fout << "<=>";
							fp += 2;
							lb = fp;
						}
						else if (IB[fp] == '"') {
							fout << "<lit," << lit << ">";
							fp++;

							while (fp < IB_SIZE && IB[fp] != '"') {
								l << IB[fp];
								fp++;
							}
							l << "\n";

							if (fp < IB_SIZE) {
								fp += 2;
							}
							else {
								e << "Error: Unclosed string literal\n";
							}
							lit++;
						}
						else
							break;
					}
					
					if (IB[fp] == '\0')
						break;
					
					ch = getchmap(IB[fp], state);
					newstate = TT[state][ch];
					if (Advance[state][ch] == 1 && IB[fp]!='\0') {
						
						fp++;
						if (IB[fp] == ' ' && isdigit(IB[fp - 1]) && !isdigit(IB[fp - 2])) {
							state = newstate;
						}
						ch = getchmap(IB[fp], state);
							
						if (ch == -1) {
							error = true;
						}
						
					}
					state = newstate;
				}
				
				if (error) {
					
					string c;
					s << id << " ";
					for (int l = lb; l < fp; l++) {
						e << IB[l];
						s << IB[l];
						c += IB[l];
					}
					e << endl;
					s << endl;
					SymbolTable.push_back(c);
					fout << "<id," << id << ">";
					id++;
					fp++;
					lb = fp;
				}
				else if (state == 16) {
					fout << "<" << IB[fp] << ">";
					fp++;
					lb = fp;
				}
				else if (state == 18 || (IB[fp]==':' && IB[fp+1]==':')) {
					fout << "<::>";
					fp++;
					lb = fp;
				}
				else if (state == 19) {
					fout << "<:=>";
					fp += 2;
					lb = fp;
				}
				else if (state == 20) {
					fout << "<" << IB[fp] << ">";
					fp++;
					lb = fp;
				}
				else if (state == 22) {
					fout << "< < >";
					fp++;
					lb = fp;
				}
				else if (state == 23) {
					fout << "< > >";
					lb = fp;
				}
				else if (state == 24) {
					fout << "< << >";
					fp += 2;
					lb = fp;
				}
				else if (state == 25) {
					fout << "< <= >";
					fp += 2;
					lb = fp;
				}
				else if (state == 28) {
					fout << "< >> >";
				}
				else if (state == 29) {
					fout << "< >= >";
					fp += 2;
					lb = fp;
				}
				else if (state == 27) {
					fout << "< > >";
					fp += 2;
					lb = fp;
				}
				else if (state == 31) {
					fout << "< || >";
					fp += 2;
					lb = fp;
				}
				else if (state == 33) {
					fout << "< && >";
					fp += 2;
					lb = fp;
				}
				else if (state == 35) {
					fout << "< != >";
					lb = fp;
				}
				else if (state == 87) {
					fout << "< ++ >";
					fp += 2;
					lb = fp;
				}
				else if (state == 88) {
					fout << "< += >";
					fp += 2;
					lb = fp;
				}
				else if (state == 90) {
					fout << "< == >";
					fp += 2;
					lb = fp;
				}
				else if (state == 8 || state==11 || state==15) {
					fout << "<";
					for (int k = lb; k < fp; k++) {
						fout << IB[k];
					}
					fout << ">";
					fp++;
					lb = fp;
				}
				else {
					if (Accept[state]) {
						string c;
						s << id << " ";
						
						for (int k = lb; k < fp; k++) {
							s << IB[k];
							c += IB[k];
						}
						s << endl;
						SymbolTable.push_back(c);
						fout << "<id," << id << ">";
						id++;
						fp++;
						lb = fp;

					}
				}

			}

			IB1or2 = !IB1or2;
		}

		while(!leftover.empty()) {

			size_t splitPos = 0;

			string chunk = leftover;
			if (leftover.length() > 25) {
				splitPos = chunk.find_last_of(" \n", IB_SIZE - 1);
				toProcess = chunk.substr(0, splitPos + 1);
				leftover = chunk.substr(splitPos + 1);
				IB = const_cast<char*>(toProcess.c_str());
			}
			else
			{
				IB = const_cast<char*>(chunk.c_str());
				leftover = "";
			}
			
			char ch = ' ';
			int state = 0; //start state
			int newstate = 0;
			int lb = 0;
			int fp = 0;
			bool error = false;
			int bufferSize = chunk.length();

			while (fp < bufferSize && IB[fp] != '\0') {
				state = 0;
				error = false;

				if (IB[fp] == '\n') {
					fp++;
					lb = fp;
					fout << endl;
				}
				if (IB[fp] == ' ') {
					fp++;
					lb = fp;
				}


				ch = getchmap(IB[fp], state);
				if (ch == -1) { error = true; break; }
				while (ch == -2) { ch = getchmap(IB[++fp], state); ++lb; }

				if (IB[fp] == '"') {
					fout << "<lit," << lit << ">";
					fp++;

					while (fp < IB_SIZE && IB[fp] != '"') {
						l << IB[fp];
						fp++;
					}
					l << "\n";

					if (fp < IB_SIZE) {
						fp += 2;
						lb = fp;
					}
					else {
						e << "Error: Unclosed string literal\n";
					}
					lit++;
				}

				if (fp + 1 < IB_SIZE) {
					if (IB[fp] == '+' && IB[fp + 1] == '+') {
						fout << "< ++ >";
						fp += 2;
					}
					if (IB[fp] == '+' && IB[fp + 1] == '=') {
						fout << "< += >";
						fp += 2;
					}
					if (IB[fp] == '=' && IB[fp + 1] == '=') {
						fout << "< == >";
						fp += 2;
					}
					if (IB[fp] == ' ') {
						while (IB[fp] == ' ' && fp + 1 < IB_SIZE) {
							fp++;
							lb++;
						}
					}
					if (IB[fp] == '=') {
						fout << "<=>";
						fp += 2;
						lb = fp;
					}
					if (isdigit(IB[fp]) && IB[fp + 1] == ' ') {
						fout << "<" << IB[fp] << ">";
						fp += 2;
						lb = fp;
					}
					if (isalpha(IB[fp]) && IB[fp + 1] == ' ') {
						fout << "<" << IB[fp] << ">";
						fp += 2;
						lb = fp;
					}
					if (isalpha(IB[fp]) && IB[fp + 1] == ' ') {
						fout << "<" << IB[fp] << ">";
						fp += 2;
						lb = fp;
					}

				}
				ch = getchmap(IB[fp], state);
				while (!Accept[state] && !error) {

					while (IB[fp] != '\0') {
						string token;
						int i = fp;
						int j = 0;

						while (IB[i] != ' ' && IB[i] != '\0' && IB[i] != '\n') {
							token += IB[i];
							i++;
							j++;
						}
						token.resize(j);

						bool flag = 0;


						for (int f = 0; f < j; f++) {
							if (token[f] == '_') {
								flag = 1;
								fp = i;
								break;
							}
						}

						int index = findIndex(SymbolTable, token);

						if (index != -1) {
							fout << "<id," << index + 1 << ">";


							for (int k = lb; k < fp; k++) {

							}

							if (fp == 25)
								continue;
							fp++;
							lb = fp;
							ch = getchmap(IB[fp], state);
						}
						else if (flag == 1)
						{
							string c;
							s << id << " ";

							for (int k = lb; k < fp; k++) {
								s << IB[k];
								c += IB[k];
							}
							s << endl;
							SymbolTable.push_back(c);
							fout << "<id," << id << ">";
							if (fp == 25)
								continue;
							fp++;
							lb = fp;
							ch = getchmap(IB[fp], state);
							flag = 0;
						}

						else if (keywordMap.isKeyword(token)) {
							fout << "<keyword," << keywordMap.getValue(token) << ">";
							fp = i + 1;
							lb = i + 1;
							ch = getchmap(IB[fp], state);
						}
						else if (IB[fp] == '=' && IB[fp + 1] == ' ') {
							fout << "<=>";
							fp += 2;
							lb = fp;
						}
						else if (IB[fp] == '"') {
							fout << "<lit," << lit << ">";
							fp++;

							while (fp < IB_SIZE && IB[fp] != '"') {
								l << IB[fp];
								fp++;
							}
							l << "\n";

							if (fp < IB_SIZE) {
								fp += 2;
							}
							else {
								e << "Error: Unclosed string literal\n";
							}
							lit++;
						}
						else
							break;
					}

					if (IB[fp] == '\0')
						break;

					ch = getchmap(IB[fp], state);
					newstate = TT[state][ch];
					if (Advance[state][ch] == 1 && IB[fp] != '\0') {

						fp++;
						if (IB[fp] == ' ' && isdigit(IB[fp - 1]) && !isdigit(IB[fp - 2])) {
							state = newstate;
						}
						ch = getchmap(IB[fp], state);

						if (ch == -1) {
							error = true;
						}

					}
					state = newstate;
				}

				if (error) {

					s << id << " ";
					for (int l = lb; l < fp; l++) {
						e << IB[l];
						s << IB[l];
					}
					e << endl;
					s << endl;
					fout << "<id," << id << ">";
					id++;
					fp++;
					lb = fp;
				}
				else if (state == 16) {
					fout << "<" << IB[fp] << ">";
					fp++;
					lb = fp;
				}
				else if (state == 18 || (IB[fp] == ':' && IB[fp + 1] == ':')) {
					fout << "<::>";
					fp++;
					lb = fp;
				}
				else if (state == 19) {
					fout << "<:=>";
					fp += 2;
					lb = fp;
				}
				else if (state == 20) {
					fout << "<" << IB[fp] << ">";
					fp++;
					lb = fp;
				}
				else if (state == 22) {
					fout << "< < >";
					fp++;
					lb = fp;
				}
				else if (state == 23) {
					fout << "< > >";
					lb = fp;
				}
				else if (state == 24) {
					fout << "< << >";
					fp += 2;
					lb = fp;
				}
				else if (state == 25) {
					fout << "< <= >";
					fp += 2;
					lb = fp;
				}
				else if (state == 28) {
					fout << "< >> >";
				}
				else if (state == 29) {
					fout << "< >= >";
					fp += 2;
					lb = fp;
				}
				else if (state == 27) {
					fout << "< > >";
					fp += 2;
					lb = fp;
				}
				else if (state == 31) {
					fout << "< || >";
					fp += 2;
					lb = fp;
				}
				else if (state == 33) {
					fout << "< && >";
					fp += 2;
					lb = fp;
				}
				else if (state == 35) {
					fout << "< != >";
					lb = fp;
				}
				else if (state == 87) {
					fout << "< ++ >";
					fp += 2;
					lb = fp;
				}
				else if (state == 88) {
					fout << "< += >";
					fp += 2;
					lb = fp;
				}
				else if (state == 90) {
					fout << "< == >";
					fp += 2;
					lb = fp;
				}
				else if (state == 8 || state == 11 || state == 15) {
					fout << "<";
					for (int k = lb; k < fp; k++) {
						fout << IB[k];
					}
					fout << ">";
					fp++;
					lb = fp;
				}
				else {
					if (Accept[state]) {
						string c;
						s << id << " ";

						for (int k = lb; k < fp; k++) {
							s << IB[k];
							c += IB[k];
						}
						s << endl;
						SymbolTable.push_back(c);
						fout << "<id," << id << ">";
						id++;
						fp++;
						lb = fp;

					}
				}

			}
		}

		ad.close();
		fout.close();
		s.close();
		l.close();
		e.close();

		

	}
	cout << "Lexical Analyzer Done" << endl;
}

string ID = "";
string value = "";
string key = "";
string label1 = "";
string label2 = "";
string label3 = "";


//------------------THREE ADDRESS CODE-----------------------
int tempVarCount = 1;
int tempLabelCount = 1;

string newTemp() {
	return "t" + to_string(tempVarCount++);
}

string newLabel() {
	return "L" + to_string(tempLabelCount++);
}

struct Entry {
	int key;
	string value;
};

vector<Entry> identifiers;
vector<Entry> keywords;
vector<string> Lit;


ofstream tac("TAC.txt");



//--------------------------PARSER---------------------------

struct StringQueue {
	string* data;
	int front = 0;
	int rear = 0;
	int capacity;

	StringQueue() {
		capacity = 1000;
		data = new string[capacity];
		front = 0;
		rear = 0;
	}

	StringQueue(int max_size) {
		capacity = max_size;
		data = new string[capacity];
	}

	~StringQueue() {
		delete[] data;
	}

	bool isEmpty() {
		return front == rear;
	}

	bool isFull() {
		return rear == capacity;
	}

	void enqueue(const string& str) {
		if (!isFull()) {
			data[rear++] = str;
		}
		else {
			cerr << "Queue is full!\n";
		}
	}

	string dequeue() {
		if (!isEmpty()) {
			return data[front++];
		}
		else {
			cerr << "Queue is empty!\n";
			return "";
		}
	}

	string peek() {
		if (!isEmpty()) {
			return data[front];
		}
		else {
			return "";
		}
	}
};

void ArgList(StringQueue& queue) {
	
}

void IdentList(StringQueue& queue);

void I(StringQueue& queue) {
	string token = queue.peek();
	if (token.find("<,>") == 0) {
		if (!queue.isEmpty())
			token = queue.dequeue();
		
		cout << "|                ";
		cout << "|--- ,\n";

		cout << "|                ";
		cout << "|___ IdentList\n";
		IdentList(queue);
	}
	else
		return;
}

void IdentList(StringQueue& queue) {
	string token = queue.peek();
	if (token.find("<id,") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|            |  ";
		cout << "|___ Identifier\n";

		int id = 0;
		size_t start = token.find(",") + 1;
		size_t end = token.find(">");
		if (start != string::npos && end != string::npos && end > start) {
			string idStr = token.substr(start, end - start);
			id = stoi(idStr);
		}

		for (const auto& entry : identifiers) {
			if (entry.key == id) {
				value = entry.value;
			}
		}
			

		cout << "|            |  ";
		cout << "|___ I\n";

		I(queue);
	}
	else if (token.find("<lit,") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		string litId = "";

		if (token.find("<lit,") == 0) {
			size_t start = token.find(",") + 1;
			size_t end = token.find(">");

			if (start != string::npos && end != string::npos && start < end) {
				litId = token.substr(start, end - start);  
			}
		}

		int litID = stoi(litId);
		value = Lit[litID-1];


		cout << "|            |  ";
		cout << "|___ StringLiteral\n";

		cout << "|            |  ";
		cout << "|___ I\n";

		I(queue);
	}
	else
		cout << "Error: Identifier not found in IdentList\n";
}

void Declaration(StringQueue& queue) {
	string token;
	if (!queue.isEmpty())
		token = queue.dequeue();

	if (token.find("<keyword,") == 0) {
		cout << "|            ";
		cout << "|___ Type\n";

		if (token.find("<keyword,61>") == 0) {	//input
			key = "READ";
		}

		if (token.find("<keyword,62>") == 0) {	//output
			key = "OUT";
		}

		cout << "|            ";
		cout << "|___ IdentList\n";

		IdentList(queue);

		string token;
		if (!queue.isEmpty())
			token = queue.dequeue();

		if (token.find("<::>") == 0) {

			cout << "|            ";
			cout << "|--- ::\n";
		}
		else
			cout << "Error: :: not found in Declaration" << endl;

	}
	else
		cout << "Error: Type not found in declaration" << endl;
}

void Expr(StringQueue& queue);

void Factor(StringQueue& queue) {

	string token;
	token = queue.peek();

	if (token.find("<(>") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|                              ";
		cout << "|--- (\n";

		cout << "|                              ";
		cout << "|--- Expression\n";

		Expr(queue);

		if (token.find("<)>") == 0) {

			if (!queue.isEmpty())
				token = queue.dequeue();

			cout << "|                              ";
			cout << "|--- )\n";

		}
		else
			cout << "Error: ) not found in Factor \n";
	}
	else if (token.find("<id,") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|                              ";
		cout << "|___ Identifier\n";

		int id = 0;
		size_t start = token.find(",") + 1;
		size_t end = token.find(">");
		if (start != string::npos && end != string::npos && end > start) {
			string idStr = token.substr(start, end - start);
			id = stoi(idStr);
		}

		for (const auto& entry : identifiers) {
			if (entry.key == id) {
				value = entry.value;
			}
		}

		string temp = newTemp();

		tac << temp << " = " << value << "\n";
		tac << ID << " = " << temp << "\n";

	}
	else if (isdigit(token[1]) || token[1] == '+' || token[1] == '-') {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|                              ";
		cout << "|___ Number\n";

		size_t start = token.find("<");
		size_t end = token.find(">");

		if (start != string::npos && end != string::npos && end > start + 1) {
			value = token.substr(start + 1, end - start - 1); // Extract number as string
		}

		string temp = newTemp();

		tac << temp << " = " << value << "\n";
		tac << ID << " = " << temp << "\n";

	}
	else if (token.find("<lit,") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|                              ";
		cout << "|___ String Literal\n";

		size_t start = token.find(",") + 1;
		size_t end = token.find(">");
		string idStr = "";

		if (start != string::npos && end != string::npos && end > start) {
			idStr = token.substr(start, end - start); // ID as string
		}

		int litID = stoi(idStr);

		value = Lit[litID-1];

		string temp = newTemp();

		tac << temp << " = " << value << "\n";
		tac << ID << " = " << temp << "\n";


	}
	else if (token.find("<keyword,19>") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|                              ";
		cout << "|___ True\n";

		string temp = newTemp();

		tac << temp << " = True\n";
		tac << ID << " = " << temp << "\n";

	}
	else if (token.find("<keyword,29>") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|                              ";
		cout << "|___ False\n";

		string temp = newTemp();

		tac << temp << " = False\n";
		tac << ID << " = " << temp << "\n";
	}
	else
		cout << "Error: Factor \n";
}

void T(StringQueue& queue) {

	string token;
	token = queue.peek();

	if (token.find("<*>") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();


		cout << "|                            ";
		cout << "|--- *\n";

		cout << "|                            ";
		cout << "|___ Factor\n";

		Factor(queue);
	}
	else if (token.find("</>") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();


		cout << "|                            ";
		cout << "|--- /\n";

		cout << "|                            ";
		cout << "|___ Factor\n";

		Factor(queue);
	}
	else
		cout << "Error: T" << endl;
}

void Term_prime(StringQueue& queue) {


	string token;
	token = queue.peek();

	if (token.find("<*>") != 0 && token.find("</>") != 0) {
		cout << "|                          ";
		cout << "|___ NULL\n";
		return;
	}

	cout << "|                          ";
	cout << "|___ T\n";
	T(queue);
	cout << "|                          ";
	cout << "|___ Term_prime\n";
	Term_prime(queue);
}

void Term(StringQueue& queue) {
	cout << "|                        ";
	cout << "|___ Factor\n";
	Factor(queue);
	cout << "|                        ";
	cout << "|___ Term_prime\n";
	Term_prime(queue);
}

void M(StringQueue& queue) {

	string token;

	token = queue.peek();

	if (token.find("<+>") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();


		cout << "|                      ";
		cout << "|--- +\n";

		cout << "|                      ";
		cout << "|___ Term\n";

		Term(queue);
	}
	else if (token.find("<->") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();


		cout << "|                      ";
		cout << "|--- -\n";

		cout << "|                      ";
		cout << "|___ Term\n";

		Term(queue);
	}
	else
		cout << "Error: M" << endl;
	
}

void Mag_prime(StringQueue& queue) {

	string token;
	token = queue.peek();

	if (token.find("<+>") != 0 && token.find("<->") != 0) {
		cout << "|                    ";
		cout << "|___ NULL\n";
		return;
	}

	cout << "|                    ";
	cout << "|___ M\n";
	M(queue);
	cout << "|                    ";
	cout << "|___ Mag_prime\n";
	Mag_prime(queue);
}

void Compare(StringQueue& queue) {

	string token;
	token = queue.peek();

	if (token.find("<==>") == 0) {
		cout << "|                ";
		cout << "|--- ==\n";
	}
	else if (token.find("<<>") == 0) {
		cout << "|                ";
		cout << "|--- <\n";
	}
	else if (token.find("<>>") == 0) {
		cout << "|                ";
		cout << "|--- >\n";
	}
	else if (token.find("<<=>") == 0) {
		cout << "|                ";
		cout << "|--- <=\n";
	}
	else if (token.find("<>=>") == 0) {
		cout << "|                ";
		cout << "|--- >=\n";
	}
	else if (token.find("<!=>") == 0) {
		cout << "|                ";
		cout << "|--- !=\n";
	}
	else if (token.find("<<>>") == 0) {
		cout << "|                ";
		cout << "|--- <>\n";
	}
	else
		cout << "Error: Compare\n";
}

void Mag(StringQueue& queue) {
	cout << "|                  ";
	cout << "|___ Term\n";
	Term(queue);
	cout << "|                  ";
	cout << "|___ Mag_prime\n";
	Mag_prime(queue);

}

void Rvalue_prime(StringQueue & queue) {

	string token;
	token = queue.peek();
	
	if (token.find("<==>") != 0 && token.find("<<>") != 0 && token.find("<>>") != 0 && token.find("<<=>") != 0 && token.find("<>=>") != 0 && token.find("<!=>") != 0 && token.find("<<>>") != 0) {
		cout << "|                ";
		cout << "|___ NULL\n";
		return;
	}

	cout << "|                ";
	cout << "|___ Compare\n";
	Compare(queue);
	cout << "|                ";
	cout << "|___ Mag\n";
	Mag(queue);
	cout << "|                ";
	cout << "|___ Rvalue_prime\n";
	Rvalue_prime(queue);

}

void Rvalue(StringQueue& queue) {

	cout << "|              ";
	cout << "|___ Mag\n";
	Mag(queue);
	cout << "|              ";
	cout << "|___ Rvalue_prime\n";
	Rvalue_prime(queue);
	
}

void Expr(StringQueue& queue) {

	string token;
	token = queue.peek();

	if (token.find("<id,") == 0) {

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|            ";
		cout << "|___ Identifier\n";
		int id = 0;
		size_t start = token.find(",") + 1;
		size_t end = token.find(">");
		if (start != string::npos && end != string::npos && end > start) {
			string idStr = token.substr(start, end - start);
			id = stoi(idStr);
		}

		for (const auto& entry : identifiers) {
			if (entry.key == id) {
				ID = entry.value; 
			}
		}

		token = queue.peek();

		if (token.find("<=>") == 0) {

			if (!queue.isEmpty())
				token = queue.dequeue();

			cout << "|            ";
			cout << "|--- =\n";

			cout << "|            ";
			cout << "|___ Expression\n";

			Expr(queue);

		}
		
	}
	else
	{
		cout << "|            ";
		cout << "|___ Rvalue\n";

		Rvalue(queue);
	}

}

void Stmt(StringQueue& queue);

void ElseStmt(StringQueue& queue) {
	string token = queue.peek();

	if (token.find("<keyword,11>") == 0) {
		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|              ";
		cout << "|___ Wagarna\n";

		cout << "|              ";
		cout << "|___ Stmt\n";

		Stmt(queue);

	}
	else
	{
		cout << "|              ";
		cout << "|___ NULL\n";
		return;
	}
}

void ifStmt(StringQueue& queue) {

	string token = queue.peek();

	if (token.find("<keyword,2>") == 0) {
		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|            ";
		cout << "|___ Agar\n";

		int id = 0;
		size_t start = token.find(",") + 1;
		size_t end = token.find(">");
		if (start != string::npos && end != string::npos && end > start) {
			string idStr = token.substr(start, end - start);
			id = stoi(idStr);
		}

		for (const auto& entry : keywords) {
			if (entry.key == id) {
				key = entry.value;
			}
		}

		token = queue.peek();
		if (token.find("<(>") == 0) {

			if (!queue.isEmpty())
				token = queue.dequeue();

			cout << "|            ";
			cout << "|--- (\n";

			cout << "|            ";
			cout << "|___ Expression\n";

			Expr(queue);

			token = queue.peek();
			if (token.find("<)>") == 0) {

				if (!queue.isEmpty())
					token = queue.dequeue();

				cout << "|            ";
				cout << "|--- )\n";


				string temp = newTemp();
				label1 = newLabel();
				label2 = newLabel();
				label3 = newLabel();

				tac <<label1<<": " << key << " " << ID << " == True goto " << label2 << "\n";
			

				cout << "|            ";
				cout << "|___ Stmt\n";

				label1 = label2;
				
				Stmt(queue);

				
				token = queue.peek();
				if (token.find("<keyword,11>") == 0) {

					cout << "|            ";
					cout << "|___ ElseStmt\n";

					tac << "goto " << label3 << "\n";
					tac << label1 << ": " << key << " " << value << "\n";


					label1 = label3;
					

					ElseStmt(queue);
					tac << label1 << ": " << key << " " << value << "\n";

				}
				else
				{
					tac << label1 << ": " << key << " " << value << "\n";
					cout << "Error: If Statement" << endl;
				}
					

			}
			else
				cout << "Error: ) not in If Statement" << endl;

		}
		else
			cout << "Error: ( not in If Statement" << endl;

	}
	else
		cout << "Error: If Statement" << endl;
}

void Stmt(StringQueue& queue) {
	string token = queue.peek();
	if (token.find("<keyword,8>") == 0) {
		//for
		
	}
	else if (token.find("<keyword,1>") == 0) {


		if (!queue.isEmpty())
			token = queue.dequeue();
		//return or Wapas
		cout << "|          ";
		cout << "|___ Wapas\n";

		if (!queue.isEmpty())
			token = queue.dequeue();

		cout << "|          ";
		cout << "|___ Number\n";

		size_t start = token.find("<");
		size_t end = token.find(">");

		if (start != string::npos && end != string::npos && end > start + 1) {
			value = token.substr(start + 1, end - start - 1); // Extract number as string
		}

		tac << "Wapas "<<value<<"\n";

		if (!queue.isEmpty())
			token = queue.dequeue();

		if (token.find("<::>") == 0) {
			cout << "|          ";
			cout << "|--- ::\n";
		}
		else
			cout << "Error: :: not found in Reurn\n";
	}
	else if (token.find("<keyword,4>") == 0) {
		//while
		
	}
	else if (token.find("<keyword,2>") == 0) {
		//if
		cout << "|          ";
		cout << "|___ IfStmt\n";
		ifStmt(queue);
	}
	else if (token.find("<id,") == 0) {
		//expression

		cout << "|          ";
		cout << "|___ Expression\n";

		Expr(queue);

		if (!queue.isEmpty())
			token = queue.dequeue();

		if (token.find("<::>") == 0) {
			cout << "|          ";
			cout << "|--- ::\n";
		}
		else
			cout << "Error: :: not found in Expression\n";
		
	}
	else if (token.find("<{>") == 0) {
		//comptstmt
		
	}
	else if (token.find("<keyword,") == 0) {
		//declaration
		
		cout << "|          ";
		cout << "|___ Declaration\n";
		Declaration(queue);
	}
	else if (token.find("<keyword,") == 0) {
		//::
	}
	else
		cout << "Error: Stmt" << endl;

}

void StmtList(StringQueue& queue) {

	string token = queue.peek();
	if (token.find("<}>") == 0) {
		
		return;
	}
	else {
		
		cout << "|        ";
		cout << "|___ Stmt\n";
		Stmt(queue);
		cout << "|        ";
		cout << "|___ StmtList\n";
		StmtList(queue);
	}
	
}

 void CompStmt(StringQueue& queue) {
	 string token;
	 if (!queue.isEmpty())
		 token = queue.dequeue();

	if (token.find("<{>") == 0) {
		cout << "|    ";
		cout << "|--- {\n";


		cout << "|    ";
		cout << "|--- StmtList\n";
		StmtList(queue);

		string token;
		if (!queue.isEmpty())
			if (!queue.isEmpty())
				token = queue.dequeue();

		if (token.find("<}>") == 0) {
			cout << "|    ";
			cout << "|--- }\n";
		}
		else
			cout << "Error: } not found in Compt Stmt\n";

	}
	else
		cout << "Error: { not found in Compt Stmt\n";
	
}

void Function(StringQueue& queue) {
	  string token;
	  if(!queue.isEmpty())
		token = queue.dequeue();

	  if (token.find("<keyword,") == 0) {
		  cout << "\n|___ Type\n";

		  if (!queue.isEmpty())
			  token = queue.dequeue();

		  if (token.find("<id,") == 0) {
			  cout << "|___ Identifier\n";

			  if (!queue.isEmpty())
				  token = queue.dequeue();

			  if (token.find("<(>") == 0) {
				  cout << "|___ (\n";

				  token = queue.peek();

				  if (token.find("<)>") == 0) {
					  if (!queue.isEmpty())
						  token = queue.dequeue();
					  cout << "|___ )\n";

					  cout << "|___ CompStmt\n";

					  CompStmt(queue);
				  }
				  else {
					  cout << "|___ ArgList\n";
					  ArgList(queue);

					  if (!queue.isEmpty())
						  token = queue.dequeue();

					  if (token.find("<)>") == 0) {
						  cout << "|___ )\n";

						  cout << "|___ CompStmt\n";

						  CompStmt(queue);

					  }
					  else {
						  cout << "Error: ) not found in Function\n";
					  }

				  }

			  }
			  else
				  cout << "Error: ( not found in Function\n";
		  }
		  else
			  cout << "Error: Identifier not found in Function\n";
	  }
	  else
		  cout << "Error: Type not found in Function\n";
}

void Parser() {

	ifstream file("Token.txt");
	if (!file) {
		cerr << "Error Opening the File!";
		return;
	}
	else {


		ifstream in("Symbol_Table_22L-6946.txt");
		if (!in.is_open()) {
			cerr << "Could not open the file!" << endl;
		}

		string l = "";
		while (getline(in, l)) {
			stringstream ss(l);
			int key;
			string value;
			ss >> key >> value;

			identifiers.push_back({ key, value });
		}

		in.close();

		ifstream keyFile("Keyword.txt");
		if (!keyFile.is_open()) {
			cerr << "Could not open the keyword file!" << endl;
		}

		string k = "";
		while (getline(keyFile, k)) {
			stringstream ss(k);
			int key;
			string value;
			ss >> key >> value;

			keywords.push_back({ key, value });
		}

		keyFile.close();

		ifstream litFile("Literal_Table_22L-6946.txt");
		if (!litFile.is_open()) {
			cerr << "Could not open the literal file!" << endl;
		}

		string lit = "";
		while (getline(litFile, lit)) {
		
			Lit.push_back(lit);
		}

		litFile.close();

		for (const auto& e : Lit) {
			cout << " Value: " << e << endl;
		}

		string content, line;
		while (getline(file, line)) {
			content += line;
		}

		StringQueue queue;

		size_t start = 0;
		while ((start = content.find('<', start)) != string::npos) {
			size_t end = content.find('>', start);
			if (end == string::npos) break;

			string token = content.substr(start, end - start + 1);
			queue.enqueue(token);
			start = end + 1;
		}

		cout << "Function";
		Function(queue);

		cout << "\n\nSuccessful Parsing" << endl;

		return;

	}

	tac.close();
	
}

int main() {
	CleanCode("Sourcecode.txt");
	Scanner("Sourcecode.txt");
	Parser();
	return 0;
}