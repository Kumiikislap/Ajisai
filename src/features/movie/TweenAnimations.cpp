#include "features/movie/TweenAnimations.h"
#include "util/scene.hpp"

TweenAnimations::TweenAnimations()
{
	rl::scene::node::set_unique_name(this, "TweenAnimations");
}

void TweenAnimations::set_fade_duration(float p_duration)
{
	fade_duration = p_duration;
}

void TweenAnimations::set_slide_duration(float p_duration)
{
	slide_duration = p_duration;
}

void TweenAnimations::set_slide_distance(float p_distance)
{
	slide_distance = p_distance;
}

float TweenAnimations::get_fade_duration() const
{
	return fade_duration;
}

float TweenAnimations::get_slide_duration() const
{
	return slide_duration;
}

float TweenAnimations::get_slide_distance() const
{ 
	return slide_distance;
}
