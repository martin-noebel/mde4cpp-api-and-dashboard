#include "api/GenericApi.hpp"
#include "api/ModelApi.hpp"
#include "libraryModel_ecore/libraryModel_ecorePlugin.hpp"

int main ()
{
    //Create Factories and Packages
    std::shared_ptr<libraryModel_ecoreFactory> factory = libraryModel_ecoreFactory::eInstance();
    std::shared_ptr<libraryModel_ecorePackage> package = libraryModel_ecorePackage::eInstance();
    std::shared_ptr<MDE4CPPPlugin> plugin = libraryModel_ecorePlugin::eInstance();

    //Create API
    std::shared_ptr<ModelApi> modelApi = ModelApi::eInstance(factory, package);
    //std::shared_ptr<GenericApi> genericApi = GenericApi::eInstance(plugin);

    return 0;
}