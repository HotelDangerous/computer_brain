#include <iostream>
#include <vector>
#include <cmath>

#include "../include/regression/linear_regression.h"


bool approximatelyEqual(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

void test(){
    std::cout << "Running LinearRegression tests...\n";

    // Test 1: Perfect line y = 2x + 1
    {
        std::vector<double> x = {1, 2, 3, 4, 5};
        std::vector<double> y = {3, 5, 7, 9, 11}; // exactly 2x + 1

        LinearRegression model;
        model.fit(x, y);

        bool slope_ok = approximatelyEqual(model.slope(), 2.0);
        bool intercept_ok = approximatelyEqual(model.intercept(), 1.0);
        bool predict_ok = approximatelyEqual(model.predict(6), 13.0);

        if (slope_ok && intercept_ok && predict_ok) {
            std::cout << "Test 1 passed ✅\n";
        } else {
            std::cout << "Test 1 failed ❌\n";
            std::cout << "Slope: " << model.slope() << "\n";
            std::cout << "Intercept: " << model.intercept() << "\n";
            std::cout << "Predict(6): " << model.predict(6) << "\n";
        }
    }

    // Test 2: Horizontal line y = 4
    {
        std::vector<double> x = {1, 2, 3, 4, 5};
        std::vector<double> y = {4, 4, 4, 4, 4};

        LinearRegression model;
        model.fit(x, y);

        bool slope_ok = approximatelyEqual(model.slope(), 0.0);
        bool intercept_ok = approximatelyEqual(model.intercept(), 4.0);

        if (slope_ok && intercept_ok) {
            std::cout << "Test 2 passed ✅\n";
        } else {
            std::cout << "Test 2 failed ❌\n";
            std::cout << "Slope: " << model.slope() << "\n";
            std::cout << "Intercept: " << model.intercept() << "\n";
        }
    }

    // Test 3: MAE, MSE, RMSE all 0 
    {
        std::vector<double> x = {1, 2, 3, 4, 5};
        std::vector<double> y = {3, 5, 7, 9, 11}; // exactly 2x + 1
    
        LinearRegression model;
        model.fit(x,y);
        
        bool mae_ok = approximatelyEqual(model.mae(x, y), 0.0);
        bool mse_ok = approximatelyEqual(model.mse(x, y), 0.0);
        bool rmse_ok = approximatelyEqual(model.rmse(x, y), 0.0);
    
        if (mae_ok) {
          std::cout << "Test 3 passed ✅\n";
        } else {
            std::cout << "Test 2 failed ❌\n";
            std::cout << "MAE: " << model.mae(x, y) << "\n";
            std::cout << "MSE: " << model.mse(x, y) << "\n";
            std::cout << "RMSE: " << model.rmse(x, y) << "\n";
        }
    }
}
