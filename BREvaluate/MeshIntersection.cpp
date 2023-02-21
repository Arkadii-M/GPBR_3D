#include "MeshIntersection.h"

MeshIntersection::MeshIntersection(uint n_rows, uint n_cols, uint row_skip, uint col_skip) :
    n_rows(n_rows),
    n_cols(n_cols),
    row_skip(row_skip),
    col_skip(col_skip)
{
    if (row_skip == 0 || (n_rows - 1) % row_skip != 0)
        throw std::invalid_argument("invalid row skip number");
    if (col_skip == 0 || (n_cols - 1) % col_skip != 0)
        throw std::invalid_argument("invalid column skip number");
    formGridTrianglesIndeces();
    formPairsToCheck();
}

void MeshIntersection::formGridTrianglesIndeces()
{
    uint tri_id = 0;
    bool first_row = false;
    bool last_row = false;
    /* for (uint row = 0; row < n_rows - 1; row++)
     {
         first_row = row == 0;
         last_row = row == n_rows - 2;

         for (uint column = 0; column < n_cols - 1; column++)
         {
             if (column != 0)
             {
                 triangles_grid.push_back(tri_index(tri_id++,
                     first_row,
                     last_row,
                     column == 0,
                     column == n_cols - 2,
                     grid_index(row, column),
                     grid_index(row + 1, column),
                     grid_index(row, column + 1)
                 ));
             }
             if (column != n_cols - 2)
             {
                 triangles_grid.push_back(tri_index(tri_id++,
                     first_row,
                     last_row,
                     column == 0,
                     column == n_cols - 2,
                     grid_index(row + 1, column + 1),
                     grid_index(row + 1, column),
                     grid_index(row, column + 1)
                 ));
             }
         }
     }*/
    for (uint row = 0; row < n_rows - 1; row += row_skip)
    {
        first_row = row == 0;
        last_row = row == n_rows - row_skip - 1;

        for (uint column = 0; column < n_cols - 1; column += col_skip)
        {
            if (column != 0)// skip where thetha is 0. All those has one common point
            {
                triangles_grid.push_back(tri_index(tri_id++,
                    first_row,
                    last_row,
                    column == 0,
                    column == n_cols - col_skip - 1,
                    grid_index(row, column),
                    grid_index(row + row_skip, column),
                    grid_index(row, column + col_skip)
                ));
            }
            if (column != n_cols - col_skip - 1)// skip where thetha is pi. All those has one common point
            {
                triangles_grid.push_back(tri_index(tri_id++,
                    first_row,
                    last_row,
                    column == 0,
                    column == n_cols - col_skip - 1,
                    grid_index(row + row_skip, column + col_skip),
                    grid_index(row + row_skip, column),
                    grid_index(row, column + col_skip)
                ));
            }
        }
    }
}

void MeshIntersection::formPairsToCheck()
{
    check_pairs = std::vector<std::pair<uint, std::vector<uint>>>();
    auto to_check = std::vector<uint>();
    for (auto fit = triangles_grid.begin(); fit != triangles_grid.end(); fit++)
    {
        to_check.clear();
        auto tr1 = *fit;
        for (auto sit = fit; sit != triangles_grid.end(); sit++)
        {
            if (!hasCommonPoint(tr1, *sit))// check if this triangles does not have common points
            {
                to_check.push_back((*sit).id);
            }
        }
        check_pairs.emplace_back(tr1.id, to_check);
    }
}

