#include "MainFrame.h"
#include"8085.cpp"

wxString ToWxString(const std::string& str)
{
	return  wxString(str.c_str(), wxConvUTF8);
}

std::string ToString(const wxString& str)
{
	return str.ToStdString();
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
EVT_MENU(wxID_SAVE, MainFrame::OnSave)
EVT_MENU(wxID_SAVEAS, MainFrame::OnSaveAs)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(wxID_EXECUTE, MainFrame::OnRun)
END_EVENT_TABLE()

MainFrame::MainFrame() :wxFrame(nullptr, wxID_ANY, "8085 Simulator", wxPoint(30, 30), wxSize(600, 600))
{
	this->CreateStatusBar();

	m_MenuBar = new wxMenuBar();

	m_FileMenu = new wxMenu();
	m_FileMenu->Append(wxID_OPEN, _("Open\tCtrl+O"));
	m_FileMenu->Append(wxID_SAVE, _("Save\tCtrl+S"));
	m_FileMenu->Append(wxID_SAVEAS, _("Save As\tCtrl+Shift+S"));
	m_FileMenu->AppendSeparator();
	m_FileMenu->Append(wxID_EXIT, _("Exit"));

	m_HelpMenu = new wxMenu();
	m_HelpMenu->Append(wxID_ABOUT, _("About"));
	m_HelpMenu->Append(wxID_HELP, _("Help"));

	m_MenuBar->Append(m_FileMenu, _("&File"));
	m_MenuBar->Append(m_HelpMenu, _("&More"));

	this->SetMenuBar(m_MenuBar);

	m_ToolBar = this->CreateToolBar();

	m_ToolBar->AddTool(wxID_OPEN, _("Open"), wxArtProvider::GetBitmap("wxART_FILE_OPEN", wxART_OTHER, wxSize(16, 16)), _("Open"));
	m_ToolBar->AddTool(wxID_SAVE, _("Save"), wxArtProvider::GetBitmap("wxART_FILE_SAVE", wxART_OTHER, wxSize(16, 16)), _("Save"));
	m_ToolBar->AddTool(wxID_EXECUTE, _("Execute"), wxArtProvider::GetBitmap("wxART_GO_FORWARD", wxART_OTHER, wxSize(16, 16)), _("Run"));
	m_ToolBar->Realize();


	m_EditBox = new wxStyledTextCtrl(this);
	m_EditBox->SetUseHorizontalScrollBar(false);

	m_FlagPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_FlagPanelStaticBox = new wxStaticBox(m_FlagPanel, wxID_ANY, "FLAG REGISTER");
	m_FlagPanelStaticBoxSizer = new wxStaticBoxSizer(m_FlagPanelStaticBox, wxDEFAULT);
	const char* flagReg[] = { "Z", "S", "P", "AC", "CY" };
	m_FlagRegCheckList = new wxCheckListBox(m_FlagPanelStaticBox, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxArrayString(5, flagReg), 1, wxDefaultValidator);
	m_FlagPanelStaticBoxSizer->Add(m_FlagRegCheckList);
	m_FlagPanel->SetSizer(m_FlagPanelStaticBoxSizer);

	m_RegisterPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_RegisterPanelStaticBox = new wxStaticBox(m_RegisterPanel, wxID_ANY, "REGISTERS");
	m_RegisterPanelStaticBoxSizer = new wxStaticBoxSizer(m_RegisterPanelStaticBox, wxDEFAULT);
	const char reg[] = { 'A', 'B', 'C', 'D', 'E', 'H', 'L' };
	for (int i = 0; i < 7; ++i)
	{
		std::string label= reg[i] + std::string(" :");
		m_MainRegisterLabel[reg[i]] = new wxStaticText(m_RegisterPanelStaticBox, wxID_ANY, label, wxPoint(10, 22 + i * 25), wxSize(20, 20));
		m_MainRegister[reg[i]] = new wxTextCtrl(m_RegisterPanelStaticBox, wxID_ANY, "00", wxPoint(30, 20 + i * 25), wxSize(20, 20), wxTE_READONLY);
	}
	m_RegisterPanel->SetSizer(m_RegisterPanelStaticBoxSizer);

	m_MemoryPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_MemoryPanelStaticBox = new wxStaticBox(m_MemoryPanel, wxID_ANY, "MEMORY MANAGER");
	m_MemoryPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryPanelStaticBox, wxHORIZONTAL);
	wxButton* button = new wxButton(m_MemoryPanelStaticBox, wxID_ANY, "Button");
	m_MemoryPanel->SetSizer(m_MemoryPanelStaticBoxSizer);



	m_PanelSizer = new wxBoxSizer(wxVERTICAL);
	m_PanelSizer->Add(m_FlagPanel, 1, wxEXPAND);
	m_PanelSizer->Add(m_RegisterPanel, 1, wxEXPAND);

	m_MainSizer = new wxBoxSizer(wxHORIZONTAL);
	m_MainSizer->Add(m_PanelSizer, 1, wxEXPAND|wxALL, 1);
	m_MainSizer->Add(m_EditBox, 1, wxEXPAND);
	m_MainSizer->Add(m_MemoryPanel, 1, wxEXPAND|wxALL, 1);
	this->SetSizerAndFit(m_MainSizer);


}

