#define CROW_JSON_USE_MAP
#include "libraryModel_genericApi.hpp"

#include <utility>

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
    CROW_ROUTE(app, "/<string>").methods(crow::HTTPMethod::Post)([this](const crow::request& request, const std::string& objectName){
        if(m_objects.find(objectName) != m_objects.end()){
            return crow::response(400, "Object already exists!");
        }
        auto object = readValue(crow::json::load(request.body));
        m_objects[objectName] = object;
        return crow::response(201);
    });

    //Read function
    CROW_ROUTE(app, "/<string>").methods(crow::HTTPMethod::Get)([this](const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        auto result = writeValue(m_objects[objectName]);
        return crow::response(200, result);
    });

    //Update function
    CROW_ROUTE(app, "/<string>").methods(crow::HTTPMethod::Put)([this](const crow::request& request, const std::string& objectName){
        return crow::response(200);
    });

    //Delete function
    CROW_ROUTE(app, "/<string>").methods(crow::HTTPMethod::Delete)([this](const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        m_objects.erase(m_objects.find(objectName));
        return crow::response(204);
    });

    app.port(8080).multithreaded().run_async();
}

std::shared_ptr<ecore::EClass> libraryModel_genericApi::readValue(const crow::json::rvalue& content){
    auto result = m_factory->createEClass();
    for(const auto & entry : content){
        auto key = entry.key();
        std::shared_ptr<EAttribute> value;
        switch (entry.t()) {
            case crow::json::type::True:
            case crow::json::type::False:
                value = constructAttribute(key, (bool) entry.b(), ecorePackage::EBOOLEAN_CLASS, m_package->getEBoolean_Class());
                break;
            case crow::json::type::String:
                value = constructAttribute(key, (std::string) entry.s(), ecorePackage::ESTRING_CLASS, m_package->getEString_Class());
                break;
            case crow::json::type::Number:
                switch (entry.nt()) {
                    case crow::json::num_type::Signed_integer:
                        value = constructAttribute(key, (int) entry.i(), ecorePackage::EINT_CLASS, m_package->getEInt_Class());
                        break;
                    case crow::json::num_type::Unsigned_integer:
                        value = constructAttribute(key, (int) entry.u(), ecorePackage::EINT_CLASS, m_package->getEInt_Class());
                        break;
                    case crow::json::num_type::Floating_point:
                        value = constructAttribute(key, (double) entry.d(), ecorePackage::EDOUBLE_CLASS, m_package->getEDouble_Class());
                        break;
                    case crow::json::num_type::Null:
                        value = constructAttribute(key, nullptr, ecorePackage::EOBJECT_CLASS, m_package->getEObject_Class());
                        break;
                }
                break;
            case crow::json::type::List:
            {
                break;
            }
            case crow::json::type::Object:
            {
                value = constructAttribute(key, readValue(entry), ecorePackage::EOBJECT_CLASS, m_package->getEObject_Class());
                break;
            }
            case crow::json::type::Null:
            {
                value = constructAttribute(key, nullptr, ecorePackage::EOBJECT_CLASS, m_package->getEObject_Class());
                break;
            }
            default:
            {
                throw std::runtime_error("unknown type");
            }
        }
        result->getEAttributes()->add(value);
    }
    return result;
}

template <class T>
std::shared_ptr<ecore::EAttribute> libraryModel_genericApi::constructAttribute(const std::string& key, T value, int type, std::shared_ptr<EClassifier> classifier) {
    auto attribute = m_factory->createEAttribute();
    attribute->setName(key);
    attribute->setEType(std::move(classifier));
    attribute->setUpperBound(1);
    auto eObjectAny = m_factory->createEObjectAny();
    eObjectAny->setAny(eAny(value, type, false));
    attribute->getEContentUnion()->add(eObjectAny);
    return attribute;
}

crow::json::wvalue libraryModel_genericApi::writeValue(const std::shared_ptr<ecore::EClass>& eClass){
    auto result = crow::json::wvalue();
    auto attributes = eClass->getEAttributes();
    for(const auto & attribute : *attributes){
        auto key = attribute->getName();
        Any value = std::dynamic_pointer_cast<EObjectAny>(attribute->getEContentUnion()->at(0))->getAny();
        switch (attribute->getEType()->getClassifierID()) {
            case ecorePackage::EBOOLEAN_CLASS:
                result[key] = value->get<bool>();
                break;
            case ecorePackage::ESTRING_CLASS:
                result[key] = value->get<std::string>();
                break;
            case ecorePackage::EINT_CLASS:
                result[key] = value->get<int>();
                break;
            case ecorePackage::EDOUBLE_CLASS:
                result[key] = value->get<double>();
                break;
            case ecorePackage::EOBJECT_CLASS:
                result[key] = writeValue(value->get<std::shared_ptr<EClass>>());
                break;
            default:
                throw std::runtime_error("unknown type");
        }
    }
    return result;
}