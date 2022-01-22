/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  aisTX Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                *
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

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif // precompiled headers

#include "aisTX_pi.h"
#include "aisTXgui.h"
#include "aisTXgui_impl.h"
#include "ocpn_plugin.h"

class aisTX_pi;
class Dlg;

using namespace std;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr)
{
    return new aisTX_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p) { delete p; }

//---------------------------------------------------------------------------------------------------------
//
//    aisTX PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

aisTX_pi::aisTX_pi(void* ppimgr)
    : opencpn_plugin_116(ppimgr)
{
    // Create the PlugIn icons
    initialize_images();

    wxFileName fn;

    auto path = GetPluginDataDir("aisTX_pi");
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetFullName("aisTX_panel_icon.png");

    path = fn.GetFullPath();

    wxInitAllImageHandlers();

    wxLogDebug(wxString("Using icon path: ") + path);
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    if (panelIcon.IsOk())
        m_panelBitmap = wxBitmap(panelIcon);
    else
        wxLogWarning("aisTX panel icon has NOT been loaded");
    m_bShowaisTX = false;
}

aisTX_pi::~aisTX_pi(void)
{

    delete _img_aisTXIcon;

    if (m_pDialog) {

        wxFileConfig* pConf = GetOCPNConfigObject();
        ;

        if (pConf) {

            pConf->SetPath(_T("/Settings/aisTX"));

            pConf->Write(_T("aisTXUseAis"), m_bCopyUseAis);
            pConf->Write(_T("aisTXUseFile"), m_bCopyUseFile);
            pConf->Write(_T("aisTXMMSI"), m_tCopyMMSI);
        }
    }
}

int aisTX_pi::Init(void)
{
    AddLocaleCatalog(_T("opencpn-aisTX_pi"));

    // Set some default private member parameters
    m_hr_dialog_x = 40;
    m_hr_dialog_y = 80;
    m_hr_dialog_sx = 400;
    m_hr_dialog_sy = 300;
    ::wxDisplaySize(&m_display_width, &m_display_height);

    //    Get a pointer to the opencpn display canvas, to use as a parent for
    //    the POI Manager dialog
    m_parent_window = GetOCPNCanvasWindow();

    //    Get a pointer to the opencpn configuration object
    m_pconfig = GetOCPNConfigObject();

    //    And load the configuration items
    LoadConfig();

    //    This PlugIn needs a toolbar icon, so request its insertion
    if (m_baisTXShowIcon) {
#ifdef aisTX_USE_SVG
        m_leftclick_tool_id = InsertPlugInToolSVG(_T( "aisTX" ),
            _svg_aisTX, _svg_aisTX, _svg_aisTX_toggled,
            wxITEM_CHECK, _("aisTX"), _T( "" ), NULL,
            aisTX_TOOL_POSITION, 0, this);
#else
        m_leftclick_tool_id = InsertPlugInTool(_T(""), _img_aisTXIcon,
            _img_aisTXIcon, wxITEM_CHECK, _("aisTX"), _T(""), NULL,
            aisTX_TOOL_POSITION, 0, this);
#endif
    }
    wxMenu dummy_menu;
    m_position_menu_id = AddCanvasContextMenuItem(
        new wxMenuItem(&dummy_menu, -1, _("aisTX Start Position")),
        this);
    SetCanvasContextMenuItemViz(m_position_menu_id, true);

    m_pDialog = NULL;

    return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK
        | WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL | WANTS_CURSOR_LATLON
        | WANTS_NMEA_SENTENCES | WANTS_AIS_SENTENCES | WANTS_PREFERENCES
        | WANTS_PLUGIN_MESSAGING | WANTS_CONFIG);
}

bool aisTX_pi::DeInit(void)
{
    //    Record the dialog position
    if (NULL != m_pDialog) {
        // Capture dialog position
        wxPoint p = m_pDialog->GetPosition();
        wxRect r = m_pDialog->GetRect();
        SetaisTXDialogX(p.x);
        SetaisTXDialogY(p.y);
        SetaisTXDialogSizeX(r.GetWidth());
        SetaisTXDialogSizeY(r.GetHeight());

        if ((m_pDialog->m_Timer != NULL)
            && (m_pDialog->m_Timer
                    ->IsRunning())) { // need to stop the timer or crash on exit
            m_pDialog->m_Timer->Stop();
        }
        m_pDialog->Close();
        delete m_pDialog;
        m_pDialog = NULL;

        m_bShowaisTX = false;
        SetToolbarItemState(m_leftclick_tool_id, m_bShowaisTX);
    }

    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

    return true;
}

