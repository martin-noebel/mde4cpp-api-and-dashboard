#include <iostream>
#include "libraryModel_ecore/libraryModel_ecoreFactory.hpp"
#include "libraryModel_ecore/Book.hpp"
#include "libraryModel_ecore/Author.hpp"
#include "libraryModel_ecore/LibraryModel.hpp"
#include "libraryModel_ecore/NamedElement.hpp"
#include "libraryModel_ecore/Picture.hpp"
#include "crow/crow_all.h"

using namespace libraryModel_ecore;

std::map<std::string,std::shared_ptr<ecore::EObject>> objects{};

int main ()
{
    //Create Model Factory
    std::shared_ptr<libraryModel_ecoreFactory> factory = libraryModel_ecoreFactory::eInstance();

    //Base Route
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Mde4cpp-Api for libraryModel_ecore";
    });

    //Create function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Post)([factory](const crow::request& request, const std::string& className, const std::string& objectName){
        if(objects.find(objectName) != objects.end()){
            return crow::response(400, "Object already exists!");
        };
        auto object = factory->create(className);
        objects[objectName] = object;
        return crow::response(201);
    });

    //Read function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Get)([factory](const std::string& className, const std::string& objectName){
        if(objects.find(objectName) == objects.end()){
            return crow::response(404);
        }
        auto object = objects[objectName];
        auto result = factory->convertToString(nullptr, object->eAllContents());
        return crow::response(200, result);
    });

    //Update function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Put)([](const crow::request& request, const std::string& className, const std::string& objectName){
        if(objects.find(objectName) == objects.end()){
            return crow::response(404);
        }
        auto newName = crow::json::load(request.body)["newName"].s();
        auto entry = objects.extract(objectName);
        entry.key() = newName;
        objects.insert(std::move(entry));
        return crow::response(204);
    });

    //Delete function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Delete)([](const std::string& className, const std::string& objectName){
        if(objects.find(objectName) == objects.end()){
            return crow::response(404);
        }
        objects.erase(objects.find(objectName));
        return crow::response(204);
    });

    app.port(8080).multithreaded().run();
    return 0;
}