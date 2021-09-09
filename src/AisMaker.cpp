/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  aisTX Plugin
 * Author:   Mike Rossiter. AIS encoding ported from AISConverter Python code by
 *@transmitterdan
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include "aisTXgui_impl.h"

static const std::vector<std::pair<uint32_t, char>> payloadencoding
    = { { 0, '0' }, { 1, '1' }, { 2, '2' }, { 3, '3' }, { 4, '4' }, { 5, '5' },
          { 6, '6' }, { 7, '7' }, { 8, '8' }, { 9, '9' }, { 10, ':' },
          { 11, ';' }, { 12, '<' }, { 13, '=' }, { 14, '>' }, { 15, '?' },
          { 16, '@' }, { 17, 'A' }, { 18, 'B' }, { 19, 'C' }, { 20, 'D' },
          { 21, 'E' }, { 22, 'F' }, { 23, 'G' }, { 24, 'H' }, { 25, 'I' },
          { 26, 'J' }, { 27, 'K' }, { 28, 'L' }, { 29, 'M' }, { 30, 'N' },
          { 31, 'O' }, { 32, 'P' }, { 33, 'Q' }, { 34, 'R' }, { 35, 'S' },
          { 36, 'T' }, { 37, 'U' }, { 38, 'V' }, { 39, 'W' }, { 40, '`' },
          { 41, 'a' }, { 42, 'b' }, { 43, 'c' }, { 44, 'd' }, { 45, 'e' },
          { 46, 'f' }, { 47, 'g' }, { 48, 'h' }, { 49, 'i' }, { 50, 'j' },
          { 51, 'k' }, { 52, 'l' }, { 53, 'm' }, { 54, 'n' }, { 55, 'o' },
          { 56, 'p' }, { 57, 'q' }, { 58, 'r' }, { 59, 's' }, { 60, 't' },
          { 61, 'u' }, { 62, 'v' }, { 63, 'w' } };

// Sixbit ASCII encoding
static const std::vector<std::pair<char, uint32_t>> sixbitencoding
    = { { '@', 0 }, { 'A', 1 }, { 'B', 2 }, { 'C', 3 }, { 'D', 4 }, { 'E', 5 },
          { 'F', 6 }, { 'G', 7 }, { 'H', 8 }, { 'I', 9 }, { 'J', 10 },
          { 'K', 11 }, { 'L', 12 }, { 'M', 13 }, { 'N', 14 }, { 'O', 15 },
          { 'P', 16 }, { 'Q', 17 }, { 'R', 18 }, { 'S', 19 }, { 'T', 20 },
          { 'U', 21 }, { 'V', 22 }, { 'W', 23 }, { 'X', 24 }, { 'Y', 25 },
          { 'Z', 26 }, { '[', 27 }, { '\\', 28 }, { ']', 29 }, { '^', 30 },
          { '_', 31 }, { ' ', 32 }, { '1', 33 }, { '"', 34 }, { '#', 35 },
          { '$', 36 }, { '%', 37 }, { '&', 38 }, { '\'', 39 }, { '(', 40 },
          { ')', 41 }, { '*', 42 }, { '+', 43 }, { '}', 44 }, { '-', 45 },
          { '.', 46 }, { '/', 47 }, { '0', 48 }, { '1', 49 }, { '2', 50 },
          { '3', 51 }, { '4', 52 }, { '5', 53 }, { '6', 54 }, { '7', 55 },
          { '8', 56 }, { '9', 57 }, { ',', 58 }, { ';', 59 }, { '<', 60 },
          { '=', 61 }, { '>', 62 }, { '?', 63 } };

