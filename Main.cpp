#include "libraryModel_ecoreApi.hpp"

int main ()
{
    //Create Model Factory and Model Package
    std::shared_ptr<libraryModel_ecoreFactory> factory = libraryModel_ecoreFactory::eInstance();
    std::shared_ptr<libraryModel_ecorePackage> package = libraryModel_ecorePackage::eInstance();

    //Create Model Api
    std::shared_ptr<libraryModel_ecoreApi> api = libraryModel_ecoreApi::eInstance(factory, package);

    return 0;
}