## smoother.py 🧹

Python package providing spatial smoothing methods for probability maps.

## Features

**Bayesian Smoothing**: [Bayes smoothing method](https://e-sensing.github.io/sitsbook/bayesian-smoothing-for-post-processing.html) using the C++ functions from the [sits](https://github.com/e-sensing/sits) R package.

## Installation

To install the package, you must have [Armadillo](https://arma.sourceforge.net/) installed, then you can use pip:

```bash
pip install git+https://github.com/m3nin0-labs/smoother.py
```

## Usage

The `smoother.py` package is designed for simplicity. It is simple to get started with it. Here's a quick example:

```python
import smoother

smoothed_data = smoother.bayes(your_numpy_array)
```

## Learn more

The smoothing methods implemented in this package uses the approach described in the [sits documentation](https://e-sensing.github.io/sitsbook/bayesian-smoothing-for-post-processing.html). This method helps in refining the probability maps by considering the spatial context of each pixel.

## Acknowledgments

We would like to thank the developers and contributors of the `sits` R package for their work on spatial smoothing methods for Earth observation data. Their comprehensive [documentation](https://e-sensing.github.io/sitsbook/) and methodologies have been invaluable in the development of `smoother.py`.

## Contributing

We welcome contributions! If you have suggestions for improvements or bug fixes, please feel free to fork the repository and submit a pull request.

## License

`smoother.py` is distributed under the MIT license. See LICENSE for more details.
