#include "Searcher.h"
#include <iostream>


Searcher::Searcher(string s) :sid(s)
{
	TO = new TessOcr();
}


Searcher::~Searcher()
{
	delete TO;
}


void Searcher::Search()
{
	GetScreenShot();

	sum = 0;
	map<int,int> count_no_map;
	for (int i = 0; i<A.size(); i++)
	{
		count_no_map.insert(make_pair(OutCounter(Q+" "+A[i]),i));
	}

	for (map<int,int>::iterator iter = count_no_map.begin(); iter!=count_no_map.end(); iter++)
	{
		cout<<iter->first<<"\t："<<A[iter->second]<<endl;
	}


}


int Searcher::OutCounter(string keyWord/*,map<int,int>count_no_map*/)
{
	Spider* s = new Spider(keyWord);

	string count;
	count = UtfToGbk(s->GetResult().c_str());
	int start = count.find("百度为您找到相关结果约");
	count = count.substr(start+22);
	int end = count.find("个");
	count = count.substr(0,end);

	DeleteChar(count,',');
	return atoi(count.c_str());
}


void Searcher::GetScreenShot()
{
	A.clear();
	string cmd = "nox_adb -s "+sid+" shell /system/bin/screencap -p /sdcard/1.png";
	execmd(cmd);
	cmd = "nox_adb -s "+sid+" pull /sdcard/1.png ./";
	execmd(cmd);
	
	//need read from config file
	int rectangle[] = { 28,188,500,623 };
	string s = TO->OcrProcess("./1.png",rectangle);
	Q = s.substr(2,s.find("?"));
	s = s.substr(s.find("?")+1);

	DeleteChar(Q,'\n');

	cout<<endl;
	cout<<Q<<endl;

	SpiltAns(s);
}


void Searcher::SpiltAns(string ans)
{
	int pos;
	while (ans.length()>0)
	{
		pos = ans.find('\n');
		if (pos==0)
			ans.erase(ans.begin());
		else
		{
			A.push_back(ans.substr(0,pos));
			ans = ans.substr(pos+1);
		}
	}

	for (int i = 0; i<A.size(); i++)
		cout<<A[i]<<endl;
	cout<<endl;
}

void Searcher::DeleteChar(string& s,char c)
{
	int pos = s.find(c);
	while (pos!=-1)
	{
		s.erase(s.begin()+pos);
		pos = s.find(c);
	}
}
