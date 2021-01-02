#pragma once

#include<wx\wx.h>
#include"MainFrame.h"

class Emulator: public wxApp
{
private:
	MainFrame* m_MainWindow = nullptr;
public:
	Emulator();
	~Emulator();
	virtual bool OnInit();
};
