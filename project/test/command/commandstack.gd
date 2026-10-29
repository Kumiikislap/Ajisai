class_name CommandStack extends Resource

# this bad boy will eat tons of pointers for breakfast

# needs dynamic naming
const path = "user://CommandStack/command.tres"

var data := SaveData.new()
var actor := ActorResource.new()

# TODO put all commands in array of resource
# known where we are in the stack -- counter
# or I can load and create all commands in the array
# creating 500 objects at once isnt bad right?

# bruh u can just -- no storing type name as string isnt enough, we need other variables
# Dictionary might work eh class is more readable imo

# undo and redo
func ready():
	#var data = SaveData.new()
	#save_data(data)
	actor.character_name = "Yumi"
	if not FileAccess.file_exists(path):
		printerr('Unable to load save data!')
		return
	ResourceSaver.save(actor, path)
	load_data()

func execute_command(cmd : Command):
	if cmd.execute():
		save_data(cmd)

func save_data(cmd : Command):
	var dir = DirAccess.open('user://')

	if !dir.dir_exists('CommandStack'):
		dir.make_dir('CommandStack')
	ResourceSaver.save(cmd, path )
	print("saved")

# load the command in stack and create as object
func load_data():
	if not FileAccess.file_exists(path):
		printerr('Unable to load save data!')
		return
	actor = ResourceLoader.load(path, '', ResourceLoader.CacheMode.CACHE_MODE_IGNORE)
	print(actor.get_class())
	print(actor)
	# create the type of command
	var command 
	match actor.get_class():
		"ActorResource":
			command = SaveData.new()
			command.bind_pointers(42)
			command.execute()
			# bind pointers and variables
			
			print("a")
		_:
			push_error("UNKNOWN COMMAND CLASS")
