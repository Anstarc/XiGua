#include <string>
#include <windows.h>

#include "api/baseapi.h"
#include "allheaders.h"
#include "strngs.h"
#include "encoding.h"


using namespace std;


class TessOcr
{
	tesseract::TessBaseAPI *api;

public:
	TessOcr(string path = "./",string lag = "chi_sim");
	~TessOcr();

	string OcrProcess(string file_path,int* rectangle=NULL);

private:
	void InitTess(string path,string lag);
};