static const std::vector<std::pair<char, uint32_t>> NMEA_TABLE
    = { { '0', 0 }, { '1', 1 }, { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 },
          { '6', 6 }, { '7', 7 }, { '8', 8 }, { '9', 9 }, { ':', 10 },
          { ';', 11 }, { '<', 12 }, { '=', 13 }, { '>', 14 }, { '?', 15 },
          { '@', 16 }, { 'A', 17 }, { 'B', 18 }, { 'C', 19 }, { 'D', 20 },
          { 'E', 21 }, { 'F', 22 }, { 'G', 23 }, { 'H', 24 }, { 'I', 25 },
          { 'J', 26 }, { 'K', 27 }, { 'L', 28 }, { 'M', 29 }, { 'N', 30 },
          { 'O', 31 }, { 'P', 32 }, { 'Q', 33 }, { 'R', 34 }, { 'S', 35 },
          { 'T', 36 }, { 'U', 37 }, { 'V', 38 }, { 'W', 39 }, { '`', 40 },
          { 'a', 41 }, { 'b', 42 }, { 'c', 43 }, { 'd', 44 }, { 'e', 45 },
          { 'f', 46 }, { 'g', 47 }, { 'h', 48 }, { 'i', 49 }, { 'j', 50 },
          { 'k', 51 }, { 'l', 52 }, { 'm', 53 }, { 'n', 54 }, { 'o', 55 },
          { 'p', 56 }, { 'q', 57 }, { 'r', 58 }, { 's', 59 }, { 't', 60 },
          { 'u', 61 }, { 'v', 62 }, { 'w', 63 } };

static const std::vector<std::pair<uint8_t, char>> SIXBIT_ASCII_TABLE = {
    { 0, '@' },
    { 1, 'A' },
    { 2, 'B' },
    { 3, 'C' },
    { 4, 'D' },
    { 5, 'E' },
    { 6, 'F' },
    { 7, 'G' },
    { 8, 'H' },
    { 9, 'I' },
    { 10, 'J' },
    { 11, 'K' },
    { 12, 'L' },
    { 13, 'M' },
    { 14, 'N' },
    { 15, 'O' },
    { 16, 'P' },
    { 17, 'Q' },
    { 18, 'R' },
    { 19, 'S' },
    { 20, 'T' },
    { 21, 'U' },
    { 22, 'V' },
    { 23, 'W' },
    { 24, 'X' },
    { 25, 'Y' },
    { 26, 'Z' },
    { 27, '[' },
    { 28, '\\' },
    { 29, ']' },
    { 30, '^' },
    { 31, '_' },
    { 32, ' ' },
    { 33, '!' },
    { 34, '\"' },
    { 35, '#' },
    { 36, '$' },
    { 37, '%' },
    { 38, '&' },
    { 39, '\'' },
    { 40, '(' },
    { 41, ')' },
    { 42, '*' },
    { 43, '+' },
    { 44, ',' },
    { 45, '-' },
    { 46, '.' },
    { 47, '/' },
    { 48, '0' },
    { 49, '1' },
    { 50, '2' },
    { 51, '3' },
    { 52, '4' },
    { 53, '5' },
    { 54, '6' },
    { 55, '7' },
    { 56, '8' },
    { 57, '9' },
    { 58, ':' },
    { 59, ';' },
    { 60, '<' },
    { 61, '=' },
    { 62, '>' },
    { 63, '?' },
};

string AisMaker::Str2Str(string str, const char* charsToRemove)
{
    for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
        str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
    }
    return str;
}

float AisMaker::Str2Float(string str, const char* exc)
{
    float result;
    string floatString = Str2Str(str, exc);
    result = strtof((floatString).c_str(), 0); // string to float

    return result;
}

int AisMaker::Str2Int(string str, const char* exc)
{
    int result;
    string intString = Str2Str(str, exc);
    result = atoi((intString).c_str()); // string to float
    return result;
}

string AisMaker::Int2BString(int value, int length)
{

    string result = "";
    bitset<200> myBitset(value);
    result = myBitset.to_string();

    result = result.substr(result.size() - length, length);
    return result;
}

int AisMaker::findIntFromLetter(char letter)
{
    auto i = std::find_if(SIXBIT_ASCII_TABLE.begin(), SIXBIT_ASCII_TABLE.end(),
        [letter](
            const std::pair<uint8_t, char>& p) { return p.second == letter; });
    return i != SIXBIT_ASCII_TABLE.end() ? i->first : 0xff;
}

char AisMaker::findCharFromNumber(int mp)
{

    auto i = std::find_if(NMEA_TABLE.begin(), NMEA_TABLE.end(),
        [mp](const std::pair<char, uint32_t> p) {
            return p.second == (unsigned)mp;
        });
    return i != NMEA_TABLE.end() ? i->first : 0xff;
}

string AisMaker::Str2Six(string str, int length)
{

    string result;
    char letter;

    for (size_t i = 0; i < str.size(); i++) {

        letter = str[i];
        int si = findIntFromLetter(letter);
        result = result + Int2BString(si, 6);
    }
    while (result.size() < (size_t)length) {

        int sj = findIntFromLetter(' ');
        result =  result + Int2BString(sj, 6);
    }
    return result;
}

