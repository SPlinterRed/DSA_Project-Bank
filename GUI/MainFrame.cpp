#include "MainFrame.h"
#include <wx/wx.h>
 wxPanel* panel;
 wxPanel* bankpanel;
// STARTMENU
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    panel = new wxPanel(this);
    panel->SetBackgroundColour(*wxLIGHT_GREY);  

    wxFont buttonFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD); 
 
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

    wxFont buttonFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
   
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
void MainFrame::OnButton2Clicked(wxCommandEvent& evt) {
    
}

void MainFrame::OnButton3Clicked(wxCommandEvent& evt) {
    wxLogMessage("System Closing");
    Close(true); 
}
