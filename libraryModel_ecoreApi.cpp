#define CROW_JSON_USE_MAP
#include "libraryModel_ecoreApi.hpp"

std::shared_ptr<libraryModel_ecoreApi> libraryModel_ecoreApi::eInstance(std::shared_ptr<libraryModel_ecoreFactory> &factory, std::shared_ptr<libraryModel_ecorePackage> &package) {
    static std::shared_ptr<libraryModel_ecoreApi> instance = std::make_shared<libraryModel_ecoreApi>(libraryModel_ecoreApi(factory, package));
    return instance;
}

libraryModel_ecoreApi::libraryModel_ecoreApi(std::shared_ptr<libraryModel_ecoreFactory>& factory, std::shared_ptr<libraryModel_ecorePackage>& package) {
    m_factory = factory;
    m_package = package;
    //Base Route
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Mde4cpp-Api for libraryModel_ecore";
    });

    //Create function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Post)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) != m_objects.end()){
            return crow::response(400, "Object already exists!");
        }
        auto object = readValue(crow::json::load(request.body), m_factory->create(className)->eClass());
        m_objects[objectName] = object;
        return crow::response(201);
    });

    //Read function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Get)([this](const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        auto result = writeValue(m_objects[objectName]);
        return crow::response(200, result);
    });

    //Update function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Put)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        auto newName = crow::json::load(request.body)["newName"].s();
        auto entry = m_objects.extract(objectName);
        entry.key() = newName;
        m_objects.insert(std::move(entry));
        return crow::response(204);
    });

    //Delete function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Delete)([this](const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        m_objects.erase(m_objects.find(objectName));
        return crow::response(204);
    });

    app.port(8080).multithreaded().run();
}

std::shared_ptr<ecore::EObject> libraryModel_ecoreApi::readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass){
    return nullptr;
}

crow::json::wvalue libraryModel_ecoreApi::writeValue(const std::shared_ptr<ecore::EObject>& object){
    return nullptr;
}