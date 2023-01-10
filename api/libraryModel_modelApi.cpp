#define CROW_JSON_USE_MAP
#include "libraryModel_modelApi.hpp"

std::shared_ptr<libraryModel_modelApi> libraryModel_modelApi::eInstance(std::shared_ptr<libraryModel_ecoreFactory> &factory, std::shared_ptr<libraryModel_ecorePackage> &package, crow::SimpleApp& app) {
    static std::shared_ptr<libraryModel_modelApi> instance = std::make_shared<libraryModel_modelApi>(libraryModel_modelApi(factory, package, app));
    return instance;
}

libraryModel_modelApi::libraryModel_modelApi(std::shared_ptr<libraryModel_ecoreFactory>& factory, std::shared_ptr<libraryModel_ecorePackage>& package, crow::SimpleApp& app) {
    m_factory = factory;
    m_package = package;

    //Base Route
    CROW_ROUTE(app, "/")([](){
        return "Model-specific API for MDE4CPP";
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
}

Any libraryModel_modelApi::readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass){
    return nullptr;
}

crow::json::wvalue libraryModel_modelApi::writeValue(Any object){
    return nullptr;
}