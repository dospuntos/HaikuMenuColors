#include "MainWindow.h"

#include <MenuBar.h>
#include <Menu.h>
#include <MenuItem.h>
#include <View.h>
#include <cstdlib>

enum
{
	M_SET_COLOR_RED = 'sred',
	M_SET_COLOR_GREEN = 'sgrn',
	M_SET_COLOR_BLUE = 'sblu',
	M_SET_COLOR_BLACK = 'sblk',
	M_SET_COLOR_PINK = 'spnk',
	M_SET_COLOR_RANDOM = 'rndm'
};

MainWindow::MainWindow(void)
	:	BWindow(BRect(100,100,500,400),"MenuColors",B_TITLED_WINDOW,
			B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE)
{
	
	
	BRect r(Bounds());
	r.bottom = 20;
	
	BMenuBar *menuBar = new BMenuBar(r,"menubar");
	AddChild(menuBar);
	
	//Create a "File" menu
	BMenu *filemenu = new BMenu("File");
	filemenu->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED),'Q'));

	menuBar->AddItem(filemenu);
	
	//This is the code that creates and populates the menu
	BMenu *menu = new BMenu("Colors");
	menu->AddItem(new BMenuItem("Red",new BMessage(M_SET_COLOR_RED),'R'));
	menu->AddItem(new BMenuItem("Green",new BMessage(M_SET_COLOR_GREEN),'G'));
	menu->AddItem(new BMenuItem("Blue",new BMessage(M_SET_COLOR_BLUE),'B'));
	menu->AddItem(new BMenuItem("Black",new BMessage(M_SET_COLOR_BLACK),'K'));
	menu->AddItem(new BMenuItem("Pink",new BMessage(M_SET_COLOR_PINK),'P'));
	menu->AddItem(new BMenuItem("Random",new BMessage(M_SET_COLOR_RANDOM),'X'));
	
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
		case M_SET_COLOR_GREEN:
		{
			view->SetViewColor(0,160,0);
			view->Invalidate();
			break;
		}
		case M_SET_COLOR_BLUE:
		{
			view->SetViewColor(0,0,160);
			view->Invalidate();
			break;
		}
		case M_SET_COLOR_BLACK:
		{
			view->SetViewColor(0,0,0);
			view->Invalidate();
			break;
		}
		case M_SET_COLOR_PINK:
		{
			view->SetViewColor(255,100,255);
			view->Invalidate();
			break;
		}
		case M_SET_COLOR_RANDOM:
		{
			int red = rand()%256;
			int green = rand()%256;
			int blue = rand()%256;
			
			view->SetViewColor(red,green,blue);
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
