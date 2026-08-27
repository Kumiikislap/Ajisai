extends Node2D
@onready var sprite_2d: Sprite2D = $Sprite2D
const TEST = preload("uid://bgbb4b3a3lfex")
const TEST_GDSCRIPT_DM = preload("uid://cwvn0sdxmtmnp")


var tween : Tween
var is_fast_forward := false

func _ready() -> void:
	tween = create_tween()
	#tween.set_ignore_time_scale(true)
	tween.tween_property(sprite_2d, "position:y", sprite_2d.position.y -100, 3)
	
	DialogueManager.show_dialogue_balloon(TEST_GDSCRIPT_DM, "start", [self, { "movie" = MovieData.new() } ])


func _unhandled_input(event: InputEvent) -> void:
	get_viewport().set_input_as_handled()
	if Input.is_action_just_pressed("fast_forward_dialogue"):
		is_fast_forward = true
	
	elif Input.is_action_just_released("fast_forward_dialogue"):
		is_fast_forward = false


func _process(delta: float) -> void: pass
	

#func _physics_process(_delta: float) -> void:
	#if Input.is_action_pressed("fast_forward_dialogue"):
		#Engine.time_scale = 2
		#print(Engine.time_scale)
	#else:
		#Engine.time_scale = 0.5
		#print(Engine.time_scale)
	
	#if is_fast_forward:
		#Engine.time_scale = 2
	#else: 
		#Engine.time_scale = 1
	#print(is_fast_forward)
