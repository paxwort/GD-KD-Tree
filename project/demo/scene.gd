extends Node

func _ready() -> void:
	print("Hello GDScript!")
	var arr = PackedVector3Array([
	Vector3(0, 1, 0),
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
	Vector3(7.0, 3.5, 1.8)
])
	$GDKDTree.initialize_tree(arr)
	var arr2 : PackedVector3Array = $GDKDTree.k_nearest_neighbours(Vector3(0,0,0), 5)
	print("kn:%s"%arr2)
