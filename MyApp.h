//
// Created by zhuoq on 2021/4/20.
//

#ifndef WX2048_MYAPP_H
#define WX2048_MYAPP_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


class MyApp: public wxApp {
protected:
    virtual bool OnInit();
};


#endif //WX2048_MYAPP_H
