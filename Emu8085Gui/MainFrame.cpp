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
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_HELP, MainFrame::OnHelp)
EVT_MENU(ID_LOAD, MainFrame::OnLoadProgram)
EVT_BUTTON(ButtonID::SET_BUTTON, MainFrame::OnSet)
EVT_BUTTON(ButtonID::VIEW_BUTTON, MainFrame::OnView)
EVT_BUTTON(ButtonID::DEBUG_BUTTON, MainFrame::OnDebug)
EVT_BUTTON(ButtonID::EXECUTE_BUTTON, MainFrame::OnExecute)
EVT_BUTTON(ButtonID::STOP_BUTTON, MainFrame::OnStopDebug)
EVT_BUTTON(ButtonID::SET_LOADING_LOCATION_BUTTON, MainFrame::OnSetLoadingLocation)
END_EVENT_TABLE()

MainFrame::MainFrame() :wxFrame(nullptr, wxID_ANY, "8085 Simulator", wxPoint(30, 30), wxSize(800, 800))
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
	m_HelpMenu->Append(wxID_HELP, _("Help"));
	m_HelpMenu->Append(wxID_ABOUT, _("About"));


	m_MenuBar->Append(m_FileMenu, _("&File"));
	m_MenuBar->Append(m_HelpMenu, _("&More"));

	this->SetMenuBar(m_MenuBar);

	//ToolBar
	m_ToolBar = this->CreateToolBar();
	m_ToolBar->AddTool(wxID_OPEN, _("Open"), wxArtProvider::GetBitmap("wxART_FILE_OPEN", wxART_OTHER, wxSize(16, 16)), _("Open"));
	m_ToolBar->AddTool(wxID_SAVE, _("Save"), wxArtProvider::GetBitmap("wxART_FLOPPY", wxART_OTHER, wxSize(16, 16)), _("Save"));
	m_ToolBar->AddTool(ID_LOAD, _("Load"), wxArtProvider::GetBitmap("wxART_FILE_SAVE", wxART_OTHER, wxSize(16, 16)), _("Load Program"));
	m_ToolBar->AddTool(wxID_EXECUTE, _("Execute"), wxArtProvider::GetBitmap("wxART_GO_FORWARD", wxART_OTHER, wxSize(16, 16)), _("Load + Run"));
	m_ToolBar->Realize();


	//EditBox
	m_TextBoxPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_TextBoxStaticBox = new wxStaticBox(m_TextBoxPanel, wxID_ANY, "");
	m_TextBoxStaticBoxSizer = new wxStaticBoxSizer(m_TextBoxStaticBox, wxHORIZONTAL);
	m_EditBox = new wxStyledTextCtrl(m_TextBoxStaticBox, wxID_ANY, wxPoint(0, 20), wxSize(200, 800));
	m_EditBox->SetMarginType(1, wxSTC_MARGIN_NUMBER);
	m_EditBox->SetMarginWidth(1, 80);
	m_EditBox->SetLexer(wxSTC_LEX_ASM);
	m_EditBox->StyleSetForeground(wxSTC_H_TAGUNKNOWN, wxColour(0, 150, 0));
	m_EditBox->SetUseHorizontalScrollBar(false);
	m_EditBox->SetUseVerticalScrollBar(true);
	m_TextBoxStaticBoxSizer->Add(m_EditBox, wxEXPAND);
	m_TextBoxPanel->SetSizer(m_TextBoxStaticBoxSizer);

	//Program Loading Panel
	m_ProgramLoadingPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_ProgramLoadingPanelStaticBox = new wxStaticBox(m_ProgramLoadingPanel, wxID_ANY, PANEL::PROGRAM_LOADER);
	m_ProgramLoadingPanelStaticBoxSizer = new wxStaticBoxSizer(m_ProgramLoadingPanelStaticBox, wxVERTICAL);
	m_ProgramLoadingPanelLabel = new wxStaticText(m_ProgramLoadingPanelStaticBox, wxID_ANY, "[Load Program From Location(HEX)]", wxPoint(5, 30));
	m_ProgramLoadingPanelTextCtrl = new wxTextCtrl(m_ProgramLoadingPanelStaticBox, wxID_ANY, "0000", wxPoint(20, 55), wxSize(50, 20));
	m_ProgramLoadingPanelTextCtrl->SetMaxLength(4);
	m_ProgramLoadingPanelSetButton = new wxButton(m_ProgramLoadingPanelStaticBox, ButtonID::SET_LOADING_LOCATION_BUTTON, BUTTON::SET, wxPoint(100, 54), wxSize(60, 22));
	m_ProgramLoadingPanelCurrentLocationTextLabel = new wxStaticText(m_ProgramLoadingPanelStaticBox, wxID_ANY, "[Current Loading Location(HEX)]", wxPoint(10, 120));
	m_ProgramLoadingPanelCurrentLocationTextCtrl = new wxTextCtrl(m_ProgramLoadingPanelStaticBox, wxID_ANY, "0000", wxPoint(70, 140), wxSize(45, 20), wxTE_READONLY);
	m_ProgramLoadingPanelCurrentLocationTextCtrl->SetMaxLength(4);
	m_ProgramLoadingPanel->SetSizer(m_ProgramLoadingPanelStaticBoxSizer);


	//FlagPanel
	m_FlagPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_FlagPanelStaticBox = new wxStaticBox(m_FlagPanel, wxID_ANY, PANEL::FLAG_REGISTER);
	m_FlagPanelStaticBoxSizer = new wxStaticBoxSizer(m_FlagPanelStaticBox, wxVERTICAL);
	m_FlagRegCheckList = new wxCheckListBox(m_FlagPanelStaticBox, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxArrayString(5, m_FlagRegisterArray), 1, wxDefaultValidator);
	m_FlagPanelStaticBoxSizer->Add(m_FlagRegCheckList);
	m_FlagPanel->SetSizer(m_FlagPanelStaticBoxSizer);

	//Register Panel
	m_RegisterPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_RegisterPanelStaticBox = new wxStaticBox(m_RegisterPanel, wxID_ANY, PANEL::REGISTER);
	m_RegisterPanelStaticBoxSizer = new wxStaticBoxSizer(m_RegisterPanelStaticBox, wxVERTICAL);

	for (int i = 0; i < 7; ++i)
	{
		std::string label = m_MainRegisterArray[i] + std::string(" :");
		m_MainRegisterLabel[m_MainRegisterArray[i]] = new wxStaticText(m_RegisterPanelStaticBox, wxID_ANY, label, wxPoint(10, 22 + i * 25), wxSize(20, 20));
		m_MainRegister[m_MainRegisterArray[i]] = new wxTextCtrl(m_RegisterPanelStaticBox, wxID_ANY, "00", wxPoint(30, 20 + i * 25), wxSize(25, 20), wxTE_READONLY);
		m_MainRegister[m_MainRegisterArray[i]]->SetMaxLength(2);
	}
	//Program counter
	m_PC_StaticText = new wxStaticText(m_RegisterPanelStaticBox, wxID_ANY, REGISTER::PC + " :", wxPoint(90, 22), wxSize(30, 20));
	m_PC_TextCtrl = new wxTextCtrl(m_RegisterPanelStaticBox, wxID_ANY, "0000", wxPoint(115, 20), wxSize(50, 20), wxTE_READONLY);
	m_PC_TextCtrl->SetMaxLength(4);
	//Stack Pointer
	m_SP_StaticText = new wxStaticText(m_RegisterPanelStaticBox, wxID_ANY, REGISTER::SP + " :", wxPoint(90, 47), wxSize(30, 20));
	m_SP_TextCtrl = new wxTextCtrl(m_RegisterPanelStaticBox, wxID_ANY, "FFFF", wxPoint(115, 45), wxSize(50, 20), wxTE_READONLY);
	m_SP_TextCtrl->SetMaxLength(4);
	//Program Status Word
	m_PSW_StaticText = new wxStaticText(m_RegisterPanelStaticBox, wxID_ANY, REGISTER::PSW + " :", wxPoint(80, 72), wxSize(30, 20));
	m_PSW_TextCtrl = new wxTextCtrl(m_RegisterPanelStaticBox, wxID_ANY, "0000", wxPoint(115, 70), wxSize(50, 20), wxTE_READONLY);
	m_PSW_TextCtrl->SetMaxLength(4);
	m_RegisterPanel->SetSizer(m_RegisterPanelStaticBoxSizer);

	//Memory Init Panel
	m_MemoryInitPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_MemoryInitPanelStaticBox = new wxStaticBox(m_MemoryInitPanel, wxID_ANY, PANEL::MEMORY_INITIALIZER);
	m_MemoryInitPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryInitPanelStaticBox, wxVERTICAL);
	m_MemoryLocationLabel = new wxStaticText(m_MemoryInitPanelStaticBox, wxID_ANY, "Address(HEX) :", wxPoint(5, 30));
	m_MemoryAddressTextCtrl = new wxTextCtrl(m_MemoryInitPanelStaticBox, wxID_ANY, "0000", wxPoint(88, 30), wxSize(50, 20));
	m_MemoryAddressTextCtrl->SetMaxLength(4);
	m_DataLabel = new wxStaticText(m_MemoryInitPanelStaticBox, wxID_ANY, "Data(HEX) :", wxPoint(150, 30));
	m_DataTextCtrl = new wxTextCtrl(m_MemoryInitPanelStaticBox, wxID_ANY, "00", wxPoint(215, 30), wxSize(25, 20));
	m_DataTextCtrl->SetMaxLength(2);
	m_SetButton = new wxButton(m_MemoryInitPanelStaticBox, ButtonID::SET_BUTTON, BUTTON::SET, wxPoint(115, 60));
	m_MemoryInitPanel->SetSizer(m_MemoryInitPanelStaticBoxSizer);

	//Memory View Panel
	m_MemoryViewPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_MemoryViewPanelStaticBox = new wxStaticBox(m_MemoryViewPanel, wxID_ANY, PANEL::MEMORY_VIEWER);
	m_MemoryViewPanelStaticBoxSizer = new wxStaticBoxSizer(m_MemoryViewPanelStaticBox, wxVERTICAL);
	m_FromLabel = new wxStaticText(m_MemoryViewPanelStaticBox, wxID_ANY, "From(HEX) :", wxPoint(5, 30));
	m_FromMemoryAddressTextCtrl = new wxTextCtrl(m_MemoryViewPanelStaticBox, wxID_ANY, "0000", wxPoint(73, 30), wxSize(38, 20));
	m_FromMemoryAddressTextCtrl->SetMaxLength(4);
	m_CountLabel = new wxStaticText(m_MemoryViewPanelStaticBox, wxID_ANY, "Count(DEC) :", wxPoint(148, 30));
	m_CountTextCtrl = new wxTextCtrl(m_MemoryViewPanelStaticBox, wxID_ANY, "000", wxPoint(220, 30), wxSize(30, 20));
	m_CountTextCtrl->SetMaxLength(3);
	m_ViewButton = new wxButton(m_MemoryViewPanelStaticBox, ButtonID::VIEW_BUTTON, BUTTON::VIEW, wxPoint(115, 60));
	m_MemoryViewList = new wxListView(m_MemoryViewPanelStaticBox, wxID_ANY, wxPoint(5, 90), wxSize(190, 315));
	m_MemoryViewList->AppendColumn("Address");
	m_MemoryViewList->AppendColumn("Data");
	m_MemoryViewPanel->SetSizer(m_MemoryViewPanelStaticBoxSizer);

	//Debug Panel
	m_DebugPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_DebugStaticBox = new wxStaticBox(m_DebugPanel, wxID_ANY, PANEL::DEBUGGER);
	m_DebugStaticBoxSizer = new wxStaticBoxSizer(m_DebugStaticBox, wxVERTICAL);
	m_CurrentLineLabel = new wxStaticText(m_DebugStaticBox, wxID_ANY, "Current Line Number : ", wxPoint(30, 35));
	m_CurrentLineTextCtrl = new wxTextCtrl(m_DebugStaticBox, wxID_ANY, "---", wxPoint(150, 30), wxSize(20, 20), wxTE_READONLY);
	m_ExecuteButton = new wxButton(m_DebugStaticBox, ButtonID::EXECUTE_BUTTON, BUTTON::EXECUTE, wxPoint(65, 55));
	m_DebugButton = new wxButton(m_DebugStaticBox, ButtonID::DEBUG_BUTTON, BUTTON::DEBUG, wxPoint(25, 100));
	m_StopButton = new wxButton(m_DebugStaticBox, ButtonID::STOP_BUTTON, BUTTON::STOP, wxPoint(105, 100));
	m_ExecuteButton->Disable();
	m_StopButton->Disable();
	m_DebugPanel->SetSizer(m_DebugStaticBoxSizer);


	//Sizers
	m_LeftPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_LeftPanelSizer->Add(m_ProgramLoadingPanel, 1, wxEXPAND);
	m_LeftPanelSizer->Add(m_FlagPanel, 3, wxEXPAND);
	m_LeftPanelSizer->Add(m_RegisterPanel, 3, wxEXPAND);
	m_RightPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_RightPanelSizer->Add(m_MemoryInitPanel, 1, wxEXPAND);
	m_RightPanelSizer->Add(m_MemoryViewPanel, 4, wxEXPAND);
	m_RightPanelSizer->Add(m_DebugPanel, 1, wxEXPAND);


	m_MainSizer = new wxBoxSizer(wxHORIZONTAL);
	m_MainSizer->Add(m_LeftPanelSizer, 1, wxEXPAND | wxALL, 1);
	m_MainSizer->Add(m_TextBoxPanel, 2, wxEXPAND | wxTOP | wxBOTTOM, 1);
	m_MainSizer->Add(m_RightPanelSizer, 2, wxEXPAND | wxALL, 1);

	this->SetSizerAndFit(m_MainSizer);

	Init();
}

