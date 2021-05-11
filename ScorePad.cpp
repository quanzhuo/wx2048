//
// Created by H2404689 on 2021/5/5.
//

#include "ScorePad.h"

ScorePad::ScorePad(wxWindow *parent, wxWindowID id, const wxString &label):wxWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    Init();
    Create(parent, id, label);
}

ScorePad::ScorePad()
{
    Init();
}

bool ScorePad::Create(wxWindow *parent, wxWindowID id, const wxString &label)
{
    return true;
}

wxSize ScorePad::DoGetBestSize() const
{
    // we need to calculate and return the best size of the widget...
    return wxSize(120, 120);
}

void ScorePad::OnPaint(wxPaintEvent &event)
{
    // draw the widget on a wxDC...
    wxPaintDC dc(this);
    render(dc);
}

void ScorePad::Init()
{
    Bind(wxEVT_PAINT, &ScorePad::OnPaint, this);
    Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent &event){ GetParent()->GetParent()->SetFocus();});
}

ScorePad::~ScorePad()
{

}

void ScorePad::render(wxDC &dc)
{
    wxColor bk_color;

    if (m_digit == 0)
    {
        bk_color = *wxWHITE;
    }
    else
    {
        auto f_get_power = [](int x){
            int ret = 0;
            while(x >= 2)
            {
                x /= 2;
                ++ret;
            }
            return ret;
        };
        int power = f_get_power(m_digit);
        bk_color = *colors[(power-1)%7];
    }

    dc.SetBrush(bk_color);
    dc.SetPen(*wxTRANSPARENT_PEN);
    wxSize size = GetSize();
    dc.DrawRoundedRectangle(0, 0, size.GetWidth(), size.GetHeight(), 5);

    //设置字体
    wxFont font(28,  wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    dc.SetFont(font);

    // 设置文字颜色
    dc.SetTextForeground(*wxWHITE);
    if (m_digit)
    {
        wxString text = wxString::Format("%d", m_digit);
        dc.DrawLabel(text, wxRect(0,0, size.GetWidth(), size.GetHeight()), wxALIGN_CENTER);
    }
}
