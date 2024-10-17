#pragma once

#include "renengine_node.hpp"

#define GLM_FORCE_LEFT_HANDED
#include <glm/ext/matrix_transform.hpp>


namespace ReneNgine {
    
    enum CameraDirection {
        LEFT = 0b100000,
        RIGHT = 0b010000,
        UP = 0b001000,
        DOWN = 0b000100,
        FRONT = 0b000010,
        BACK = 0b000001,
    };

    class Camera : public Node
    {
    public:
        const glm::vec3 UP_VECTOR = glm::vec3(0.0, 1.0, 0.0);
        const glm::vec3 FRONT_VECTOR = glm::vec3(0.0, 0.0, 1.0);
        Camera(Scene* scene, Node* parent = nullptr) : Node{ scene, parent } {
            transform.rotation = glm::vec3(0.0, glm::half_pi<float>(), 0.0);
        }
        void Input(const SDL_Event event) override;
        void Process(const double delta_time) override;
        glm::mat4 GetViewMatrix();
        void MakeActiveCamera();
        bool IsActiveCamera() const;
    private:
        glm::mat4 view_matrix = glm::identity<glm::mat4>();
        short unsigned int movement = 0b000000; // Left, Right, Up, Down, Back, Front

        glm::vec3 front = { 0.0, 0.0, 0.0 };
        
        float camera_speed = 20.0f;
        float camera_sensitivity = 0.05f;


    };
}