int aisTX_pi::GetAPIVersionMajor()
{
    return atoi(API_VERSION);
}

int aisTX_pi::GetAPIVersionMinor()
{
    std::string v(API_VERSION);
    size_t dotpos = v.find('.');
    return atoi(v.substr(dotpos + 1).c_str());
}

int aisTX_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int aisTX_pi::GetPlugInVersionMinor() { return PLUGIN_VERSION_MINOR; }

wxBitmap* aisTX_pi::GetPlugInBitmap() { return &m_panelBitmap; }

wxString aisTX_pi::GetCommonName() { return _("aisTX"); }

wxString aisTX_pi::GetShortDescription() { return _("aisTX player"); }

wxString aisTX_pi::GetLongDescription() { return _("Almost a simulator"); }

int aisTX_pi::GetToolbarToolCount(void) { return 1; }

void aisTX_pi::SetColorScheme(PI_ColorScheme cs)
{
    if (NULL == m_pDialog)
        return;

    DimeWindow(m_pDialog);
}

void aisTX_pi::ShowPreferencesDialog(wxWindow* parent)
{
    aisTXPreferences* Pref = new aisTXPreferences(parent);

    Pref->m_cbTransmitAis->SetValue(m_bCopyUseAis);
    Pref->m_cbAisToFile->SetValue(m_bCopyUseFile);
    Pref->m_textCtrlMMSI->SetValue(m_tCopyMMSI);

    if (Pref->ShowModal() == wxID_OK) {

        bool copyAis = Pref->m_cbTransmitAis->GetValue();
        bool copyFile = Pref->m_cbAisToFile->GetValue();
        wxString copyMMSI = Pref->m_textCtrlMMSI->GetValue();

        if (m_bCopyUseAis != copyAis || m_bCopyUseFile != copyFile
            || m_tCopyMMSI != copyMMSI) {
            m_bCopyUseAis = copyAis;
            m_bCopyUseFile = copyFile;
            m_tCopyMMSI = copyMMSI;
        }

        if (m_pDialog) {
            m_pDialog->m_bUseAis = m_bCopyUseAis;
            m_pDialog->m_bUseFile = m_bCopyUseFile;
            m_pDialog->m_tMMSI = m_tCopyMMSI;
        }

        SaveConfig();

        RequestRefresh(m_parent_window); // refresh main window
    }
}

void aisTX_pi::OnToolbarToolCallback(int id)
{

    if (NULL == m_pDialog) {
        m_pDialog = new Dlg(m_parent_window);
        m_pDialog->plugin = this;
		m_pDialog->SetTitle("aisTX - version - 0.4");
        m_pDialog->m_Timer = new wxTimer(m_pDialog);
        m_pDialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
        m_pDialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);
    }

    // m_pDialog->Fit();
    // Toggle
    m_bShowaisTX = !m_bShowaisTX;

    //    Toggle dialog?
    if (m_bShowaisTX) {
        m_pDialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
        m_pDialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);
        m_pDialog->Show();

    } else {
        m_pDialog->Hide();
    }

    // Toggle is handled by the toolbar but we must keep plugin manager b_toggle
    // updated to actual status to ensure correct status upon toolbar rebuild
    SetToolbarItemState(m_leftclick_tool_id, m_bShowaisTX);

    // Capture dialog position
    wxPoint p = m_pDialog->GetPosition();
    wxRect r = m_pDialog->GetRect();
    SetaisTXDialogX(p.x);
    SetaisTXDialogY(p.y);
    SetaisTXDialogSizeX(r.GetWidth());
    SetaisTXDialogSizeY(r.GetHeight());

    RequestRefresh(m_parent_window); // refresh main window
}


