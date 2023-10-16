#include "gd_kd_tree.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDKDTree::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("initialize_tree", "p_points"), &GDKDTree::initialize_tree);
	ClassDB::bind_method(D_METHOD("nearest_neighbour", "p_position"), &GDKDTree::nearest_neighbour);
	ClassDB::bind_method(D_METHOD("k_nearest_neighbours", "p_position", "p_k"), &GDKDTree::k_nearest_neighbours);
}

GDKDTree::GDKDTree()
{
}

GDKDTree::~GDKDTree()
{
	if (tree != nullptr) {
		delete tree;
	}
}

void GDKDTree::_ready()
{
}

void GDKDTree::_process(double delta)
{
}

void GDKDTree::initialize_tree(PackedVector3Array p_points)
{
	if (tree != nullptr) {
		delete tree;
	}

	Kdtree::KdNodeVector nodes;
	for (int i = 0; i < p_points.size(); i++) {
		Vector3 vector3Element = p_points[i];
		std::vector<double> point = vector3_to_double_vector(&vector3Element);
			nodes.push_back(Kdtree::KdNode(point));
	}
	tree = new Kdtree::KdTree(&nodes);
}

Vector3 GDKDTree::nearest_neighbour(Vector3 p_position)
{
	return GDKDTree::k_nearest_neighbours(p_position, 1)[0];
}

PackedVector3Array GDKDTree::k_nearest_neighbours(Vector3 p_position, int p_k)
{
	Kdtree::KdNodeVector result;
	Kdtree::CoordPoint coord = vector3_to_double_vector(&p_position);
	tree->k_nearest_neighbors(coord, p_k, &result);
	return kdNodeVector_to_packedVector3(&result);
}

std::vector<double> GDKDTree::vector3_to_double_vector(Vector3* p_vector)
{
	std::vector<double> point(3);
	point[0] = p_vector->x;
	point[1] = p_vector->y;
	point[2] = p_vector->z;
	return point;
}

PackedVector3Array GDKDTree::kdNodeVector_to_packedVector3(Kdtree::KdNodeVector *p_vector)
{
	PackedVector3Array pv;
	for (int i = 0; i < p_vector->size(); i++) {
		Kdtree::KdNode kd_node = (*p_vector)[i];
		pv.push_back(kdNode_to_Vector3(&kd_node));
	}
	return pv;
}

Vector3 GDKDTree::kdNode_to_Vector3(Kdtree::KdNode *p_node)
{
	Vector3 v;
	v.x = p_node->point[0];
	v.y = p_node->point[1];
	v.z = p_node->point[2];
	return v;
}


