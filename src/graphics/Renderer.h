#pragma once


#include "Meshrenderer.h"
#include "Camera.h"
#include "Light.h"

class Renderer {
public:
    static void RenderScene(
        const std::vector<MeshRenderer*>& renderers,
        const Camera& camera,
        const Light& light
    ){
        Shader* currentShader = nullptr;
        for(auto* mr : renderers) {
            Shader* shader = mr->material->shader;
            if(shader != currentShader){
                shader->use();

                int viewLoc = shader->getLocation("view");
                if (viewLoc != -1)
                    shader->upload(viewLoc, camera.getView());
                
                int projLoc = shader->getLocation("projection");
                if (projLoc != -1)
                    shader->upload(projLoc, camera.getProjection());

                int viewPosLoc = shader->getLocation("viewPos");
                if (viewPosLoc != -1)
                    shader->upload(viewPosLoc, camera.Position);

                int lightPosLoc = shader->getLocation("lightPos");
                if (lightPosLoc != -1)
                    shader->upload(lightPosLoc, light.position);
                
                int lightColorLoc = shader->getLocation("lightColor");
                if (lightColorLoc != -1)
                    shader->upload(lightColorLoc, light.color);


                
                currentShader= shader;
            }

            mr->Draw();
            
        }
    }
};