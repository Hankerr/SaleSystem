#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <list>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	int id;
	string name;
	int price;
	int num;
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();
	
	void ReadLogin(CString &name, CString &pwd);

	void WritePwd(char* name, char* pwd);

	void ReadDocline();

	void WirteDocline();

	void Addline(CString name, int num, int price);
	
	list<msg> ls;
	int num;
};