bool aisTX_pi::LoadConfig(void)
{
    wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

    if (pConf) {
        pConf->SetPath(_T( "/Settings/aisTX_pi" ));
        pConf->Read(_T( "ShowaisTXIcon" ), &m_baisTXShowIcon, 1);
        pConf->Read(_T("aisTXUseAis"), &m_bCopyUseAis, 0);
        pConf->Read(_T("aisTXUseFile"), &m_bCopyUseFile, 0);
        m_tCopyMMSI = pConf->Read(_T("aisTXMMSI"), _T("12345"));

        m_hr_dialog_x = pConf->Read(_T ( "DialogPosX" ), 40L);
        m_hr_dialog_y = pConf->Read(_T ( "DialogPosY" ), 140L);
        m_hr_dialog_sx = pConf->Read(_T ( "DialogSizeX"), 330L);
#ifdef __WXOSX__
        m_hr_dialog_sy = pConf->Read(_T ( "DialogSizeY"), 250L);
#else
        m_hr_dialog_sy = pConf->Read(_T ( "DialogSizeY"), 300L);
#endif
        if ((m_hr_dialog_x < 0) || (m_hr_dialog_x > m_display_width))
            m_hr_dialog_x = 40;
        if ((m_hr_dialog_y < 0) || (m_hr_dialog_y > m_display_height))
            m_hr_dialog_y = 140;

        return true;
    } else
        return false;
}

bool aisTX_pi::SaveConfig(void)
{
    wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

    if (pConf) {
        pConf->SetPath(_T ( "/Settings/aisTX_pi" ));
        pConf->Write(_T ( "ShowaisTXIcon" ), m_baisTXShowIcon);
        pConf->Write(_T("aisTXUseAis"), m_bCopyUseAis);
        pConf->Write(_T("aisTXUseFile"), m_bCopyUseFile);
        pConf->Write(_T("aisTXMMSI"), m_tCopyMMSI);

        pConf->Write(_T ( "DialogPosX" ), m_hr_dialog_x);
        pConf->Write(_T ( "DialogPosY" ), m_hr_dialog_y);
        pConf->Write(_T ( "DialogSizeX"), m_hr_dialog_sx);
        pConf->Write(_T ( "DialogSizeY"), m_hr_dialog_sy);

        return true;
    } else
        return false;
}

void aisTX_pi::OnaisTXDialogClose()
{
    m_bShowaisTX = false;
    SetToolbarItemState(m_leftclick_tool_id, m_bShowaisTX);
    m_pDialog->Hide();
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window
}

void aisTX_pi::OnContextMenuItemCallback(int id)
{

    if (!m_pDialog)
        return;

    if (id == m_position_menu_id) {

        m_cursor_lat = GetCursorLat();
        m_cursor_lon = GetCursorLon();

        m_pDialog->OnContextMenu(m_cursor_lat, m_cursor_lon);
    }
}

void aisTX_pi::SetCursorLatLon(double lat, double lon)
{
    m_cursor_lat = lat;
    m_cursor_lon = lon;
}


void aisTX_pi::SetNMEASentence(wxString& sentence)
{

    // $GPAPB,A,A,0.10,R,N,V,V,011,M,DEST,011,M,011,M*3C

    if (NULL == m_pDialog)
        return;

    wxString token[40];
    wxString s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    token[0] = _T("");

    wxStringTokenizer tokenizer(sentence, wxT(","));
    int i = 0;

    while (tokenizer.HasMoreTokens()) {
        token[i] = tokenizer.GetNextToken();
        i++;
    }
    if (token[0].Right(3) == _T("APB")) {

        s11 = token[11];

        if (m_pDialog->m_bAuto) {

            double value;
            s11.ToDouble(&value);
            m_pDialog->myDir = value;
        }
        /*
        s6 = token[6];
        if (s6 == _T("A")) {
                wxMessageBox(_("Vessel has arrived at the final waypoint"));
        }
        */
    }
}

wxString aisTX_pi::StandardPath()
{
   
	wxString stdPath(*GetpPrivateApplicationDataLocation());
	wxString s = wxFileName::GetPathSeparator();

	stdPath += s + _T("plugins") + s + _T("aisTX_pi");
	if (!wxDirExists(stdPath))
		wxMkdir(stdPath);
	stdPath += s + _T("data");
	if (!wxDirExists(stdPath))
		wxMkdir(stdPath);
	
    return stdPath;
}