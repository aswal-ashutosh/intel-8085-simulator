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
	wxBoxSizer* m_MainSizer = nullptr;
	wxBoxSizer* m_PanelSizer = nullptr;
	wxStyledTextCtrl* m_EditBox = nullptr;
	wxCheckListBox* m_FlagRegCheckList = nullptr;
	wxString m_currentFilePath;
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
	void UpdateFlagRegister();
	void UpdateRegisters();
	DECLARE_EVENT_TABLE();
};


