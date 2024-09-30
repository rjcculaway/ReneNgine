#include "renengine_scene.hpp"
#include "renengine_node.hpp"
#include "renengine_camera.hpp"

namespace ReneNgine {
	Scene::Scene() {
		// TODO: Temporary, just to get a camera set up in the scene
		Camera* camera_ptr = new Camera(this, scene_tree.get());
		camera_ptr->transform.position.z = 15.0;
		SetActiveCamera(camera_ptr);

		std::unique_ptr<Node> camera(
			dynamic_cast<Node*>(camera_ptr)
		);
		scene_tree->AddChild(std::move(camera));
	}
	void Scene::HandleInput(const SDL_Event event) {
		scene_tree->HandleInput(event); 
	}

	void Scene::HandleProcess(const uint64_t delta_time) {
		scene_tree->HandleProcess(delta_time);
	}
	Camera * Scene::GetActiveCamera() const
	{
		return active_camera;
	}
}