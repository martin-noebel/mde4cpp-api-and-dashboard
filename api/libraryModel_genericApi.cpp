#define CROW_JSON_USE_MAP
#include "libraryModel_genericApi.hpp"

std::shared_ptr<libraryModel_genericApi> libraryModel_genericApi::eInstance(std::shared_ptr<ecoreFactory> &factory, std::shared_ptr<ecorePackage> &package) {
    static std::shared_ptr<libraryModel_genericApi> instance = std::make_shared<libraryModel_genericApi>(libraryModel_genericApi(factory, package));
    return instance;
}

libraryModel_genericApi::libraryModel_genericApi(std::shared_ptr<ecoreFactory>& factory, std::shared_ptr<ecorePackage>& package) {
    m_factory = factory;
    m_package = package;
    crow::SimpleApp app;

    //Base Route
    CROW_ROUTE(app, "/")([](){
        return "Generic API for MDE4CPP";
    });

    //Create function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Post)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        return crow::response(201);
    });

    //Read function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Get)([this](const std::string& className, const std::string& objectName){
        return crow::response(200);
    });

    //Update function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Put)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        return crow::response(200);
    });

    //Delete function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Delete)([this](const std::string& className, const std::string& objectName){
        return crow::response(204);
    });

    app.port(8080).multithreaded().run_async();
}

std::shared_ptr<ecore::EObject> libraryModel_genericApi::readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass){
    return nullptr;
}

crow::json::wvalue libraryModel_genericApi::writeValue(const std::shared_ptr<ecore::EObject>& object){
    return nullptr;
}