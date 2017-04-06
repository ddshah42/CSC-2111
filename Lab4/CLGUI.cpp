#include "CLGUI.h"
#include <iostream>
using namespace std;


BEGIN_EVENT_TABLE (CLGUI, wxFrame)
   EVT_BUTTON (wxID_HIGHEST + 1, CLGUI::on_cl_button_click_event) 
END_EVENT_TABLE() 

CLGUI::CLGUI(CircularList<CD>* list, int width, int height) : wxFrame((wxFrame *)NULL, -1,  wxT("Circular List"), wxPoint(500,300), wxSize(width,height))
{
   cl = list;
}

void CLGUI::setTextBox(wxTextCtrl* cl_text_box)
{
   cl_remove_text_box = cl_text_box;
}

void CLGUI::setDrawPanel(DrawPanel* draw_panel)
{
   cl_draw_panel = draw_panel;
}

CLGUI::~CLGUI()
{
   delete cl;
}

void CLGUI::update()
{
   Refresh();
}

void CLGUI::on_cl_button_click_event(wxCommandEvent& evt)
{
   wxString remove_text = cl_remove_text_box->GetLineText(0);
   long index;
   remove_text.ToLong(&index);
   cout << index << endl;
   
   cl->remove(index);
   update();
}
