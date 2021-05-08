//
// Created by zhuoq on 2021/4/20.
//


#include "MyApp.h"
#include "MyFrame.h"

bool MyApp::OnInit() {
    wxFrame *frame = new MyFrame("MyFrame");
    frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);