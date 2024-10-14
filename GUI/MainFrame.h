#pragma once
#include <wx/wx.h>

class MainFrame	: public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnButton1Clicked(wxCommandEvent& evt);
	void OnButton2Clicked(wxCommandEvent& evt);
	void OnButton3Clicked(wxCommandEvent& evt);
	void OnEnrollButtonClicked(wxCommandEvent& evt);
	void OnDepositButtonClicked(wxCommandEvent& evt);
	void OnReturnButtonClicked(wxCommandEvent& evt);
};