MainFrame::~MainFrame()
{

}

void MainFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open text file"), "", "", "TEXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
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
	wxFileDialog saveFileDialog(this, _("Save text file"), "", "", "TEXT files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

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
	Mnemonic::LoadInstructionSet();
	ProgramManager::LoadProgramLoadingInstruction();
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
		m_EditBox->SaveFile(m_currentFilePath);
		Run8085(ToString(m_currentFilePath));
	}
}

void MainFrame::OnSet(wxCommandEvent& envet)
{
	if (m_MemoryAddressTextCtrl->IsEmpty() || m_DataTextCtrl->IsEmpty())
	{
		Error::Throw(ERROR_TYPE::EMPTY_FIELD);
		m_MemoryAddressTextCtrl->Clear();
		m_DataTextCtrl->Clear();
		m_MemoryAddressTextCtrl->AppendText("0000");
		m_DataTextCtrl->AppendText("00");
	}
	else if (MemoryManager::SetMemory(ToString(m_MemoryAddressTextCtrl->GetValue()), ToString(m_DataTextCtrl->GetValue())))//No need to report error as SetMemory will report if any.
	{
		m_MemoryAddressTextCtrl->Clear();
		m_DataTextCtrl->Clear();
		m_MemoryAddressTextCtrl->AppendText("0000");
		m_DataTextCtrl->AppendText("00");
		UpdateMemory();
	}
}

