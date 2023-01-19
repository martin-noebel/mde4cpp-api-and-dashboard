#define CROW_JSON_USE_MAP
#include "libraryModel_mixedApi.hpp"

std::shared_ptr<libraryModel_mixedApi> libraryModel_mixedApi::eInstance(std::shared_ptr<libraryModel_ecoreFactory> &factory, std::shared_ptr<libraryModel_ecorePackage> &package) {
    static std::shared_ptr<libraryModel_mixedApi> instance = std::make_shared<libraryModel_mixedApi>(libraryModel_mixedApi(factory, package));
    return instance;
}

libraryModel_mixedApi::libraryModel_mixedApi(std::shared_ptr<libraryModel_ecoreFactory>& factory, std::shared_ptr<libraryModel_ecorePackage>& package) {
    m_factory = factory;
    m_package = package;
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

std::shared_ptr<ecore::EObject> libraryModel_mixedApi::readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass){
    auto result = m_factory->create(eClass);
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
        // Switch type of the current feature
        switch (attributeTypeId) {
            // Bool
            case ecore::ecorePackage::EBOOLEANOBJECT_CLASS:
            case ecore::ecorePackage::EBOOLEAN_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<bool>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = std::make_shared<bool>(entry.b());
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                bool value = content[feature->getName()].b();
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Char
            case ecore::ecorePackage::EBYTE_CLASS:
            case ecore::ecorePackage::EBYTEARRAY_CLASS:
            case ecore::ecorePackage::EBYTEOBJECT_CLASS:
            case ecore::ecorePackage::ECHARACTEROBJECT_CLASS:
            case ecore::ecorePackage::ECHAR_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<char>>>();
                    for(const auto & entry : content[feature->getName()]){
                        std::string string = entry.s();
                        auto value = std::make_shared<char>(string[0]);
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                std::string string = content[feature->getName()].s();
                char *value = &string[0];
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Int
            case ecore::ecorePackage::EDATE_CLASS:
            case ecore::ecorePackage::ERESOURCE_CLASS:
            case ecore::ecorePackage::EINTEGEROBJECT_CLASS:
            case ecore::ecorePackage::EBIGINTEGER_CLASS:
            case ecore::ecorePackage::ESHORT_CLASS:
            case ecore::ecorePackage::ESHORTOBJECT_CLASS:
            case ecore::ecorePackage::EINT_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<int>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = std::make_shared<int>(entry.i());
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                int value = content[feature->getName()].i();
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Long
            case ecore::ecorePackage::ELONGOBJECT_CLASS:
            case ecore::ecorePackage::ELONG_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<long>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = std::make_shared<long>(entry.i());
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                long value = content[feature->getName()].i();
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Float
            case ecore::ecorePackage::EFLOATOBJECT_CLASS:
            case ecore::ecorePackage::EFLOAT_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<float>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = std::make_shared<float>(entry.d());
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                float value = content[feature->getName()].d();
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Double
            case ecore::ecorePackage::EBIGDECIMAL_CLASS:
            case ecore::ecorePackage::EDOUBLE_CLASS:
            case ecore::ecorePackage::EDOUBLEOBJECT_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<double>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = std::make_shared<double>(entry.d());
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                double value = content[feature->getName()].d();
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // String
            case ecore::ecorePackage::ESTRING_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<std::string>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = std::make_shared<std::string>(entry.s());
                        bag->add(value);
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                std::string value = content[feature->getName()].s();
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Library class
            case libraryModel_ecorePackage::LIBRARYMODEL_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<LibraryModel>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = readValue(entry, m_package->getLibraryModel_Class());
                        bag->add(std::dynamic_pointer_cast<LibraryModel>(value));
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                auto value = readValue(content[feature->getName()], m_package->getLibraryModel_Class());
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Book class
            case libraryModel_ecorePackage::BOOK_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<Book>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = readValue(entry, m_package->getBook_Class());
                        bag->add(std::dynamic_pointer_cast<Book>(value));
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                auto value = readValue(content[feature->getName()], m_package->getBook_Class());
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Author class
            case libraryModel_ecorePackage::AUTHOR_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<Author>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = readValue(entry, m_package->getAuthor_Class());
                        bag->add(std::dynamic_pointer_cast<Author>(value));
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                auto value = readValue(content[feature->getName()], m_package->getAuthor_Class());
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Picture class
            case libraryModel_ecorePackage::PICTURE_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<Picture>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = readValue(entry, m_package->getPicture_Class());
                        bag->add(std::dynamic_pointer_cast<Picture>(value));
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                auto value = readValue(content[feature->getName()], m_package->getPicture_Class());
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // NamedElement class
            case libraryModel_ecorePackage::NAMEDELEMENT_CLASS:
            {
                if(isContainer){
                    auto bag = result->eGet(feature)->get<std::shared_ptr<Bag<NamedElement>>>();
                    for(const auto & entry : content[feature->getName()]){
                        auto value = readValue(entry, m_package->getNamedElement_Class());
                        bag->add(std::dynamic_pointer_cast<NamedElement>(value));
                    }
                    result->eSet(feature, eAny(bag, attributeTypeId, true));
                    break;
                }
                auto value = readValue(content[feature->getName()], m_package->getNamedElement_Class());
                result->eSet(feature, eAny(value, attributeTypeId, false));
                break;
            }
            // Undefined
            default:
                break;
        }
    }
    return result;
}

