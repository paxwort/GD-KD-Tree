extends Node

func _ready() -> void:

	var v_arr = PackedVector3Array([
	Vector3(0.0, 1.0, 0.0),
	Vector3(5.2, 1, 6),
	Vector3(2.3, 4.7, 1.1),
	Vector3(-3.5, 2.2, 8.9),
	Vector3(6.0, -2.3, 7.4),
	Vector3(1.0, 3.0, 2.0),
	Vector3(-2.5, -1.0, 0.5),
	Vector3(0.7, -4.2, 3.1),
	Vector3(4.5, 2.3, -1.7),
	Vector3(-2.1, 6.7, -5.5),
	Vector3(3.3, 0.9, -0.2),
	Vector3(0.0, 0.0, 0.0),
	Vector3(9.8, 7.6, 2.3),
	Vector3(1.5, 3.8, 9.0),
	Vector3(-5.2, -1.1, 4.6),
	Vector3(2.0, 2.0, 2.0),
	Vector3(-3.0, -3.0, -3.0),
	Vector3(0.5, 0.5, 0.5),
	Vector3(-1.0, 0.0, 1.0),
	Vector3(7.0, 3.5, 1.8)])
	
	var data_arr = [
	"$Node1",
	$Node2,
	Vector3(0,1,0),
	Basis.IDENTITY,
	$Node1,
	$Node2,
	$Node1,
	$Node2,
	$Node1,
	$Node2,
	$Node1,
	$Node2,
	$Node1,
	$Node2,
	$Node1,
	$Node1,
	$Node2,
	$Node1,
	$Node2,
	$Node1
	]
	var target_vector = Vector3(0.0, 1.0, 0.0)
	#kd search for closest
	
	var init_start = Time.get_ticks_usec()
	$GDKDTree.initialize_tree(v_arr, data_arr)
	var query_start = Time.get_ticks_usec()
	var query = $GDKDTree.k_nearest_neighbours(target_vector, 20)
	var query_end = Time.get_ticks_usec()
	
	#naive search for closest
	var naive_start = Time.get_ticks_usec()
	
	var best : Vector3
	var best_data
	var best_len : float = INF
	for i in range(0, v_arr.size()):
		if (target_vector - v_arr[i]).length() < best_len:
			best = v_arr[i]
			best_data = data_arr[i]
	
	var naive_end = Time.get_ticks_usec()
	
	print("init: %s\nquery: %s\nnaive:%s"%[query_start - init_start, query_end - query_start, naive_end - naive_start])
