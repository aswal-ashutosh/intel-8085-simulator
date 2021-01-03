#include"MainFrame.h"
#include"8085.h"

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
EVT_BUTTON(ButtonID::DEBUG_BUTTON, MainFrame::OnDebug)
EVT_BUTTON(ButtonID::EXECUTE_BUTTON, MainFrame::OnExecute)
EVT_BUTTON(ButtonID::STOP_BUTTON, MainFrame::OnStopDebug)
END_EVENT_TABLE()

MainFrame::MainFrame() :wxFrame(nullptr, wxID_ANY, "8085 Simulator", wxPoint(30, 30), wxSize(600, 650))
{
	//StatusBar
	this->CreateStatusBar();

	//MenuBar
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

	//ToolBar
	m_ToolBar = this->CreateToolBar();
	m_ToolBar->AddTool(wxID_OPEN, _("Open"), wxArtProvider::GetBitmap("wxART_FILE_OPEN", wxART_OTHER, wxSize(16, 16)), _("Open"));
	m_ToolBar->AddTool(wxID_SAVE, _("Save"), wxArtProvider::GetBitmap("wxART_FILE_SAVE", wxART_OTHER, wxSize(16, 16)), _("Save"));
	m_ToolBar->AddTool(wxID_EXECUTE, _("Execute"), wxArtProvider::GetBitmap("wxART_GO_FORWARD", wxART_OTHER, wxSize(16, 16)), _("Run"));
	m_ToolBar->Realize();


	//EditBox
	m_TextBoxPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_TextBoxStaticBox = new wxStaticBox(m_TextBoxPanel, wxID_ANY, "");
	m_TextBoxStaticBoxSizer = new wxStaticBoxSizer(m_TextBoxStaticBox, wxHORIZONTAL);
	m_EditBox = new wxStyledTextCtrl(m_TextBoxStaticBox, wxID_ANY, wxPoint(0, 20), wxSize(200, 380));
	m_EditBox->SetMarginType(1, wxSTC_MARGIN_NUMBER);
	//m_EditBox->SetMarginMask(1, 0);
	m_EditBox->SetMarginWidth(1, 25);
	m_EditBox->SetLexer(wxSTC_LEX_ASM);
	m_EditBox->StyleSetForeground(wxSTC_H_TAGUNKNOWN, wxColour(0, 150, 0));
	m_EditBox->SetUseHorizontalScrollBar(false);
	m_EditBox->SetUseVerticalScrollBar(true);
	m_TextBoxStaticBoxSizer->Add(m_EditBox, wxEXPAND);
	m_TextBoxPanel->SetSizer(m_TextBoxStaticBoxSizer);
	
	//FlagPanel
	m_FlagPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_FlagPanelStaticBox = new wxStaticBox(m_FlagPanel, wxID_ANY, "FLAG REGISTER");
	m_FlagPanelStaticBoxSizer = new wxStaticBoxSizer(m_FlagPanelStaticBox, wxVERTICAL);
	m_FlagRegCheckList = new wxCheckListBox(m_FlagPanelStaticBox, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxArrayString(5, m_FlagRegisterArray), 1, wxDefaultValidator);
	m_FlagPanelStaticBoxSizer->Add(m_FlagRegCheckList);
	m_FlagPanel->SetSizer(m_FlagPanelStaticBoxSizer);

	//Register Panel
	m_RegisterPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_RegisterPanelStaticBox = new wxStaticBox(m_RegisterPanel, wxID_ANY, "REGISTERS");
	m_RegisterPanelStaticBoxSizer = new wxStaticBoxSizer(m_RegisterPanelStaticBox, wxVERTICAL);
	
	for (int i = 0; i < 7; ++i)
	{
		std::string label= m_MainRegisterArray[i] + std::string(" :");
		m_MainRegisterLabel[m_MainRegisterArray[i]] = new wxStaticText(m_RegisterPanelStaticBox, wxID_ANY, label, wxPoint(10, 22 + i * 25), wxSize(20, 20));
		m_MainRegister[m_MainRegisterArray[i]] = new wxTextCtrl(m_RegisterPanelStaticBox, wxID_ANY, "00", wxPoint(30, 20 + i * 25), wxSize(20, 20), wxTE_READONLY);
		m_MainRegister[m_MainRegisterArray[i]]->SetMaxLength(2);
	}
	m_RegisterPanel->SetSizer(m_RegisterPanelStaticBoxSizer);

	//Memory Init Panel
	m_MemoryInitPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_MemoryInitPanelStaticBox = new wxStaticBox(m_MemoryInitPanel, wxID_ANY, "MEMORY INITIALIZER");
	m_MemoryInitPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryInitPanelStaticBox, wxVERTICAL);
	m_MemoryLocationLabel = new wxStaticText(m_MemoryInitPanelStaticBox, wxID_ANY, "Address :", wxPoint(5, 30));
	m_MemoryAddressTextCtrl = new wxTextCtrl(m_MemoryInitPanelStaticBox, wxID_ANY, "0000", wxPoint(55, 30), wxSize(38, 20));
	m_MemoryAddressTextCtrl->SetMaxLength(4);
	m_DataLabel = new wxStaticText(m_MemoryInitPanelStaticBox, wxID_ANY, "Data :", wxPoint(110, 30));
	m_DataTextCtrl = new wxTextCtrl(m_MemoryInitPanelStaticBox, wxID_ANY, "00", wxPoint(145, 30), wxSize(20, 20));
	m_DataTextCtrl->SetMaxLength(2);
	m_SetButton = new wxButton(m_MemoryInitPanelStaticBox, ButtonID::SET_BUTTON, "Set", wxPoint(58, 60));
	m_MemoryInitPanel->SetSizer(m_MemoryInitPanelStaticBoxSizer);


	//Memory View Panel
	m_MemoryViewPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_MemoryViewPanelStaticBox = new wxStaticBox(m_MemoryViewPanel, wxID_ANY, "MEMORY VIEWER");
	m_MemoryViewPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryViewPanelStaticBox, wxVERTICAL);
	m_FromLabel = new wxStaticText(m_MemoryViewPanelStaticBox, wxID_ANY, "From :", wxPoint(5, 30));
	m_FromMemoryAddressTextCtrl = new wxTextCtrl(m_MemoryViewPanelStaticBox, wxID_ANY, "0000", wxPoint(40, 30), wxSize(38, 20));
	m_FromMemoryAddressTextCtrl->SetMaxLength(4);
	m_CountLabel = new wxStaticText(m_MemoryViewPanelStaticBox, wxID_ANY, "Count :", wxPoint(110, 30));
	m_CountTextCtrl = new wxTextCtrl(m_MemoryViewPanelStaticBox, wxID_ANY, "00", wxPoint(150, 30), wxSize(20, 20));
	m_CountTextCtrl->SetMaxLength(2);
	m_ViewButton = new wxButton(m_MemoryViewPanelStaticBox, ButtonID::VIEW_BUTTON, "View", wxPoint(58, 60));
	m_MemoryViewList = new wxListView(m_MemoryViewPanelStaticBox, wxID_ANY, wxPoint(5, 90), wxSize(190, 300));
	m_MemoryViewList->AppendColumn("Address");
	m_MemoryViewList->AppendColumn("Data");
	m_MemoryViewPanelStaticBoxSizer->Add(m_MemoryViewList, wxEXPAND);
	m_MemoryViewPanel->SetSizer(m_MemoryViewPanelStaticBoxSizer);

	//Debug Panel
	m_DebugPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_DebugStaticBox = new wxStaticBox(m_DebugPanel, wxID_ANY, "DEBUGGER");
	m_DebugStaticBoxSizer = new wxStaticBoxSizer(m_DebugStaticBox, wxVERTICAL);
	m_CurrentLineLabel = new wxStaticText(m_DebugStaticBox, wxID_ANY, "Current Line Number: ", wxPoint(10, 35));
	m_CurrentLineTextCtrl = new wxTextCtrl(m_DebugStaticBox, wxID_ANY, "---", wxPoint(130, 30), wxSize(20, 20), wxTE_READONLY);
	m_ExecuteButton = new wxButton(m_DebugStaticBox, ButtonID::EXECUTE_BUTTON, "Execute", wxPoint(50, 55));
	m_DebugButton = new wxButton(m_DebugStaticBox, ButtonID::DEBUG_BUTTON, "DEBUG", wxPoint(25, 100));
	m_StopButton = new wxButton(m_DebugStaticBox, ButtonID::STOP_BUTTON, "STOP", wxPoint(100, 100));
	m_ExecuteButton->Disable();
	m_StopButton->Disable();
	m_DebugPanel->SetSizer(m_DebugStaticBoxSizer);


	//Sizers
	m_LeftPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_LeftPanelSizer->Add(m_FlagPanel, 1, wxEXPAND);
	m_LeftPanelSizer->Add(m_RegisterPanel, 1, wxEXPAND);
	m_RightPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_RightPanelSizer->Add(m_MemoryInitPanel, 1, wxEXPAND);
	m_RightPanelSizer->Add(m_MemoryViewPanel, 2, wxEXPAND);
	m_MidSizer = new wxBoxSizer(wxVERTICAL);
	m_MidSizer->Add(m_TextBoxPanel, 2, wxEXPAND);
	m_MidSizer->Add(m_DebugPanel, 1, wxEXPAND);

	m_MainSizer = new wxBoxSizer(wxHORIZONTAL);
	m_MainSizer->Add(m_LeftPanelSizer, 1, wxEXPAND|wxALL, 1);
	m_MainSizer->Add(m_MidSizer, 2, wxEXPAND|wxTOP|wxBOTTOM, 1);
	m_MainSizer->Add(m_RightPanelSizer, 1, wxEXPAND|wxALL, 1);
	this->SetSizerAndFit(m_MainSizer);

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
	m_TextBoxStaticBox->SetLabel(openFileDialog.GetFilename());
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
	m_TextBoxStaticBox->SetLabel(saveFileDialog.GetFilename());
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
		}
	}
	else
	{
		Run8085(ToString(m_currentFilePath));
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
	for (const char& reg : m_MainRegisterArray)
	{
		m_MainRegister[reg]->Clear();
		m_MainRegister[reg]->AppendText(ToWxString(Converter::DecToHex(Register::Main[reg])));
	}
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

void MainFrame::Clear()
{
	//Clearing Registers(Frontend)
	for (const char& reg : m_MainRegisterArray)
	{
		m_MainRegister[reg]->Clear();
		m_MainRegister[reg]->AppendText("00");
	}
	
	//Clearing Flag Register(Frontend)
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("AC"), false);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("CY"), false);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("Z"), false);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("S"), false);
	m_FlagRegCheckList->Check(m_FlagRegCheckList->FindString("P"), false);

	//Clearing Backend
	Program::Loop.clear();
	Program::program.clear();
	Register::Clear();
}