bool MeshIntersection::hasCommonPoint(const tri_index& tr1, const tri_index& tr2)
{
    if (tr1.on_left_boundary && tr2.on_left_boundary || tr1.on_right_boundary && tr2.on_right_boundary)// skip when thetha is 0 or pi
        return true;
    //Check if triangles lies on the cyclic boundary
    if (tr1.on_upper_boundary && tr2.on_lower_boundary)
    {
        // check if each point is on upper boundary and shift to the last row
        if (tr1.A.row == 0)
        {
            const grid_index shiftA = grid_index(n_rows - 1, tr1.A.col);
            if (checkPoint(shiftA, tr2))
                return true;
        }
        if (tr1.B.row == 0)
        {
            const grid_index shiftB = grid_index(n_rows - 1, tr1.B.col);
            if (checkPoint(shiftB, tr2))
                return true;
        }
        if (tr1.C.row == 0)
        {
            const grid_index shiftC = grid_index(n_rows - 1, tr1.C.col);
            if (checkPoint(shiftC, tr2))
                return true;
        }

    }
    else if (tr1.on_lower_boundary && tr2.on_upper_boundary)
    {
        // check if each point is on lower boundary and shift to the last row
        if (tr1.A.row == n_rows - 1)
        {
            const grid_index shiftA = grid_index(0, tr1.A.col);
            if (checkPoint(shiftA, tr2))
                return true;
        }
        if (tr1.B.row == n_rows - 1)
        {
            const grid_index shiftB = grid_index(0, tr1.B.col);
            if (checkPoint(shiftB, tr2))
                return true;
        }
        if (tr1.C.row == n_rows - 1)
        {
            const grid_index shiftC = grid_index(0, tr1.C.col);
            if (checkPoint(shiftC, tr2))
                return true;
        }

    }

    return checkPoint(tr1.A, tr2) || checkPoint(tr1.B, tr2) || checkPoint(tr1.C, tr2);
}

bool MeshIntersection::checkPoint(const grid_index& g_i, const tri_index& tr)
{
    return g_i == tr.A || g_i == tr.B || g_i == tr.C;
}

bool MeshIntersection::hasSelfIntersection(const arma::Cube<double>& mesh)
{
    //std::vector<std::future<bool>> threads_res = std::vector<std::future<bool>>();
    //for(auto& pair : check_pairs)
    //    threads_res.push_back(std::async(std::launch::async, &MeshIntersection::oneAndManyIntersect, mesh, triangles_grid, pair));
    //std::cout << "launched\n";
    //for (auto& res : threads_res)
    //{
    //    if (res.get())
    //        return true;
    //}
    for (auto& pair : check_pairs)
        if (MeshIntersection::oneAndManyIntersect(mesh, triangles_grid, pair))
            return true;
    return false;
}

void MeshIntersection::getTriangle(const arma::Cube<double>& mesh, Triangle& triangle, const tri_index& index)
{
    const arma::dmat& x_mat = mesh.slice(0);
    const arma::dmat& y_mat = mesh.slice(1);
    const arma::dmat& z_mat = mesh.slice(2);
    triangle = Triangle(
        Point(x_mat(index.A.row, index.A.col), y_mat(index.A.row, index.A.col), z_mat(index.A.row, index.A.col)),
        Point(x_mat(index.B.row, index.B.col), y_mat(index.B.row, index.B.col), z_mat(index.B.row, index.B.col)),
        Point(x_mat(index.C.row, index.C.col), y_mat(index.C.row, index.C.col), z_mat(index.C.row, index.C.col)));
}

bool MeshIntersection::oneAndManyIntersect(
    const arma::Cube<double>& mesh,
    const std::vector<tri_index>& tri_indeces,
    const std::pair<uint, std::vector<uint>>& to_check)
{

    Triangle tr1, tr2;

    if (to_check.second.empty())
        return false;
    auto t1 = std::find_if(tri_indeces.begin(), tri_indeces.end(), [&](const tri_index ind) { return ind.id == to_check.first; });
    MeshIntersection::getTriangle(mesh, tr1, *t1);

    for (auto cIt = to_check.second.begin(); cIt != to_check.second.end(); cIt++)
    {
        auto t2 = std::find_if(tri_indeces.begin(), tri_indeces.end(), [&](const tri_index ind) { return ind.id == (*cIt); });
        MeshIntersection::getTriangle(mesh, tr2, *t2);

        if (CGAL::do_intersect(tr1, tr2))
        {
            //std::cout << std::format("Intersect id's {} and {}\n", to_check.first, (*cIt));
            return true;
        }
    }
    return false;
}