void MainFrame::OnView(wxCommandEvent& envet)
{
	UpdateMemory();
}


void MainFrame::OnSetLoadingLocation(wxCommandEvent& envet)
{
	if (m_ProgramLoadingPanelTextCtrl->IsEmpty())
	{
		Error::Throw(ERROR_TYPE::EMPTY_FIELD);
		m_ProgramLoadingPanelTextCtrl->AppendText("0000");
	}
	else
	{
		std::string address = ToString(m_ProgramLoadingPanelTextCtrl->GetValue());
		int nAddress = 0;
		bool OK = true;
		if (!Validator::IsValidHex(address))
		{
			OK = false;
		}
		else
		{
			nAddress = Converter::HexToDec(address);
			if (nAddress < 0x0000 && nAddress > 0xffff)
			{
				OK = false;
			}
		}

		if (OK)
		{
			m_nLoadingLocation = nAddress;
			Converter::ToUpperString(address);
			Utility::_16Bit(address);
			m_ProgramLoadingPanelCurrentLocationTextCtrl->Clear();
			m_ProgramLoadingPanelCurrentLocationTextCtrl->AppendText(address);
			m_ProgramLoadingPanelTextCtrl->Clear();
			m_ProgramLoadingPanelTextCtrl->AppendText("0000");
		}
		else
		{
			Error::Throw(ERROR_TYPE::INVALID_DATA);
		}
	}
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
	//Update main Register
	for (const std::string& reg : m_MainRegisterArray)
	{
		m_MainRegister[reg]->Clear();
		m_MainRegister[reg]->AppendText(ToWxString(Converter::DecToHex(Register::Main[reg])));
	}

	//Update Program counter
	m_PC_TextCtrl->Clear();
	m_PC_TextCtrl->AppendText(Converter::DecToHex(Register::PC, 16));

	//Update Stack Pointer
	m_SP_TextCtrl->Clear();
	m_SP_TextCtrl->AppendText(Converter::DecToHex(Register::SP, 16));

	//Update Program Status Word
	m_PSW_TextCtrl->Clear();
	m_PSW_TextCtrl->AppendText(Converter::DecToHex(Register::PSW(), 16));
}


