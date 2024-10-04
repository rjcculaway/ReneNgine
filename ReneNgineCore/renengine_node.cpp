#include "renengine_node.hpp"

namespace ReneNgine {
	void Node::HandleInput(const SDL_Event event) {
		Input(event);
		for (auto& child : children) {
			child->HandleInput(event);
		}
	}

	void Node::HandleProcess(const double delta_time) {
		Process(delta_time);
		for (auto& child : children) {
			child->HandleProcess(delta_time);
		}
	}
	void Node::AddChild(std::unique_ptr<Node>&& new_node) {
		new_node->SetParent(this);
		children.emplace_back(std::move(new_node));
	}
}