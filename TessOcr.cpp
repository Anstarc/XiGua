#include "TessOcr.h"



TessOcr::TessOcr(string path,string lag)
{
	InitTess(path,lag);
}


TessOcr::~TessOcr()
{
	api->End();
}

void TessOcr::InitTess(string path,string lag)
{
	api = new tesseract::TessBaseAPI();
	if (path=="")
	{
		// Initialize tesseract-ocr with English, without specifying tessdata path
		if (api->Init(NULL,lag.c_str(),tesseract::OEM_DEFAULT)) {
			fprintf(stderr,"Could not initialize tesseract.\n");
			exit(1);
		}
	}
	else
	{
		if (api->Init(path.c_str(),lag.c_str(),tesseract::OEM_DEFAULT)) {
			fprintf(stderr,"Could not initialize tesseract.\n");
			exit(1);
		}
	}
}

string TessOcr::OcrProcess(string file_path, int* rectangle)
{
	char *outText;
	// Open input image with leptonica library
	Pix *image = pixRead(file_path.c_str());
	api->SetImage(image);
	if (rectangle)
		api->SetRectangle(rectangle[0],rectangle[1],rectangle[2],rectangle[3]);
	// Get OCR result
	outText = api->GetUTF8Text();
	string out = UtfToGbk(outText);

	// Destroy used object and release memory
	delete[] outText;
	pixDestroy(&image);

	return out;
}