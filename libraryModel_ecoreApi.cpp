#define CROW_JSON_USE_MAP
#include "libraryModel_ecoreApi.hpp"

std::shared_ptr<libraryModel_ecoreApi> libraryModel_ecoreApi::eInstance(std::shared_ptr<libraryModel_ecoreFactory> &factory, std::shared_ptr<libraryModel_ecorePackage> &package) {
    static std::shared_ptr<libraryModel_ecoreApi> instance = std::make_shared<libraryModel_ecoreApi>(libraryModel_ecoreApi(factory, package));
    return instance;
}

libraryModel_ecoreApi::libraryModel_ecoreApi(std::shared_ptr<libraryModel_ecoreFactory>& factory, std::shared_ptr<libraryModel_ecorePackage>& package) {
    m_factory = factory;
    m_package = package;
}

std::shared_ptr<ecore::EObject> libraryModel_ecoreApi::readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass){
    return nullptr;
}

crow::json::wvalue libraryModel_ecoreApi::writeValue(const std::shared_ptr<ecore::EObject>& object){
    return nullptr;
}