int AisMaker::BString2Int(char* bitlist)
{
    int s = std::bitset<6>(bitlist).to_ulong();
    return s;
}

string AisMaker::NMEAencapsulate(string BigString, int numsixes)
{

    string capsule = "";
    int chindex;
    int substart = 0;
    int* intChars = (int*)calloc(numsixes, 6);
    char* myChars; // = &BigString[0u];
    for (chindex = 0; chindex < numsixes; chindex++) {
        string StrVal = BigString.substr(substart, 6);
        // wxMessageBox(StrVal);
        myChars = &StrVal[0u];
        intChars[chindex] = BString2Int(myChars);
        substart += 6;
    }
    // Now intChars contains the encoded bits for the AIS string
    for (chindex = 0; chindex < numsixes; chindex++) {
        wxString mystring = wxString::Format(_T("%i"), intChars[chindex]);
        // wxMessageBox(mystring);
        char plChar = findCharFromNumber(intChars[chindex]);
        capsule = capsule + plChar;
    }
    // Now we have the NMEA payload in capsule
    free(intChars);
    return capsule;
}

wxString AisMaker::makeCheckSum(wxString mySentence)
{
    size_t i;
    unsigned char XOR;

    wxString s(mySentence);
    wxCharBuffer buffer = s.ToUTF8();
    char* Buff = buffer.data(); // data() returns const char *
    size_t iLen = strlen(Buff);
    for (XOR = 0, i = 0; i < iLen; i++)
        XOR ^= (unsigned char)Buff[i];
    stringstream tmpss;
    tmpss << hex << (int)XOR << endl;
    wxString mystr = tmpss.str();
    return mystr;
}

wxString AisMaker::nmeaEncode(wxString type, int iMMSI, wxString status,
    double spd, double ilat, double ilon, double crse, double hdg,
    wxString channel, wxString timestamp)
{

    string MessageID(Int2BString(Str2Int("18", ""), 6));

    string RepeatIndicator = Int2BString(0, 2);

    wxString MMSI = wxString::Format(_T("%i"), iMMSI);
    string sMMSI = (const char*)MMSI.mb_str();

    string oMMSI = Int2BString(Str2Int(sMMSI, ""), 30);

    string Spare1 = Int2BString(0, 8);

    wxString sChannel;
    string Channel = (const char*)sChannel.mb_str();

    wxString SPEED = wxString::Format(_T("%f"), spd * 10);
    string sSPEED = (const char*)SPEED.mb_str();
    float sog = Str2Float(sSPEED, "");
    string SOG = Int2BString(sog, 10);

    string PosAccuracy = Int2BString(1, 1);

    wxString LON = wxString::Format(_T("%f"), ilon);
    string sLON = (const char*)LON.mb_str();
    float flon = Str2Float(sLON, "");
    string Longitude = Int2BString(int(flon * 600000), 28);

    wxString LAT = wxString::Format(_T("%f"), ilat);
    string sLAT = (const char*)LAT.mb_str();
    float flat = Str2Float(sLAT, "");
    string Latitude = Int2BString(int(flat * 600000), 27);

    wxString COURSE = wxString::Format(_T("%f"), crse);
    string sCOURSE = (const char*)COURSE.mb_str();
    float cog = Str2Float(sCOURSE, "");
    string COG = Int2BString(int(cog * 10), 12);

    wxString HEADING = wxString::Format(_T("%f"), hdg);
    string sHEADING = (const char*)HEADING.mb_str();
    int heading = Str2Int(sHEADING, "");
    string Heading = Int2BString(heading, 9);

    wxString TIMESTAMP;
    string sTIMESTAMP = (const char*)TIMESTAMP.mb_str();
    string tStamp = sTIMESTAMP;
    int tSecond = wxGetUTCTime();
    // 123456; // Str2Int(tStamp[tStamp.length() - 2:len(tStamp)], "");
    string TimeStamp = Int2BString(tSecond, 6);

    string Spare2 = Int2BString(0, 2);

    string State = Int2BString(393222, 27);

    string BigString = MessageID;
    BigString = BigString + RepeatIndicator;
    BigString = BigString + oMMSI + Spare1 + SOG + PosAccuracy + Longitude
        + Latitude + COG + Heading + TimeStamp + Spare2;
    BigString = BigString + State;

    string capsule = NMEAencapsulate(BigString, 28);
    string aisnmea = "AIVDM,1,1,," + Channel + "," + capsule + ",O";
    wxString myNMEA = aisnmea;
    wxString myCheck = makeCheckSum(myNMEA);

    myNMEA = _T("!") + myNMEA + _T("*") + myCheck;

    return myNMEA;
}