MainFrame::~MainFrame()
{
	
}

void MainFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open text file"), "", "","TEXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	m_currentFilePath = openFileDialog.GetPath();
	m_EditBox->LoadFile(m_currentFilePath);
}

void MainFrame::OnSave(wxCommandEvent& event)
{
	if (m_currentFilePath.empty())
	{
		OnSaveAs(event);
	}
	else
	{
		m_EditBox->SaveFile(m_currentFilePath);
	}
	
}

void MainFrame::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save text file"), "", "","TEXT files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return; 
	m_currentFilePath = saveFileDialog.GetPath();
	m_EditBox->SaveFile(m_currentFilePath);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	this->Close();
}

void MainFrame::OnRun(wxCommandEvent& event)
{
	
	if (m_currentFilePath.empty())
	{
		OnSaveAs(event);
		if (!m_currentFilePath.empty())
		{
			Init8085();
			UpdateFlagRegister();
			UpdateRegisters();
		}
	}
	else
	{
		Init8085();
		UpdateFlagRegister();
		UpdateRegisters();
	}
}

void MainFrame::UpdateFlagRegister()
{
	//wxMessageBox(wxString(Converter::DecToHex(Register::Main['A'])));
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("AC"), Register::Flag::AC);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("CY"), Register::Flag::CY);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("Z"), Register::Flag::ZF);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("S"), Register::Flag::SF);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("P"), Register::Flag::PF);
}

void MainFrame::UpdateRegisters()
{
	m_MainRegister['A']->Clear();
	m_MainRegister['B']->Clear();
	m_MainRegister['C']->Clear();
	m_MainRegister['D']->Clear();
	m_MainRegister['E']->Clear();
	m_MainRegister['H']->Clear();
	m_MainRegister['L']->Clear();

	m_MainRegister['A']->AppendText(ToWxString(Converter::DecToHex(Register::Main['A'])));
	m_MainRegister['B']->AppendText(ToWxString(Converter::DecToHex(Register::Main['B'])));
	m_MainRegister['C']->AppendText(ToWxString(Converter::DecToHex(Register::Main['C'])));
	m_MainRegister['D']->AppendText(ToWxString(Converter::DecToHex(Register::Main['D'])));
	m_MainRegister['E']->AppendText(ToWxString(Converter::DecToHex(Register::Main['E'])));
	m_MainRegister['H']->AppendText(ToWxString(Converter::DecToHex(Register::Main['H'])));
	m_MainRegister['L']->AppendText(ToWxString(Converter::DecToHex(Register::Main['L'])));
}