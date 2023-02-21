#include "EvaluateCpu.h"

EvaluateCpu::EvaluateCpu(
    std::unique_ptr<ProblemHelper> helper,
    std::unique_ptr<MeshIntersection> inter,
    std::unique_ptr<BezierCurvature> curv):
    helper(std::move(helper)),
    intersection(std::move(inter)),
    curvature(std::move(curv))
{
    auto collocation = this->helper->getCollocation();

    auto boundary = collocation.getBoundary();
    auto boundary_meshgrid = ProblemHelper::meshGrid(boundary.getThetha(), boundary.getPhi());


    boundary_cyclic = collocation.getBoundaryCyclic();
    boundary_cyclic_meshgrid = ProblemHelper::meshGrid(boundary_cyclic.getThetha(), boundary_cyclic.getPhi());

    sources = collocation.getSources();


    Gamma1 = this->helper->getGamma1();
    Gamma2Mesh = this->helper->getGamma2()(boundary_meshgrid.slice(0), boundary_meshgrid.slice(1));
    G2Distance = sqrt(sum(arma::pow(Gamma2Mesh, 2), 2));

}

double EvaluateCpu::evaluateOne(const std::weak_ptr<Individuum> individuum)
{
    auto& tree = individuum.lock()->getTree();
    auto r_boundary_cyclic = tree->evaluate(boundary_cyclic_meshgrid.slice(0), boundary_cyclic_meshgrid.slice(1));// mesh is cyclyc there!
    auto G1_mesh_cyclic = Gamma1(r_boundary_cyclic, boundary_cyclic_meshgrid.slice(0), boundary_cyclic_meshgrid.slice(1));
    //std::string tree_str= tree->print();
    //if (tree_str == "sqrt(thetha)")
    //{
    //    tree_str.c_str();
    //}
    if(!G1_mesh_cyclic.is_finite())// check if all elements are finite
        return INVALID_FITNESS;

    if (arma::all(abs(vectorise(G1_mesh_cyclic)) < DBL_EPSILON)) // All are zeros.
        return INVALID_FITNESS;

    //G1_mesh_cyclic.print("Mesh (cyclic)");
    if (!periodic_mesh::isPeriodic(G1_mesh_cyclic))  // check if mesh is closed surface
        return INVALID_FITNESS;

    //std::cout << std::format("Check tree: {}\n\n", tree->print());



    arma::dcube G1_mesh = G1_mesh_cyclic(arma::span(0, G1_mesh_cyclic.n_rows-2), arma::span(0, G1_mesh_cyclic.n_cols-2), arma::span::all);// skip cyclic values

    // check if mesh is in external boundary
    //arma::dmat G1_dist = sqrt(sum(arma::pow(G1_mesh, 2),2));// distance from origin to surface in each point
    //arma::dmat G2_dist = sqrt(sum(arma::pow(Gamma2Mesh, 2), 2));// distance from origin to surface in each point

    //std::cout << std::format("Tree: {}\n\n", tree->print());
    arma::umat points_inside = (arma::dmat)sqrt(sum(arma::pow(G1_mesh, 2), 2)) < G2Distance;
    if (!arma::all(vectorise(points_inside)))// check if all points inside outter mesh
    {
        return INVALID_FITNESS;//TODO: check
    }


    if (!curvature->checkMesh(G1_mesh)) // check curvature
    {
 /*       std::cout << std::format("Curvature failed for tree: {}\n\n", tree->print());
        curvature->checkMesh(G1_mesh);*/
        return INVALID_FITNESS;
    }
    try
    {
        if (intersection->hasSelfIntersection(G1_mesh))    // check self-intersections
        {
            //std::cout << std::format("Intersection test failed for : {}\n\n", tree->print());
            return INVALID_FITNESS;
        }
    }
    catch (std::exception e)
    {
        return INVALID_FITNESS;
    }


    // after boundary satisfiy previous conditions we can calculate the error

    arma::dcolvec r_sources = tree->evaluate(sources.getThetha(), sources.getPhi()).as_col();// TODO: change
    auto G1_sources = Gamma1(r_sources, sources.getThetha(), sources.getPhi());

    arma::dcube G1_boundary = arma::dcube(G1_mesh.n_rows, 1, 3);
    G1_boundary.slice(0) = G1_mesh.slice(0).diag();
    G1_boundary.slice(1) = G1_mesh.slice(1).diag();
    G1_boundary.slice(2) = G1_mesh.slice(2).diag();
    try
    {
        return helper->l2Norm(G1_boundary, G1_sources);
    }
    catch (std::exception e)
    {
        std::cout <<std::format("Tree: {}, error: {}\n\n",tree->print(), e.what());
        return INVALID_FITNESS;
    }
}

void EvaluateCpu::evaluatePopulation(Population& population)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& ind : population)
    {
        if (!ind->isCalculated())
        {
            ind->setFitness(evaluateOne(ind));
            ind->setCalculated(true);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Evaluated in : "
        << duration.count() << " milliseconds\n";
}