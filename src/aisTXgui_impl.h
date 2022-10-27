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

#ifndef _HRGUI_IMPL_H_
#define _HRGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "AisMaker.h"
#include "aisTX_pi.h"
#include "aisTXgui.h"
#include "ocpn_plugin.h"
#include "tinyxml.h"
#include "wx/process.h"
#include "json/reader.h"
#include "json/writer.h"
#include <cmath>
#include <sstream>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/listctrl.h>
#include <wx/stdpaths.h>
#include <wx/thread.h>
#include <wx/utils.h>

#include <memory>

#ifdef __WXOSX__
#define aisTX_DLG_STYLE                                                   \
    wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxSTAY_ON_TOP
#else
#define aisTX_DLG_STYLE                                                   \
    wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
#endif
using namespace std;

class aisTX_pi;
class AisMaker;
class AISdisplay;

class Dlg : public aisTXBase {
public:
    Dlg(wxWindow* parent, wxWindowID id = wxID_ANY,
        const wxString& title = _("aisTX"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = aisTX_DLG_STYLE);
    aisTX_pi* plugin;

	//wxString createAIVDMSentence();

	// utility functions left for further use
    wxString LatitudeToString(double mLat);
    wxString LongitudeToString(double mLon);
    wxString DateTimeToTimeString(wxDateTime myDT);
    wxString DateTimeToDateString(wxDateTime myDT);
    void OnContextMenu(double m_lat, double m_lon);

    wxString makeCheckSum(wxString mySentence);

    wxTimer* m_Timer;
    void OnTimer(wxTimerEvent& event);

    double GetLatitude() { return initLat; };
    double GetLongitude() { return initLon; };

    double initLat;
    double initLon;
    double nextLat;
    double nextLon;

    double stepLat;
    double stepLon;
    AisMaker* myAIS;
	AisMaker* myaisTX;
	AISdisplay* m_pAISdialog;
	bool m_bDisplayStarted;
	wxString SetaisTXMessage(string &msg);

    wxTextFile* nmeafile;

    bool m_bUseAis;
    bool m_bUseFile;
    wxString m_tMMSI;

    bool m_bAuto;

    double myDir;

	wxArrayString myNMEAais44_8;
	wxString myNMEAais26_8;
    wxString myNMEAais;

protected:
    

private:
	
	void GetMessage();
    void Notify();
    wxString AIVDM;
    double initDir, initSpd, initRudder, myDist, followStepDistance;

    wxDateTime dt;
    void SetInterval(int interval);
    int m_interval;

    wxString m_sTimeSentence;
    wxString m_sTimeID;
    wxString m_sNmeaTime;

    bool dbg;

    bool m_bUseSetTime;
    bool m_bUseStop;
    bool m_bUsePause;


    void OnStart(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    void SetStop();
    void StartDriving();

    long m_iMMSI;

    virtual void Lock() { routemutex.Lock(); }
    virtual void Unlock() { routemutex.Unlock(); }
    wxMutex routemutex;


    double AttributeDouble(TiXmlElement* e, const char* name, double def);

    bool m_bUsingWind;
    bool m_bUsingFollow;
    bool m_baisTXHasStarted;
};

#endif
