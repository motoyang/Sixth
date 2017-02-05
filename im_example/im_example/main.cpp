// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "../../x_uml/imgui/imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include "../GL/gl3w.h"    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include "ImWindow.hpp"
#include <list>
#include <memory>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

struct App
{
    
    std::list<std::unique_ptr<ImWindow>> m_windows;
    static App* s_instance;

    App()
    {
        s_instance = this;
    }
    
    GLFWwindow* init(int argc, const char** argv)
    {
        // Setup window
        glfwSetErrorCallback(error_callback);
        if (!glfwInit())
            return nullptr;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        
//      GLFWmonitor* monitor = glfwGetPrimaryMonitor();
//      const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//      GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", monitor, NULL);
//      GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
        GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
        glfwMakeContextCurrent(window);
        gl3wInit();
        
        // Setup ImGui binding
        ImGui_ImplGlfwGL3_Init(window, true);
        
        // Load Fonts
        // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
        ImGuiIO& io = ImGui::GetIO();
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("~/extra_fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
        //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
        io.Fonts->AddFontFromFileTTF("../../extra_fonts/华文仿宋.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChinese());
        
        return window;
    }
    
    void run(GLFWwindow* window)
    {
 //       bool show_test_window = true;
   //     bool show_another_window = false;
        ImVec4 clear_color = ImColor(114, 144, 154);
/*
        ImWindow simpleWindow;
        simpleWindow.layout([]()->void
                             {static float f = 0.0f;
                                 ImGui::Text("Hello, world!");
                                 ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
             //                    ImGui::ColorEdit3("clear color", (float*)&clear_color);
                              //   if (ImGui::Button("Test Window")) show_test_window ^= 1;
                                // if (ImGui::Button("Another Window")) show_another_window ^= 1;
                                 ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
                             );
        simpleWindow.show();
*/
        
        createWindows();
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            ImGui_ImplGlfwGL3_NewFrame();
  //          simpleWindow.run();
            
            for (auto pw = m_windows.cbegin(); pw != m_windows.cend(); )
            {
                if ((*pw)->isShow()) {
                    (*pw)->run();
                    ++pw;
                }
                else {
                    pw = m_windows.erase(pw);
                }
            }
/*
            // 1. Show a simple window
            // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
            {
                static float f = 0.0f;
                ImGui::Text("Hello, world!");
                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
                ImGui::ColorEdit3("clear color", (float*)&clear_color);
                if (ImGui::Button("Test Window")) show_test_window ^= 1;
                if (ImGui::Button("Another Window")) show_another_window ^= 1;
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }
   
            // 2. Show another simple window, this time using an explicit Begin/End pair
            if (show_another_window)
            {
                ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
                ImGui::Begin("Another Window", &show_another_window);
                ImGui::Text("你好！中国人民解放军。。。");
                ImGui::Button("这是一个按钮！");
                ImGui::End();
            }
            
            // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
            if (show_test_window)
            {
                ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
                ImGui::ShowTestWindow(&show_test_window);
            }
*/
            // Rendering
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();
            glfwSwapBuffers(window);
        }
       
    }
    
    void terminate()
    {
        ImGui_ImplGlfwGL3_Shutdown();
        glfwTerminate();
    }
    
    ~App()
    {
        s_instance = nullptr;
    }
    
    bool createWindow(const std::string& title, const ImVec2& pos, const ImVec2& size, Layout l) {
        auto w = std::make_unique<ImWindow>(title, pos, size, l);
        m_windows.push_front(std::move(w));
        
        return true;
    }
    
    bool createWindows()
    {
        ImVec2 pos(100, 100);
        ImVec2 size(400, 200);
        
        Layout l2 = [] (ImWindow* pw) -> void {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin(pw->m_title.c_str(), &(pw->m_show));
            ImGui::Text("你好！中国人民解放军。。。");
            ImGui::Button("这是一个按钮！");
            ImGui::End();
        };

        createWindow("Window1 title", pos, size, l2);
        createWindow("Window2 title", ImVec2(150, 150), size, l2);
        createWindow("Window3 title", ImVec2(250, 250), size, l2);
        createWindow("Window4 title", ImVec2(350, 350), size, l2);
        createWindow("Window5 title", ImVec2(350, 250), size, l2);
        createWindow("Window6 title", ImVec2(550, 350), size, l2);
        
        Layout l1 = [] (ImWindow*) -> void {
            static float f = 0.0f;
            ImVec4 clear_color = ImColor(4, 144, 154);
            
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            //      if (ImGui::Button("Test Window")) show_test_window ^= 1;
 //           if (ImGui::Button("Another Window")) createWindow("Another window", ImVec2(750, 350), size, l2);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        };
        createWindow("", ImVec2(150, 350), size, l1);
        
        return true;
    }
};
    
App* App::s_instance = nullptr;

int main(int argc, const char** argv)
{
    App a;
    GLFWwindow* w = a.init(argc, argv);
    if (w) a.run(w);
    a.terminate();
    
/*
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//    GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", monitor, NULL);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
//    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);

 
    glfwMakeContextCurrent(window);
    gl3wInit();
    
    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);
    
    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("~/extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    io.Fonts->AddFontFromFileTTF("../../extra_fonts/华文仿宋.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChinese());
    
    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
*/
    // Main loop
/*    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();
        
        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        
        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("你好！中国人民解放军。。。");
            ImGui::Button("这是一个按钮！");
            ImGui::End();
        }
        
        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }
        
        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
 */
    return 0;
}
