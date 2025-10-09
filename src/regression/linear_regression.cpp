#include <cmath>      // powers bb
#include <numeric>    // for std::accumulate 
#include <stdexcept>  // std::runtime_error 

#include "../../include/regression/linear_regression.h"


// constructor
LinearRegression::LinearRegression():
  slope_(0.0),
  intercept_(0.0),
  fitted_(false) {}


// train model on x, y data
void LinearRegression::fit(const std::vector<double>& x, const std::vector<double>& y) {
  if (x.size() != y.size() || x.empty()) {
    throw std::runtime_error("Input vectors must be the same, non-zero, length.");
  }

  const size_t n = x.size();

  // compute means 
  double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / n;
  double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / n;

  // compute slope and intercept 
  double numerator = 0.0;
  double denominator = 0.0;

  for (size_t i = 0; i < n; ++i) {
    numerator   += (x[i] - mean_x) * (y[i] - mean_y);
    denominator += (x[i] - mean_x) * (x[i] - mean_x);
  }

  // assign attributes
  slope_ = numerator / denominator;
  intercept_ = mean_y - (slope_ * mean_x);
  fitted_ = true;
}


// predict y given x
double LinearRegression::predict(double x_value) const {
  if (!fitted_) {
    throw std::runtime_error("Model must be fit before prediction.");
  }

  return (x_value * slope_) + intercept_;
}


// predict a vector of y's given a vector of x's 
std::vector<double> LinearRegression::predict(const std::vector<double>& x_values) const {
  if (!fitted_) {
    throw std::runtime_error("Model must be fit before prediction.");
  }
  
  // create output vector and allocate enough memory for it
  std::vector<double> y_values;
  y_values.reserve(x_values.size());

  for (double x : x_values){ y_values.push_back(predict(x)); }

  return y_values;
}


// compute the mean squared error (MAE) for the model
double LinearRegression::mae(const std::vector<double>& x_values, const std::vector<double>& y_values) const {
  double sum = 0.0;

  for (int i=0; i < x_values.size(); ++i) {
    sum += std::abs(predict(x_values[i]) - y_values[i]);
  }

  return sum / x_values.size();
}


// compute the mean squared error (MAE) for the model
double LinearRegression::mse(const std::vector<double>& x_values, const std::vector<double>& y_values) const {
  double sum = 0.0;

  for (int i=0; i < x_values.size(); ++i) {
    sum += std::pow(std::abs(predict(x_values[i]) - y_values[i]), 2);
  }

  return sum / x_values.size();
}


// compute the mean squared error (MAE) for the model
double LinearRegression::rmse(const std::vector<double>& x_values, const std::vector<double>& y_values) const {
  double sum = 0.0;

  for (int i=0; i < x_values.size(); ++i) {
    sum += std::pow(std::abs(predict(x_values[i]) - y_values[i]), 2);
  }

  return std::sqrt(sum/x_values.size());
}


