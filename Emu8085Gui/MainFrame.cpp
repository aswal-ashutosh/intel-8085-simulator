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
EVT_BUTTON(ButtonID::SET_BUTTON, MainFrame::OnSet)
EVT_BUTTON(ButtonID::VIEW_BUTTON, MainFrame::OnView)
END_EVENT_TABLE()

MainFrame::MainFrame() :wxFrame(nullptr, wxID_ANY, "8085 Simulator", wxPoint(30, 30), wxSize(600, 650))
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
		m_MainRegister[reg[i]]->SetMaxLength(2);
	}
	m_RegisterPanel->SetSizer(m_RegisterPanelStaticBoxSizer);

	m_MemoryInitPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_MemoryInitPanelStaticBox = new wxStaticBox(m_MemoryInitPanel, wxID_ANY, "MEMORY INITIALIZER");
	m_MemoryInitPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryInitPanelStaticBox, wxHORIZONTAL);
	m_MemoryLocationLabel = new wxStaticText(m_MemoryInitPanelStaticBox, wxID_ANY, "Address :", wxPoint(5, 35));
	m_MemoryAddressTextCtrl = new wxTextCtrl(m_MemoryInitPanelStaticBox, wxID_ANY, "0000", wxPoint(55, 30), wxSize(35, 20));
	m_MemoryAddressTextCtrl->SetMaxLength(4);
	m_DataLabel = new wxStaticText(m_MemoryInitPanelStaticBox, wxID_ANY, "Data :", wxPoint(110, 35));
	m_DataTextCtrl = new wxTextCtrl(m_MemoryInitPanelStaticBox, wxID_ANY, "00", wxPoint(145, 30), wxSize(20, 20));
	m_DataTextCtrl->SetMaxLength(2);
	m_SetButton = new wxButton(m_MemoryInitPanelStaticBox, ButtonID::SET_BUTTON, "Set", wxPoint(58, 60));
	m_MemoryInitPanel->SetSizer(m_MemoryInitPanelStaticBoxSizer);



	m_MemoryViewPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_MemoryViewPanelStaticBox = new wxStaticBox(m_MemoryViewPanel, wxID_ANY, "MEMORY VIEWER");
	m_MemoryViewPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryViewPanelStaticBox, wxHORIZONTAL);
	m_FromLabel = new wxStaticText(m_MemoryViewPanelStaticBox, wxID_ANY, "From :", wxPoint(5, 35));
	m_FromMemoryAddressTextCtrl = new wxTextCtrl(m_MemoryViewPanelStaticBox, wxID_ANY, "0000", wxPoint(40, 30), wxSize(35, 20));
	m_FromMemoryAddressTextCtrl->SetMaxLength(4);
	m_CountLabel = new wxStaticText(m_MemoryViewPanelStaticBox, wxID_ANY, "Count :", wxPoint(110, 35));
	m_CountTextCtrl = new wxTextCtrl(m_MemoryViewPanelStaticBox, wxID_ANY, "00", wxPoint(150, 30), wxSize(20, 20));
	m_CountTextCtrl->SetMaxLength(2);
	m_ViewButton = new wxButton(m_MemoryViewPanelStaticBox, ButtonID::VIEW_BUTTON, "View", wxPoint(58, 60));
	m_MemoryViewPanel->SetSizer(m_MemoryViewPanelStaticBoxSizer);


	m_LeftPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_LeftPanelSizer->Add(m_FlagPanel, 1, wxEXPAND);
	m_LeftPanelSizer->Add(m_RegisterPanel, 1, wxEXPAND);
	m_RightPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_RightPanelSizer->Add(m_MemoryInitPanel, 1, wxEXPAND);
	m_RightPanelSizer->Add(m_MemoryViewPanel, 2, wxEXPAND);

	m_MainSizer = new wxBoxSizer(wxHORIZONTAL);
	m_MainSizer->Add(m_LeftPanelSizer, 1, wxEXPAND|wxALL, 1);
	m_MainSizer->Add(m_EditBox, 1, wxEXPAND);
	m_MainSizer->Add(m_RightPanelSizer, 1, wxEXPAND|wxALL, 1);
	this->SetSizerAndFit(m_MainSizer);

	m_MemoryViewList = new wxListView(m_MemoryViewPanel, wxID_ANY, wxPoint(5, 90), wxSize(190, 300));
	m_MemoryViewList->AppendColumn("Address");
	m_MemoryViewList->AppendColumn("Data");

	Init();
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

void MainFrame::Init()
{
	Mnemonic::LoadInsctructionSet();
}

void MainFrame::OnRun(wxCommandEvent& event)
{
	
	if (m_currentFilePath.empty())
	{
		OnSaveAs(event);
		if (!m_currentFilePath.empty())
		{
			Run8085(ToString(m_currentFilePath));
			UpdateFlagRegister();
			UpdateRegisters();
			UpdateMemory();
		}
	}
	else
	{
		Run8085(ToString(m_currentFilePath));
		UpdateFlagRegister();
		UpdateRegisters();
		UpdateMemory();
	}
}

void MainFrame::OnSet(wxCommandEvent& envet)
{
	MemoryManager::SetMemory(ToString(m_MemoryAddressTextCtrl->GetValue()), ToString(m_DataTextCtrl->GetValue()));
	m_MemoryAddressTextCtrl->Clear();
	m_DataTextCtrl->Clear();
	m_MemoryAddressTextCtrl->AppendText("0000");
	m_DataTextCtrl->AppendText("00");
}

void MainFrame::OnView(wxCommandEvent& envet)
{
	m_MemoryViewList->ClearAll();
	m_MemoryViewList->AppendColumn("Address");
	m_MemoryViewList->AppendColumn("Data");
	
	int from = Converter::HexToDec(ToString(m_FromMemoryAddressTextCtrl->GetValue()));
	int cnt = std::stoi(ToString(m_CountTextCtrl->GetValue()));

	for (int i = 0; i < cnt; ++i)
	{
		std::string address = Converter::DecToHex(from + i, 16);
		std::string data = Converter::DecToHex(MemoryManager::Memory[from + i]);
		m_MemoryViewList->InsertItem(i, ToWxString(address));
		m_MemoryViewList->SetItem(i, 1, ToWxString(data));
	}
	m_MemoryViewList->Refresh();
}

void MainFrame::UpdateFlagRegister()
{
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


void MainFrame::UpdateMemory()
{
	m_MemoryViewList->ClearAll();
	m_MemoryViewList->AppendColumn("Address");
	m_MemoryViewList->AppendColumn("Data");

	int from = Converter::HexToDec(ToString(m_FromMemoryAddressTextCtrl->GetValue()));
	int cnt = std::stoi(ToString(m_CountTextCtrl->GetValue()));

	for (int i = 0; i < cnt; ++i)
	{
		std::string address = Converter::DecToHex(from + i, 16);
		std::string data = Converter::DecToHex(MemoryManager::Memory[from + i]);
		m_MemoryViewList->InsertItem(i, ToWxString(address));
		m_MemoryViewList->SetItem(i, 1, ToWxString(data));
	}
	m_MemoryViewList->Refresh();
}