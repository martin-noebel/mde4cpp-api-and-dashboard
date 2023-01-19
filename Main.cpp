#include "api/libraryModel_genericApi.hpp"
#include "api/libraryModel_modelApi.hpp"
#include "api/libraryModel_mixedApi.hpp"

int main ()
{
    //Create Factories and Packages
    std::shared_ptr<libraryModel_ecoreFactory> libraryFactory = libraryModel_ecoreFactory::eInstance();
    std::shared_ptr<libraryModel_ecorePackage> libraryPackage = libraryModel_ecorePackage::eInstance();
    std::shared_ptr<ecoreFactory> ecoreFactory = ecore::ecoreFactory::eInstance();
    std::shared_ptr<ecorePackage> ecorePackage = ecore::ecorePackage::eInstance();

    //Create APIs
    std::shared_ptr<libraryModel_mixedApi> mixedApi = libraryModel_mixedApi::eInstance(libraryFactory, libraryPackage);
    //std::shared_ptr<libraryModel_modelApi> modelApi = libraryModel_modelApi::eInstance(libraryFactory, libraryPackage);
    //std::shared_ptr<libraryModel_genericApi> genericApi = libraryModel_genericApi::eInstance(ecoreFactory, ecorePackage);

    return 0;
}