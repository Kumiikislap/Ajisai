extends Node

@export var max_sprites : int = 10000
const THREESOME = preload("uid://bkfssd2tenwcw")
const WALLPAPER_SE_1A = preload("uid://bpgduxg4rhtvl")

var array : Array[Sprite2D]


var counter := 0
func _ready() -> void:
	#var start = Time.get_ticks_usec()
	for sprites in max_sprites:
		var sprite = Sprite2D.new()
		sprite.texture = WALLPAPER_SE_1A
		array.append(sprite)
		add_child(sprite)
		sprite.hide()
	print(WALLPAPER_SE_1A.get_reference_count())
	#var end = Time.get_ticks_usec()
	#print((end-start)/100000.0)
	loop()
	looparray()
	var start = Time.get_ticks_usec()
	#printt()
	print("sshi")
	var end = Time.get_ticks_usec()
	print((end-start)/1000000.0)

func loop():
	var start = Time.get_ticks_usec()
	for child in get_children() as Array[Sprite2D]:
		child.texture = THREESOME
		#print("looping")
	var end = Time.get_ticks_usec()
	print((end-start)/1000000.0)

func looparray():
	var start = Time.get_ticks_usec()
	for child in array as Array[Sprite2D]:
		child.texture = WALLPAPER_SE_1A
		#print("looping")
	var end = Time.get_ticks_usec()
	print((end-start)/1000000.0)
	
func printt():
	#var start = Time.get_ticks_usec()
	print("sshi")
	#var end = Time.get_ticks_usec()
	#print((end-start)/100000.0)