void MainFrame::UpdateMemory()
{
	if (m_FromMemoryAddressTextCtrl->IsEmpty() || m_CountTextCtrl->IsEmpty())
	{
		m_FromMemoryAddressTextCtrl->Clear();
		m_CountTextCtrl->Clear();
		m_FromMemoryAddressTextCtrl->AppendText("0000");
		m_CountTextCtrl->AppendText("000");
	}

	const std::string sFrom = ToString(m_FromMemoryAddressTextCtrl->GetValue());
	const std::string sCount = ToString(m_CountTextCtrl->GetValue());
	if (Validator::IsValidHex(sFrom) && Validator::IsValidInt(sCount))
	{
		m_MemoryViewList->ClearAll();
		m_MemoryViewList->AppendColumn("Address");
		m_MemoryViewList->AppendColumn("Data");

		int nFrom = Converter::HexToDec(sFrom);
		int nCount = std::stoi(sCount);

		for (int i = 0; i < nCount && (nFrom + i) <= 0xffff; ++i)
		{
			std::string address = Converter::DecToHex(nFrom + i, 16);
			std::string data = Converter::DecToHex(MemoryManager::Memory[nFrom + i]);
			m_MemoryViewList->InsertItem(i, ToWxString(address));
			m_MemoryViewList->SetItem(i, 1, ToWxString(data));
		}
	}
	else
	{
		Error::Throw(ERROR_TYPE::INVALID_DATA);
	}
}

