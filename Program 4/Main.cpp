#include "wx/wx.h"
#include "wx/sizer.h"

#include "DrawPanel.h"
#include "ImageLoader.h"


#include "Circle.h"
#include "Line.h"
#include "AVLTree.h"
#include "ListArray.h"
#include "CD.h"
using namespace CSC2110;

class MyApp: public wxApp
{
    bool OnInit();
 
    wxFrame* frame;
    DrawPanel* drawPane;
public:
 
};
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
	ListArray<CD>* cds = CD::readCDs(argv[1]);
	int num_items = cds->size();
	cout << num_items << endl;

	ListArrayIterator<CD>* iter = cds->iterator();
	AVLTree<CD>* avl = new AVLTree<CD>(&CD::compare_items, &CD::compare_keys);
	while(iter->hasNext())
	{
		CD* cd = iter->next();
		avl->insert(cd);
		bool bf_check = avl->checkBalanceFactors();
		if (!bf_check)
		{
			cd->displayCD();
			exit(0);
		}
	}
	delete iter;
	delete cds;
   
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("AVL Tree"), wxPoint(500,500), wxSize(1100,600));
 
    drawPane = new DrawPanel((wxFrame*) frame, avl);
    sizer->Add(drawPane, 1, wxEXPAND);
 
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
 
    frame->Show();
    return true;
} 

 
/*
Important Notes
You need to handle the paint event, and it must be able to redraw the whole drawing at any time. This is because your window manager may throw away your drawing at any time and ask you to draw it again later through a paint event.
The best way to deal with this is to separate state/data from view. (The render routine reads variables describing current state and draws according to these variables. When something needs to change, don't render it straight ahead; instead, update the variables and call for a repaint - if well-coded, your paint routine should catch the change).
Use a wx[Buffered]PaintDC in paint events, and a wxClientDC outside paint events.
If you do catch the paint event, you must create a wx[Buffered]PaintDC in it, even if you don't use it. If a wx[Buffered]PaintDC object isn't created, the event isn't correctly handled which can cause weird behavior.
Do not store the created DC or keep it for later in any way.
To avoid flickering
Try bufferred DCs, they are necessary on some platforms. wxBufferedDC and wxAutoBufferedPaintDC might help you.
Call ->SetDoubleBuffered(true); on the panel (On Windows only?)
Call SetBackgroundStyle(wxBG_STYLE_CUSTOM) ( See this : http://docs.wxwidgets.org/stable/wx_wxwindow.html#wxwindowsetbackgroundstyle )
On wx 2.9.1+, wxBG_STYLE_PAINT can help too and is clearer than "custom"
Or, alternatively, Catch the wxEVT_ERASE_BACKGROUND event
*/
