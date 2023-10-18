#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class GDKDQueryResult : public RefCounted
{
	GDCLASS(GDKDQueryResult, RefCounted);

protected:
	static void _bind_methods();
	PackedVector3Array points;
	Array data;
public:

	void set_points(const PackedVector3Array& p_points);
	PackedVector3Array get_points() const;
	void set_data(const Array& p_data);
	Array get_data() const;
	GDKDQueryResult();
	~GDKDQueryResult();
};
