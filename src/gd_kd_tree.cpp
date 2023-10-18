#include "gd_kd_tree.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDKDTree::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("initialize_tree", "p_points", "p_data"), &GDKDTree::initialize_tree);
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

void GDKDTree::initialize_tree(const PackedVector3Array &p_points, const godot::Array &p_data)
{
	if (p_data.size() != p_points.size()) {
		//TODO: Throw error
		return;
	}

	if (tree != nullptr) {
		delete tree;
	}
	data = p_data;

	Kdtree::KdNodeVector nodes;
	for (int i = 0; i < p_points.size(); i++) {
		Vector3 vector3Element = p_points[i];
		std::vector<double> point = vector3_to_double_vector(vector3Element);
		Kdtree::KdNode node = Kdtree::KdNode(point);
		node.index = i;
		nodes.push_back(node);
	}
	tree = new Kdtree::KdTree(&nodes);
}

Ref<GDKDQueryResult> GDKDTree::k_nearest_neighbours(const Vector3& p_position, const int& p_k)
{
	Ref<GDKDQueryResult> query_result(memnew(GDKDQueryResult));
	
	Kdtree::KdNodeVector result;
	Kdtree::CoordPoint coord = vector3_to_double_vector(p_position);

	godot::Array arr;
	godot::PackedVector3Array points;
	tree->k_nearest_neighbors(coord, p_k, &result);
	
	for (int i = 0; i < result.size(); i++) {
		Kdtree::KdNode node = result[i];
		if ((node.index >= 0) && (node.index < data.size())) {
			Vector3 point = kdNode_to_Vector3(&node);
			points.push_back(point);
			arr.append(data[node.index]);
		}
	}
	
	query_result->set_points(points);
	query_result->set_data(arr);
	
	return query_result;
}

std::vector<double> GDKDTree::vector3_to_double_vector(const Vector3 &p_vector)
{
	std::vector<double> point(3);
	point[0] = p_vector.x;
	point[1] = p_vector.y;
	point[2] = p_vector.z;
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


