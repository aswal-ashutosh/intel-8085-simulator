#include "Emulator.h"

wxIMPLEMENT_APP(Emulator);

Emulator::Emulator()
{

}

Emulator::~Emulator()
{

}

bool Emulator::OnInit()
{
	this->m_MainWindow = new MainFrame();
	this->m_MainWindow->Show();
	return true;
}