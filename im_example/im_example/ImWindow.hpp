//
//  ImWindow.hpp
//  im_example
//
//  Created by moto2 yang on 2017/2/2.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#ifndef ImWindow_hpp
#define ImWindow_hpp

#include <string>
#include <functional>
#include "imgui.h"

class ImWindow;


using Layout = std::function<void(ImWindow*)>;

class ImWindow
{
public:
    std::string m_title;
    ImVec2 m_pos;
    ImVec2 m_size;
    bool m_show;
    Layout m_l;
    
public:
    
    ImWindow(const std::string& title, const ImVec2& pos, const ImVec2& size, Layout l)
    : m_show(true), m_title(title)
    {
        m_l = l;
    }
        
    bool run()
    {
        if (m_show) {
            m_l(this);
        }
        
        return true;
    }
    void show() { m_show = true; }
    void hide() { m_show = false; }
    bool isShow() { return m_show; }
    
};
#endif /* ImWindow_hpp */
