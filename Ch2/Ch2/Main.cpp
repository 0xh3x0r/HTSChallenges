#include <metin.h>
#include <iostream>
#include "lodepng.h"
#include <Windows.h>
#include <map>

using namespace std;


/*
	Metin.h used in this challange is my own wrapper(Turkish) class for string manipulation processes. 
	-> You can change the morse2ascii map to function in lowercase characters
	-> I used lodepng library to convert IDAT to rawpixels. Everything used in this project already embedded to itself
	

	Let me now if you encounter a problem!
	GL, Happy coding ^.^

*/

std::map<string, char > morse2ascii =
{
	{ ".-"		,	'A' },
	{ "-..."	,	'B' },
	{ "-.-."	,	'C' },
	{ "-.."		,	'D' },
	{ "."		,	'E' },
	{ "..-."	,	'F' },
	{ "--."		,	'G' },
	{ "...."	,	'H' },
	{ ".."		,	'I' },
	{ ".---"	,	'J' },
	{ "-.-"		,	'K' },
	{ ".-.."	,	'L' },
	{ "--"		,	'M' },
	{ "-."		,	'N' },
	{ "---"		,	'O' },
	{ ".--."	,	'P' },
	{ "--.-"	,	'Q' },
	{ ".-."		,	'R' },
	{ "..."		,	'S' },
	{ "-"		,	'T' },
	{ "..-"		,	'U' },
	{ "...-"	,	'V'	},
	{ ".--"		,	'W'	},
	{ "-..-"	,	'X'	},
	{ "-.--"	,	'Y'	},
	{ "--.."	,	'Z'	},
	{ "/"		,	' '	},	 // this isn't a morse code but algo uses it as space ' ' character.(just in case *)

	{ "-----"	,	'0' },
	{ ".----"	,	'1'	},
	{ "..---"	,	'2'	},
	{ "...--"	,	'3'	},
	{ "....-"	,	'4'	},
	{ "....."	,	'5'	},
	{ "-...."	,	'6'	},
	{ "--..."	,	'7'	},
	{ "---.."	,	'8'	},
	{ "----."	,	'9'	},
	{ ".-.-.-"	,	'.'	},
	{ "--..--"	,	',' },
	{ "..--.."	,	'?' },
	{ "-...-"	,	'=' },

};


// to fasten things up :)
void toClipboard(const std::string &s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}



string decodeMorse(string morseCodes)
{
	string ret = "";


	int i = 0;

	

	string morse = "";
	for (size_t i = 0; i < morseCodes.size(); i++)
	{
		char ch = morseCodes[i];
	
		if (ch == 0x20) // ' ' (space) is the seperator  
		{
			
			char decoded = morse2ascii[morse];
			if (decoded != 0) ret += decoded; // for safety purposes otherwise it will add null terminator.
			else
				cout << "to err is human" << endl;

			morse = "";
			continue;
		}


		morse += morseCodes[i];

	}


	return ret;
}


void decodeImage(const char* filename)
{
	vector<unsigned char> png; // whole file data
	vector<unsigned char> rawPixels; // decoded pixels.
	vector<int> whiteDotLocations;

	lodepng::load_file(png, filename);
	unsigned width = 0, height = 0;


	unsigned int err = lodepng::decode(rawPixels, width, height,png);
	if (err == 0)
	{

		cout << "PNG is decoded" << endl;
		for (size_t i = 0; i < rawPixels.size(); i += 4)
		{
			if (
				rawPixels[i]	 == 0xFF &&
				rawPixels[i + 1] == 0xFF &&
				rawPixels[i + 2] == 0xFF &&
				rawPixels[i + 3] == 0xFF
			)
			{
		
				int iPixel = (i / 4); // pixel index

				whiteDotLocations.push_back(iPixel);

			}
		}
	}
	cout << "White pixels detected : " << whiteDotLocations.size() <<endl;
	// * Decode ascii chars

	cout << "Decoding ascii characters" << endl;

	Metin morseCodez = "";

	morseCodez += (char)whiteDotLocations[0];
	for (size_t c = 1; c < whiteDotLocations.size(); c++)
	{

			
			char ch = (  (whiteDotLocations[c]) - (whiteDotLocations[c-1]) );

			morseCodez += ch;
	}




		


	Metin result = decodeMorse(morseCodez); 
	result = result.lowercase();
	toClipboard(result); // this code sometimes doesn't copy the whole result.
	
	cout << "Output copied to your clipboard! " << endl;

	cout << "Result is :" << result << endl;

}

int main()
{
	decodeImage("hts.png");
	

	// system("pause");


	return 0;
}