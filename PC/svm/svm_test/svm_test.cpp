#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <fstream>

#include "common.h"
#include "print_vector.cpp"

//see https://docs.opencv.org/2.4/modules/ml/doc/support_vector_machines.html#cvsvm-predict for reference

using namespace cv;
using json = nlohmann::json;

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout << "Usage:\n./svm_test <trained svm file> <testing dataset>\n";
        exit(1);
    }

    std::string svmFile(argv[1]);
    std::string testing_dataset(argv[2]);

    CvSVM svm;
    std::cout << "Loading SVM from file " << svmFile  << "... ";
    svm.load(svmFile.c_str());

    std::cout << "SUCCESS!\n";

    for (int i = 0; i < svm.get_support_vector_count(); ++i)
    {
        auto v = svm.get_support_vector(i);
        std::cout << "Support vector #" << i << " " << *v << "\n";
    }

    // Read input training data to JSON object
    std::ifstream test_data(testing_dataset);
    json test_data_json;
    test_data >> test_data_json;

    std::cout << "Test points: " << test_data_json.size() << "\n";
    std::cout << "Testing trained svm... ";
    std::cout << (test_svm_with_data(svm, test_data_json) ? "OK" : "NOT OK") << std::endl;

    return 0;
}
