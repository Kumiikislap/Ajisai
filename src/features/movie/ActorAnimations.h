#include <godot_cpp/classes/resource.hpp>
#include "features/movie/Actor.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/tween.hpp"
#include "godot_cpp/classes/wrapped.hpp"


using namespace godot;

class ActorAnimations : public Resource
{
	GDCLASS(ActorAnimations, Resource)
	
	static void _bind_methods(){};

	public:

	void fade_out(Actor* p_actor, float p_duration = 1.0);
	void fade_in(Actor* p_actor);
	void slide(Actor* p_actor);
	void scale(Actor* p_actor);
	void rotate(Actor* p_actor);

	void shake(Actor* p_actor);

	// think of other animations

	void animate(Actor* p_actor);

	private:
	float duration { 1.0 };
	Ref<Tween> tween;
};
