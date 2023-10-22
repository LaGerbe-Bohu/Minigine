#pragma once

#include <vector>
#include <stack>
#include <iostream>

//libs
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <ext/matrix_clip_space.hpp> // glm::perspective
#include <ext/scalar_constants.hpp> // glm::pi
#include <gtc/type_ptr.hpp>

#include "Object.h"
#include "../Headers/GLShader.h"


class Scene{
    protected:
    int width;
    int height;
    std::vector<Object*> Objects;
    unsigned int VAO,UBO;
    unsigned int VAOS;
    uint32_t programShader;
    uint32_t programShaderWireFrame;
    uint32_t programShaderGrid;

   
    public:
    Scene(){
    };

    Scene(const Scene& scene){
        this->height = scene.height;
        this->width = scene.width;

        std::vector<Object*> tmp;
        for (int i = 0; i < scene.Objects.size(); i++)
        {
            tmp.push_back(new Object(scene.Objects[i]->GetMesh(),scene.Objects[i]->GetName(),scene.Objects[i]->GetObjectType()));
        }

        Objects = tmp;
    }

    Scene operator=(const Scene& copy){
        this->height = copy.height;
        this->width = copy.width;

        std::vector<Object*> tmp;
        for (int i = 0; i < copy.Objects.size(); i++)
        {
            tmp.push_back(new Object(copy.Objects[i]->GetMesh(),copy.Objects[i]->GetName(),copy.Objects[i]->GetObjectType()));
        }

        for (int i = 0; i < Objects.size(); i++)
        {
            delete Objects[i];
        }

        Objects = tmp;
        return *this;
    }


    ~Scene(){
        for(auto p : Objects){
            delete p;
        }
    }

     virtual void SetUp();

    virtual void RemoveObjectScene(int idx){
        Objects.erase(Objects.begin()+idx);
    }

    virtual void AddObjectScene(Object* object){
        Objects.push_back(object);
    }

       virtual void Render(glm::mat4* _MVP,int debug);

    virtual std::vector<Object*> GetObjects(){
        return this->Objects;
    }

    virtual int VertexToRender(){
        return 0;
    }
};


