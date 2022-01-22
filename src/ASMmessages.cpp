///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ASMmessages.h"
#include "aisTXgui_impl.h"



///////////////////////////////////////////////////////////////////////////

asmMessages::asmMessages( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("label") ), wxVERTICAL );

	m_pListCtrlAISTargets = new wxListView( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_REPORT|wxLC_SINGLE_SEL);
	sbSizer3->Add( m_pListCtrlAISTargets, 0, wxALL|wxEXPAND, 5 );


	mainSizer->Add( sbSizer3, 0, wxALL|wxEXPAND, 5 );

	m_pHeaderText = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_pHeaderText->Wrap( -1 );
	mainSizer->Add( m_pHeaderText, 0, wxALL|wxEXPAND, 5 );

	m_htmlWin = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	mainSizer->Add( m_htmlWin, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonHide = new wxButton( this, wxID_ANY, _("Hide"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonHide, 0, wxALL, 5 );

	m_buttonEdit = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonEdit, 0, wxALL, 5 );

	m_buttonDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonDelete, 0, wxALL, 5 );


	mainSizer->Add( bSizer4, 1, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonHide->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnHideList ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnEditItem ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnDeleteItem ), NULL, this );

}

asmMessages::~asmMessages()
{
	// Disconnect Events
	m_buttonHide->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnHideList ), NULL, this );
	m_buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnEditItem ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnDeleteItem ), NULL, this );
}
void asmMessages::OnHideList( wxCommandEvent& event) {

	this->Hide();
}

void asmMessages::OnEditItem( wxCommandEvent& event) {

	wxString item_edit;
		
	long id = m_pListCtrlAISTargets->GetFirstSelected();
	theDialog->m_idEdit = id;
		
	if (m_pListCtrlAISTargets->IsSelected(id)) {
		item_edit = m_pListCtrlAISTargets->GetItemText(id, 1);
		// Remove it from the listctrl.		
	}

	   SignalsList::iterator iter;

		// let's iterate over the list in STL syntax

		for (iter = theDialog->mySignalsList.begin(); iter != theDialog->mySignalsList.end(); ++iter)
		{
			Signals *current = *iter;
			//...process the current element...
			wxString sCountry = current->Country;
			if (item_edit == sCountry) {
				
				wxString MMSI = current->MMSI;
				theDialog->m_textMMSI->SetValue(MMSI);
				wxString Country = current->Country;
				theDialog->m_textCountry->SetValue(Country);
				wxString FairwaySection = current->FairwaySection;
				theDialog->m_textFairwaySection->SetValue(FairwaySection);
				wxString StationType = current->StationType;
				theDialog->m_textStationType->SetValue(StationType);
				wxString StationNumber = current->StationNumber;
				theDialog->m_textStationNumber->SetValue(StationNumber);
				wxString Hectometre = current->Hectometre;
				theDialog->m_textHectometre->SetValue(Hectometre);
				wxString SignalForm = current->SignalForm;
				theDialog->m_textSignalForm->SetValue(SignalForm);
				wxString Orientation = current->Orientation;
				theDialog->m_textOrientation->SetValue(Orientation);
				wxString Impact = current->Impact;
				theDialog->m_textImpact->SetValue(Impact);
				wxString LightStatus = current->LightStatus;
				theDialog->m_textLightStatus->SetValue(LightStatus);
			}
		}
}


void asmMessages::OnDeleteItem( wxCommandEvent& event) {

	 wxString item_bin;
		
	long id = m_pListCtrlAISTargets->GetFirstSelected();
		
	if (m_pListCtrlAISTargets->IsSelected(id)) {
		item_bin = m_pListCtrlAISTargets->GetItemText(id, 1);
		// Remove it from the listctrl.
		m_pListCtrlAISTargets->DeleteItem(id);
	}
		
	SignalsList::iterator iter;

    int index = 0;

		// let's iterate over the list in STL syntax

	for (iter = theDialog->mySignalsList.begin(); iter != theDialog->mySignalsList.end(); ++iter)
	{
		Signals *current = *iter;
		//...process the current element...
		wxString sCountry = current->Country;
		if (item_bin == sCountry) {
			theDialog->mySignalsList.remove(current);
		}
	}		

	theDialog->SaveSignalsToXml(theDialog->mySignalsList, "Signals.xml");
}

