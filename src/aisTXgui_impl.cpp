/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  aisTX Plugin
 * Author:   Mike Rossiter
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
#include "aisTX_pi.h"
#include <wx/progdlg.h>
#include <wx/wx.h>

#include "wx/textfile.h"
#include <stdio.h>
#include <wx/timer.h>

#include <memory>

using mylibais::AisMsg;
using std::unique_ptr;
using namespace mylibais;


void assign(char* dest, char* arrTest2) { strcpy(dest, arrTest2); }

#define BUFSIZE 0x10000

Dlg::Dlg(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style)
    : aisTXBase(parent, id, title, pos, size, style)
{
    this->Fit();
    dbg = false; // for debug output set to true
    initLat = 50.0;
    initLon = -4.0;
	myDir = 30.0;
	
    m_interval = 500;
    m_bUseSetTime = false;
    m_bUseStop = true;
    m_bUsePause = false;
    m_sNmeaTime = wxEmptyString;

    m_bUsingWind = false;
    m_bUsingFollow = false;
    m_baisTXHasStarted = false;
	m_bDisplayStarted = false;

    wxFileConfig* pConf = GetOCPNConfigObject();

    if (pConf) {
        pConf->SetPath(_T("/Settings/aisTX_pi"));

        pConf->Read(_T("aisTXUseAis"), &m_bUseAis, 0);
        pConf->Read(_T("aisTXUseFile"), &m_bUseFile, 0);
        pConf->Read(_T("aisTXMMSI"), &m_tMMSI, "12345");
    }

	AISTargetList = new AIS_Target_Hash;
	AISTargetNamesC = new AIS_Target_Name_Hash;
    AISTargetNamesNC = new AIS_Target_Name_Hash;
	pTargetData = new AIS_Target_Data;
	
}

