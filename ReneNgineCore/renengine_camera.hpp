#pragma once

#include "renengine_node.hpp"

constexpr glm::vec3 up_vector(0.0, 1.0, 0.0);

namespace ReneNgine {
    class Camera : public Node
    {
    public:
        void Input(const SDL_Event event) override;
        void Process(uint64_t delta_time) override;
        glm::mat4 GetViewMatrix();
    private:
        glm::mat4 view_matrix;
    };
}

