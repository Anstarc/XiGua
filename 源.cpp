#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <thread>
#include "api/baseapi.h"
#include "allheaders.h"
#include "strngs.h"
#include "Searcher.h"
//#include "execmd.h"

using namespace std;

//0 store simulator pixel
//1 store phone pixel
int x[2],y[2],line[2];
set<int> fail;

void devices(vector<string>& sid, int type)
{
	// type=0 夜神nox_adb
	// type=1 adb
	string cmd;
	if (type==0)
		cmd = "nox_adb devices";
	else if (type==1)
		cmd = "adb devices";
	//////////////////////////////////////////////////////////////////////////

	string result;
	string device = "device";
	string n = "\n";
	string t = "\t";
	string buffer;

	if (1==execmd(cmd,result)){
		int start = 0;

		while (result.find(device,start)!=-1)
		{
			start=result.find(device,start);
			if (result.rfind(n,start)!=-1)
			{
				result.rfind(t,start);
				buffer = result.substr(result.rfind(n,start)+1,start-1);
				buffer = buffer.substr(0,buffer.find("\t"));
				sid.push_back(buffer);
				
				//for debug
				cout<<sid[sid.size()-1]<<endl;
			}
			start = result.find(device,start) + 1;
		}
	}
}

void touch(int num, string sid)
{
	string cmd;
	if (sid.find('.')!=-1)
		cmd = "nox_adb -s "+sid+" shell input swipe "+to_string(x[0])+" "+to_string(y[0]+(num-1)*line[0])+" "+to_string(x[0])+" "+to_string(y[0]+(num-1)*line[0]);
	else
		cmd = "nox_adb -s "+sid+" shell input swipe "+to_string(x[1])+" "+to_string(y[1]+(num-1)*line[1])+" "+to_string(x[1])+" "+to_string(y[1]+(num-1)*line[1]);

	//system(cmd.c_str());
	execmd(cmd);
}

vector<int> touch_logi(int num, vector<string>& sid)
{
	vector<int> ans;
	if (num<10)
	{
		ans.push_back(num);
		vector<thread> threads;
		for (int i = 0; i<sid.size(); i++)
		{
			if (fail.find(i+1)!=fail.end())
				continue;
			threads.push_back(thread(touch,num,sid[i]));
			threads[threads.size()-1].detach();
		}
	}

	else
	{
		int a[2];
		a[0] = num/10;
		a[1] = num%10;
		int b = 0;

		vector<thread> threads;
		for (int i = 0; i<sid.size(); i++)
		{
			if (fail.find(i+1)!=fail.end())
			{
				ans.push_back(0);
				continue;
			}
			threads.push_back(thread(touch,a[b%2],sid[i]));
			ans.push_back(a[b%2]);
			b++;
			threads[threads.size()-1].detach();
		}
	}
	return ans;
}

void switch_devices(vector<string>& sid)
{
	string start = " shell am start -n com.ss.android.article.video/.activity.SplashActivity";
	for (int i = 0; i<sid.size(); i++)
	{
		cout<<"device "<<i+1<<" start"<<endl;

		string cmd = "nox_adb -s "+sid[i]+start;
		//execmd(cmd);
		getchar();
	}
}

void delete_devices(vector<string>& sid, string cmd)
{
	stringstream stream;
	stream<<cmd;
	int id;
	while (stream>>id)
	{
		fail.insert(id);
	}
}

void check(vector<int>ans)
{
	int a;
	cout<<"答案:";
	cin>>a;

	if (ans.size()==1&&ans[0]==a)
		cout<<"正确"<<endl;
	if (ans.size()>1)
	{
		for (int i = 0; i<ans.size(); i++)
		{
			if (ans[i]!=0&&ans[i]!=a)
				cout<<i+1<<" ";
		}
		cout<<"错误"<<endl;
	}
}

void show_alive(vector<string>& sid)
{
	cout<<"在线：";
	for (int i = 0; i<sid.size();i++)
	{
		if (fail.find(i+1)==fail.end())
			cout<<i+1<<" ";
	}
	cout<<endl;
}

int main(){
	string result;                   //定义存放结果的字符串数组
	vector<string> sid;
	devices(sid, 0);
	//devices(sid, 1);
	string opt;
	Searcher* seacher;
	

	ifstream fin("sim.config");
	fin>>x[0]>>y[0]>>line[0];
	fin.close();
	fin.open("phone.config");
	fin>>x[1]>>y[1]>>line[1];
	fin.close();

	switch_devices(sid);

	vector<int> ans;
	int counter = 1;
	
	cout<<endl;
	cout<<"-----------------------";
	cout<<endl;
	while (cin>>opt)
	{
		if (opt[0]>='0' && opt[0]<='9')
		{
			cout<<"第"<<counter<<"题\n";
			ans = touch_logi(stoi(opt),sid);
			check(ans);
			show_alive(sid);


			counter++;
			cout<<endl;
			cout<<"-----------------------";
			cout<<endl;
		}
		if (opt[0]=='d')
			delete_devices(sid,opt.substr(1));
		if (opt[0]=='l')
		{
			for (int i = 0; i<sid.size(); i++)
				cout<<sid[i]<<endl;
			cout<<"fail:";
			for (set<int>::iterator i= fail.begin(); i!=fail.end(); i++)
				cout<<*i<<" ";
			cout<<endl;
		}
		if (opt[0]=='s')
		{
			if (opt.size()>1)
				seacher = new Searcher(sid[opt[1]-'1']);
			else
				seacher->Search();
		}

	}
}


