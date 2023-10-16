
#include <iostream>

// glew and glfw include
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// glm include
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <ext/matrix_clip_space.hpp> // glm::perspective
#include <ext/scalar_constants.hpp> // glm::pi
#include <gtc/type_ptr.hpp>

// imgui include
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// my Headers include
#include "../Headers/GLShader.h"
#include "../Headers/ApplicationState.h"
#include "../Headers/Scene.h"
#include "../Headers/RenderContext.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../stbload/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stbload/stb_image_write.h"

ApplicationState app; 
Scene1 scene;
RenderContextShadedWireFrame renderContext;
RenderContextShaded rcShaded;
RenderContextWireFrame renderContextShaded;
RenderContextNOFramed Noframed;

int main(int, char**){


   // Application Setup
    app = ApplicationState(1920,1080);
    int err = app.SetupApplication();    

    if(err == 1){
        return 1;
    }

    GLFWwindow* window = app.GetGLFWwindow();
    float height = (float)app.GetHeight();
    float width = (float)app.GetWidth();

    glm::mat4 matrices[2];
    matrices[0] =  glm::translate(glm::mat4(1.f), -glm::vec3({ 0.f, 0.f,3.f }));
    matrices[1] =   glm::perspectiveFov(glm::radians(45.0f), (float)width, (float)height, 0.5f, 1000.0f);

    glm::mat4 matricesWire[2];
    matricesWire[0] =  glm::translate(glm::mat4(1.f), -glm::vec3({ 0.f, 0.f,3.f }));
    matricesWire[1] =  glm::perspectiveFov(glm::radians(45.0f), (float)width, (float)height, 0.5f, 1000.0f);

    renderContext.SetUp(matricesWire,width/2.0f,height/2.0f);
    renderContextShaded.SetUp(matrices,width/2.0f,height/2.0f);
    rcShaded.SetUp(matricesWire,width/2.0f,height/2.0f);
    Noframed.SetUp(matricesWire,width/2.0f,height/2.0f);
    scene.SetUp((int)width,(int)height);

   
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  
    glCullFace(GL_FRONT); 
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    float i = 0;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 2.0f;
    ImGui::StyleColorsLight();
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_TitleBg]                = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(1.00f, 0.79f, 0.80f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.83f, 0.89f, 0.83f, 1.00f);


    ImGui::GetStyle().WindowRounding = 9.0f;
    ImGui::GetStyle().FramePadding = ImVec2(11.0f,11.0f);
    ImGui::GetStyle().WindowBorderSize = 0.0f;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");




    while(!glfwWindowShouldClose(window)){
        i += 0.1f;

        // rendering stuff
        glViewport(0,0,(int)width,(int)height);
        glClearColor(0.98f,0.95f,0.94f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Noframed.RenderScene(&scene);

        matrices[0] =  glm::translate(glm::mat4(1.f), -glm::vec3({ 0.f, 0.f,10.f }));
        matrices[0] *= glm::rotate(glm::mat4(1.0f), 80 * (glm::pi<float>() / 180.0f), glm::vec3(1.0f, 0.0, 0.0));
        matrices[0] *= glm::rotate(glm::mat4(1.0f), i * (glm::pi<float>() / 180.0f), glm::vec3(0.0f, 1.0, 0.0));

        matricesWire[0] =  glm::translate(glm::mat4(1.f), -glm::vec3({ 0.f, 0.f,7.f }));
        matricesWire[0] *= glm::rotate(glm::mat4(1.0f), 50 * (glm::pi<float>() / 180.0f), glm::vec3(1.0f, 0.0, 0.0));
        matricesWire[0] *= glm::rotate(glm::mat4(1.0f), i * (glm::pi<float>() / 180.0f), glm::vec3(0.0f, 1.0, 0.0));
    

        unsigned int tex2 = renderContext.RenderScene(&scene);
        unsigned int tex = renderContextShaded.RenderScene(&scene);
        unsigned int tex3 = rcShaded.RenderScene(&scene);

        // UI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        
        ImGui::NewFrame();
         
         {
            ImGui::SetNextWindowSize(ImVec2(renderContext.GetWidth(),renderContext.GetHeight()));
            ImGui::Begin("Wireframe game view");

                ImGui::BeginChild("Game Render");

                    ImVec2 size = ImGui::GetWindowSize();

                   ImGui::Image((void*)(intptr_t)tex,size,ImVec2(0,1 ),ImVec2(1,0 ));

                ImGui::EndChild();


            ImGui::End();
        }

        {
            ImGui::SetNextWindowSize(ImVec2(renderContextShaded.GetWidth(),renderContextShaded.GetHeight()));
            ImGui::Begin("Shaded Wireframe game view ");

                ImGui::BeginChild("Game Render");

                    ImVec2 size = ImGui::GetWindowSize();

                   ImGui::Image((void*)(intptr_t)tex2,size,ImVec2(0,1 ),ImVec2(1,0 ));

                ImGui::EndChild();


            ImGui::End();
        }



        {
            ImGui::SetNextWindowSize(ImVec2(rcShaded.GetWidth(),rcShaded.GetHeight()));
            ImGui::Begin("Shaded game view");

                ImGui::BeginChild("Game Render");

                    ImVec2 size = ImGui::GetWindowSize();

                   ImGui::Image((void*)(intptr_t)tex3,size,ImVec2(0,1 ),ImVec2(1,0 ));

                ImGui::EndChild();


            ImGui::End();
        }


        ImGui::Render();

      
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // event
        app.ApplicationEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
