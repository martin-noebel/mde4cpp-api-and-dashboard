#define CROW_JSON_USE_MAP
#include "GenericApi.hpp"

std::shared_ptr<GenericApi> GenericApi::eInstance(std::shared_ptr<MDE4CPPPlugin> &plugin) {
    static std::shared_ptr<GenericApi> instance = std::make_shared<GenericApi>(GenericApi(plugin));
    return instance;
}

GenericApi::GenericApi(std::shared_ptr<MDE4CPPPlugin>& plugin) {
    m_plugin = plugin;
    crow::SimpleApp app;

    //Create function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Post)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) != m_objects.end()){
            return crow::response(400, "Object already exists!");
        }
        auto object = readValue(crow::json::load(request.body), className);
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
        m_objects.erase(m_objects.find(objectName));
        auto object = readValue(crow::json::load(request.body), className);
        m_objects[objectName] = object;
        return crow::response(200);
    });

    //Delete function
    CROW_ROUTE(app, "/<string>/<string>").methods(crow::HTTPMethod::Delete)([this](const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        m_objects.erase(m_objects.find(objectName));
        return crow::response(204);
    });

    //create instance model
    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Post)([this](const crow::request& request){
        for(const auto & entry : crow::json::load(request.body)){
            auto object = readValue(entry, entry["ecore_type"].s());
            m_objects[entry["ecore_identifier"].s()] = object;
        }
        return crow::response(201);
    });

    //get instance model
    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Get)([this](){
        crow::json::wvalue result;
        int i = 0;
        for(const auto & object : m_objects){
            auto wvalue = writeValue(object.second);
            wvalue["ecore_identifier"] = object.first;
            wvalue["ecore_type"] = object.second->eClass()->getName();
            result[i] = std::move(wvalue);
            i++;
        }
        return crow::response(200, result);
    });

    app.port(8080).multithreaded().run();
}

crow::json::wvalue GenericApi::writeValue(const std::shared_ptr<ecore::EObject>& object){
    auto result = crow::json::wvalue();
    auto features = object->eClass()->getEAllStructuralFeatures();
    for(const auto & feature : *features){
        if(object == nullptr){
            continue;
        }
        auto attributeTypeId = object->eGet(feature)->getTypeId();
        auto reference = std::dynamic_pointer_cast<EReference>(feature);
        if(reference != nullptr && reference->getEOpposite() != nullptr && !reference->isContainment()){
            continue;
        }
        crow::json::wvalue newValue;
        switch (attributeTypeId) {
            // Bool
            case ecore::ecorePackage::EBOOLEANOBJECT_CLASS:
            case ecore::ecorePackage::EBOOLEAN_CLASS:
                newValue = writeFeature<bool>(object, feature);
                break;
                // Char
            case ecore::ecorePackage::EBYTE_CLASS:
            case ecore::ecorePackage::EBYTEARRAY_CLASS:
            case ecore::ecorePackage::EBYTEOBJECT_CLASS:
            case ecore::ecorePackage::ECHARACTEROBJECT_CLASS:
            case ecore::ecorePackage::ECHAR_CLASS:
                newValue = writeFeature<char>(object, feature);
                break;
                // Int
            case ecore::ecorePackage::EDATE_CLASS:
            case ecore::ecorePackage::ERESOURCE_CLASS:
            case ecore::ecorePackage::EINTEGEROBJECT_CLASS:
            case ecore::ecorePackage::EBIGINTEGER_CLASS:
            case ecore::ecorePackage::ESHORT_CLASS:
            case ecore::ecorePackage::ESHORTOBJECT_CLASS:
            case ecore::ecorePackage::EINT_CLASS:
                newValue = writeFeature<int>(object, feature);
                break;
                // Long
            case ecore::ecorePackage::ELONGOBJECT_CLASS:
            case ecore::ecorePackage::ELONG_CLASS:
                newValue = writeFeature<int>(object, feature);
                break;
                // Float
            case ecore::ecorePackage::EFLOATOBJECT_CLASS:
            case ecore::ecorePackage::EFLOAT_CLASS:
                newValue = writeFeature<float>(object, feature);
                break;
                // Double
            case ecore::ecorePackage::EBIGDECIMAL_CLASS:
            case ecore::ecorePackage::EDOUBLE_CLASS:
            case ecore::ecorePackage::EDOUBLEOBJECT_CLASS:
                newValue = writeFeature<bool>(object, feature);
                break;
                // String
            case ecore::ecorePackage::ESTRING_CLASS:
            {
                newValue = writeFeature<std::string>(object, feature);
                break;
            }
                // Object
            default:
            {
                //TODO: fix bags
                break;
            }
        }
        result[feature->getName()] = std::move(newValue);
    }
    return result;
}

