#include "Spider.h"


Spider::Spider(string keyWord)
{
	res = "";
	string szUrl = string_To_UTF8("http://www.baidu.com/s?wd="+keyWord+"&tn=98131360_hao_pg" );
	CHAR szAgent[] = "";
	HINTERNET hInternet1 =
		InternetOpen(NULL,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,NULL);
	if (NULL==hInternet1)
	{
		InternetCloseHandle(hInternet1);
		return;
	}
	WCHAR szUrl2[256];
	memset(szUrl2,0,sizeof(szUrl2));
	MultiByteToWideChar(CP_ACP,0,szUrl.c_str(),szUrl.length()+1,szUrl2,
		sizeof(szUrl2)/sizeof(szUrl2[0]));

	HINTERNET hInternet2 =
		InternetOpenUrl(hInternet1,szUrl2,NULL,NULL,INTERNET_FLAG_NO_CACHE_WRITE,NULL);
	if (NULL==hInternet2)
	{
		InternetCloseHandle(hInternet2);
		InternetCloseHandle(hInternet1);
		return;
	}
	DWORD dwMaxDataLength = 5000;
	PBYTE pBuf = (PBYTE)malloc(dwMaxDataLength*sizeof(TCHAR));
	if (NULL==pBuf)
	{
		InternetCloseHandle(hInternet2);
		InternetCloseHandle(hInternet1);
		return;
	}
	Sleep(1000);
	DWORD dwReadDataLength = NULL;
	BOOL bRet = TRUE;
	do
	{
		ZeroMemory(pBuf,dwMaxDataLength*sizeof(TCHAR));
		bRet = InternetReadFile(hInternet2,pBuf,dwMaxDataLength,&dwReadDataLength);
		for (DWORD dw = 0; dw<dwReadDataLength; dw++)
		{
			res+=pBuf[dw];
		}
	} while (NULL!=dwReadDataLength);
}


Spider::~Spider()
{
}
