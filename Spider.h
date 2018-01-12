#pragma once

#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <vector>
#include "encoding.h"


using namespace std;

class Spider
{
	string res;
public:
	Spider(string keyWord);
	~Spider();

	string GetResult()
	{
		return res;
	}
};

