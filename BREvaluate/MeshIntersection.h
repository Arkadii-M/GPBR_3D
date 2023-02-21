#pragma once
#ifndef MESH_INTERSECTION_H
#define MESH_INTERSECTION_H
#include <armadillo>
#include <cassert>
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_rational.h>
#include <thread>
#include <chrono>
#include <future>


// leda_rational, or Gmpq, or Quotient<MP_float>
typedef CGAL::Exact_rational               NT;
typedef CGAL::Cartesian<NT>                Kernel;
typedef Kernel::Triangle_3                 Triangle;
typedef Kernel::Point_3                    Point;
typedef Kernel::Segment_3                  Segment;
typedef std::vector<Point>                 Polygon2;
#define INTERSECTION_EPS 1e-3

using uint = unsigned int;


struct grid_index {
	const uint row;
	const uint col;
	grid_index(uint row, uint col) : row(row), col(col) {}
	friend bool operator==(const grid_index& lhs, const grid_index& rhs)
	{
		return (lhs.row == rhs.row) && (lhs.col == rhs.col);
	}
};

struct tri_index {
	const uint id;
	const grid_index A;
	const grid_index B;
	const grid_index C;
	const bool on_upper_boundary;
	const bool on_lower_boundary;
	const bool on_left_boundary;
	const bool on_right_boundary;
	tri_index() :id(0),
		on_upper_boundary(false),
		on_lower_boundary(false),
		on_left_boundary(false),
		on_right_boundary(false),
		A(0, 0), B(0, 0), C(0, 0) {}
	tri_index(uint id,
		bool on_upper,
		bool on_lower,
		bool on_left,
		bool on_right,
		grid_index A,
		grid_index B,
		grid_index C) :
		id(id),
		on_upper_boundary(on_upper),
		on_lower_boundary(on_lower),
		on_left_boundary(on_left),
		on_right_boundary(on_right),
		A(A), B(B), C(C) {}
};


class MeshIntersection {
private:
	const uint n_rows;
	const uint n_cols;
	const uint row_skip;
	const uint col_skip;
	std::vector<std::pair<uint, std::vector<uint>>> check_pairs;

	std::vector<tri_index> triangles_grid;
public:
	MeshIntersection(uint n_rows, uint n_cols, uint row_skip = 1, uint col_skip = 1);

	bool hasSelfIntersection(const arma::Cube<double>& mesh);
private:
	void formGridTrianglesIndeces();
	void formPairsToCheck();
	bool hasCommonPoint(const tri_index& tr1, const tri_index& tr2);
	bool checkPoint(const grid_index& g_i, const tri_index& tr);


	static void getTriangle(const arma::Cube<double>& mesh, Triangle& triangle, const tri_index& index);

	static bool oneAndManyIntersect(
		const arma::Cube<double>& mesh,
		const std::vector<tri_index>& tri_indeces,
		const std::pair < uint, std::vector<uint>>& to_check);

};



#endif // !MESH_INTERSECTION_H