void MainFrame::OnDebug(wxCommandEvent& event)
{
	if (m_currentFilePath.empty())
	{
		OnSaveAs(event);
		if (!m_currentFilePath.empty())
		{
			Debug8085(ToString(m_currentFilePath));
		}
	}
	else
	{
		Debug8085(ToString(m_currentFilePath));
	}
}

void MainFrame::Run8085(const std::string& filePath)
{
	Clear();//Clearing Front End + Back End
	Program::Read(filePath);
	Program::Run();
	UpdateFlagRegister();
	UpdateRegisters();
	UpdateMemory();
}

void MainFrame::Debug8085(const std::string& filePath)
{
	Clear();//Clearing Front End + Back End
	Program::Read(filePath);
	m_ExecuteButton->Enable();
	m_DebugButton->Disable();
	m_StopButton->Enable();
	m_CurrentLineTextCtrl->Clear();
	m_CurrentLineTextCtrl->AppendText(ToWxString(std::to_string(Register::PC + 1)));
}

void MainFrame::OnExecute(wxCommandEvent& event)
{
	const Instruction& instruction = Program::program[Register::PC];
	if (instruction.mnemonic == "HLT")
	{
		wxMessageBox("Program Executed Successfully.");
		m_ExecuteButton->Disable();
		m_StopButton->Disable();
		m_DebugButton->Enable();
		m_CurrentLineTextCtrl->Clear();
		m_CurrentLineTextCtrl->AppendText("---");
		return;
	}
	Mnemonic::Execute[instruction.mnemonic](instruction.operands);
	UpdateFlagRegister();
	UpdateRegisters();
	UpdateMemory();
	m_CurrentLineTextCtrl->Clear();
	m_CurrentLineTextCtrl->AppendText(ToWxString(std::to_string(Register::PC + 1)));
}


void MainFrame::OnStopDebug(wxCommandEvent& event)
{
	m_ExecuteButton->Disable();
	m_StopButton->Disable();
	m_DebugButton->Enable();
	m_CurrentLineTextCtrl->Clear();
	m_CurrentLineTextCtrl->AppendText("---");
}