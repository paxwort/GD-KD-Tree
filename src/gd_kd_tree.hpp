#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "../kdtree-cpp/kdtree.hpp"
#include "gd_kd_query_result.hpp"

using namespace godot;

class GDKDTree : public Node
{
	GDCLASS(GDKDTree, Node);

protected:
	static void _bind_methods();
	static std::vector<double> vector3_to_double_vector(const Vector3& p_vector);
	static PackedVector3Array kdNodeVector_to_packedVector3(Kdtree::KdNodeVector *p_vector);
	static Vector3 kdNode_to_Vector3(Kdtree::KdNode *p_node);
	Kdtree::KdTree *tree;
	godot::Array data;

public:
	GDKDTree();
	~GDKDTree();

	void _ready() override;
	void _process(double delta) override;

	void initialize_tree(const PackedVector3Array& p_points, const godot::Array& p_data);

	Ref<GDKDQueryResult> k_nearest_neighbours(const Vector3 &p_position, const int &p_k);
	
};
