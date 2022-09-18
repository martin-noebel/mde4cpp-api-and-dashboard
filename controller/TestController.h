#pragma once
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include <libraryModel_ecore/libraryModel_ecoreFactory.hpp>
#include OATPP_CODEGEN_BEGIN(ApiController)
#include <libraryModel_ecore/Book.hpp>
#include <libraryModel_ecore/Author.hpp>
#include <libraryModel_ecore/Picture.hpp>
#include <libraryModel_ecore/LibraryModel.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <abstractDataTypes/Bag.hpp>
#include <ecore/EStructuralFeature.hpp>

using namespace libraryModel_ecore;
using namespace oatpp::web::server::api;
using namespace ecore;

class TestController : public ApiController {
public:
    TestController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)): ApiController(objectMapper) {}
private:
    OATPP_COMPONENT(std::shared_ptr<libraryModel_ecoreFactory>, factory);
    OATPP_COMPONENT(std::shared_ptr<std::vector<std::shared_ptr<EObject>>>, objects);
public:
    ENDPOINT("POST", "/objects/{className}", createObjectByName, PATH(String, className)) {
        std::shared_ptr<EObject> object = factory->create(className);
        auto result = factory->convertToString(nullptr, object->eAllContents());
        return createResponse(Status::CODE_200, result);
    }
};

#include OATPP_CODEGEN_END(ApiController)