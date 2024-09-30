#include "renengine_node.hpp"

namespace ReneNgine {
	void Node::HandleInput(const SDL_Event event) {
		Input(event);
		for (auto& child : children) {
			child->HandleInput(event);
		}
	}

	void Node::HandleProcess(const uint64_t delta_time) {
		Process(delta_time);
		for (auto& child : children) {
			child->HandleProcess(delta_time);
		}
	}
}