void MainFrame::Clear()
{
	//Clearing Registers(Frontend)
	for (const std::string& reg : m_MainRegisterArray)
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

	//Clearing Program Counter
	m_PC_TextCtrl->Clear();
	m_PC_TextCtrl->AppendText("0000");

	//Clearing Stack Pointer
	m_SP_TextCtrl->Clear();
	m_SP_TextCtrl->AppendText("FFFF");

	//Clearing Program Status Word
	m_PSW_TextCtrl->Clear();
	m_PSW_TextCtrl->AppendText("0000");

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
		m_EditBox->SaveFile(m_currentFilePath);
		Debug8085(ToString(m_currentFilePath));
	}
}

void MainFrame::Run8085(const std::string& filePath)
{
	Clear();//Clearing Frontend
	if (ProgramManager::LoadProgramInMemory(filePath, m_nLoadingLocation))//Read function in LoadProgramInMemory is responsible for clearing the backend
	{
		ProgramManager::Run();
		if (ProgramManager::HALT)
		{
			UpdateFlagRegister();
			UpdateRegisters();
			UpdateMemory();
			wxMessageBox(MESSAGE::SUCCESSFUL_EXECUTION, DIALOG::SUCCESS);
		}
		else
		{
			UpdateMemory();
		}
	}
}

void MainFrame::Debug8085(const std::string& filePath)
{
	Clear();//Clearing Front End
	if (ProgramManager::LoadProgramInMemory(filePath, m_nLoadingLocation))//Read function int LoadProgramInMemory is responsible for clearing the backend
	{
		UpdateMemory();
		UpdateRegisters();//Updating all register but we just need to update PC at this time
		m_ExecuteButton->Enable();
		m_DebugButton->Disable();
		m_StopButton->Enable();
		m_CurrentLineTextCtrl->Clear();
		m_CurrentLineTextCtrl->AppendText(ToWxString(std::to_string(ProgramManager::Program[Register::iPC].line_number)));
		m_EditBox->SetEditable(false);//Disabling Editor
		m_ToolBar->Disable();//Disabling the toolbar
		m_EditBox->MarkerAdd(ProgramManager::Program[Register::iPC].line_number - 1, 0);
		m_EditBox->MarkerSetBackground(0, *wxRED);
	}
}

