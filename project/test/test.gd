extends Node

@export var mcharacters : CharactersResource
var actor : ActorResource

var avenix
var crowe


var what := false
var tween : Tween

func _ready() -> void: pass
	#%Sprite2D.modulate.a = 0.0

func _unhandled_key_input(_event: InputEvent) -> void:
	get_viewport().set_input_as_handled()
	if Input.is_action_just_pressed("fast_forward_dialogue"):
		#if is_instance_valid(tween) and tween.is_running() and tween.is_valid():
		if tween:
			tween.set_speed_scale(1000)
			#tween.kill()
			#%Sprite2D.modulate.a = 0.0
			printerr("pressd")

		tween = create_tween()
		tween.tween_property(%Sprite2D, "modulate:a", 0.0 , 1.0)
		#tween.tween_await(tween.finished)
		what = true

		
	elif  Input.is_action_just_pressed("test"):
		#is_fast_forward = false
		wtf()
		print("real")

func wtf():
	#if what:
		#var tween : Tween
	#tween = create_tween()
	if is_instance_valid(tween) and tween.is_running():
		tween.set_speed_scale(100)
		#tween.kill()
	tween = create_tween()
	tween.tween_property(%Sprite2D2, "modulate:a", 0.0 , 1.0)
	#await get_tree().create_timer(1.0).timeout
	#tween.tween_await(tween.finished)
	tween.tween_callback(test)
	#printerr("ja")
	
func test():
	printerr("test")
