#pragma once
#include <optional>
#include <godot_cpp/classes/node.hpp>
#include "features/movie/ActorsLayer.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/tween.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/property_tweener.hpp>
#include "Actor.h"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "util/bind.hpp"


using namespace godot;

class TweenAnimations : public Node
{
	GDCLASS(TweenAnimations, Node)

	public:
		TweenAnimations();
		~TweenAnimations() = default;

		// TODO shake, other animations
		// shake, nod?, rotate

		enum DIRECTION {
			RIGHT,
			LEFT,
		};
		enum FADE {
			IN,
			OUT,
		};

		void fade_out(auto  p_object, std::optional<float> p_duration = std::nullopt)
		{
			if (tween.is_valid() and tween->is_running())
			{
				tween->custom_step(999);
			}
			float final_duration = p_duration.value_or(fade_duration);
			tween = create_tween();
			tween->set_parallel();
			tween->tween_property(p_object, "modulate:a", 0.0, final_duration);
			UtilityFunctions::printerr("did this shit even reach, const Args &p_args...");
		}

		// only works on nodes with position properties
		void slide ( auto p_object, DIRECTION direction, std::optional<float> p_pixels = std::nullopt, 
				std::optional<float> p_duration = std::nullopt,
				Tween::EaseType p_easing = Tween::EaseType::EASE_IN,
				Tween::TransitionType p_trans = Tween::TransitionType::TRANS_QUART)
		{
			if (tween.is_valid() and tween->is_running())
			{
				//tween->set_speed_scale(1000);
				tween->custom_step(999);
			}
			tween = create_tween();
			tween->set_ease(p_easing);
			tween->set_trans(p_trans);
			float final_pixels = p_pixels.value_or(slide_distance);
			float final_duration = p_duration.value_or(slide_duration);

			switch (direction) {
				case RIGHT:
					tween->tween_property(p_object, "position:x", p_object->get_position().x + final_pixels, final_duration);
					break;
				case LEFT:
					tween->tween_property(p_object, "position:x", p_object->get_position().x - final_pixels, final_duration);
					break;
			}
		}

		void scale(auto p_object, Vector2 p_scale)
		{
			if (tween.is_valid() and tween->is_running())
			{
				tween->custom_step(999);
			}
			tween = create_tween();
			tween->tween_property(p_object, "scale", p_scale, 0.5);
		}

		void set_fade_duration(float p_duration);
		void set_slide_duration(float p_duration);
		void set_slide_distance(float p_distance);

		float get_fade_duration() const;
		float get_slide_duration() const;
		float get_slide_distance() const;

	protected:
		static void _bind_methods(){
			rl::utils::bind_property(TweenAnimations, fade_duration, float);
			rl::utils::bind_property(TweenAnimations, slide_duration, float);
			rl::utils::bind_property(TweenAnimations, slide_distance, float);
		}
	private:
		Ref<Tween> tween;

		// default properties
		float fade_duration { 0.5 };
		Tween::EaseType fade_ease;
		Tween::TransitionType fade_trans;

		float slide_duration { 0.5 };
		float slide_distance { 80.0 };
		Tween::EaseType slide_ease;;
		Tween::TransitionType slide_trans;;
};