wxString AisMaker::nmeaEncode24(int iMMSI,
    wxString name, wxString channel)
{

    string MessageID(Int2BString(Str2Int("24", ""), 6));

    string RepeatIndicator = Int2BString(0, 2);

    wxString MMSI = wxString::Format(_T("%i"), iMMSI);
    string sMMSI = (const char*)MMSI.mb_str();

    string oMMSI = Int2BString(Str2Int(sMMSI, ""), 30);

	string oPartNum = Int2BString(0, 2);

	wxString myName = name;
    string sName = (const char*)myName.mb_str();
	string oName = Str2Six(sName, 120);

    string BigString = MessageID;
    BigString = BigString + RepeatIndicator;
    BigString = BigString + oMMSI + oPartNum + oName;

	wxString sChannel;
    string Channel = (const char*)sChannel.mb_str();

	int sz = BigString.size();
	int numSixes = (sz / 6) + 1;

    string capsule = NMEAencapsulate(BigString, numSixes);
    string aisnmea = "AIVDM,1,1,,B," + capsule + ",O";
    wxString myNMEA = aisnmea;
    wxString myCheck = makeCheckSum(myNMEA);

    myNMEA = _T("!") + myNMEA + _T("*") + myCheck;

    return myNMEA;
}

wxString AisMaker::nmeaEncodeAtonTX(wxString type, int iMMSI, wxString status,
    double ilat, double ilon, wxString channel, wxString timestamp)
{

    string MessageID(Int2BString(Str2Int("21", ""), 6));

	

    string RepeatIndicator = Int2BString(0, 2);

    wxString MMSI = wxString::Format(_T("%i"), iMMSI);
    string sMMSI = (const char*)MMSI.mb_str();
    string oMMSI = Int2BString(Str2Int(sMMSI, ""), 30);

    string aisTXtype = Int2BString(0, 5);

    wxString myName = "992030009";
    string sName = (const char*)myName.mb_str();
	string oName = Str2Six(sName, 120);

    string PosAccuracy = Int2BString(1, 1);

    wxString LON = wxString::Format(_T("%f"), ilon);
    string sLON = (const char*)LON.mb_str();
    float flon = Str2Float(sLON, "");
    string Longitude = Int2BString(int(flon * 600000), 28);

    wxString LAT = wxString::Format(_T("%f"), ilat);
    string sLAT = (const char*)LAT.mb_str();
    float flat = Str2Float(sLAT, "");
    string Latitude = Int2BString(int(flat * 600000), 27);

    wxString Dimension = wxString::Format(_T("%i"), 8);
    string sDimension = (const char*)Dimension.mb_str();
    string oDim = Int2BString(Str2Int(sDimension, ""), 30);

    string aisTXpositiondevice = Int2BString(0,4);

	wxString TIMESTAMP;
    string sTIMESTAMP = (const char*)TIMESTAMP.mb_str();
    string tStamp = sTIMESTAMP;
    int tSecond = wxGetUTCTime();
    // 123456; // Str2Int(tStamp[tStamp.length() - 2:len(tStamp)], "");
    string TimeStamp = Int2BString(tSecond, 6);

	string offPosition = Int2BString(1, 1);

	string sstatus = Int2BString(00000000, 8);

	string raim = Int2BString(0, 1);

	string flag = Int2BString(0, 1);

	string mode = Int2BString(0, 1);

    string Spare2 = Int2BString(0, 2);

	wxString sChannel = channel;
    string Channel = (const char*)sChannel.mb_str();

    string BigString = MessageID;
    BigString = BigString + RepeatIndicator;
	

    BigString = BigString + oMMSI +  aisTXtype + oName + PosAccuracy + Longitude
        + Latitude + oDim + aisTXpositiondevice + TimeStamp + offPosition + sstatus + raim + flag + mode + Spare2;

	int sz = BigString.size();
    wxString mySize = wxString::Format(_T("%i"), sz);
	 //wxMessageBox(mySize);

    string capsule = NMEAencapsulate(BigString, 46);
    string aisnmea = "AIVDM,1,1,," + Channel + "," + capsule + ",4";
    wxString myNMEA = aisnmea;
    wxString myCheck = makeCheckSum(myNMEA);

    myNMEA = _T("!") + myNMEA + _T("*") + myCheck;
	
   // wxMessageBox(myNMEA);
    return myNMEA;
}