namespace mylibais {
	template <typename T, typename... Args>
	std::unique_ptr<T> MakeUnique(Args &&... args) {
		//wxMessageBox("here");
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	unique_ptr<AisMsg>CreateAisMsg8(const string &body, const int fill_bits) {
		mylibais::Ais8 msg(body.c_str(), fill_bits);
		int dac = msg.fi;
		wxString dacs = wxString::Format("%i", dac);
		//wxMessageBox(dacs);

		

		return MakeUnique<mylibais::Ais8_200_41>(body.c_str(), fill_bits);

	}



	unique_ptr<AisMsg> CreateAisMsg(const string &body, const int fill_bits) {


		string mybody = body;
		//wxMessageBox(mybody);

		int fill = fill_bits;
		wxString fills = wxString::Format("%i", fill);
		//wxMessageBox(fills);

		Ais8 msg(body.c_str(), fill_bits);

		int dac = msg.fi;
		wxString dacs = wxString::Format("%i", dac);
		//wxMessageBox(dacs);
		return CreateAisMsg8(body, fill_bits);



	}

} // mylibais


void Dlg::OnTimer(wxTimerEvent& event) { Notify(); }


void Dlg::OnStart(wxCommandEvent& event) { 
	
	WX_DECLARE_HASH_MAP( int, AIS_Target_Data*, wxIntegerHash, wxIntegerEqual, AIS_Target_Hash);
	
	myAIS = new AisMaker();
	myaisTX = new AisMaker();

	GetMessage();

	//AIVDM = createAIVDMSentence();
	//wxMessageBox(AIVDM);
	StartDriving(); 

}

void Dlg::StartDriving()
{

	
    m_baisTXHasStarted = true;


    if (!m_tMMSI.ToLong(&m_iMMSI)) {
        wxMessageBox(_("MMSI must be a number, please change in Preferences"));
        return;
    }

    if (m_bUseFile) {

        wxString caption = wxT("Choose a file");
        wxString wildcard = wxT("Text files (*.txt)|*.txt|All files (*.*)|*.*");

        wxString s = _T("/");
        const char* pName = "aisTX_pi";
        wxString defaultDir = GetPluginDataDir(pName) + s + _T("data") + s;

        wxString defaultFilename = wxEmptyString;
        wxFileDialog filedlg(this->m_parent, caption, defaultDir,
            defaultFilename, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (filedlg.ShowModal() != wxID_OK) {
            wxMessageBox(_("aisTX has been stopped"));
            return;
        } else {
            nmeafile = new wxTextFile(filedlg.GetPath());
            nmeafile->Open();
            nmeafile->Clear();
        }
    }


    dt = dt.Now();
 

    m_interval = 500;
    m_Timer->Start(m_interval, wxTIMER_CONTINUOUS); // start timer
    m_bAuto = false;

    
}

void Dlg::OnStop(wxCommandEvent& event) { SetStop(); }

void Dlg::SetStop()
{

    if (m_Timer->IsRunning())
        m_Timer->Stop();
 

    m_interval = m_Timer->GetInterval();
    m_bUseSetTime = false;
    m_bUseStop = true;
    m_bAuto = false;
    m_bUsingWind = false;
    m_bUsingFollow = false;


    if (m_bUseFile) {
        nmeafile->Write();
        nmeafile->Close();
    }
 
}


AIS_Target_Data* Dlg::Get_Target_Data_From_MMSI( int mmsi )
{
	int sz = AISTargetList->count(pTargetData->MMSI);

	wxString testCount = wxString::Format("%i", sz);
	wxMessageBox(testCount);

	
	if( AISTargetList->find( mmsi ) == AISTargetList->end() )     // if entry does not exist....
    return NULL;
    else
        return ( *AISTargetList )[mmsi];          // find current entry
}


wxString Dlg::SetaisTXMessage(string &msg) {
	unique_ptr<AisMsg> myMsg;

	//AIS_Bitstring* myBits;

	string payload;
	//   !AIVDM,1,1,,A,E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0,4*05
	//payload = "E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0"; //aisTX
	payload = msg;
	//string output;

	// myMsg = CreateAisMsg(payload,0);
	 int mm = myMsg->mmsi;
	 int ms = myMsg->message_id;

	 wxString outstring(wxString::Format(("%i"), mm));
	 return outstring;
	// wxMessageBox(outString);

	//wxString paystring = payload;

	//  Create the bit accessible string
	///AIS_Bitstring strbit(paystring.mb_str());


	///char testOut;

	///strbit.GetStr(10, 20, &testOut, 7);
	///wxMessageBox(testOut);
	/*
	AisBitset bs;
	const char* load = "E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0";
	bs.ParseNmeaPayload(load, 0);
	AisPoint myPt;
	myPt = bs.ToAisPoint(164, 55);

	double lat = myPt.lat_deg;

	wxString out(wxString::Format(("%f"), lat));
	wxMessageBox(out);*/
}

void Dlg::OnAIS(wxCommandEvent& event)
{
	
    ///m_iMMSI = 992030009;
	///wxString timeStamp = wxString::Format(_T("%i"), wxGetUTCTime());

	//wxString myNMEAais = myAIS->nmeaEncode(_T("18"), 1234, _T("5"), 5,
    //    49.0, 17.0, 270, 270, _T("B"), timeStamp);

	
	///wxString myNMEAaisTX = myAIS->nmeaEncodeaisTX("21", m_iMMSI, "", 48.148, 16.9149, "A", timeStamp);
	///wxMessageBox(myNMEAaisTX);
	int x = plugin->m_hr_dialog_x + 200;
	int y = plugin->m_hr_dialog_y;
	
	m_pAISdialog = new AISdisplay(this->GetParent());
	m_pAISdialog->Show();
	m_pAISdialog->m_tbAISPause->SetValue(false);

	m_bDisplayStarted = true;
    m_bAuto = true;

    Refresh();
}

void Dlg::OnStandby(wxCommandEvent& event) { GoToStandby(); }

void Dlg::GoToStandby()
{

    m_bAuto = false;

    Refresh();
}

void Dlg::OnClose(wxCloseEvent& event)
{
    if (m_Timer->IsRunning())
        m_Timer->Stop();
    plugin->OnaisTXDialogClose();
}

void Dlg::GetMessage() {

	long value;
	
	int pageSelected = m_notebookMessage->GetSelection();

    if (pageSelected == 0) {
		wxString mMMSI = m_textMMSI->GetValue();
		mMMSI.ToLong(&value);
		int vMMSI = value;

		string country = m_textCountry->GetValue();	
		std::transform(country.begin(), country.end(),country.begin(), ::toupper);
		
		wxString mSection = m_textFairwaySection->GetValue();
		mSection.ToLong(&value);
		int vSection = value;

		wxString mType = m_textStationType->GetValue();
		mType.ToLong(&value);
		int vType = value;

		wxString mNumber = m_textStationNumber->GetValue();
		mNumber.ToLong(&value);
		int vNumber = value;		

		wxString mHect = m_textHectometre->GetValue();
		mHect.ToLong(&value);
		int vHect = value;


		wxString mForm = m_textSignalForm->GetValue();
		mForm.ToLong(&value);
		int vForm = value;

		wxString mOrient = m_textOrientation->GetValue();
		mOrient.ToLong(&value);
		int vOrient = value;

		wxString mImpact = m_textImpact->GetValue();
		mImpact.ToLong(&value);
		int vImpact = value;

		wxString mStat = m_textLightStatus->GetValue();
		mStat.ToLong(&value);
		int vStatus = value;

		int vSpare = 0;

        myNMEAais41_8 = myAIS->nmeaEncode41_8(vMMSI,country, vSection, 
		vType, vNumber, vHect, vForm, vOrient, vImpact, vStatus, vSpare);

		myNMEAais = myNMEAais41_8;

		wxString CR = "\n";
		wxString test = mMMSI + CR + country + CR + mSection + CR +mType + CR + mNumber + CR + mHect + CR + mOrient + CR + mImpact + CR + mStat;
		wxMessageBox(test);
	}
	else

	if (pageSelected == 1) {

		wxString mMMSI = m_textMMSI1->GetValue();
		mMMSI.ToLong(&value);
		int vMMSI = value;

		string country = m_textCountry1->GetValue();
		std::transform(country.begin(), country.end(),country.begin(), ::toupper);

		
		wxString mSection = m_textFairwaySection1->GetValue();
		mSection.ToLong(&value);
		int vSection = value;	

		string mCode = m_textObjectCode1->GetValue();
		std::transform(mCode.begin(), mCode.end(),mCode.begin(), ::toupper);
				
		wxString mHect = m_textHectometre1->GetValue();
		mHect.ToLong(&value);
		int vHect = value;


		string mText = m_textText1->GetValue();
		std::transform(mText.begin(), mText.end(),mText.begin(), ::toupper);

		int vSpare = 0;

		myNMEAais44_8 = myAIS->nmeaEncode44_8(vMMSI, country, vSection, mCode, vHect, mText);

		myNMEAais = myNMEAais44_8.Item(0);


		wxString CR = "\n";
		wxString test = mMMSI + CR + country + CR + mSection + CR + mCode + CR + mHect + CR + mText;
		wxMessageBox(test);
	}
	else

	if (pageSelected == 2) {

		wxString mMMSI = m_textMMSI2->GetValue();
		mMMSI.ToLong(&value);
		int vMMSI = value;

		string country = m_textCountry2->GetValue();
		std::transform(country.begin(), country.end(),country.begin(), ::toupper);
		
		wxString mSection = m_textFairwaySection2->GetValue();
		mSection.ToLong(&value);
		int vSection = value;	

		string mCode = m_textObjectCode2->GetValue();
		std::transform(mCode.begin(), mCode.end(),mCode.begin(), ::toupper);
				
		wxString mHect = m_textHectometre2->GetValue();
		mHect.ToLong(&value);
		int vHect = value;		

		wxString mClear = m_textBridgeClearance->GetValue();
		mClear.ToLong(&value);
		int vClear = value;	

		wxString mTime = m_textTime->GetValue();
		mTime.ToLong(&value);
		int vTime = value;

		wxString mAcc = m_textAccuracy->GetValue();
		mAcc.ToLong(&value);
		int vAcc = value;

		myNMEAais25_8 = myAIS->nmeaEncode25_8(vMMSI, country, vSection, mCode, vHect, vClear, vTime, vAcc);

		myNMEAais = myNMEAais25_8;


		wxString CR = "\n";
		wxString test = mMMSI + CR + country + CR + mSection + CR + mCode + CR + mHect + CR + mClear + CR + mTime + CR + mAcc;
		wxMessageBox(test);
	}
	else

	if (pageSelected == 3) {

		wxString mMMSI = m_textMMSI3->GetValue();
		mMMSI.ToLong(&value);
		int vMMSI = value;

		string country = m_textCountry3->GetValue();
		std::transform(country.begin(), country.end(),country.begin(), ::toupper);

		wxString mGauge1 = m_textGauge1->GetValue();
		mGauge1.ToLong(&value);
		int vGauge1 = value;	

		wxString mRef1 = m_textWaterRef1->GetValue();
		mRef1.ToLong(&value);
		int vRef1 = value;	

		wxString mVal1 = m_textValue1->GetValue();
		mVal1.ToLong(&value);
		int vVal1 = value;	

		wxString mGauge2 = m_textGauge2->GetValue();
		mGauge2.ToLong(&value);
		int vGauge2 = value;	

		wxString mRef2 = m_textWaterRef2->GetValue();
		mRef2.ToLong(&value);
		int vRef2 = value;	

		wxString mVal2 = m_textValue2->GetValue();
		mVal2.ToLong(&value);
		int vVal2 = value;	

		wxString mGauge3 = m_textGauge3->GetValue();
		mGauge3.ToLong(&value);
		int vGauge3 = value;	

		wxString mRef3 = m_textWaterRef3->GetValue();
		mRef3.ToLong(&value);
		int vRef3 = value;	

		wxString mVal3 = m_textValue3->GetValue();
		mVal3.ToLong(&value);
		int vVal3 = value;	

		myNMEAais26_8 = myAIS->nmeaEncode26_8(vMMSI, country, vGauge1, vRef1, vVal1, vGauge2, vRef2, vVal2, vGauge3, vRef3, vVal3);

		myNMEAais = myNMEAais26_8;


		wxString CR = "\n";
		wxString test = mMMSI + CR + country + CR + mGauge1 + CR + mRef1 + CR + mVal1 + CR + mGauge2 + CR + mRef2 + CR + mVal2 + CR + mGauge3 + CR + mRef3 + CR + mVal3;
		wxMessageBox(test);
	}



	

}

void Dlg::Notify()
{
    wxString mySentence;
    plugin->SetNMEASentence(mySentence);

	wxString myAISsentence;
	plugin->SetAISSentence(myAISsentence);

    wxString timeStamp = wxString::Format(_T("%i"), wxGetUTCTime());

   // wxString myNMEAais = myAIS->nmeaEncode(_T("18"), m_iMMSI, _T("5"), initSpd,
       // initLat, initLon, myDir, myDir, _T("B"), timeStamp);

	wxString myNMEAais24 = myAIS->nmeaEncode24(m_iMMSI, "KAMISH", "B");
	//wxString myNMEA_aton_TX = myAIS->nmeaEncodeAtonTX("21", m_iMMSI, "", 49.148, 15.9149, "A", timeStamp);

	// Testing RIS Signal Station message
	//wxString myNMEAais41_8 = myAIS->nmeaEncode41_8(m_iMMSI,"AT", 5555, 2, 10, 1768, 10, 99, 1, 15541);
	PushNMEABuffer(myNMEAais + _T("\n"));

	// Testing RIS Text message
	//wxArrayString myNMEAais44_8 = myAIS->nmeaEncode44_8(m_iMMSI,"TESTING THE QUICK BROWN FOX", "AT", "OBH1");

	// Testing RIS Bridge Clearance message
	//wxString myNMEAais25_8 = myAIS->nmeaEncode25_8(m_iMMSI, 0,"AT", 1234, "OBH2", 15, 2047, 0);
	//PushNMEABuffer(myNMEAais25_8 + _T("\n"));


	// Testing RIS Water Level message
	//wxString myNMEAais26_8 = myAIS->nmeaEncode26_8(m_iMMSI,"AT", 0, 0, 140,  0, 0, 140,  0, 0, 140);
	//PushNMEABuffer(myNMEAais26_8 + _T("\n"));

	/*int slots = myNMEAais44_8.GetCount();
	for (int i = 0; i < slots; i++) {
		if (m_bUseFile) {
			nmeafile->AddLine(myNMEAais26_8);
		}
		PushNMEABuffer(myNMEAais26_8 + _T("\n"));
	}
	*/
    
	int ss = 1;
    wxTimeSpan mySeconds = wxTimeSpan::Seconds(ss);
    wxDateTime mdt = dt.Add(mySeconds);
 
	// 
	//AIVDM = createAIVDMSentence();
	//PushNMEABuffer(AIVDM + _T("\n"));
	//

	// Testing encoding AIS
	PushNMEABuffer(myNMEAais + _T("\n"));
	PushNMEABuffer(myNMEAais24 + _T("\n"));
	
	// Not using at present:
	// PushNMEABuffer(myNMEA_aton_TX + _T("\n"));
	// 

    dt = mdt;

	
}

void Dlg::SetInterval(int interval)
{
    m_interval = interval;
    if (m_Timer->IsRunning()) // Timer started?
        m_Timer->Start(
            m_interval, wxTIMER_CONTINUOUS); // restart timer with new interval
}
/*
wxString Dlg::createAIVDMSentence()
{
	
	wxString nFinal;

	int sel = m_choiceMessage->GetSelection();
	switch (sel) {
		case (0): {
			nFinal = "!AIVDM,1,1,,A,E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0,4*05";
			break;
		}
		case (1): {
			nFinal = "!AIVDM,1,1,,A,E>j4e>PLtqHIpHHp@@@@@@@@@@@0Vf25=iVr000000NBp0,4*3F";
			break;
		}
		case (2): {
			nFinal = "!AIVDM,1,1,,A,8000000j:@2`004dBhpb0WVGsP00,0*61";
			break;
		}
		case (3): {
			nFinal = "!AIVDM,1,1,,A,8000000j;02`004<8tS4`eP85D588DU@Dr04r1=A8tlhDUADpLDp,0*2F";
			break;
		}    		
    }
	
	return nFinal;

}
*/
wxString Dlg::makeCheckSum(wxString mySentence)
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

double StringToLatitude(wxString mLat)
{

    // 495054
    double returnLat;
    wxString mBitLat = mLat(0, 2);
    double degLat;
    mBitLat.ToDouble(&degLat);
    wxString mDecLat = mLat(2, mLat.length());
    double decValue;
    mDecLat.ToDouble(&decValue);

    returnLat = degLat + decValue / 100 / 60;

    return returnLat;
}

wxString Dlg::LatitudeToString(double mLat)
{

    wxString singlezero = _T("0");
    wxString mDegLat;

    int degLat = std::abs(mLat);
    wxString finalDegLat = wxString::Format(_T("%i"), degLat);

    int myL = finalDegLat.length();
    switch (myL) {
    case (1): {
        mDegLat = singlezero + finalDegLat;
        break;
    }
    case (2): {
        mDegLat = finalDegLat;
        break;
    }
    }

    double minLat = std::abs(mLat) - degLat;
    double decLat = minLat * 60;

    wxString returnLat;
    // wxMessageBox(returnLat, _T("returnLat"));

    if (mLat >= 0) {
        if (decLat < 10) {
            returnLat = mDegLat + _T("0") + wxString::Format(_T("%.6f"), decLat)
                + _T(",N,");
        } else {
            returnLat
                = mDegLat + wxString::Format(_T("%.6f"), decLat) + _T(",N,");
        }

    } else if (mLat < 0) {
        if (decLat < 10) {
            returnLat = mDegLat + _T("0") + wxString::Format(_T("%.6f"), decLat)
                + _T(",S,");
        } else {
            returnLat
                = mDegLat + wxString::Format(_T("%.6f"), decLat) + _T(",S,");
        }
    }

    return returnLat;
}
double StringToLongitude(wxString mLon)
{

    wxString mBitLon = "";
    wxString mDecLon;
    double value1;
    double decValue1;

    double returnLon;

    int m_len = mLon.length();

    if (m_len == 7) {
        mBitLon = mLon(0, 3);
    }

    if (m_len == 6) {
        mBitLon = mLon(0, 2);
    }

    if (m_len == 5) {
        mBitLon = mLon(0, 1);
    }

    if (m_len == 4) {
        mBitLon = "00.00";
    }

    if (mBitLon == "-") {
        value1 = -0.00001;
    } else {
        mBitLon.ToDouble(&value1);
    }

    mDecLon = mLon(mLon.length() - 4, mLon.length());
    mDecLon.ToDouble(&decValue1);

    if (value1 < 0) {
        returnLon = value1 - decValue1 / 100 / 60;
    } else {
        returnLon = value1 + decValue1 / 100 / 60;
    }

    return returnLon;
}

wxString Dlg::LongitudeToString(double mLon)
{

    wxString mDecLon;
    wxString mDegLon;
    double decValue;
    wxString returnLon;
    wxString doublezero = _T("00");
    wxString singlezero = _T("0");

    int degLon = fabs(mLon);
    wxString inLon = wxString::Format(_T("%i"), degLon);

    // wxMessageBox(returnLon, _T("inLon"));

    int myL = inLon.length();
    switch (myL) {
    case (1): {
        mDegLon = doublezero + inLon;
        break;
    }
    case (2): {
        mDegLon = singlezero + inLon;
        break;
    }
    case (3): {
        mDegLon = inLon;
        break;
    }
    }
    decValue = std::abs(mLon) - degLon;
    double decLon = decValue * 60;

    if (mLon >= 0) {
        if (decLon < 10) {
            returnLon = mDegLon + _T("0") + wxString::Format(_T("%.6f"), decLon)
                + _T(",E,");
        } else {
            returnLon
                = mDegLon + wxString::Format(_T("%.6f"), decLon) + _T(",E,");
        }

    } else {
        if (decLon < 10) {
            returnLon = mDegLon + _T("0") + wxString::Format(_T("%.6f"), decLon)
                + _T(",W,");
        } else {
            returnLon
                = mDegLon + wxString::Format(_T("%.6f"), decLon) + _T(",W,");
        }
    }
    // wxMessageBox(returnLon, _T("returnLon"));
    return returnLon;
}

wxString Dlg::DateTimeToTimeString(wxDateTime myDT)
{
    wxString sHours, sMinutes, sSecs;
    sHours = myDT.Format(_T("%H"));
    sMinutes = myDT.Format(_T("%M"));
    sSecs = myDT.Format(_T("%S"));
    wxString dtss = sHours + sMinutes + sSecs;
    return dtss;
}

wxString Dlg::DateTimeToDateString(wxDateTime myDT)
{

    wxString sDay, sMonth, sYear;
    sDay = myDT.Format(_T("%d"));
    sMonth = myDT.Format(_T("%m"));
    sYear = myDT.Format(_T("%y"));

    return sDay + sMonth + sYear;
}

void Dlg::OnContextMenu(double m_lat, double m_lon)
{

    m_bUsingWind = false;

    initLat = m_lat;
    initLon = m_lon;
}

double Dlg::AttributeDouble(TiXmlElement* e, const char* name, double def)
{
    const char* attr = e->Attribute(name);
    if (!attr)
        return def;
    char* end;
    double d = strtod(attr, &end);
    if (end == attr)
        return def;
    return d;
}

void Dlg::OnTest(wxCommandEvent& event)
{
	
	string myMessage = "8000000j:@2`004dBhpb0WVGsP00";

	unique_ptr<mylibais::AisMsg> myMsg;
	myMsg = mylibais::CreateAisMsg(myMessage,0);

	mylibais::AisBitset bs;
	const char* load = "8000000j:@2`004dBhpb0WVGsP00";
	bs.ParseNmeaPayload(load, 0);
	int i = bs.ToInt(71, 17);
	
	const char* payload =  "8000000j:@2`004dBhpb0WVGsP00";
	mylibais::Ais8_200_41 myRIS(payload,0);
	int myID = myRIS.hectometre;
	string myCountry = myRIS.country;

	//int mid = myMsg->message_id;
	wxString outID = wxString::Format("%i", myID);
	//AIS_Target_Data* myData;
	//myData = Get_Target_Data_From_MMSI(992030009);
	//int myID = myRis->version; // myData->MID;
	wxMessageBox(outID);
	wxMessageBox(myCountry);
}