#include "stdafx.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}

void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs;
	ifs.open(_F_LOGIN);

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));
	name = CString(buf);

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close();
}

void CInfoFile::WritePwd(char* name, char* pwd) {
	ofstream ofs;
	ofs.open(_F_LOGIN);
	ofs << name << endl;
	ofs << pwd << endl;
	ofs.close();
}

void CInfoFile::ReadDocline() {
	ifstream ifs(_F_STOCK);

	char buf[1024] = { 0 };
	num = 0;
	ls.clear();
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) {
		msg tmp;
		ifs.getline(buf, sizeof(buf));
		num++;
		char *sst = strtok(buf, "|");
		if (sst != NULL) {
			tmp.id = atoi(sst);
		}
		else { 
			break; 
		}
		sst = strtok(NULL, "|");
		tmp.name = sst;

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);

		ls.push_back(tmp);
	}
	ifs.close();
}

void CInfoFile::WirteDocline() {
	ofstream ofs(_F_STOCK);
	if (ls.size()>0) {
		ofs << "商品ID|商品名称|商品价格|库存" << endl;
		for (list<msg>::iterator it = ls.begin(); it != ls.end();it++) {
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << endl;
		}
	}
	ofs.close();
}

//添加新商品
//name:商品名称，num：库存，price：价格
void CInfoFile::Addline(CString name, int num, int price)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//商品名称，库存，价格有效
		if (!name.IsEmpty() && num > 0 && price > 0)
		{
			tmp.id = ls.size() + 1;	//id自动加1
			CStringA str;
			str = name;	//CString转CStirngA
			tmp.name = str.GetBuffer(); //CStirngA转char *，商品名称
			tmp.num = num;	//库存
			tmp.price = price;	//价格

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}