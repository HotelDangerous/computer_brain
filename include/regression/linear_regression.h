#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

class LinearRegression{
public:
  LinearRegression();

  // train model on x, y data
  void fit(const std::vector<double>& x, const std::vector<double>& y);

  // predict y given x
  double predict(double x_value) const;

  // predict a vector of y's given a vector of x's 
  std::vector<double> predict(const std::vector<double>& x_values) const;

  // compute the mean squared error (MAE) for the model
  double mae(const std::vector<double>& x, const std::vector<double>& y) const;

  // compute the mean squared error (MSE) for the model
  double mse(const std::vector<double>& x, const std::vector<double>& y) const;

  // compute the mean squared error (RMSE) for the model
  double rmse(const std::vector<double>& x, const std::vector<double>& y) const;

  // access slope and intercept attributes 
  double slope() const { return slope_; }
  double intercept() const { return intercept_; } 

private:
  double slope_;
  double intercept_;
  bool fitted_;
};

#endif // !LINEAR_REGRESSION_H
