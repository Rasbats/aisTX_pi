///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "aisTXgui.h"

///////////////////////////////////////////////////////////////////////////

aisTXBase::aisTXBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	this->SetBackgroundColour( wxColour( 201, 201, 201 ) );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	m_staticText82 = new wxStaticText( this, wxID_ANY, _("   AIS Message for Tx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	m_staticText82->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer121->Add( m_staticText82, 0, wxALL|wxEXPAND, 5 );

	wxString m_choiceMessageChoices[] = { _("On-Position"), _("Off-Position"), _("Signal Station Shore"), _("ISRS Text Message"), _("Present Bridge Clearance"), _("Water Level Shore"), _("Geographic Notice Shore"), wxEmptyString, wxEmptyString, wxEmptyString };
	int m_choiceMessageNChoices = sizeof( m_choiceMessageChoices ) / sizeof( wxString );
	m_choiceMessage = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceMessageNChoices, m_choiceMessageChoices, 0 );
	m_choiceMessage->SetSelection( 0 );
	bSizer121->Add( m_choiceMessage, 0, wxALL|wxEXPAND, 5 );


	bSizer10->Add( bSizer121, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxHORIZONTAL );


	bSizer14->Add( bSizer92, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );


	bSizer14->Add( bSizer13, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	m_bpPlay = new wxButton( this, wxID_ANY, _("Start Tx"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_bpPlay->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_bpPlay->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_bpPlay->SetBackgroundColour( wxColour( 0, 255, 0 ) );

	bSizer16->Add( m_bpPlay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bpStop = new wxButton( this, wxID_ANY, _("Stop Tx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bpStop->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_bpStop->SetBackgroundColour( wxColour( 255, 0, 0 ) );

	bSizer16->Add( m_bpStop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer6->Add( bSizer16, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer6, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer10->Add( bSizer14, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer82;
	fgSizer82 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer82->AddGrowableCol( 0 );
	fgSizer82->AddGrowableCol( 1 );
	fgSizer82->AddGrowableCol( 2 );
	fgSizer82->AddGrowableCol( 3 );
	fgSizer82->AddGrowableRow( 0 );
	fgSizer82->AddGrowableRow( 1 );
	fgSizer82->SetFlexibleDirection( wxVERTICAL );
	fgSizer82->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	bSizer10->Add( fgSizer82, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer10 );
	this->Layout();
	bSizer10->Fit( this );
	m_timer1.SetOwner( this, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( aisTXBase::OnClose ) );
	m_bpPlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisTXBase::OnStart ), NULL, this );
	m_bpStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisTXBase::OnStop ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( aisTXBase::OnTimer ) );
}

aisTXBase::~aisTXBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( aisTXBase::OnClose ) );
	m_bpPlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisTXBase::OnStart ), NULL, this );
	m_bpStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisTXBase::OnStop ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( aisTXBase::OnTimer ) );

}

aisTXPreferences::aisTXPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("AIS") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbTransmitAis = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Transmit"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbTransmitAis, 0, wxALL, 5 );

	m_cbAisToFile = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Save to file"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbAisToFile, 0, wxALL, 5 );


	sbSizer1->Add( fgSizer2, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("MMSI") ), wxVERTICAL );

	m_textCtrlMMSI = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_textCtrlMMSI, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( sbSizer1->GetStaticBox(), wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( sbSizer1->GetStaticBox(), wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	sbSizer1->Add( m_sdbSizer1, 1, wxEXPAND, 5 );


	this->SetSizer( sbSizer1 );
	this->Layout();
	sbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

aisTXPreferences::~aisTXPreferences()
{
}

AISdisplay::AISdisplay( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelAIS = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_tcAIS = new wxTextCtrl( m_panelAIS, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer4->Add( m_tcAIS, 1, wxALL|wxEXPAND, 5 );

	m_tbAISPause = new wxToggleButton( m_panelAIS, wxID_ANY, _("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_tbAISPause, 0, wxALL, 5 );


	m_panelAIS->SetSizer( bSizer4 );
	m_panelAIS->Layout();
	bSizer4->Fit( m_panelAIS );
	m_notebook1->AddPage( m_panelAIS, _("AIS"), false );

	bSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1->Realize();

	bSizer1->Add( m_sdbSizer1, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
}

AISdisplay::~AISdisplay()
{
}
