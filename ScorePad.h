//
// Created by H2404689 on 2021/5/5.
//

#ifndef WX2048_SCOREPAD_H
#define WX2048_SCOREPAD_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class ScorePad : public wxWindow
{
public:
    ScorePad(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &label="");
    ScorePad();
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &label="");
    virtual ~ScorePad();
    void SetDigit(const int digit) {m_digit = digit;};
    int GetDigit() const {return m_digit;};

protected:
    virtual wxSize DoGetBestSize() const;
    void OnPaint(wxPaintEvent &event);
    void render(wxDC &dc);

private:
    void Init();
    int m_digit = 0;
    std::vector<const wxColor*> colors{wxRED, wxGREEN, wxBLACK, wxBLUE, wxCYAN, wxYELLOW, wxLIGHT_GREY,};
};

#endif //WX2048_SCOREPAD_H
