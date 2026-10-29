class_name SaveData extends Resource

@export var Ajisai := 39 

func execute():
	print("from save data class")
	print(Ajisai)

func bind_pointers(unit : int):
	Ajisai = unit
