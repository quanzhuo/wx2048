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
#include <map>
#include <vector>

class MyFrame:public wxFrame {

public:
    MyFrame(const wxString &title);

private:
    void OnKeyUp(wxKeyEvent &event);
    void Init();
    void ReArrange(int dir);
    void MoveDigit(std::vector<int> &vi);
    void AddTheSame(std::vector<int> &vi);

    int n = 4; // default 4x4 keyboard
    std::map<int, std::vector<std::vector<int>>> indexs;
    std::vector<ScorePad*> pads;
};

#endif //WX2048_MYFRAME_H
