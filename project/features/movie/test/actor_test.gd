extends Actor

#func _notification(what: int) -> void:
	#match what:
		#NOTIFICATION_ENTER_TREE:
			#await get_tree().create_timer(1.5).timeout
			#on_tween_finished(0)
			#await get_tree().create_timer(1.0).timeout
			#on_tween_finished(1)
			#pass