crow::json::wvalue libraryModel_mixedApi::writeValue(const std::shared_ptr<ecore::EObject>& object){
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
        // Switch type of the current feature
        switch (attributeTypeId) {
            // Bool
            case ecore::ecorePackage::EBOOLEANOBJECT_CLASS:
            case ecore::ecorePackage::EBOOLEAN_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<bool>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<bool>();
                result[feature->getName()] = value;
                break;
            }
            // Char
            case ecore::ecorePackage::EBYTE_CLASS:
            case ecore::ecorePackage::EBYTEARRAY_CLASS:
            case ecore::ecorePackage::EBYTEOBJECT_CLASS:
            case ecore::ecorePackage::ECHARACTEROBJECT_CLASS:
            case ecore::ecorePackage::ECHAR_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<char>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<char>();
                result[feature->getName()] = value;
                break;
            }
            // Int
            case ecore::ecorePackage::EDATE_CLASS:
            case ecore::ecorePackage::ERESOURCE_CLASS:
            case ecore::ecorePackage::EINTEGEROBJECT_CLASS:
            case ecore::ecorePackage::EBIGINTEGER_CLASS:
            case ecore::ecorePackage::ESHORT_CLASS:
            case ecore::ecorePackage::ESHORTOBJECT_CLASS:
            case ecore::ecorePackage::EINT_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<int>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<int>();
                result[feature->getName()] = value;
                break;
            }
            // Long
            case ecore::ecorePackage::ELONGOBJECT_CLASS:
            case ecore::ecorePackage::ELONG_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<long>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<long>();
                result[feature->getName()] = value;
                break;
            }
            // Float
            case ecore::ecorePackage::EFLOATOBJECT_CLASS:
            case ecore::ecorePackage::EFLOAT_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<float>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<float>();
                result[feature->getName()] = value;
                break;
            }
            // Double
            case ecore::ecorePackage::EBIGDECIMAL_CLASS:
            case ecore::ecorePackage::EDOUBLE_CLASS:
            case ecore::ecorePackage::EDOUBLEOBJECT_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<double>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<double>();
                result[feature->getName()] = value;
                break;
            }
            // String
            case ecore::ecorePackage::ESTRING_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<std::string>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = bag->at(j).get();
                        list[j] = value;
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::string>();
                result[feature->getName()] = value;
                break;
            }
            // Library class
            case libraryModel_ecore::libraryModel_ecorePackage::LIBRARYMODEL_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<LibraryModel>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = writeValue(bag->at(j));
                        list[j] = std::move(value);
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::shared_ptr<LibraryModel>>();
                result[feature->getName()] = writeValue(value);
                break;
            }
            // Book class
            case libraryModel_ecore::libraryModel_ecorePackage::BOOK_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<Book>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = writeValue(bag->at(j));
                        list[j] = std::move(value);
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::shared_ptr<Book>>();
                result[feature->getName()] = writeValue(value);
                break;
            }
            // Author class
            case libraryModel_ecore::libraryModel_ecorePackage::AUTHOR_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<Author>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = writeValue(bag->at(j));
                        list[j] = std::move(value);
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::shared_ptr<Author>>();
                result[feature->getName()] = writeValue(value);
                break;
            }
            // Picture class
            case libraryModel_ecore::libraryModel_ecorePackage::PICTURE_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<Picture>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = writeValue(bag->at(j));
                        list[j] = std::move(value);
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::shared_ptr<Picture>>();
                result[feature->getName()] = writeValue(value);
                break;
            }
            // NamedElement class
            case libraryModel_ecore::libraryModel_ecorePackage::NAMEDELEMENT_CLASS:
            {
                if(isContainer){
                    auto list = crow::json::wvalue();
                    auto bag = object->eGet(feature)->get<std::shared_ptr<Bag<NamedElement>>>();
                    for (int j=0;j<bag->size();j++) {
                        auto value = writeValue(bag->at(j));
                        list[j] = std::move(value);
                    }
                    result[feature->getName()] = std::move(list);
                    break;
                }
                auto value = object->eGet(feature)->get<std::shared_ptr<NamedElement>>();
                result[feature->getName()] = writeValue(value);
                break;
            }
            // Undefined
            default:
                break;
        }
    }
    return result;
}