#include "EvaluateCpu.h"

EvaluateCpu::EvaluateCpu(
    std::shared_ptr<ProblemHelper> helper,
    std::shared_ptr<ErrorFunction> err,
    std::unique_ptr<MeshIntersection> inter,
    std::unique_ptr<BezierCurvature> curv):
    helper(helper),
    error(err),
    data(helper->getProblemData()),
    intersection(std::move(inter)),
    curvature(std::move(curv))
{
    //auto collocation = this->helper->getCollocation();

    //auto boundary = collocation.getBoundary();
    //auto boundary_meshgrid = ProblemHelper::meshGrid(boundary.getThetha(), boundary.getPhi());


    //boundary_cyclic = collocation.getBoundaryCyclic();
    //boundary_cyclic_meshgrid = ProblemHelper::meshGrid(boundary_cyclic.getThetha(), boundary_cyclic.getPhi());

    //sources = collocation.getSources();


    //Gamma1 = this->helper->getGamma1();
    //Gamma2Mesh = this->helper->getGamma2()(boundary_meshgrid.slice(0), boundary_meshgrid.slice(1));
    //G2Distance = sqrt(sum(arma::pow(Gamma2Mesh, 2), 2));
    auto boundary_cyclic = data->getCollocation().getBoundaryCyclic();
    boundary_cyclic_meshgrid = ProblemHelper::meshGrid(boundary_cyclic.getThetha(), boundary_cyclic.getPhi());

    auto boundary_meshgrid = ProblemHelper::meshGrid(data->getBoundaryTheta(), data->getBoundaryPhi());
    auto G2Mesh = data->getG2Boundary()(boundary_meshgrid.slice(0), boundary_meshgrid.slice(1));
    G2Distance = sqrt(sum(arma::pow(G2Mesh, 2), 2));

    f_exact = data->getG2TestConditionValues();


}

double EvaluateCpu::evaluateOne(const std::weak_ptr<Individuum> individuum)
{
    auto& tree = individuum.lock()->getTree();
    auto r_boundary_cyclic = tree->evaluate(boundary_cyclic_meshgrid.slice(0), boundary_cyclic_meshgrid.slice(1));// mesh is cyclyc there!
    auto G1_mesh_cyclic = data->getG1Boundary()(r_boundary_cyclic, boundary_cyclic_meshgrid.slice(0), boundary_cyclic_meshgrid.slice(1));

    if(!G1_mesh_cyclic.is_finite())// check if all elements are finite
        return INVALID_FITNESS;

    if (arma::all(abs(vectorise(G1_mesh_cyclic)) < DBL_EPSILON)) // All are zeros.
        return INVALID_FITNESS;

    if (!periodic_mesh::isPeriodic(G1_mesh_cyclic))  // check if mesh is closed surface
        return INVALID_FITNESS;

    arma::dcube G1_mesh = G1_mesh_cyclic(arma::span(0, G1_mesh_cyclic.n_rows - 2), arma::span::all, arma::span::all);// skip cyclic values


    arma::umat points_inside = (arma::dmat)sqrt(sum(arma::pow(G1_mesh, 2), 2)) < G2Distance;
    if (!arma::all(vectorise(points_inside)))// check if all points inside outter mesh
    {
        return INVALID_FITNESS;//TODO: check
    }


 //   if (!curvature->checkMesh(G1_mesh)) // check curvature
 //   {
 ///*       std::cout << std::format("Curvature failed for tree: {}\n\n", tree->print());
 //       curvature->checkMesh(G1_mesh);*/
 //       return INVALID_FITNESS;
 //   }
    //try
    //{
    //    if (intersection->hasSelfIntersection(G1_mesh_cyclic))    // check self-intersections
    //    {
    //        //std::cout << std::format("Intersection test failed for : {}\n\n", tree->print());
    //        return INVALID_FITNESS;
    //    }
    //}
    //catch (std::exception e)
    //{
    //    return INVALID_FITNESS;
    //}


    // after boundary satisfiy previous conditions we can calculate the error
    arma::dcolvec r_sources = tree->evaluate(data->getSourcesTheta(), data->getSourcesPhi()).as_col();// TODO: change
    auto G1_sources = data->getG1Boundary()(r_sources, data->getSourcesTheta(), data->getSourcesPhi());

    arma::dcube G1_boundary = arma::dcube(G1_mesh.n_rows, 1, 3);
    G1_boundary.slice(0) = G1_mesh.slice(0).diag();
    G1_boundary.slice(1) = G1_mesh.slice(1).diag();
    G1_boundary.slice(2) = G1_mesh.slice(2).diag();


    arma::dcolvec f_approx;

    if (!helper->uOnG2(G1_boundary, G1_sources, f_approx))
    {
        std::cout << std::format("No valid solution for tree: {}\n\n", tree->print());
        return INVALID_FITNESS;
    }
    return this->error->evaluate(f_exact, f_approx);
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
