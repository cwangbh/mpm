#ifndef MPM_QUADRILATERALSHAPEFN_H_
#define MPM_QUADRILATERALSHAPEFN_H_

#include <exception>
#include <iostream>

#include <Eigen/Dense>

#include "shapefn.h"

namespace mpm {

//! Quadrilateral shape function class derived from ShapeFn class
//! \brief Shape functions of a quadrilateral element
//! \tparam Tdim Dimension
template <unsigned Tdim>
class QuadrilateralShapeFn : public ShapeFn<Tdim> {

 public:
  //! Define a vector of size dimension
  using VectorDim = Eigen::Matrix<double, Tdim, 1>;

  //! constructor with number of shape functions
  QuadrilateralShapeFn(unsigned nfunctions) : mpm::ShapeFn<Tdim>(nfunctions) {
    static_assert(Tdim == 2, "Invalid dimension for a quadrilateral element");
    try {
      if (!(nfunctions == 4 || nfunctions == 8 || nfunctions == 9)) {
        throw std::runtime_error(
            "Specified number of shape functions is not defined");
      }
      shapefn_.resize(this->nfunctions_, 1);
      grad_shapefn_.resize(this->nfunctions_, Tdim);
    } catch (std::exception& exception) {
      std::cerr << exception.what() << '\n';
      std::abort();
    }
  }

  //! Evaluate shape functions at given local coordinates
  //! \param[in] xi given local coordinates
  Eigen::MatrixXd shapefn(const VectorDim& xi);

  //! Evaluate gradient of shape functions
  //! \param[in] xi given local coordinates
  Eigen::MatrixXd grad_shapefn(const VectorDim& xi);

 protected:
  // Number of functions
  using ShapeFn<Tdim>::nfunctions_;
  // Shape functions
  using ShapeFn<Tdim>::shapefn_;
  // Gradient shape functions
  using ShapeFn<Tdim>::grad_shapefn_;
};

}  // namespace mpm
#include "quad_shapefn.tcc"

#endif  // MPM_QUADRILATERALSHAPEFN_H_
