#include <armadillo>
#include <carma/carma.h>

#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

// compute outside indices of a vector as a mirror
arma::ivec locus_neigh(int size, int leg)
{
    arma::ivec res(size + 2 * leg);
    for (int i = 0; i < res.n_elem; ++i)
    {
        if (i < leg)
            res(i) = leg - i - 1;
        else if (i < size + leg)
            res(i) = i - leg;
        else
            res(i) = 2 * size + leg - i - 1;
    }
    return res;
}

// Code adapted from the sits R package.
// You can learn more using the following link:
//  https://github.com/e-sensing/sits/blob/master/src/smooth.cpp
arma::mat bayes_smooth(const arma::mat &logits,
                       const int &nrows,
                       const int &ncols,
                       const int &window_size,
                       const arma::vec &smoothness,
                       const double &neigh_fraction)
{
    // initialize result vectors
    arma::mat res(logits.n_rows, logits.n_cols);
    arma::vec neigh(window_size * window_size);
    // compute window leg
    int leg = window_size / 2;
    // compute locus mirror
    arma::ivec loci = locus_neigh(nrows, leg);
    arma::ivec locj = locus_neigh(ncols, leg);
    // compute number of neighbors to be used
    int neigh_high = std::ceil(neigh_fraction * window_size * window_size);
    // compute values for each pixel
    for (int i = 0; i < nrows; ++i)
    {
        for (int j = 0; j < ncols; ++j)
        {
            // for all bands
            for (int band = 0; band < logits.n_cols; ++band)
            {
                // compute the neighborhood
                for (int wi = 0; wi < window_size; ++wi)
                {
                    for (int wj = 0; wj < window_size; ++wj)
                    {
                        neigh(wi * window_size + wj) =
                            logits(loci(wi + i) * ncols + locj(wj + j), band);
                    }
                }
                if (neigh_fraction < 1.0)
                {
                    // Sort the neighbor logit values
                    neigh = arma::sort(neigh, "descend");
                }
                // Create a vector to store the highest values
                arma::vec high_values(neigh_high);
                // copy the highest values to the new vector
                int nh = 0;
                for (auto it = neigh.begin(); it != neigh.begin() + neigh_high; ++it)
                {
                    high_values(nh++) = (*it);
                }
                // get the estimates for prior
                // normal with mean m0 and variance s0
                double s0 = var(high_values);
                double m0 = mean(high_values);
                // get the current value
                double x0 = logits(i * ncols + j, band);
                // weight for Bayesian estimator
                double w = s0 / (s0 + smoothness(band));
                // apply Bayesian smoother
                res(i * ncols + j, band) = w * x0 + (1 - w) * m0;
            }
        }
    }
    return res;
}

PYBIND11_MODULE(_smoother, m)
{
    // Optional docstring
    m.doc() = "(Internal) Spatial Smoothing Functions";

    m.def("bayes", &bayes_smooth, "Bayes Smooth");
}
