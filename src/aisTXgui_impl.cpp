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

Dlg::Dlg(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style)
    : aisTXBase(parent, id, title, pos, size, style)
{
    this->Fit();
    dbg = false; // for debug output set to true
	
    m_interval = 500;
    m_bUseSetTime = false;
    m_bUseStop = true;
    m_bUsePause = false;
    m_sNmeaTime = wxEmptyString;

    m_baisTXHasStarted = false;
	m_bDisplayStarted = false;

    wxFileConfig* pConf = GetOCPNConfigObject();

    if (pConf) {
        pConf->SetPath(_T("/Settings/aisTX_pi"));

        pConf->Read(_T("aisTXUseAis"), &m_bUseAis, 0);
        pConf->Read(_T("aisTXUseFile"), &m_bUseFile, 0);
        pConf->Read(_T("aisTXMMSI"), &m_tMMSI, "12345");
    }	
}

void Dlg::OnTimer(wxTimerEvent& event) { Notify(); }


void Dlg::OnStart(wxCommandEvent& event) { 
		
	myAIS = new AisMaker();
    
	GetMessage();
    m_textCtrlAIVDM->SetValue(myAIS->testAIVDM);

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

    if (m_bUseFile) {
        nmeafile->Write();
        nmeafile->Close();
    }
 
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

		wxString mMMSI = m_textMMSI1->GetValue();
		mMMSI.ToLong(&value);
		int vMMSI = value;

		wxString xcountry = m_textCountry1->GetValue();
        const char* mcountry = xcountry.c_str();
        string country = mcountry;
		std::transform(country.begin(), country.end(),country.begin(), ::toupper);

		
		wxString mSection = m_textFairwaySection1->GetValue();
		mSection.ToLong(&value);
		int vSection = value;	

		wxString xCode = m_textObjectCode1->GetValue();
        const char* mCode = xCode.c_str();
        string Code = mCode;
		std::transform(Code.begin(), Code.end(),Code.begin(), ::toupper);
				
		wxString mHect = m_textHectometre1->GetValue();
		mHect.ToLong(&value);
		int vHect = value;


		wxString Text = m_textText1->GetValue();
        const char* cText = Text.c_str();
        string mText = cText;
		std::transform(mText.begin(), mText.end(),mText.begin(), ::toupper);

		int vSpare = 0;

		myNMEAais44_8 = myAIS->nmeaEncode44_8(vMMSI, country, vSection, Code, vHect, mText);

		myNMEAais = myNMEAais44_8.Item(0);
	}
	else

	if (pageSelected == 1) {

		wxString mMMSI = m_textMMSI3->GetValue();
		mMMSI.ToLong(&value);
		int vMMSI = value;

		wxString xcountry = m_textCountry3->GetValue();
        const char* mcountry = xcountry.c_str();
        string country = mcountry;
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
	}

}

void Dlg::Notify()
{
    wxString timeStamp = wxString::Format(_T("%i"), wxGetUTCTime());
	    
	int ss = 1;
    wxTimeSpan mySeconds = wxTimeSpan::Seconds(ss);
    wxDateTime mdt = dt.Add(mySeconds);

    // Transmit the BBM
	PushNMEABuffer(myNMEAais + _T("\n"));

    dt = mdt;	
}

void Dlg::SetInterval(int interval)
{
    m_interval = interval;
    if (m_Timer->IsRunning()) // Timer started?
        m_Timer->Start(
            m_interval, wxTIMER_CONTINUOUS); // restart timer with new interval
}

//
// Below here are utility functions
// Not all used for aisTX
//

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