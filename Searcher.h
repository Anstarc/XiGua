#pragma once
#include "TessOcr.h"
#include "execmd.h"
#include <atlimage.h>
#include <vector>
#include "Spider.h"
#include <map>

class Searcher
{
	TessOcr* TO;
	string sid;
	string Q;
	vector<string> A;
	int sum;
public:

	Searcher(string s);
	~Searcher();

	void Search();
	void GetScreenShot();
	void SpiltAns(string ans);
	int OutCounter(string keyWord/*,map<int,int>count_no_map*/);
	void DeleteChar(string& s,char c);

};