// ***************  Signal Station *************************************
wxString AisMaker::nmeaEncode41_8(int iMMSI,
    wxString countrycode, int fairwaySection, int objectType, int objectRef,
	int hectometre, int signalForm, int orientation, int impact, int lightStatus, int spare)
{

    string MessageID(Int2BString(8, 6));

    string RepeatIndicator = Int2BString(0, 2);

	string oMMSI = Int2BString(iMMSI, 30);

	string oSpare1 = Int2BString(0, 2);

	string AppID_dac = Int2BString(200, 10);
	string AppID_fi = Int2BString(41, 6);

	string VersionInd = Int2BString(0, 3);

	wxString cc = countrycode;
    string scc = (const char*)cc.mb_str();
	string CountryCode = Str2Six(scc, 12);
    
	string FairwaySection = Int2BString(fairwaySection, 17);

	string ObjectType = Int2BString(objectType, 3);;
     
	string ObjectRef = Int2BString(objectRef, 4);;

	string Hectometre = Int2BString(hectometre, 17);

	string SignalForm = Int2BString(signalForm, 4);

	string Orientation = Int2BString(orientation, 9);;
     
	string Impact = Int2BString(impact, 3);;

	string LightStatus = Int2BString(lightStatus, 30);

	string oSpare2 = Int2BString(0, 10);

	string BigString = MessageID + RepeatIndicator;
	BigString = BigString + oMMSI + oSpare1 + AppID_dac + AppID_fi + VersionInd + CountryCode + FairwaySection + ObjectType + ObjectRef
		+ Hectometre + SignalForm + Orientation + Impact + LightStatus + oSpare2;

	int bsz = BigString.size();

	int numSixes = (bsz / 6);

    string capsule = NMEAencapsulate(BigString, numSixes);
    string aisnmea = "AIVDM,1,1,,A," + capsule + ",O";

	wxString myCheck;
	wxString myNMEA;
	myCheck = makeCheckSum(aisnmea);
	myNMEA = "!" + aisnmea + "*" + myCheck;

	return myNMEA;
	
}

