#include "include/crow_all.h"
#include "libraryModel_ecore/libraryModel_ecoreFactory.hpp"
#include "ecore/EObject.hpp"

using namespace ecore;
using namespace libraryModel_ecore;
using namespace std;

shared_ptr<libraryModel_ecoreFactory> factory = libraryModel_ecoreFactory::eInstance();
map<string,shared_ptr<EObject>> objects{};

int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Mde4cpp-Api and -Dashboard Home!!!";
    });
    CROW_ROUTE(app, "/objects").methods(crow::HTTPMethod::Get)([](){
        auto result = string();
        for(auto & object : objects){
            result.append(object.first + ",");
        }
        if(!result.empty()){
            result.pop_back();
        }
        return crow::response(200, result);
    });
    CROW_ROUTE(app, "/objects/<string>").methods(crow::HTTPMethod::Get)([](string objectName){
        if(objects.find(objectName) == objects.end()){
            return crow::response(404);
        }
        auto object = objects[objectName];
        auto result = factory->convertToString(nullptr, object->eAllContents());
        return crow::response(200, result);
    });
    CROW_ROUTE(app, "/objects/<string>").methods(crow::HTTPMethod::Post)([](const crow::request& request, string objectName){
        if(objects.find(objectName) != objects.end()){
            return crow::response(400, "Object already exists!");
        }
        auto className = crow::json::load(request.body)["class"].s();
        auto object = factory->create(className);
        objects[objectName] = object;
        auto result = factory->convertToString(nullptr, object->eAllContents());
        return crow::response(201, result);
    });
    CROW_ROUTE(app, "/objects/<string>").methods(crow::HTTPMethod::Delete)([](string objectName){
        if(objects.find(objectName) == objects.end()){
            return crow::response(404);
        }
        objects.erase(objects.find(objectName));
        return crow::response(204);
    });
    CROW_ROUTE(app, "/objects/<string>").methods(crow::HTTPMethod::Put)([](const crow::request& request, string objectName){
        if(objects.find(objectName) == objects.end()){
            return crow::response(404);
        }
        auto newName = crow::json::load(request.body)["newName"].s();
        auto entry = objects.extract(objectName);
        entry.key() = newName;
        objects.insert(std::move(entry));
        return crow::response(204);
    });

    app.port(8080).multithreaded().run();
}
