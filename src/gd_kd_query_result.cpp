#include "gd_kd_tree.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "gd_kd_query_result.hpp"

using namespace godot;


void GDKDQueryResult::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_data", "p_data"), &GDKDQueryResult::set_data);
	ClassDB::bind_method(D_METHOD("get_data"), &GDKDQueryResult::get_data);
	ClassDB::bind_method(D_METHOD("set_points", "p_points"), &GDKDQueryResult::set_points);
	ClassDB::bind_method(D_METHOD("get_points"), &GDKDQueryResult::get_points);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data"), "set_data", "get_data");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "points"), "set_points", "get_points");
}

void GDKDQueryResult::set_points(const PackedVector3Array& p_points)
{
	points = p_points;
}

PackedVector3Array GDKDQueryResult::get_points() const
{
	return points;
}

void GDKDQueryResult::set_data(const Array &p_data)
{
	data = p_data;
}

Array GDKDQueryResult::get_data() const
{
	return data;
}

GDKDQueryResult::GDKDQueryResult()
{

}

GDKDQueryResult::~GDKDQueryResult()
{
}