// *******************  Text Message  *****************************************
wxArrayString AisMaker::nmeaEncode44_8(int iMMSI,
    wxString countrycode, int FairwaySection, string object, int hectometre, string text)
{

    string MessageID(Int2BString(8, 6));

    string RepeatIndicator = Int2BString(0, 2);

	string oMMSI = Int2BString(iMMSI, 30);

	string oSpare1 = Int2BString(0, 2);

	string AppID_dac = Int2BString(200, 10);
	string AppID_fi = Int2BString(44, 6);

	string VersionInd = Int2BString(0, 3);

	wxString cc = countrycode;
    string scc = (const char*)cc.mb_str();
	string CountryCode = Str2Six(scc, 12);
    
	string FairwaySection1(Int2BString(FairwaySection, 17));

	wxString Object = object;
    string sObject = (const char*)Object.mb_str();
	string oObject = Str2Six(sObject, 30);

	string Hectometre = Int2BString(hectometre, 17);

	string oSpare2 = Int2BString(0, 1);

	string myText = Str2Six(text, 30);
	std::transform(myText.begin(), myText.end(),myText.begin(), ::toupper);

	//wxString mySize = wxString::Format(_T("%i"),bitSize);
	//wxMessageBox(mySize);
	/*
	int text_size = 222;   // 6 * (sText.size() / 6);
	int over_bits = sText.size() - text_size;
	
	//string oText;
	if (over_bits == 0) {   // Text fits in 6-bit characters
		oText = Str2Six(sText, text_size);   
	}
	else {
		text_size += 6; // Need to add a further 6-bit character to accommodate the text
		oText = Str2Six(sText, text_size);
	}

	*/

	string BigString = MessageID + RepeatIndicator;
	BigString = BigString + oMMSI + oSpare1 + AppID_dac + AppID_fi + VersionInd + CountryCode + FairwaySection1 + oObject + Hectometre + oSpare2 +  myText;

	int bsz = BigString.size();

	//wxString mySize = wxString::Format(_T("%i"), bsz);
	//wxMessageBox(mySize);
	int text_size;
	int over_bits;
	text_size = 6 * (bsz / 6);
	over_bits = 6 - (bsz - text_size);

	//mySize = wxString::Format(_T("%i"), over_bits);
	//wxMessageBox(mySize);

	string oSpare3;
	if (over_bits == 0) {
		oSpare3 = Int2BString(0, 6);		
	}
	else {		
		oSpare3 = Int2BString(0, over_bits);
	}

	BigString = BigString + oSpare3;

	bsz = BigString.size();
	

	//int osize = oText.size();
	//wxString mySize1 = wxString::Format(_T("%i"), bsz);
	//wxMessageBox(mySize1);

	// now to make a string of 6-bit characters

	int numSixes = (bsz / 6);

    string capsule = NMEAencapsulate(BigString, numSixes);
    string aisnmea = "AIVDM,1,1,,A," + capsule + ",O";

	wxString myCheck;
	wxString myNMEA;
	myCheck = makeCheckSum(aisnmea);
	myNMEA = "!" + aisnmea + "*" + myCheck;

	wxArrayString nmeaArray;
	nmeaArray.Add(myNMEA);
	return nmeaArray;
	
	int numSlots = abs(bsz / 168) + 1;

	wxString myTest(wxString::Format("%i", numSlots));
	//wxMessageBox(myTest);
/*
	string slots[3];
	string capsule;
	
	string aisNMEA;
	wxString myCheck;
	wxString myNMEA;
	int numSixes;
	
	switch (numSlots) {
	case 2:
		slots[0] = BigString.substr(0, 167);
		capsule = NMEAencapsulate(slots[0], 28);
		aisNMEA = "AIVDM,1,1,,A," + capsule + ",O";
		myCheck = makeCheckSum(aisNMEA);
		myNMEA = "!" + aisNMEA + "*" + myCheck;
		nmeaArray.Add(myNMEA);

		slots[1] = BigString.substr(168);
		sz = slots[1].size();
		numSixes = (sz / 6) + 1;
		capsule = NMEAencapsulate(slots[1], numSixes);
		aisNMEA = "AIVDM,1,2,,A," + capsule + ",O";
		myCheck = makeCheckSum(aisNMEA);
		myNMEA = "!" + aisNMEA + "*" + myCheck;
		nmeaArray.Add(myNMEA);
		//wxMessageBox(myNMEA);

		return nmeaArray;
		break;
	case 3:
		slots[0] = BigString.substr(0, 167);
		capsule = NMEAencapsulate(slots[0], 28);
		aisNMEA = "AIVDM,1,1,,A," + capsule + ",O";
		myCheck = makeCheckSum(aisNMEA);
		myNMEA = "!" +aisNMEA + "*" + myCheck;
		nmeaArray.Add(myNMEA);
		//wxMessageBox(myNMEA);

		slots[1] = BigString.substr(168, 335);
		capsule = NMEAencapsulate(slots[1], 28);
		aisNMEA = "AIVDM,1,2,,A," + capsule + ",O";
		myCheck = makeCheckSum(aisNMEA);
		myNMEA = "!" + aisNMEA + "*" + myCheck;
		nmeaArray.Add(myNMEA);
		//wxMessageBox(myNMEA);

		slots[2] = BigString.substr(336);
		sz = slots[2].size();
		numSixes = (sz / 6) + 1;
		capsule = NMEAencapsulate(slots[2], numSixes);
		aisNMEA = "AIVDM,1,3,,A," + capsule + ",O";
		myCheck = makeCheckSum(aisNMEA);
		myNMEA = "!" + aisNMEA + "*" + myCheck;
		nmeaArray.Add(myNMEA);
		//wxMessageBox(myNMEA);

		return nmeaArray;
		break;
	}


	string slot1 = BigString.substr(0, 167);



	wxString sChannel;
    string Channel = (const char*)sChannel.mb_str();

    return nmeaArray;

	*/
}

