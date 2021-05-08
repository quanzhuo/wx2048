//
// Created by zhuoq on 2021/4/20.
//

#include "MyFrame.h"
#include "ScorePad.h"
#include <random>
#include <set>

MyFrame::MyFrame(const wxString &title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxGridSizer *grid = new wxGridSizer(4, 4, 5, 5);
    for(int i=0; i<16; ++i)
    {
        ScorePad *score_pad = new ScorePad(panel);
        sps.push_back(score_pad);
        grid->Add(score_pad, wxSizerFlags(1).Expand());
    }

    for (auto iter=sps.begin(); iter != sps.end(); ++iter)
    {
        std::vector<const wxColor*> cls{wxRED, wxWHITE, wxBLACK, wxGREEN, wxBLUE, wxCYAN,wxYELLOW, wxLIGHT_GREY };
        std::vector<int> digits{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, 7);
        std::uniform_int_distribution<int> uniform_dist2(0, 10);

        int idx1 = uniform_dist(e1);
        int idx2 = uniform_dist2(e1);
        (*iter)->SetColor(*(cls[idx1]));
        (*iter)->SetDigit(digits[idx2]);
        (*iter)->Refresh();
    }

    wxSizer *top = new wxBoxSizer(wxVERTICAL);
    top->Add(grid, wxSizerFlags(1).Expand().Border(wxALL, 10));

    panel->SetSizer(top);
    top->SetSizeHints(this);

    Bind(wxEVT_KEY_UP, &MyFrame::OnKeyUp, this);
    Bind(wxEVT_ACTIVATE, [this](wxActivateEvent &event){SetFocus();});
}

void MyFrame::OnKeyUp(wxKeyEvent &event)
{
    std::set<int> valid_keys{WXK_UP, WXK_DOWN, WXK_LEFT, WXK_DOWN};
    if (valid_keys.find(event.GetKeyCode()) == valid_keys.end()) return;
    std::vector<const wxColor*> cls{wxRED, wxWHITE, wxBLACK, wxGREEN, wxBLUE, wxCYAN,wxYELLOW, wxLIGHT_GREY };
    std::vector<int> digits{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 7);
    std::uniform_int_distribution<int> uniform_dist2(0, 10);
    for (auto iter=sps.begin(); iter != sps.end(); ++iter)
    {
        int idx1 = uniform_dist(e1);
        int idx2 = uniform_dist2(e1);
        (*iter)->SetColor(*(cls[idx1]));
        (*iter)->SetDigit(digits[idx2]);
//            (*iter)->Refresh();
    }
    this->Refresh();
}
