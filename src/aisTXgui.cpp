///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "aisTXgui.h"

///////////////////////////////////////////////////////////////////////////

aisTXBase::aisTXBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );
	this->SetBackgroundColour( wxColour( 201, 201, 201 ) );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	m_staticText82 = new wxStaticText( this, wxID_ANY, _("   AIS Message for Tx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	m_staticText82->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

	bSizer121->Add( m_staticText82, 0, wxALL|wxEXPAND, 5 );

	m_notebookMessage
	= new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel3 = new wxPanel( m_notebookMessage
	, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText12 = new wxStaticText( m_panel3, wxID_ANY, _("MMSI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	gSizer2->Add( m_staticText12, 0, wxALL, 5 );

	m_textMMSI1 = new wxTextCtrl( m_panel3, wxID_ANY, _("244123459"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textMMSI1, 0, wxALL, 5 );

	m_staticText13 = new wxStaticText( m_panel3, wxID_ANY, _("Country"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gSizer2->Add( m_staticText13, 0, wxALL, 5 );

	m_textCountry1 = new wxTextCtrl( m_panel3, wxID_ANY, _("NL"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textCountry1, 0, wxALL, 5 );

	m_staticText14 = new wxStaticText( m_panel3, wxID_ANY, _("Fairway Section"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	gSizer2->Add( m_staticText14, 0, wxALL, 5 );

	m_textFairwaySection1 = new wxTextCtrl( m_panel3, wxID_ANY, _("137"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textFairwaySection1, 0, wxALL, 5 );

	m_staticText15 = new wxStaticText( m_panel3, wxID_ANY, _("Object Code"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	gSizer2->Add( m_staticText15, 0, wxALL, 5 );

	m_textObjectCode1 = new wxTextCtrl( m_panel3, wxID_ANY, _("5204"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textObjectCode1, 0, wxALL, 5 );

	m_staticText16 = new wxStaticText( m_panel3, wxID_ANY, _("Hectometre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	gSizer2->Add( m_staticText16, 0, wxALL, 5 );

	m_textHectometre1 = new wxTextCtrl( m_panel3, wxID_ANY, _("86"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textHectometre1, 0, wxALL, 5 );


	bSizer131->Add( gSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );

	m_staticText17 = new wxStaticText( m_panel3, wxID_ANY, _("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

	bSizer101->Add( m_staticText17, 0, wxALL, 5 );

	m_textText1 = new wxTextCtrl( m_panel3, wxID_ANY, _("BRUG OPEN"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer101->Add( m_textText1, 0, wxALL|wxEXPAND, 5 );


	bSizer131->Add( bSizer101, 0, wxEXPAND, 5 );


	m_panel3->SetSizer( bSizer131 );
	m_panel3->Layout();
	bSizer131->Fit( m_panel3 );
	m_notebookMessage
	->AddPage( m_panel3, _("Text"), true );
	m_panel5 = new wxPanel( m_notebookMessage
	, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText31 = new wxStaticText( m_panel5, wxID_ANY, _("MMSI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	gSizer11->Add( m_staticText31, 0, wxALL, 5 );

	m_textMMSI3 = new wxTextCtrl( m_panel5, wxID_ANY, _("00000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textMMSI3, 0, wxALL, 5 );

	m_staticText21 = new wxStaticText( m_panel5, wxID_ANY, _("Country"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	gSizer11->Add( m_staticText21, 0, wxALL, 5 );

	m_textCountry3 = new wxTextCtrl( m_panel5, wxID_ANY, _("ZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textCountry3, 0, wxALL, 5 );

	m_staticText41 = new wxStaticText( m_panel5, wxID_ANY, _("Gauge ID 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gSizer11->Add( m_staticText41, 0, wxALL, 5 );

	m_textGauge1 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textGauge1, 0, wxALL, 5 );

	m_staticText51 = new wxStaticText( m_panel5, wxID_ANY, _("Water level Ref 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer11->Add( m_staticText51, 0, wxALL, 5 );

	m_textWaterRef1 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textWaterRef1, 0, wxALL, 5 );

	m_staticText61 = new wxStaticText( m_panel5, wxID_ANY, _("Water level value 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	gSizer11->Add( m_staticText61, 0, wxALL, 5 );

	m_textValue1 = new wxTextCtrl( m_panel5, wxID_ANY, _("-65536"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textValue1, 0, wxALL, 5 );

	m_staticText71 = new wxStaticText( m_panel5, wxID_ANY, _("Gauge ID 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	gSizer11->Add( m_staticText71, 0, wxALL, 5 );

	m_textGauge2 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textGauge2, 0, wxALL, 5 );

	m_staticText81 = new wxStaticText( m_panel5, wxID_ANY, _("Water level Ref 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	gSizer11->Add( m_staticText81, 0, wxALL, 5 );

	m_textWaterRef2 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textWaterRef2, 0, wxALL, 5 );

	m_staticText91 = new wxStaticText( m_panel5, wxID_ANY, _("Water level value 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	gSizer11->Add( m_staticText91, 0, wxALL, 5 );

	m_textValue2 = new wxTextCtrl( m_panel5, wxID_ANY, _("-65536"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textValue2, 0, wxALL, 5 );

	m_staticText101 = new wxStaticText( m_panel5, wxID_ANY, _("Gauge ID 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	gSizer11->Add( m_staticText101, 0, wxALL, 5 );

	m_textGauge3 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textGauge3, 0, wxALL, 5 );

	m_staticText111 = new wxStaticText( m_panel5, wxID_ANY, _("Water level Ref 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	gSizer11->Add( m_staticText111, 0, wxALL, 5 );

	m_textWaterRef3 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textWaterRef3, 0, wxALL, 5 );

	m_staticText511 = new wxStaticText( m_panel5, wxID_ANY, _("Water level value 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText511->Wrap( -1 );
	gSizer11->Add( m_staticText511, 0, wxALL, 5 );

	m_textValue3 = new wxTextCtrl( m_panel5, wxID_ANY, _("-65536"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textValue3, 0, wxALL, 5 );


	m_panel5->SetSizer( gSizer11 );
	m_panel5->Layout();
	gSizer11->Fit( m_panel5 );
	m_notebookMessage
	->AddPage( m_panel5, _("Water_level"), false );

	bSizer121->Add( m_notebookMessage
	, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	m_bpPlay = new wxButton( this, wxID_ANY, _("Start Tx"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_bpPlay->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );
	m_bpPlay->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_bpPlay->SetBackgroundColour( wxColour( 0, 255, 0 ) );

	bSizer16->Add( m_bpPlay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bpStop = new wxButton( this, wxID_ANY, _("Stop Tx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bpStop->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );
	m_bpStop->SetBackgroundColour( wxColour( 255, 0, 0 ) );

	bSizer16->Add( m_bpStop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer6->Add( bSizer16, 1, wxEXPAND, 5 );


	bSizer121->Add( bSizer6, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer10->Add( bSizer121, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxVERTICAL );

	m_staticText37 = new wxStaticText( this, wxID_ANY, _("AIVDM Message"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	m_staticText37->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

	bSizer132->Add( m_staticText37, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrlAIVDM = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer132->Add( m_textCtrlAIVDM, 0, wxALL|wxEXPAND, 5 );


	bSizer10->Add( bSizer132, 1, wxEXPAND, 5 );


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
