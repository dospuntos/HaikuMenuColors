#include "MainWindow.h"

#include <MenuBar.h>
#include <Menu.h>
#include <MenuItem.h>
#include <View.h>

enum
{
	M_SET_COLOR_RED = 'sred',
	M_SET_COLOR_GREEN = 'sgrn',
	M_SET_COLOR_BLUE = 'sblu',
	M_SET_COLOR_BLACK = 'sblk'
};

MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,500,400),"MenuColors",B_TITLED_WINDOW,
			B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE)
{
	
	
	BRect r(Bounds());
	r.bottom = 20;
	
	BMenuBar *menuBar = new BMenuBar(r,"menubar");
	AddChild(menuBar);
	
	//This is the code that creates and populates the menu
	BMenu *menu = new BMenu("Colors");
	menu->AddItem(new BMenuItem("Red",new BMessage(M_SET_COLOR_RED),'R'));
	menu->AddItem(new BMenuItem("Green",new BMessage(M_SET_COLOR_GREEN),'G'));
	menu->AddItem(new BMenuItem("Blue",new BMessage(M_SET_COLOR_BLUE),'B'));
	menu->AddItem(new BMenuItem("Black",new BMessage(M_SET_COLOR_BLACK),'K'));
	
	//The menu bar adds menus the same way that a menu adds items.
	menuBar->AddItem(menu);
	
	BView *view = new BView(BRect(100,100,300,200),"colorview"
					,B_FOLLOW_ALL
					,B_WILL_DRAW);
	AddChild(view);
	view->SetViewColor(0,0,160);
}

void
MainWindow::MessageReceived(BMessage *msg)
{
	// FindView() is a BWindow method which searches for a BView by name and
	// returns a pointer to it.
	BView *view = FindView("colorview");
	
	switch (msg->what)
	{
		case M_SET_COLOR_RED:
		{
			view->SetViewColor(160,0,0);
			
			// Calling Invalidate() forces the view to redraw itself.
			view->Invalidate();
			break;
		}
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}