#ifndef CLGUI_H
#define CLGUI_H

#include "CircularList.h"
#include "CD.h"
using CSC2110::CD;
#include "DrawPanel.h"

class CLGUI : public wxFrame, Update
{
   private:
		CircularList<CD>* cl;
		DrawPanel* cl_draw_panel;
		wxTextCtrl* cl_remove_text_box;

   public:
		CLGUI(CircularList<CD>* cl, int width, int height);
		virtual ~CLGUI();
		virtual void update();       
		virtual void on_cl_button_click_event(wxCommandEvent& evt);
		void setDrawPanel(DrawPanel* draw_panel);
		void setTextBox(wxTextCtrl* cl_text_box);

		DECLARE_EVENT_TABLE()

};

#endif 
