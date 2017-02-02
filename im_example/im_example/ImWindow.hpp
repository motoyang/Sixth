//
//  ImWindow.hpp
//  im_example
//
//  Created by moto2 yang on 2017/2/2.
//  Copyright © 2017年 moto2 yang. All rights reserved.
//

#ifndef ImWindow_hpp
#define ImWindow_hpp

class ImWindow
{
    bool m_show;
public:
    
    ImWindow()
    : m_show(false)
    {
    }
    
    bool create(const char* title);
    void layout()
    {}
    
    bool run()
    {
        if (m_show) {
            layout();
        }
        
        return true;
    }
    void show() { m_show = true; }
    void hide() { m_show = false; }
    
};
#endif /* ImWindow_hpp */
