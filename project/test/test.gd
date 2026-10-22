extends Node

@export var mcharacters : CharactersResource
const BALLOON = preload("uid://cnixhaofyde15")
var actor : ActorResource

@onready var dialogue_box : Balloon = %ExampleBalloon

var dialogue_resource := load("res://resources/test_gdscript_dm.dialogue")

var what := false
var tween : Tween

func _ready() -> void: 
	#show_dialogue()
	# passing the line id to cue arguments works like magic
	#DialogueManager.show_dialogue_balloon(dialogue_resource, 'cwvn0sdxmtmnp@4')
	#var line = await DialogueManager.get_next_dialogue_line(dialogue_resource, "cwvn0sdxmtmnp@4")
	#print(line)
	#%Sprite2D.modulate.a = 0.0
	pass

func show_dialogue():
	dialogue_box = DialogueManager.show_dialogue_balloon_scene(BALLOON, dialogue_resource, 'start')
	

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
		# start dialogue box
		if is_instance_valid(dialogue_box):
			dialogue_box.start(dialogue_resource, 'cwvn0sdxmtmnp@4')
			#dialogue_box.queue_free()
		#is_fast_forward = false
		#wtf()
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
