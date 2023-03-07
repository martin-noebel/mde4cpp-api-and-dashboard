#define CROW_JSON_USE_MAP
#include "ModelApi.hpp"

std::shared_ptr<ModelApi> ModelApi::eInstance(std::shared_ptr<libraryModel_ecoreFactory> &factory) {
    static std::shared_ptr<ModelApi> instance = std::make_shared<ModelApi>(ModelApi(factory));
    return instance;
}

ModelApi::ModelApi(std::shared_ptr<libraryModel_ecoreFactory>& factory) {
    m_factory = factory;
    crow::SimpleApp app;

    //Create function
    CROW_ROUTE(app, "/objects/<string>/<string>").methods(crow::HTTPMethod::Post)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) != m_objects.end()){
            return crow::response(400, "Object already exists!");
        }
        auto object = readValue(crow::json::load(request.body), m_factory->create(className)->eClass()->getMetaElementID());
        m_objects[objectName] = object;
        return crow::response(201);
    });

    //Read function
    CROW_ROUTE(app, "/objects/<string>/<string>").methods(crow::HTTPMethod::Get)([this](const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        auto result = writeValue(m_objects[objectName]);
        return crow::response(200, result);
    });

    //Update function
    CROW_ROUTE(app, "/objects/<string>/<string>").methods(crow::HTTPMethod::Put)([this](const crow::request& request, const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        m_objects.erase(m_objects.find(objectName));
        auto object = readValue(crow::json::load(request.body), m_factory->create(className)->eClass()->getMetaElementID());
        m_objects[objectName] = object;
        return crow::response(200);
    });

    //Delete function
    CROW_ROUTE(app, "/objects/<string>/<string>").methods(crow::HTTPMethod::Delete)([this](const std::string& className, const std::string& objectName){
        if(m_objects.find(objectName) == m_objects.end()){
            return crow::response(404);
        }
        m_objects.erase(m_objects.find(objectName));
        return crow::response(204);
    });

    //create instance model
    CROW_ROUTE(app, "/objects").methods(crow::HTTPMethod::Post)([this](const crow::request& request){
        for(const auto & entry : crow::json::load(request.body)){
            auto object = readValue(entry, entry["ecore_type"].i());
            m_objects[entry["ecore_identifier"].s()] = object;
        }
        return crow::response(201);
    });

    //get instance model
    CROW_ROUTE(app, "/objects/").methods(crow::HTTPMethod::Get)([this](){
        crow::json::wvalue result;
        int i = 0;
        for(const auto & object : m_objects){
            auto wvalue = writeValue(object.second);
            wvalue["ecore_identifier"] = object.first;
            wvalue["ecore_type"] = object.second->getTypeId();
            result[i] = std::move(wvalue);
            i++;
        }
        return crow::response(200, result);
    });

    //Swagger
    CROW_ROUTE(app, "/<string>")([](const std::string& path){
        std::string page;
        if(path == "swagger"){
            page = crow::mustache::load_text("index.html");
        }else{
            page = crow::mustache::load_text(path);
        }
        return crow::response(page);
    });

    app.port(8080).multithreaded().run();
}

crow::json::wvalue ModelApi::writeValue(const std::shared_ptr<Any>& any){
    auto result = crow::json::wvalue();
    auto metaElementId = any->getTypeId();
    switch (metaElementId) {
        case libraryModel_ecorePackage::LIBRARYMODEL_CLASS:
        {
            auto value = any->get<std::shared_ptr<LibraryModel>>();
            for(int i=0;i<value->getAuthors()->size();i++){
                result["authors"][i] = writeValue(eAny(value->getAuthors()->at(i), libraryModel_ecorePackage::AUTHOR_CLASS, false));
            }
            for(int i=0;i<value->getBook()->size();i++){
                result["books"][i] = writeValue(eAny(value->getBook()->at(i), libraryModel_ecorePackage::BOOK_CLASS, false));
            }
            break;
        }
        case libraryModel_ecorePackage::BOOK_CLASS:
        {
            auto value = any->get<std::shared_ptr<Book>>();
            for(int i=0;i<value->getAuthors()->size();i++){
                result["authors"][i] = writeValue(eAny(value->getAuthors()->at(i), libraryModel_ecorePackage::AUTHOR_CLASS, false));
            }
            for(int i=0;i<value->getPictures()->size();i++){
                result["pictures"][i] = writeValue(eAny(value->getPictures()->at(i), libraryModel_ecorePackage::PICTURE_CLASS, false));
            }
            result["Name"] = value->getName();
            break;
        }
        case libraryModel_ecorePackage::AUTHOR_CLASS:
        {
            auto value = any->get<std::shared_ptr<Author>>();
            result["Name"] = value->getName();
            break;
        }
        case libraryModel_ecorePackage::PICTURE_CLASS:
        {
            auto value = any->get<std::shared_ptr<Picture>>();
            result["pageNumber"] = value->getPageNumber();
            result["Name"] = value->getName();
            break;
        }
        case libraryModel_ecorePackage::NAMEDELEMENT_CLASS:
        {
            auto value = any->get<std::shared_ptr<NamedElement>>();
            result["Name"] = value->getName();
            break;
        }
        default:
        {
            result = nullptr;
            break;
        }
    }
    return result;
}

