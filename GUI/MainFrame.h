#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	// START MENU BUTTONS
	void OnButton1Clicked(wxCommandEvent& evt);
	void OnButton2Clicked(wxCommandEvent& evt);
	void OnButton3Clicked(wxCommandEvent& evt);
	// BANK MAIN MENU BUTTONS
	void OnEnrollButtonClicked(wxCommandEvent& evt);
	void OnDepositButtonClicked(wxCommandEvent& evt);
	void OnReturnButtonClicked(wxCommandEvent& evt);
	// ATM MAIN MENU BUTTONS
	void OnDisplayBalanceClicked(wxCommandEvent& evt);
	void OnWithdrawClicked(wxCommandEvent& evt);
	void OnDepositClicked(wxCommandEvent& evt);
	void OnTransferClicked(wxCommandEvent& evt);
	void OnChangePinClicked(wxCommandEvent& evt);
	void OnExitATMClicked(wxCommandEvent& evt);
};
