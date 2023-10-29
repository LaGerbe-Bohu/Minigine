#pragma once
#include "Component.h"
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <ext/matrix_clip_space.hpp> // glm::perspective
#include <ext/scalar_constants.hpp> // glm::pi
#include <gtc/type_ptr.hpp>
#include <vector>
#include <math.h> 
#include <limits>
#include <chrono>
#include <iostream>

class LineRenderer:public Component{
    Object* targetMouse;
    Projet* projet;
    std::vector<Object*> lstObject;
    std::vector<Object*> lstLines;
    int lastIdx;
    bool RenderLine;
    bool start ;
    
    public :
    virtual void Editor();
    virtual void SetUp();
    virtual void Update();

    LineRenderer(Object* obj):Component(obj){
        headerName = "LineRenderer";
        RenderLine = false;
        SetID();
    }

    LineRenderer(const LineRenderer& copy):Component(copy){
        RenderLine = false;
    }

        
    virtual LineRenderer* Clone(Object* obj){
        LineRenderer* comp = new LineRenderer(obj);
        return comp;
    }

    LineRenderer( std::vector<Object*> point,Object* obj):Component(obj){
        headerName = "LineRenderer";
        RenderLine = false;
        SetID();

       CopyObject(point);

    }

    LineRenderer(std::string id,int i,YAML::Node& yamlFile,Object* obj):Component(id,i,yamlFile,obj){
        headerName = "LineRenderer";
        RenderLine = yamlFile[id][i]["RenderLine"].as<bool>();
    }
    
    void CopyObject( std::vector<Object*> point);

    virtual void Save(std::string id,int i,YAML::Node& yamlFile){
        Component::Save(id,i,yamlFile);
        yamlFile[id][i]["RenderLine"] = RenderLine;
    }

    virtual void SetID(){
        ID = c_LineRenderer;
    }

    void CreateLine();
    
    void GiftWraping();

    void GrahamScan();

    LineRenderer operator=(const LineRenderer& copy){
        return *this;
    }



    ~LineRenderer(){
       // delete targetMouse;
    }
};