std::shared_ptr<Any> ModelApi::readValue(const crow::json::rvalue& content, const long& metaElementId){
    switch (metaElementId) {
        case libraryModel_ecorePackage::LIBRARYMODEL_CLASS:
        {
            auto value = m_factory->createLibraryModel();
            auto result = eAny(value, libraryModel_ecorePackage::LIBRARYMODEL_CLASS, false);
            if(keyIsAvailable(content, "authors")){
                for(const auto& it : content["authors"]) {
                    value->getAuthors()->add(readValue(it, libraryModel_ecorePackage::AUTHOR_CLASS)->get<std::shared_ptr<Author>>());
                }
            }
            if(keyIsAvailable(content, "books")){
                for(const auto& it : content["books"]) {
                    value->getBook()->add(readValue(it, libraryModel_ecorePackage::BOOK_CLASS)->get<std::shared_ptr<Book>>());
                }
            }
            return result;
        }
        case libraryModel_ecorePackage::BOOK_CLASS:
        {
            auto value = m_factory->createBook();
            auto result = eAny(value, libraryModel_ecorePackage::BOOK_CLASS, false);
            if(keyIsAvailable(content, "authors")){
                for(const auto& it : content["authors"]) {
                    value->getAuthors()->add(readValue(it, libraryModel_ecorePackage::AUTHOR_CLASS)->get<std::shared_ptr<Author>>());
                }
            }
            if(keyIsAvailable(content, "pictures")){
                for(const auto& it : content["pictures"]) {
                    value->getPictures()->add(readValue(it, libraryModel_ecorePackage::PICTURE_CLASS)->get<std::shared_ptr<Picture>>());
                }
            }
            if(keyIsAvailable(content, "Name")){
                value->setName(convert_to<std::string>(content["Name"]));
            }
            return result;
        }
        case libraryModel_ecorePackage::AUTHOR_CLASS:
        {
            auto value = m_factory->createAuthor();
            auto result = eAny(value, libraryModel_ecorePackage::AUTHOR_CLASS, false);
            if(keyIsAvailable(content, "Name")){
                value->setName(convert_to<std::string>(content["Name"]));
            }
            return result;
        }
        case libraryModel_ecorePackage::PICTURE_CLASS:
        {
            auto value = m_factory->createPicture();
            auto result = eAny(value, libraryModel_ecorePackage::PICTURE_CLASS, false);
            if(keyIsAvailable(content, "pageNumber")){
                value->setPageNumber(convert_to<int>(content["pageNumber"]));
            }
            if(keyIsAvailable(content, "Name")){
                value->setName(convert_to<std::string>(content["Name"]));
            }
            return result;
        }
        case libraryModel_ecorePackage::NAMEDELEMENT_CLASS:
        {
            auto value = m_factory->createNamedElement();
            auto result = eAny(value, libraryModel_ecorePackage::NAMEDELEMENT_CLASS, false);
            if(keyIsAvailable(content, "Name")){
                value->setName(convert_to<std::string>(content["Name"]));
            }
            return result;
        }
        default:
        {
            return nullptr;
        }
    }
}

bool ModelApi::keyIsAvailable(const crow::json::rvalue& content, const std::string& key){
    try{
        content[key];
        return true;
    }catch (std::runtime_error& error){
        return false;
    }
}

//generic conversion methods for json
template<> bool ModelApi::convert_to<bool>(const crow::json::rvalue& value){
    return value.b();
}
template <typename T> T ModelApi::convert_to(const crow::json::rvalue& value){
    std::istringstream ss(value.operator std::string());
    T num;
    ss >> num;
    return num;
}