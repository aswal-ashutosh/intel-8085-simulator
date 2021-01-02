#pragma once

#include<wx\wx.h>
#include<wx\artprov.h>
#include<wx/stc/stc.h>
#include<wx/listctrl.h>
#include<map>



class MainFrame : public wxFrame
{
private:
	wxMenuBar* m_MenuBar = nullptr;
	wxMenu* m_FileMenu = nullptr;
	wxMenu* m_HelpMenu = nullptr;
	wxToolBar* m_ToolBar = nullptr;
	wxPanel* m_FlagPanel = nullptr;
	wxPanel* m_RegisterPanel = nullptr;
	wxPanel* m_MemoryInitPanel = nullptr;
	wxPanel* m_MemoryViewPanel = nullptr;
	wxBoxSizer* m_MainSizer = nullptr;
	wxBoxSizer* m_LeftPanelSizer = nullptr;
	wxBoxSizer* m_RightPanelSizer = nullptr;
	wxStyledTextCtrl* m_EditBox = nullptr;
	wxCheckListBox* m_FlagRegCheckList = nullptr;
	wxString m_currentFilePath;
	wxStaticBox* m_RegisterPanelStaticBox = nullptr;
	wxStaticBoxSizer* m_RegisterPanelStaticBoxSizer = nullptr;
	wxStaticBox* m_FlagPanelStaticBox = nullptr;
	wxStaticBoxSizer* m_FlagPanelStaticBoxSizer = nullptr;
	wxStaticBox* m_MemoryInitPanelStaticBox = nullptr;
	wxStaticBoxSizer* m_MemoryInitPanelStaticBoxSizer = nullptr;
	wxStaticBox* m_MemoryViewPanelStaticBox = nullptr;
	wxStaticBoxSizer* m_MemoryViewPanelStaticBoxSizer = nullptr;

	wxStaticText* m_MemoryLocationLabel = nullptr;
	wxTextCtrl* m_MemoryAddressTextCtrl = nullptr;
	wxStaticText* m_DataLabel = nullptr;
	wxTextCtrl* m_DataTextCtrl = nullptr;

	wxStaticText* m_FromLabel = nullptr;
	wxTextCtrl* m_CountTextCtrl = nullptr;
	wxStaticText* m_CountLabel = nullptr;
	wxTextCtrl* m_FromMemoryAddressTextCtrl = nullptr;
	wxButton* m_ViewButton = nullptr;
	wxButton* m_SetButton = nullptr;

	wxListView* m_MemoryViewList = nullptr;

	std::map<char, wxTextCtrl*> m_MainRegister;
	std::map<char, wxStaticText*> m_MainRegisterLabel;
public:

	

	MainFrame();
	~MainFrame();

	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnRun(wxCommandEvent& envet);
	void OnSet(wxCommandEvent& envet);
	void OnView(wxCommandEvent& envet);
	void UpdateFlagRegister();
	void UpdateRegisters();
	void UpdateMemory();
	void Init();
	DECLARE_EVENT_TABLE();
};

enum ButtonID
{
	VIEW_BUTTON = 3333, 
	SET_BUTTON = 6666
};


