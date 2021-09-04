

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
    wxString makeCheckSum(wxString mySentence);
    wxString nmeaEncode(wxString type, int MMSI, wxString status, double spd,
        double ilat, double ilon, double crse, double hdg, wxString channel,
        wxString timestamp);
	wxString nmeaEncode24(int iMMSI,
		wxString name, wxString channel);

	wxArrayString nmeaEncode44_8(int iMMSI,
		wxString text, wxString countrycode, wxString object);


	wxString nmeaEncodeAtonTX(wxString type, int iMMSI, wxString status,
		double ilat, double ilon, wxString channel, wxString timestamp);

protected:
};
