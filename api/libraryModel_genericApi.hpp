#include "crow/crow_all.h"
#include "ecore/ecorePackage.hpp"
#include "ecore/ecoreFactory.hpp"
#include "ecore/EObject.hpp"
#include "ecore/EClass.hpp"
#include "ecore/EStructuralFeature.hpp"
#include "ecore/EReference.hpp"
#include "ecore/EAttribute.hpp"
#include "abstractDataTypes/Union.hpp"
#include "ecore/EObjectAny.hpp"
#include "ecore/EDataType.hpp"
#include "ecore/EClassifier.hpp"

using namespace ecore;

class libraryModel_genericApi{
public:
    static std::shared_ptr<libraryModel_genericApi> eInstance(std::shared_ptr<ecoreFactory>& factory, std::shared_ptr<ecorePackage>& package);
    std::shared_ptr<ecore::EClass> readValue(const crow::json::rvalue& content);
    crow::json::wvalue writeValue(const std::shared_ptr<ecore::EClass>& eClass);

private:
    template <class T> std::shared_ptr<ecore::EAttribute> constructAttribute(const std::string& key, T value, int type, std::shared_ptr<EClassifier> classifier);
    libraryModel_genericApi(std::shared_ptr<ecoreFactory>& factory, std::shared_ptr<ecorePackage>& package);
    std::shared_ptr<ecoreFactory> m_factory;
    std::shared_ptr<ecorePackage> m_package;
    std::map<std::string,std::shared_ptr<ecore::EClass>> m_objects{};
};