void MainFrame::OnExecute(wxCommandEvent& event)
{
	const Instruction& instruction = ProgramManager::Program[Register::iPC];

	if (Mnemonic::Execute[instruction.mnemonic](instruction.operands))//Successful execution of a instruction
	{
		UpdateFlagRegister();
		UpdateRegisters();
		UpdateMemory();
		m_CurrentLineTextCtrl->Clear();
		m_CurrentLineTextCtrl->AppendText(ToWxString(std::to_string(ProgramManager::Program[Register::iPC].line_number)));
		m_EditBox->MarkerDeleteAll(0);
		m_EditBox->MarkerAdd(ProgramManager::Program[Register::iPC].line_number - 1, 0);
		m_EditBox->MarkerSetBackground(0, *wxRED);
	}
	else if (ProgramManager::HALT)//HLT get executed
	{
		UpdateRegisters();
		wxMessageBox(MESSAGE::SUCCESSFUL_EXECUTION, DIALOG::SUCCESS);
		OnStopDebug(event);
	}
	else//Error
	{
		OnStopDebug(event);
	}
}


void MainFrame::OnStopDebug(wxCommandEvent& event)
{
	m_ExecuteButton->Disable();
	m_StopButton->Disable();
	m_DebugButton->Enable();
	m_CurrentLineTextCtrl->Clear();
	m_CurrentLineTextCtrl->AppendText("---");
	m_ToolBar->Enable();
	m_EditBox->SetEditable(true);
	m_EditBox->MarkerDeleteAll(0);

}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxDialog aboutDialog(this, wxID_ANY, DIALOG::ABOUT);
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	wxHtmlWindow* html = new wxHtmlWindow(&aboutDialog, wxID_ANY, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
	html->SetBorders(1);
	html->LoadPage(PATH::ABOUT_HTML_FILE);
	html->SetSize(html->GetInternalRepresentation()->GetWidth(), html->GetInternalRepresentation()->GetHeight());
	dialogSizer->Add(html, 1, wxALL, 10);
	wxButton* OKButton = new wxButton(&aboutDialog, wxID_OK, _("OK"));
	OKButton->SetDefault();
	dialogSizer->Add(OKButton, 0, wxALIGN_CENTER | wxALL, 10);
	aboutDialog.SetSizer(dialogSizer);
	dialogSizer->Fit(&aboutDialog);
	aboutDialog.ShowModal();
}

void MainFrame::OnHelp(wxCommandEvent& event)
{
	wxDialog helpDialog(this, wxID_ANY, DIALOG::HELP);
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	wxHtmlWindow* html = new wxHtmlWindow(&helpDialog, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	html->SetBorders(1);
	html->LoadPage(PATH::HELP_HTML_FILE);
	html->SetSize(html->GetInternalRepresentation()->GetWidth(), html->GetInternalRepresentation()->GetHeight());
	dialogSizer->Add(html, 1, wxALL, 10);
	wxButton* OKButton = new wxButton(&helpDialog, wxID_OK, _("OK"));
	OKButton->SetDefault();
	dialogSizer->Add(OKButton, 0, wxALIGN_CENTER | wxALL, 10);
	helpDialog.SetSizer(dialogSizer);
	dialogSizer->Fit(&helpDialog);
	helpDialog.ShowModal();
}

void MainFrame::OnLoadProgram(wxCommandEvent& event)
{
	if (m_currentFilePath.empty())
	{
		OnSaveAs(event);
		if (!m_currentFilePath.empty())
		{
			LoadProgram(ToString(m_currentFilePath));
		}
	}
	else
	{
		m_EditBox->SaveFile(m_currentFilePath);
		LoadProgram(ToString(m_currentFilePath));
	}
}

void MainFrame::LoadProgram(const std::string& filePath)
{
	Clear();//Clearing Front End
	if (ProgramManager::LoadProgramInMemory(filePath, m_nLoadingLocation))//Read function in LoadProgramInMemory is responsible for clearing the backend
	{
		UpdateFlagRegister();
		UpdateRegisters();
		UpdateMemory();
		wxMessageBox(MESSAGE::SUCCESSFUL_PROGRAM_LOADING, DIALOG::SUCCESS);
	}
	else
	{
		UpdateMemory();
	}
}

