#pragma once

#include"MainFrame.h"
#include<wx\wx.h>

class Simulator : public wxApp
{
private:
	MainFrame* m_MainWindow = nullptr;
public:
	Simulator();
	~Simulator();
	virtual bool OnInit();
};
