

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <list>
#include <string>
#include <time.h>
#include <vector>
#include <wx/textfile.h>
#include <wx/wx.h>
#include <wx/arrstr.h>

using namespace std;

class AisMaker {

public:
    string Str2Str(string str, const char* charsToRemove);
    float Str2Float(string str, const char* exc);
    int Str2Int(string str, const char* exc);
    string Int2BString(int value, int length);
    int findIntFromLetter(char letter);
    char findCharFromNumber(int mp);
    string Str2Six(string str, int length);
    int BString2Int(char* bitlist);
    string NMEAencapsulate(string BigString, int numsixes);
    string makeCheckSum(std::string s);

    // DAC 200 FI 44
    // Text message
	wxString nmeaEncode44_8(int iMMSI,
		wxString countrycode, int FairwaySection, string object, int hectometre, string text);
	
    // DAC 200 FI 26
    // Water Depth
	wxString nmeaEncode26_8(int iMMSI,
		wxString countrycode, int gaugeID_1, int waterLevelRef_1, int waterLevelValue_1,
		int gaugeID_2, int waterLevelRef_2, int waterLevelValue_2,
		int gaugeID_3, int waterLevelRef_3, int waterLevelValue_3);

    wxString testAIVDM;

protected:
};