// ****************** Bridge Clearance ***************************************
wxString AisMaker::nmeaEncode25_8(int iMMSI,
	wxString countryCode, int sectionNumber, wxString objectCode, int hectometre, int bridgeClearance, int minutesOfDay, int accuracy)
{
	string MessageID(Int2BString(8, 6));

	string RepeatIndicator = Int2BString(0, 2);

	string oMMSI = Int2BString(iMMSI, 30);

	string oSpare1 = Int2BString(0, 2);

	string AppID_dac = Int2BString(200, 10);
	string AppID_fi = Int2BString(25, 6);

	string VersionInd = Int2BString(0, 3);

	wxString cc = countryCode;
	string scc = (const char*)cc.mb_str();
	string CountryCode = Str2Six(scc, 12);

	string FairwaySection(Int2BString(sectionNumber, 17));

	wxString Object = objectCode;
	string sObject = (const char*)Object.mb_str();
	string oObject = Str2Six(sObject, 30);

	string oHectometre = Int2BString(hectometre, 17);

	string obridgeClearance = Int2BString(bridgeClearance, 14);

	string ominutesOfDay = Int2BString(minutesOfDay, 11);

	string oaccuracy = Int2BString(accuracy, 5);

	string oSpare2 = Int2BString(0, 3);


	string BigString = MessageID + RepeatIndicator;
	BigString = BigString + oMMSI + oSpare1 + AppID_dac + AppID_fi + VersionInd + CountryCode + 
		FairwaySection + oObject + oHectometre + obridgeClearance + ominutesOfDay + oaccuracy +
		oSpare2;

	int bsz = BigString.size();

	
	int numSixes = (bsz / 6);

	string capsule = NMEAencapsulate(BigString, numSixes);
	string aisnmea = "AIVDM,1,1,,A," + capsule + ",O";

	wxString myCheck;
	wxString myNMEA;
	myCheck = makeCheckSum(aisnmea);
	myNMEA = "!" + aisnmea + "*" + myCheck;
	
	return myNMEA;
}
// ************************** Water Level ***************************************
wxString AisMaker::nmeaEncode26_8(int iMMSI, wxString countrycode, int gaugeID_1, int waterLevelRef_1, int waterLevelValue_1,
	int gaugeID_2, int waterLevelRef_2, int waterLevelValue_2, 
	int gaugeID_3, int waterLevelRef_3, int waterLevelValue_3)
{

    string MessageID(Int2BString(8, 6));

    string RepeatIndicator = Int2BString(0, 2);

    //wxString MMSI = wxString::Format(_T("%i"), iMMSI);
   // string sMMSI = (const char*)MMSI.mb_str();

	string oMMSI = Int2BString(iMMSI, 30);

	string oSpare1 = Int2BString(0, 2);

	string AppID_dac = Int2BString(200, 10);
	string AppID_fi = Int2BString(26, 6);

	string VersionInd = Int2BString(0, 3);

	wxString cc = countrycode;
    string scc = (const char*)cc.mb_str();
	string CountryCode = Str2Six(scc, 12);
    
	string ogaugeID_1 = Int2BString(gaugeID_1, 11);
	string owaterLevelRef_1 = Int2BString(waterLevelRef_1, 3);
	string owaterLevelValue_1 = Int2BString(waterLevelValue_1, 17);

	string ogaugeID_2 = Int2BString(gaugeID_2, 11);
	string owaterLevelRef_2 = Int2BString(waterLevelRef_2, 3);
	string owaterLevelValue_2 = Int2BString(waterLevelValue_2, 17);

	string ogaugeID_3 = Int2BString(gaugeID_3, 11);
	string owaterLevelRef_3 = Int2BString(waterLevelRef_3, 3);
	string owaterLevelValue_3 = Int2BString(waterLevelValue_3, 17);
	
	string oSpare = Int2BString(0, 4);

	string BigString = MessageID + RepeatIndicator;
	BigString = BigString + oMMSI + oSpare1 + AppID_dac + AppID_fi + VersionInd + CountryCode +  
		 ogaugeID_1 +  owaterLevelRef_1 +  owaterLevelValue_1 +
	     ogaugeID_2 +  owaterLevelRef_2 +  owaterLevelValue_2 +  
	     ogaugeID_3 +  owaterLevelRef_3 +  owaterLevelValue_3 +
		 oSpare;

	int bsz = BigString.size();

	int numSixes = (bsz / 6);

    string capsule = NMEAencapsulate(BigString, numSixes);
    string aisnmea = "AIVDM,1,1,,A," + capsule + ",O";

	wxString myCheck;
	wxString myNMEA;
	myCheck = makeCheckSum(aisnmea);
	myNMEA = "!" + aisnmea + "*" + myCheck;
	
	return myNMEA;
	
}

