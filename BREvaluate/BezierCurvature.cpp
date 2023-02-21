#include "BezierCurvature.h"

BezierCurvature::BezierCurvature(uint curve_power, arma::drowvec t, double threshold):
	threshold(threshold),
	curve_power(curve_power),
	d_curve(Bezier(curve_power-1,t)),
	dd_curve(Bezier(curve_power-2,t))
{
}

arma::drowvec BezierCurvature::curvature(const arma::dmat& points)
{
	arma::drowvec res = arma::drowvec(points.n_rows);
	// get first and second derivatives
	arma::dmat d = d_curve((curve_power)*arma::diff(points, 1, 0));
	arma::dmat dd = dd_curve((curve_power - 1) * arma::diff(points, 2, 0));
	//auto resIt = res.begin();
	//auto drIt = d.begin_row(0);
	//auto ddrIt = dd.begin_row(0);

	//for (; drIt != d.end_row(points.n_rows) && ddrIt!= dd.end_row(points.n_rows); drIt++ , ddrIt++, resIt++)
	//{
	//	(*resIt) = arma::norm(arma::cross((drIt)., *ddrIt)) / pow(arma::norm(*drIt), 3);
	//}
	for (int i = 0; i < points.n_rows; i++)
	{
		res(i) = arma::norm(arma::cross(d.row(i), dd.row(i))) / pow(arma::norm(d.row(i)), 3);
	}
	return res;
	//return arma::norm(arma::cross(d.each_row(), dd.each_row())) / pow(arma::norm(d), 3);
}

bool BezierCurvature::curvatureCheck(const arma::dmat& points)
{
	// get first and second derivatives
	arma::dmat d = d_curve((curve_power)*arma::diff(points, 1, 0));
	arma::dmat dd = dd_curve((curve_power - 1) * arma::diff(points, 2, 0));
	for (int i = 0; i < points.n_rows; i++)
	{
		double val = arma::norm(arma::cross(d.row(i), dd.row(i))) / pow(arma::norm(d.row(i)), 3);
		if (val > threshold)
			return false;
	}
	return true;
}

bool BezierCurvature::checkMesh(const arma::dcube& mesh)
{
	auto Pmat = arma::dmat(mesh.n_rows, 3);
	arma::dcube temp;
	//// check curvature for fixed thetha. skip poles
	//for (unsigned int i = 1; i < mesh.n_cols - 1; ++i)
	//{
	//	temp = mesh.tube(arma::span::all, arma::span(i));
	//	Pmat.submat(arma::span::all, arma::span(0)) = temp.slice(0);
	//	Pmat.submat(arma::span::all, arma::span(1)) = temp.slice(1);
	//	Pmat.submat(arma::span::all, arma::span(2)) = temp.slice(2);
	//	if (!curvatureCheck(Pmat))
	//		return false;
	//}
	//// check curvature for fixed phi
	//for (unsigned int i = 0; i < mesh.n_rows; ++i)
	//{
	//	temp = mesh.tube(arma::span(i), arma::span::all);
	//	Pmat.submat(arma::span::all, arma::span(0)) = temp.slice(0).t();
	//	Pmat.submat(arma::span::all, arma::span(1)) = temp.slice(1).t();
	//	Pmat.submat(arma::span::all, arma::span(2)) = temp.slice(2).t();

	//	if (!curvatureCheck(Pmat))
	//		return false;
	//}
		// check curvature for fixed thetha. skip poles
	for (unsigned int i = 1; i < mesh.n_cols - 1; i+=2)
	{
		temp = mesh.tube(arma::span::all, arma::span(i));
		Pmat.submat(arma::span::all, arma::span(0)) = temp.slice(0);
		Pmat.submat(arma::span::all, arma::span(1)) = temp.slice(1);
		Pmat.submat(arma::span::all, arma::span(2)) = temp.slice(2);
		if (!curvatureCheck(Pmat))
			return false;
	}
	// check curvature for fixed phi
	for (unsigned int i = 0; i < mesh.n_rows; i+=2)
	{
		temp = mesh.tube(arma::span(i), arma::span::all);
		Pmat.submat(arma::span::all, arma::span(0)) = temp.slice(0).t();
		Pmat.submat(arma::span::all, arma::span(1)) = temp.slice(1).t();
		Pmat.submat(arma::span::all, arma::span(2)) = temp.slice(2).t();

		if (!curvatureCheck(Pmat))
			return false;
	}
	return true;
}
