#include <ceres/ceres.h> 
#include <glog/logging.h>

struct CostFunctor{
    template<typename T>
    bool operator()(const T* const x, T* residual) const {
        residual[0] = 10.0 - x[0];
        return true;
    }
};

int main(int argc, char** argv){
    google::InitGoogleLogging(argv[0]);

    double x = 0.5; 
    const double initial_x = x; 
    ceres::Problem problem;
    
    ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
    problem.AddResidualBlock(cost_function, nullptr, &x);

    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary; 
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << std::endl;
    std::cout << "x: " << initial_x << "-->" << x << std::endl;
    return 0;

}