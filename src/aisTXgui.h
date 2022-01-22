///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/tglbtn.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class aisTXBase
///////////////////////////////////////////////////////////////////////////////
class aisTXBase : public wxDialog
{
	private:

	protected:
		wxButton* m_buttonSignals;
		wxButton* m_buttonBridges;
		wxStaticText* m_staticText82;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText11;
		wxPanel* m_panel3;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textMMSI1;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCountry1;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textFairwaySection1;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_textObjectCode1;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textHectometre1;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_textText1;
		wxPanel* m_panel4;
		wxStaticText* m_staticText121;
		wxTextCtrl* m_textMMSI2;
		wxStaticText* m_staticText131;
		wxTextCtrl* m_textCountry2;
		wxStaticText* m_staticText141;
		wxTextCtrl* m_textFairwaySection2;
		wxStaticText* m_staticText151;
		wxTextCtrl* m_textObjectCode2;
		wxStaticText* m_staticText161;
		wxTextCtrl* m_textHectometre2;
		wxStaticText* m_staticText28;
		wxTextCtrl* m_textBridgeClearance;
		wxStaticText* m_staticText29;
		wxTextCtrl* m_textTime;
		wxStaticText* m_staticText30;
		wxTextCtrl* m_textAccuracy;
		wxPanel* m_panel5;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_textMMSI3;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCountry3;
		wxStaticText* m_staticText41;
		wxTextCtrl* m_textGauge1;
		wxStaticText* m_staticText51;
		wxTextCtrl* m_textWaterRef1;
		wxStaticText* m_staticText61;
		wxTextCtrl* m_textValue1;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_textGauge2;
		wxStaticText* m_staticText81;
		wxTextCtrl* m_textWaterRef2;
		wxStaticText* m_staticText91;
		wxTextCtrl* m_textValue2;
		wxStaticText* m_staticText101;
		wxTextCtrl* m_textGauge3;
		wxStaticText* m_staticText111;
		wxTextCtrl* m_textWaterRef3;
		wxStaticText* m_staticText511;
		wxTextCtrl* m_textValue3;
		wxButton* m_buttonSave;
		wxButton* m_buttonDelete;
		wxButton* m_bpPlay;
		wxButton* m_bpStop;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSignals( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBridges( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMessageSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMessageDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxNotebook* m_notebookMessage;

		// The Signal Station fields
		wxPanel* m_panelSignal;
		wxTextCtrl* m_textMMSI;
		wxTextCtrl* m_textCountry;
		wxTextCtrl* m_textFairwaySection;
		wxTextCtrl* m_textStationType;
		wxTextCtrl* m_textStationNumber;
		wxTextCtrl* m_textHectometre;
		wxTextCtrl* m_textSignalForm;
		wxTextCtrl* m_textOrientation;
		wxTextCtrl* m_textImpact;
		wxTextCtrl* m_textLightStatus;





		wxTimer m_timer1;

		aisTXBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("AIS Tx"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 359,631 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~aisTXBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class aisTXPreferences
///////////////////////////////////////////////////////////////////////////////
class aisTXPreferences : public wxDialog
{
	private:

	protected:
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;

	public:
		wxCheckBox* m_cbTransmitAis;
		wxCheckBox* m_cbAisToFile;
		wxTextCtrl* m_textCtrlMMSI;

		aisTXPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxRESIZE_BORDER );
		~aisTXPreferences();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AISdisplay
///////////////////////////////////////////////////////////////////////////////
class AISdisplay : public wxDialog
{
	private:

	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panelAIS;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;

	public:
		wxTextCtrl* m_tcAIS;
		wxToggleButton* m_tbAISPause;

		AISdisplay( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("AIS Log"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 701,370 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~AISdisplay();

};

