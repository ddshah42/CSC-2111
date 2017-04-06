#include "wx/wx.h"
#include "wx/sizer.h"

#include "CLGUI.h"
#include "CircularList.h"
#include "ListArray.h"
#include "Random.h"
using namespace CSC2110;

class CLApp: public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(CLApp)
 
bool CLApp::OnInit()
{
	ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_cds = cds->size();

   CircularList<CD>* cl = new CircularList<CD>();
   Random* r = new Random();

   int count = 1;
   while(count <= 25)  //add 25 random cds to the circular list
   {
      int random_cd_index = r->getRandomInt(1, num_cds);
      CD* cd = cds->get(random_cd_index);
      cl->add(count, cd);
      count++;
   }

   delete cds;
   cl->get(1);
   
   	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    CLGUI* cl_frame = new CLGUI(cl, 600, 700);
	cl->addListener((Update*) cl_frame);
 
 	DrawPanel* cl_display_panel = new DrawPanel(cl_frame, cl);
	cl_frame->setDrawPanel(cl_display_panel);

	wxPanel* place_holder = new wxPanel(cl_frame);
	wxBoxSizer* place_holder_sizer = new wxBoxSizer(wxHORIZONTAL);
	place_holder->SetBackgroundColour(*wxWHITE);
	place_holder->SetSizer(place_holder_sizer);
	
	wxButton* cl_remove_button = new wxButton(place_holder, wxID_HIGHEST + 1, wxT("Remove"), wxPoint(25,375), wxSize(100, 25), 0);
	cl_remove_button->SetBackgroundColour(*wxWHITE);
	
	wxTextCtrl* cl_text_box = new wxTextCtrl(place_holder, wxID_HIGHEST + 1, "", wxPoint(25,375), wxSize(100, 25), wxTE_RICH);
	cl_frame->setTextBox(cl_text_box);
	cl_text_box->SetBackgroundColour(*wxWHITE);
	
	place_holder_sizer->Add(cl_remove_button, 1, wxEXPAND);
	place_holder_sizer->Add(cl_text_box, 1, wxEXPAND);
	
    sizer->Add(cl_display_panel, 9, wxEXPAND);
	sizer->Add(place_holder, 1, wxEXPAND);
 
    cl_frame->SetSizer(sizer);
    cl_frame->SetAutoLayout(true);
 
    cl_frame->Show();
    return true;
} 
