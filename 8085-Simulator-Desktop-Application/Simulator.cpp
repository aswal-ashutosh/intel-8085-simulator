#include "Simulator.h"

wxIMPLEMENT_APP(Simulator);

Simulator::Simulator()
{

}

Simulator::~Simulator()
{

}

bool Simulator::OnInit()
{
	this->m_MainWindow = new MainFrame();
	this->m_MainWindow->Show();
	return true;
}