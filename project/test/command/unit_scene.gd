extends Node

@onready var unit: Unit = $unit
#const Commandstack = preload("uid://bdxi5w7cqvr4e").instantiate()


func _ready() -> void: 
	var Commandstack = CommandStack.new()
	var cmdmove = MoveUnitCommand.new( unit, 20.0, 20.0)
	#Commandstack.execute_command(cmdmove)
	Commandstack.ready()
	#cmdmove.execute()
	#cmdmove.undo()
