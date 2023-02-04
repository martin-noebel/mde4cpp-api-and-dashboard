#include "crow/crow_all.h"
#include "json/json.hpp"
#include "ecore/EObject.hpp"
#include "ecore/EClass.hpp"
#include "ecore/EStructuralFeature.hpp"
#include "ecore/EReference.hpp"
#include "abstractDataTypes/AnyEObjectBag.hpp"
#include "ecore/MDE4CPPPlugin.hpp"
#include "ecore/ecorePackage.hpp"

using namespace ecore;
using json = nlohmann::json;

class GenericApi{
public:
    static std::shared_ptr<GenericApi> eInstance(std::shared_ptr<MDE4CPPPlugin >& plugin);
    std::shared_ptr<ecore::EObject> readValue(json content, const std::string& eClass);
    crow::json::wvalue writeValue(const std::shared_ptr<ecore::EObject>& object);

private:
    template<typename T> Any readFeature(const std::shared_ptr<EObject>& object, const std::shared_ptr<EStructuralFeature>& feature, const json& content);
    template<typename T> crow::json::wvalue writeFeature(const std::shared_ptr<EObject>& object, const std::shared_ptr<EStructuralFeature>& feature);
    explicit GenericApi(std::shared_ptr<MDE4CPPPlugin>& plugin);
    std::shared_ptr<MDE4CPPPlugin> m_plugin;
    std::map<std::string,std::shared_ptr<ecore::EObject>> m_objects{};
};