#include "api/libraryModel_genericApi.hpp"
#include "api/libraryModel_modelApi.hpp"

int main ()
{
    //Create Model Factory and Model Package
    std::shared_ptr<libraryModel_ecoreFactory> factory = libraryModel_ecoreFactory::eInstance();
    std::shared_ptr<libraryModel_ecorePackage> package = libraryModel_ecorePackage::eInstance();

    //Create APIs
    crow::SimpleApp genericApp;
    crow::SimpleApp modelApp;
    std::shared_ptr<libraryModel_genericApi> genericApi = libraryModel_genericApi::eInstance(factory, package, genericApp);
    std::shared_ptr<libraryModel_modelApi> modelApi = libraryModel_modelApi::eInstance(factory, package, modelApp);
    auto genericOutput = genericApp.port(8080).multithreaded().run_async();
    auto modelOutput = modelApp.port(8081).multithreaded().run_async();

    return 0;
}