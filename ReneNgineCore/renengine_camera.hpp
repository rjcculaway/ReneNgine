#pragma once

#include "renengine_node.hpp"

#define GLM_FORCE_LEFT_HANDED
#include <glm/ext/matrix_transform.hpp>

constexpr glm::vec3 up_vector(0.0, 1.0, 0.0);

namespace ReneNgine {
    class Camera : public Node
    {
    public:
        Camera(Scene* scene, Node* parent = nullptr) : Node{ scene, parent } {}
        void Input(const SDL_Event event) override;
        void Process(uint64_t delta_time) override;
        glm::mat4 GetViewMatrix();
        void MakeActiveCamera();
    private:
        glm::mat4 view_matrix = glm::identity<glm::mat4>();
    };
}

