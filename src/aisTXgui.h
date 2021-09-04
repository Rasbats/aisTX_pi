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
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/notebook.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class aisTXBase
///////////////////////////////////////////////////////////////////////////////
class aisTXBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText82;
		wxButton* m_bpPlay;
		wxButton* m_bpStop;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxChoice* m_choiceMessage;
		wxTimer m_timer1;

		aisTXBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("AIS Tx"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
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

