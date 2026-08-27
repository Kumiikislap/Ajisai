extends Director

@onready var happy: Sprite2D = $CanvasLayer/Control/Happy
var tween : Tween
var dialogue_node : Balloon


enum MODES {
	NORMAL,
	FAST_FORWARD,
	AUTO,
	UNSKIPPABLE,
}

@export var current_mode : MODES
@export var is_fast_forward := false

func _ready() -> void:
	dialogue_node = DialogueManager.show_dialogue_balloon(dialogue_resource, "start", [self, { "movie" = MovieData.new() } ])
	dialogue_box = dialogue_node.get_node("%Balloon")
	printerr(dialogue_box)
	init_from_gdscript()
	
	tween = create_tween()
	tween.set_trans(Tween.TransitionType.TRANS_QUART)
	tween.set_ease(Tween.EASE_IN_OUT)
	tween.tween_property(happy, "scale", Vector2(2.0,2.0), 1.0)

func _process(_delta: float) -> void: 
	match current_mode:
		MODES.NORMAL:
			return
		MODES.AUTO:
			print("auto")
			if dialogue_node:
				dialogue_node.is_auto = true
		MODES.FAST_FORWARD:
			if not is_instance_valid(dialogue_node):
				return
			print("fasttt")
			if is_fast_forward:
				is_fast_forward = false
				await get_tree().create_timer(0.2).timeout
				dialogue_node.fast_forward()
				is_fast_forward = true



func _unhandled_key_input(_event: InputEvent) -> void:
	#get_viewport().set_input_as_handled()
	if Input.is_action_just_pressed("fast_forward_dialogue"):
		is_fast_forward = true
		current_mode = MODES.FAST_FORWARD

	elif  Input.is_action_just_released("fast_forward_dialogue"):
		is_fast_forward = false
		current_mode = MODES.NORMAL
