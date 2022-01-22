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

#include "ais.h"

#include "AIS_Bitstring.h"

#include <wx/hashmap.h>
#include <memory>
#include "ASMmessages.h"

/*
TempData2(double minimum, double maximum, double cur, int id, time_t t) :
       stationId{id}, timeSet{t}, current{cur}, maxTemp{maximum}, minTemp{minimum} {}
*/
struct Signals
{
	Signals(wxString MMSI, wxString Country, wxString FairwaySection, wxString StationType,
		wxString StationNumber, wxString Hectometre, wxString SignalForm, wxString Orientation,
		wxString Impact, wxString LightStatus) :

	MMSI{ MMSI },
	Country{ Country },
	FairwaySection{ FairwaySection },
	StationType{ StationType },
	StationNumber{ StationNumber },
	Hectometre{ Hectometre },
	SignalForm{ SignalForm },
	Orientation{ Orientation },
	Impact{ Impact },
	LightStatus{ LightStatus }
	{}

	wxString MMSI = "00";
	wxString Country = "00";
	wxString FairwaySection = "00";
	wxString StationType = "00";
	wxString StationNumber = "00";
	wxString Hectometre = "00";
	wxString SignalForm = "00";
	wxString Orientation = "00";
	wxString Impact = "00";
	wxString LightStatus = "00";	
};

enum {
    tlTRK = 0,
    tlNAME,
    tlCALL,
    tlMMSI,
    tlCLASS,
    tlTYPE,
    tlNAVSTATUS,
    tlBRG,
    tlRNG,
    tlCOG,
    tlSOG,
    tlCPA,
    tlTCPA
};// AISTargetListCtrl Columns;

WX_DECLARE_LIST(Signals, SignalsList);
#include <wx/listimpl.cpp>



class Ais8;

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
class AIS_Target_Data;
// class rte_table;


// lass rtept;
class AIS_Target_Data
{
public:
	/*
    AIS_Target_Data();
    ~AIS_Target_Data();

    wxString BuildQueryResult(void);
    wxString GetRolloverString(void);
    wxString Get_vessel_type_string(bool b_short = false);
    wxString Get_class_string(bool b_short = false);
    wxString GetFullName( void );
    wxString GetCountryCode(bool b_CntryLongStr);
    void Toggle_AIS_CPA(void);
    void ToggleShowTrack(void);
    void CloneFrom( AIS_Target_Data* q );
    */

    int                       MID;
    int                       MMSI;
    int                       NavStatus;
    int                       SyncState;
    int                       SlotTO;
    double                    SOG;
    double                    COG;
    double                    HDG;
    double                    Lon;
    double                    Lat;
    int                       ROTAIS;
    int                       ROTIND;
    
    char                      ShipNameExtension[15];
    unsigned char             ShipType;
    int                       IMO;

    int                       DimA;
    int                       DimB;
    int                       DimC;
    int                       DimD;

    double                    Euro_Length;            // Extensions for European Inland AIS
    double                    Euro_Beam;
    double                    Euro_Draft;
    int                       UN_shiptype;
    bool                      b_isEuroInland;
    bool                      b_hasInlandDac;  // intermediate storage for EU Inland. SignalK
    bool                      b_blue_paddle;
    int                       blue_paddle;

    int                       ETA_Mo;
    int                       ETA_Day;
    int                       ETA_Hr;
    int                       ETA_Min;

	
  
};

// Retained for future use
WX_DECLARE_HASH_MAP( int, AIS_Target_Data*, wxIntegerHash, wxIntegerEqual, AIS_Target_Hash );
WX_DECLARE_HASH_MAP( int, wxString, wxIntegerHash, wxIntegerEqual, AIS_Target_Name_Hash );





// An identifier to notify the application when the // work is done #define
// ID_COUNTED_COLORS    100

class AisMaker;


// ECE-TRANS-SC3-2006-10e-RIS.pdf - River Information System
//section(0), type(0), objectnumber(0), hectometre(0), signal(0), orientation(0), impact(0),
      //light_status(0),spare(0)
// Signal status

// Decodes the payload of an AIS message and returns an AisMsg instance.
// Returns a nullptr on failure.
// The body is the armored text from 1 or more sentences that compose
// the encoded bits for an AIS message.
// The fill_bits are the number of pad bits in the last character of the
// body.  AIS messages are 8-bit aligned and the characters in the armored
// body are 6-bit aligned.

namespace mylibais {

// Decodes the payload of an AIS message and returns an AisMsg instance.
// Returns a nullptr on failure.
// The body is the armored text from 1 or more sentences that compose
// the encoded bits for an AIS message.
// The fill_bits are the number of pad bits in the last character of the
// body.  AIS messages are 8-bit aligned and the characters in the armored
// body are 6-bit aligned.
std::unique_ptr<mylibais::AisMsg> CreateAisMsg(const string &body,
                                             const int fill_bits);

}  // namespace mylibais


class Dlg : public aisTXBase {
public:
    Dlg(wxWindow* parent, wxWindowID id = wxID_ANY,
        const wxString& title = _("aisTX"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = aisTX_DLG_STYLE);
    aisTX_pi* plugin;

	wxString createAIVDMSentence();
	wxString ConvertSignalToString();

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

	AIS_Target_Data*  pTargetData;
	AIS_Target_Hash* AISTargetList;
	AIS_Target_Name_Hash* AISTargetNamesC;
    AIS_Target_Name_Hash* AISTargetNamesNC;
	AIS_Target_Name_Hash* HashFile;

	AIS_Target_Hash *GetTargetList(void) {return AISTargetList;}
    //AIS_Target_Hash *GetAreaNoticeSourcesList(void) {return AIS_AreaNotice_Sources;}
    AIS_Target_Data *Get_Target_Data_From_MMSI(int mmsi);

    AIS_Target_Data* m_pLatestTargetData;

	wxString myNMEAais;
	wxString myNMEAais41_8;
	wxArrayString myNMEAais44_8;
	wxString myNMEAais25_8;
	wxString myNMEAais26_8;

	SignalsList mySignalsList;
	asmMessages* m_pASMmessages1;
	bool m_bMessageWindow;
	
	aisTX_pi*				  myaisTXPlugin;
	void LoadSignalsFromXml(SignalsList &coords, wxString signalset);
	void SaveSignalsToXml(SignalsList &signals, wxString filename);
	long m_idEdit;


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
	void OnSignals(wxCommandEvent& event);

    void SetStop();
    void StartDriving();

    void OnAIS(wxCommandEvent& event);
    void OnTest(wxCommandEvent& event);

	void OnMessageSave(wxCommandEvent& event);
	void OnMessageDelete(wxCommandEvent& event);
	void CreateControlsMessageList();

    void OnStandby(wxCommandEvent& event);
    void GoToStandby();



    long m_iMMSI;

    virtual void Lock() { routemutex.Lock(); }
    virtual void Unlock() { routemutex.Unlock(); }
    wxMutex routemutex;


    double AttributeDouble(TiXmlElement* e, const char* name, double def);

    bool m_bUsingWind;
    bool m_bUsingFollow;
    bool m_baisTXHasStarted;
};

class GetRouteDialog : public wxDialog {
public:
    GetRouteDialog(wxWindow* parent, wxWindowID id, const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE);

    wxListView* dialogText;
    wxString GetText();

private:
    void OnOk(wxCommandEvent& event);
};



#endif
