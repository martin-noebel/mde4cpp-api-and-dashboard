#include "crow/crow_all.h"
#include "ecore/ecorePackage.hpp"
#include "ecore/ecoreFactory.hpp"
#include "ecore/EObject.hpp"
#include "ecore/EClass.hpp"
#include "ecore/EStructuralFeature.hpp"
#include "ecore/EReference.hpp"

using namespace ecore;

class libraryModel_genericApi{
public:
    static std::shared_ptr<libraryModel_genericApi> eInstance(std::shared_ptr<ecoreFactory>& factory, std::shared_ptr<ecorePackage>& package);
    std::shared_ptr<ecore::EObject> readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass);
    crow::json::wvalue writeValue(const std::shared_ptr<ecore::EObject>& object);

private:
    libraryModel_genericApi(std::shared_ptr<ecoreFactory>& factory, std::shared_ptr<ecorePackage>& package);
    std::shared_ptr<ecoreFactory> m_factory;
    std::shared_ptr<ecorePackage> m_package;
    std::map<std::string,std::shared_ptr<ecore::EObject>> m_objects{};
};