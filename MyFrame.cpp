//
// Created by zhuoq on 2021/4/20.
//

#include "MyFrame.h"
#include <random>
#include <set>
#include <algorithm>
#include <vector>

MyFrame::MyFrame(const wxString &title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxGridSizer *grid = new wxGridSizer(n, n, 5, 5);
    for(int i=0; i<n*n; ++i)
    {
        ScorePad *pad = new ScorePad(panel);
        pads.push_back(pad);
        grid->Add(pad, wxSizerFlags(1).Expand());
        pad->Bind(wxEVT_KEY_UP, &MyFrame::OnKeyUp, this);
    }

    wxSizer *top = new wxBoxSizer(wxVERTICAL);
    top->Add(grid, wxSizerFlags(1).Expand().Border(wxALL, 10));

    panel->SetSizer(top);
    top->SetSizeHints(this);

    Init();

    // Bind(wxEVT_KEY_UP, &MyFrame::OnKeyUp, this);
    // Bind(wxEVT_ACTIVATE, [this](wxActivateEvent &event){SetFocus();});
}

void MyFrame::OnKeyUp(wxKeyEvent &event)
{
    std::set<int> valid_keys{WXK_UP, WXK_DOWN, WXK_LEFT, WXK_RIGHT};
    if (valid_keys.find(event.GetKeyCode()) == valid_keys.end()) return;

    std::vector<int> before;
    std::for_each(pads.begin(), pads.end(), [&before](ScorePad *sp){before.push_back(sp->GetDigit());});

    ReArrange(event.GetKeyCode());

    bool changed = false;
    for(int i=0; i<n*n; ++i)
    {
        if (pads[i]->GetDigit() != before[i])
        {
            changed = true;
            pads[i]->Refresh();
        }
    }

    if (!changed)
        return;

    // create a random one
    std::vector<int> empty_idx;
    for (int i=0; i < n*n; ++i)
    {
        if (!pads[i]->GetDigit())
        {
            empty_idx.push_back(i);
        }
    }

    if (empty_idx.empty())
    {
        wxMessageBox("Failed");
    }
    else if (empty_idx.size() == 1)
    {
        pads[empty_idx.front()]->SetDigit(2);
        pads[empty_idx.front()]->Refresh();
    }
    else if (empty_idx.size() > 1)
    {
        std::default_random_engine e(time(0));
        std::uniform_int_distribution<unsigned> u(0, empty_idx.size()-1);
        int idx = u(e);
        pads[empty_idx[idx]]->SetDigit(2);
        pads[empty_idx[idx]]->Refresh();
    }
}

void MyFrame::Init()
{
    // Up
    std::vector<std::vector<int>> vvi_up;
    for(int col=0; col<n; ++col)
    {
        std::vector<int> vi;
        for(int row=0; row<n; ++row)
        {
            vi.push_back(col + row * n);
        }
        vvi_up.push_back(vi);
    }
    indexs[WXK_UP] = vvi_up;

    //Down
    std::vector<std::vector<int>> vvi_down;
    for (auto iter=vvi_up.begin(); iter != vvi_up.end(); ++iter)
    {
        std::vector<int> vi(n);
        std::reverse_copy(iter->begin(), iter->end(), vi.begin());
        vvi_down.push_back(vi);
    }
    indexs[WXK_DOWN] = vvi_down;

    // Left
    std::vector<std::vector<int>> vvi_left;
    for(int row=0; row<n; ++row)
    {
        std::vector<int> vi;
        for(int col=0; col<n; ++col)
        {
            vi.push_back(row * n + col);
        }
        vvi_left.push_back(vi);
    }
    indexs[WXK_LEFT] = vvi_left;

    // Right
    std::vector<std::vector<int>> vvi_right;
    for(auto iter=vvi_left.begin(); iter != vvi_left.end(); ++iter)
    {
        std::vector<int> vi(n);
        std::reverse_copy(iter->begin(), iter->end(), vi.begin());
        vvi_right.push_back(vi);
    }
    indexs[WXK_RIGHT] = vvi_right;

    std::default_random_engine e(time(0));
    std::uniform_int_distribution<int> u(0, n*n-1);
    int i1 = u(e);
    while (true)
    {
        int i2 = u(e);
        if (i1 != i2)
        {
            pads[i1]->SetDigit(2);
            pads[i1]->Refresh();
            pads[i2]->SetDigit(2);
            pads[i2]->Refresh();
            break;
        }
    }
}

void MyFrame::ReArrange(int dir) {
    auto & vvi = indexs[dir];
    for(auto iter = vvi.begin(); iter != vvi.end(); ++iter)
    {
        MoveDigit(*iter);
        AddTheSame(*iter);
        MoveDigit(*iter);
    }
}

void MyFrame::MoveDigit(std::vector<int> &vi) {
    while (true)
    {
        auto first_zero = std::find_if(vi.begin(), vi.end(), [this](int v){ return !pads[v]->GetDigit();});
        auto first_non_zero = std::find_if(first_zero, vi.end(), [this](int v){return pads[v]->GetDigit();});
        if (first_zero == vi.end() || first_non_zero == vi.end()) return;
        std::vector<int> temp;
        // copy first_non_zero...end to temp
        std::for_each(first_non_zero, vi.end(), [&temp, this](int v){temp.push_back(pads[v]->GetDigit());});
        // copy temp to first_zero
        decltype(first_zero) fz_copy(first_zero);
        std::for_each(temp.begin(), temp.end(), [this, &fz_copy](int v){pads[*fz_copy++]->SetDigit(v);});
        int zero_count = first_non_zero - first_zero;
        // set the remained pad to zero
        std::for_each(vi.rbegin(), vi.rbegin() + zero_count, [this](int v){pads[v]->SetDigit(0);});
    }
}

void MyFrame::AddTheSame(std::vector<int> &vi) {
    for(auto it1 = vi.begin(), it2 = it1+1; it2 != vi.end(); ++it1, ++it2)
    {
        if ((pads[*it1]->GetDigit() == pads[*it2]->GetDigit()) &&
                (pads[*it1]->GetDigit() != 0))
        {
            pads[*it1]->SetDigit(pads[*it1]->GetDigit()*2);
            pads[*it2]->SetDigit(0);
        }
    }
}
