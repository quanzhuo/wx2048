//
// Created by zhuoq on 2021/4/20.
//

#ifndef WX2048_MYFRAME_H
#define WX2048_MYFRAME_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "ScorePad.h"

class MyFrame:public wxFrame {
public:
    MyFrame(const wxString &title);
private:
    void OnKeyUp(wxKeyEvent &event);
    std::vector<ScorePad*> sps;
};

#endif //WX2048_MYFRAME_H
