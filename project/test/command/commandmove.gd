class_name MoveUnitCommand extends Command


@export var unit_test: PackedScene
var _unit : Unit 
@export var _x : float
@export var _y : float

@export var _xBefore : float 
@export var _yBefore : float 

# identifier or id to know the object

## unit and what properties to change
func _init(unit : Unit, x : float, y : float):
	_unit = unit
	_x = x
	_y = y

func execute() -> bool:
	if _unit == null:
		return false
	_xBefore = _unit.x_pos
	_yBefore = _unit.y_pos
	print("moving unit: " + str(_x) + " "+ str(_y) )
	_unit.move(_x, _y)
	return true 

func undo(): 
	_unit.move(_xBefore, _yBefore)
	
