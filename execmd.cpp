#include "execmd.h"

int execmd(string cmd,string& result) {
	char buffer[128];                         //���建����                          
	FILE* pipe = _popen(cmd.c_str(),"r");            //�򿪹ܵ�����ִ������   
	if (!pipe)
		return 0;                      //����0��ʾ����ʧ��   

	while (!feof(pipe)) {
		if (fgets(buffer,128,pipe)){             //���ܵ������result��   
			result += buffer;
		}
	}
	_pclose(pipe);                            //�رչܵ�   
	return 1;                                 //����1��ʾ���гɹ�   
}

int execmd(string cmd)
{
	string tmp;
	return execmd(cmd,tmp);
}