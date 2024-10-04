#pragma once

#include "renengine_transform.hpp"

#include <vector>
#include <memory>

#include <SDL.h>

namespace ReneNgine {
	class Scene;
	class Node
	{
	public:
		Node(Scene* scene, Node* parent = nullptr) : scene(scene), parent(parent) {}
		Transform transform;

		void HandleInput(const SDL_Event event);
		void HandleProcess(const double delta_time);

		virtual void Input(const SDL_Event event) { return; }
		virtual void Process(const double delta_time = 0) { return; }

		void AddChild(std::unique_ptr<Node>&& new_node);
		void SetParent(Node* new_parent) { parent = new_parent; }
	protected:
		Scene* scene;
		Node* parent;
		std::vector<std::unique_ptr<Node>> children;
		bool is_dirty = true;
	};
}

