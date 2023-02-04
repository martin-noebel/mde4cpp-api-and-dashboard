#define CROW_JSON_USE_MAP
#include "GenericApi.hpp"

//singleton
std::shared_ptr<GenericApi> GenericApi::eInstance(std::shared_ptr<MDE4CPPPlugin> &plugin) {
    static std::shared_ptr<GenericApi> instance = std::make_shared<GenericApi>(GenericApi(plugin));
    return instance;
}

//constructor with api creation
GenericApi::GenericApi(std::shared_ptr<MDE4CPPPlugin>& plugin) {
    m_plugin = plugin;
    crow::SimpleApp app;

    //Base Route
    CROW_ROUTE(app, "/")([](){
        return "Mde4cpp-Api for libraryModel_ecore";
    });

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

//serialization
crow::json::wvalue GenericApi::writeValue(const std::shared_ptr<ecore::EObject>& object){
    auto result = crow::json::wvalue();
    auto features = object->eClass()->getEAllStructuralFeatures();
    // Iterate over all features
    for(const auto & feature : *features){
        auto attributeTypeId = object->eGet(feature)->getTypeId();
        auto isContainer = object->eGet(feature)->isContainer();
        auto reference = std::dynamic_pointer_cast<EReference>(feature);
        // Handle infinite recursion by ignoring backreferences
        if(reference != nullptr && reference->getEOpposite() != nullptr && !reference->isContainment()){
            continue;
        }
        crow::json::wvalue newValue;
        // Switch type of the current feature
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
                if(isContainer){
                    auto list = crow::json::wvalue();
                    std::shared_ptr<Bag<EObject>> bag;
                    try{
                        bag = std::dynamic_pointer_cast<AnyEObjectBag>(object->eGet(feature))->getBag();
                    } catch (std::runtime_error& error) {
                        bag = std::make_shared<Bag<EObject>>();
                    }
                    for (int j=0;j<bag->size();j++) {
                        auto value = writeValue(bag->at(j));
                        list[j] = std::move(value);
                    }
                    newValue = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::shared_ptr<EObject>>();
                newValue = writeValue(value);
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

//deserialization
std::shared_ptr<ecore::EObject> GenericApi::readValue(const crow::json::rvalue& content, const std::string& eClass){
    auto result = m_plugin->create(eClass);
    auto features = result->eClass()->getEAllStructuralFeatures();
    // Iterate over all features
    for(const auto & feature : *features){
        auto attributeTypeId = result->eGet(feature)->getTypeId();
        auto isContainer = result->eGet(feature)->isContainer();
        auto reference = std::dynamic_pointer_cast<EReference>(feature);
        // Handle infinite recursion by ignoring backreferences
        if(reference != nullptr && reference->getEOpposite() != nullptr && !reference->isContainment()){
            continue;
        }
        Any newValue;
        // Switch type of the current feature
        switch (attributeTypeId) {
            // Bool
            case ecore::ecorePackage::EBOOLEANOBJECT_CLASS:
            case ecore::ecorePackage::EBOOLEAN_CLASS:
                newValue = readFeature<bool>(result, feature, content);
                break;
            // Char
            case ecore::ecorePackage::EBYTE_CLASS:
            case ecore::ecorePackage::EBYTEARRAY_CLASS:
            case ecore::ecorePackage::EBYTEOBJECT_CLASS:
            case ecore::ecorePackage::ECHARACTEROBJECT_CLASS:
            case ecore::ecorePackage::ECHAR_CLASS:
                newValue = readFeature<char>(result, feature, content);
                break;
            // Int
            case ecore::ecorePackage::EDATE_CLASS:
            case ecore::ecorePackage::ERESOURCE_CLASS:
            case ecore::ecorePackage::EINTEGEROBJECT_CLASS:
            case ecore::ecorePackage::EBIGINTEGER_CLASS:
            case ecore::ecorePackage::ESHORT_CLASS:
            case ecore::ecorePackage::ESHORTOBJECT_CLASS:
            case ecore::ecorePackage::EINT_CLASS:
                newValue = readFeature<int>(result, feature, content);
                break;
            // Long
            case ecore::ecorePackage::ELONGOBJECT_CLASS:
            case ecore::ecorePackage::ELONG_CLASS:
                newValue = readFeature<long>(result, feature, content);
                break;
            // Float
            case ecore::ecorePackage::EFLOATOBJECT_CLASS:
            case ecore::ecorePackage::EFLOAT_CLASS:
                newValue = readFeature<float>(result, feature, content);
                break;
            // Double
            case ecore::ecorePackage::EBIGDECIMAL_CLASS:
            case ecore::ecorePackage::EDOUBLE_CLASS:
            case ecore::ecorePackage::EDOUBLEOBJECT_CLASS:
                newValue = readFeature<double>(result, feature, content);
                break;
            // String
            case ecore::ecorePackage::ESTRING_CLASS:
                newValue = readFeature<std::string>(result, feature, content);
                break;
            // Object
            default:
            {
                if(isContainer){
                    std::shared_ptr<Bag<EObject>> bag;
                    try{
                        bag = std::dynamic_pointer_cast<AnyEObjectBag>(result->eGet(feature))->getBag();
                    } catch (std::runtime_error& error) {
                        std::cout << error.what() << std::endl;
                        bag = std::make_shared<Bag<EObject>>();
                    }
                    for(const auto & entry : content[feature->getName()]){
                        auto value = readValue(entry, feature->getEType()->getName());
                        bag->add(value);
                    }
                    newValue = eAnyBag(bag, attributeTypeId);
                    break;
                }
                auto value = readValue(content[feature->getName()], feature->getEType()->getName());
                newValue = eAny(value, attributeTypeId, false);
                break;
            }
        }
        result->eSet(feature, newValue);
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
Any GenericApi::readFeature(const std::shared_ptr<EObject>& object, const std::shared_ptr<EStructuralFeature>& feature, const crow::json::rvalue& content){
    auto attributeTypeId = object->eGet(feature)->getTypeId();
    auto isContainer = object->eGet(feature)->isContainer();
    if(isContainer){
        auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<T>>>();
        for(const auto & entry : content[feature->getName()]){
            auto value = std::make_shared<T>(convert_to<T>(content));
            bag->add(value);
        }
        return eAny(bag, attributeTypeId, true);
    }
    return eAny(convert_to<T>(content[feature->getName()]), attributeTypeId, false);
}

