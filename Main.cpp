#include "include/crow_all.h"
#include <string>
#include "ecore/ecoreFactory.hpp"
#include "ecore/ecorePackage.hpp"
#include "ecore/EAnnotation.hpp"
#include "ecore/EAttribute.hpp"
#include "ecore/EClass.hpp"
#include "ecore/EReference.hpp"
#include "ecore/EStringToStringMapEntry.hpp"
#include "ecore/EStructuralFeature.hpp"
using namespace ecore;

int main()
{
    std::shared_ptr<ecorePackage> package = ecorePackage::eInstance();
    std::shared_ptr<ecoreFactory> factory = ecoreFactory::eInstance();
    std::shared_ptr<EPackage> model = factory->createEPackage();
    crow::SimpleApp app;
    //define your endpoint at the root directory
    CROW_ROUTE(app, "/add/<string>")([factory, model](std::string className){
        std::shared_ptr<EClass> eClass = factory->createEClass_as_eClassifiers_in_EPackage(model);
        eClass->setName(className);
        return crow::response();
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.port(8080).multithreaded().run();
}