template<typename T>
crow::json::wvalue GenericApi::writeFeature(const std::shared_ptr<EObject> &object, const std::shared_ptr<EStructuralFeature> &feature) {
    auto isContainer = object->eGet(feature)->isContainer();
    if(isContainer){
        auto list = crow::json::wvalue();
        auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<T>>>();
        for (int j=0;j<bag->size();j++) {
            auto value = bag->at(j).get();
            list[j] = value;
        }
        return list;
    }
    return crow::json::wvalue(object->eGet(feature)->get<T>());
}

std::shared_ptr<ecore::EObject> GenericApi::readValue(const crow::json::rvalue& content, const std::string& eClass){
    auto result = m_plugin->create(eClass);
    auto features = result->eClass()->getEAllStructuralFeatures();
    for(const auto & feature : *features){
        try {
            auto value = content[feature->getName()];
            if(value.t() == crow::json::type::Null){
                continue;
            }
        } catch (std::runtime_error& error){
            continue;
        }
        auto attributeTypeId = result->eGet(feature)->getTypeId();
        auto reference = std::dynamic_pointer_cast<EReference>(feature);
        if(reference != nullptr && reference->getEOpposite() != nullptr && !reference->isContainment()){
            continue;
        }
        switch (attributeTypeId) {
            // Bool
            case ecore::ecorePackage::EBOOLEANOBJECT_CLASS:
            case ecore::ecorePackage::EBOOLEAN_CLASS:
                result->eSet(feature, readFeature<bool>(result, feature, content));
                break;
            // Char
            case ecore::ecorePackage::EBYTE_CLASS:
            case ecore::ecorePackage::EBYTEARRAY_CLASS:
            case ecore::ecorePackage::EBYTEOBJECT_CLASS:
            case ecore::ecorePackage::ECHARACTEROBJECT_CLASS:
            case ecore::ecorePackage::ECHAR_CLASS:
                result->eSet(feature, readFeature<char>(result, feature, content));
                break;
            // Int
            case ecore::ecorePackage::EDATE_CLASS:
            case ecore::ecorePackage::ERESOURCE_CLASS:
            case ecore::ecorePackage::EINTEGEROBJECT_CLASS:
            case ecore::ecorePackage::EBIGINTEGER_CLASS:
            case ecore::ecorePackage::ESHORT_CLASS:
            case ecore::ecorePackage::ESHORTOBJECT_CLASS:
            case ecore::ecorePackage::EINT_CLASS:
                result->eSet(feature, readFeature<int>(result, feature, content));
                break;
            // Long
            case ecore::ecorePackage::ELONGOBJECT_CLASS:
            case ecore::ecorePackage::ELONG_CLASS:
                result->eSet(feature, readFeature<long>(result, feature, content));
                break;
            // Float
            case ecore::ecorePackage::EFLOATOBJECT_CLASS:
            case ecore::ecorePackage::EFLOAT_CLASS:
                result->eSet(feature, readFeature<float>(result, feature, content));
                break;
            // Double
            case ecore::ecorePackage::EBIGDECIMAL_CLASS:
            case ecore::ecorePackage::EDOUBLE_CLASS:
            case ecore::ecorePackage::EDOUBLEOBJECT_CLASS:
                result->eSet(feature, readFeature<double>(result, feature, content));
                break;
            // String
            case ecore::ecorePackage::ESTRING_CLASS:
                result->eSet(feature, readFeature<std::string>(result, feature, content));
                break;
            // Object
            default:
            {
                //TODO: fix bags
                break;
            }
        }
    }
    return result;
}

//generic conversion methods for json
template<> bool GenericApi::convert_to<bool>(const crow::json::rvalue& value){
    return value.b();
}
template <typename T> T GenericApi::convert_to(const crow::json::rvalue& value){
    std::istringstream ss(value.operator std::string());
    T num;
    ss >> num;
    return num;
}

template<typename T>
std::shared_ptr<Any> GenericApi::readFeature(const std::shared_ptr<EObject>& object, const std::shared_ptr<EStructuralFeature>& feature, const crow::json::rvalue& content){
    auto attributeTypeId = object->eGet(feature)->getTypeId();
    auto isContainer = object->eGet(feature)->isContainer();
    if(isContainer){
        auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<T>>>();
        for(const auto & entry : content[feature->getName()]){
            auto value = std::make_shared<T>(convert_to<T>(entry));
            bag->add(value);
        }
        return eAny(bag, attributeTypeId, true);
    }
    return eAny(convert_to<T>(content[feature->getName()]), attributeTypeId, false);
}

