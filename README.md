## smoother.py - Spatial Smoothing in Python

This Python import library makes it possible to use the spatial smoothing functions implemented by Rolf Simoes in the [SITS package](https://github.com/e-sensing/sits).

The original functions are all written in C++, using the package [armadillo](http://arma.sourceforge.net/). Then, through [carma](https://carma.readthedocs.io/), they were imported into Python and are available in this library.

Avaliable functions:

- `bayes_smoother`
- `kernel_smoother`
- `bilinear_smoother`
