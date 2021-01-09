#pragma once

#include"MainFrame.h"
#include<wx\wx.h>
#include"icon.xpm"

class Emulator : public wxApp
{
private:
	MainFrame* m_MainWindow = nullptr;
public:
	Emulator();
	~Emulator();
	virtual bool OnInit();
};
