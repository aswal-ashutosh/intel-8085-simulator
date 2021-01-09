#pragma once

#include"MainFrame.h"
#include<wx\wx.h>

class Emulator : public wxApp
{
private:
	MainFrame* m_MainWindow = nullptr;
public:
	Emulator();
	~Emulator();
	virtual bool OnInit();
};
