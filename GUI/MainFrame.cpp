#include "MainFrame.h"
#include <wx/wx.h>
#include <Windows.h>
using namespace std;
 wxPanel* panel;
 wxPanel* bankpanel;
 wxPanel* atmPanel;

 wxFont buttonFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD); 

 bool IsFlashDriveInserted(){
     DWORD driveMask = GetLogicalDrives();
     for (char driveLetter = 'A'; driveLetter <= 'Z'; ++driveLetter) {
         if (driveMask & (1 << (driveLetter - 'A'))) {
             string drivePath = string(1, driveLetter) + ":\\";
             UINT driveType = GetDriveTypeA(drivePath.c_str());

             if (driveType == DRIVE_REMOVABLE) {
                 return true;
             }
         }
     }
     return false;
 }


// STARTMENU
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

    if (!IsFlashDriveInserted()) {
        wxLogError("No flash drive detected. Please insert a flash drive to continue.");
        return;
    }


    panel = new wxPanel(this);
    panel->SetBackgroundColour(*wxLIGHT_GREY);  
 
    // Interact with the Bank button
    wxPanel* IBbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
    IBbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* IBbutton = new wxButton(IBbuttonPanel, wxID_ANY, "Interact with the Bank", wxPoint(2, 2), wxSize(500, 90));
    IBbutton->SetFont(buttonFont);
    IBbutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton1Clicked, this); 

    // Interact with ATM Machine button 
    wxPanel* IMbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 418), wxSize(504, 94));
    IMbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* IMbutton = new wxButton(IMbuttonPanel, wxID_ANY, "Interact with ATM Machine", wxPoint(2, 2), wxSize(500, 90));
    IMbutton->SetFont(buttonFont); 
    IMbutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton2Clicked, this);

    // Exit Program button
    wxPanel* EbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 518), wxSize(504, 94));
    EbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* Ebutton = new wxButton(EbuttonPanel, wxID_ANY, "Exit Program", wxPoint(2, 2), wxSize(500, 90));
    Ebutton->SetBackgroundColour(*wxWHITE);
    Ebutton->SetForegroundColour(*wxBLACK);
    Ebutton->SetFont(buttonFont); 
    Ebutton->Bind(wxEVT_ENTER_WINDOW, [Ebutton](wxMouseEvent&) {
        Ebutton->SetForegroundColour(*wxRED);
        Ebutton->Refresh();
        });
    Ebutton->Bind(wxEVT_LEAVE_WINDOW, [Ebutton](wxMouseEvent&) {
        Ebutton->SetForegroundColour(*wxBLACK);
        Ebutton->Refresh();
        });
    Ebutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton3Clicked, this); 
}
    // BANK MENU
void MainFrame::OnButton1Clicked(wxCommandEvent& evt) {
    panel->Hide();
    bankpanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    bankpanel->SetBackgroundColour(*wxWHITE);
   
    // Enroll for a Bank Account button
    wxPanel* enrollPanel = new wxPanel(bankpanel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
    enrollPanel->SetBackgroundColour(*wxBLACK); 
    wxButton* enrollButton = new wxButton(enrollPanel, wxID_ANY, "Enroll for a Bank Account", wxPoint(2, 2), wxSize(500, 90));
    enrollButton->SetFont(buttonFont);
    enrollButton->Bind(wxEVT_BUTTON, &MainFrame::OnEnrollButtonClicked, this);
 

    // Deposit Money button
    wxPanel* depositPanel = new wxPanel(bankpanel, wxID_ANY, wxPoint(378, 418), wxSize(504, 94));
    depositPanel->SetBackgroundColour(*wxBLACK);
    wxButton* depositButton = new wxButton(depositPanel, wxID_ANY, "Deposit Money", wxPoint(2, 2), wxSize(500, 90));
    depositButton->SetFont(buttonFont);
    depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositButtonClicked, this);

    // Return to Main Menu button
    wxPanel* returnPanel = new wxPanel(bankpanel, wxID_ANY, wxPoint(378, 518), wxSize(504, 94));
    returnPanel->SetBackgroundColour(*wxBLACK);
    wxButton* returnButton = new wxButton(returnPanel, wxID_ANY, "3. Return back to the main menu", wxPoint(2, 2), wxSize(500, 90));
    returnButton->SetFont(buttonFont);
    returnButton->Bind(wxEVT_BUTTON, &MainFrame::OnReturnButtonClicked, this); 
}

