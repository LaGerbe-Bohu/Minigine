#pragma once
#include <vector>
#include "RenderContextDisplay.h"
#include <cstring>
#include "windows.h"
#include "psapi.h"
#include "Scene.h"

class DisplayerManager{
    std::vector<RenderContextDisplay*> RenderContextDisplays;
    RenderContextDisplay* renderContextDisplay;
    std::vector<float> memoryUsage;
    bool openMachineState;
    
    public :
    DisplayerManager(){
        memoryUsage = std::vector<float>(500);
        openMachineState = true;
    }
    
    void AddRenderContextDisplay(RenderContextDisplay* renderWindow){
        RenderContextDisplays.push_back(renderWindow);
    };

    void SetTemplateRenderContextDisplay(RenderContextDisplay* render){
        renderContextDisplay = render;
    }

    void MachineState();
    void SceneEditor(Scene* scene);
    void RenderAppOptions();
    void RenderAllRenderWindows(int width,int height,Scene* scene);


    ~DisplayerManager(){
        for (size_t i = 0; i < RenderContextDisplays.size(); i++) {
            delete RenderContextDisplays[i];
        }
    }

  

};