void MainFrame::OnEnrollButtonClicked(wxCommandEvent& evt) {

}

void MainFrame::OnDepositButtonClicked(wxCommandEvent& evt) {

}

void MainFrame::OnReturnButtonClicked(wxCommandEvent& evt) {
    bankpanel->Hide();
    panel->Show();
}

//ATM MENU
void MainFrame::OnButton2Clicked(wxCommandEvent& evt) {
    panel->Hide();
    atmPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    atmPanel->SetBackgroundColour(*wxWHITE);

    // Display Balance Button
    wxPanel* balancePanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 18), wxSize(504, 94));
    balancePanel->SetBackgroundColour(*wxBLACK);
    wxButton* balanceButton = new wxButton(balancePanel, wxID_ANY, "Display Balance", wxPoint(2, 2), wxSize(500, 90));
    balanceButton->SetFont(buttonFont);
    balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnDisplayBalanceClicked, this);

    // Withdraw Button
    wxPanel* withdrawPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 118), wxSize(504, 94));
    withdrawPanel->SetBackgroundColour(*wxBLACK);
    wxButton* withdrawButton = new wxButton(withdrawPanel, wxID_ANY, "Withdraw", wxPoint(2, 2), wxSize(500, 90));
    withdrawButton->SetFont(buttonFont);
    withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithdrawClicked, this);

    // Deposit Button
    wxPanel* depositPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 218), wxSize(504, 94));
    depositPanel->SetBackgroundColour(*wxBLACK);
    wxButton* depositButton = new wxButton(depositPanel, wxID_ANY, "Deposit", wxPoint(2, 2), wxSize(500, 90));
    depositButton->SetFont(buttonFont);
    depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositClicked, this);

    // Fund Transfer Button
    wxPanel* transferPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
    transferPanel->SetBackgroundColour(*wxBLACK);
    wxButton* transferButton = new wxButton(transferPanel, wxID_ANY, "Fund Transfer", wxPoint(2, 2), wxSize(500, 90));
    transferButton->SetFont(buttonFont);
    transferButton->Bind(wxEVT_BUTTON, &MainFrame::OnTransferClicked, this);

    // Change PIN Button
    wxPanel* pinPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 418), wxSize(504, 94));
    pinPanel->SetBackgroundColour(*wxBLACK);
    wxButton* pinButton = new wxButton(pinPanel, wxID_ANY, "Change PIN", wxPoint(2, 2), wxSize(500, 90));
    pinButton->SetFont(buttonFont);
    pinButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangePinClicked, this);

    // Exit and Save Button
    wxPanel* exitPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 518), wxSize(504, 94));
    exitPanel->SetBackgroundColour(*wxBLACK);
    wxButton* exitButton = new wxButton(exitPanel, wxID_ANY, "Exit and Save", wxPoint(2, 2), wxSize(500, 90));
    exitButton->SetFont(buttonFont);
    exitButton->Bind(wxEVT_BUTTON, &MainFrame::OnExitATMClicked, this);
}   
 
void MainFrame::OnDisplayBalanceClicked(wxCommandEvent& evt) {
    
}
void MainFrame::OnWithdrawClicked(wxCommandEvent& evt) {
   
}

void MainFrame::OnDepositClicked(wxCommandEvent& evt) {
  
}

void MainFrame::OnTransferClicked(wxCommandEvent& evt) {
    
}

void MainFrame::OnChangePinClicked(wxCommandEvent& evt) {
   
}

void MainFrame::OnExitATMClicked(wxCommandEvent& evt) {
    wxLogMessage("Data Saved. System is Closing");
    Close(true); 
}


void MainFrame::OnButton3Clicked(wxCommandEvent& evt) {
    wxLogMessage("System Closing");
    Close(true); 
}
