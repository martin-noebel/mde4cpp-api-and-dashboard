#include "crow/crow_all.h"
#include "ecore/EClass.hpp"
#include "libraryModel_ecore/libraryModel_ecoreFactory.hpp"
#include "libraryModel_ecore/libraryModel_ecorePackage.hpp"
#include "libraryModel_ecore/Author.hpp"
#include "libraryModel_ecore/Book.hpp"
#include "libraryModel_ecore/Picture.hpp"
#include "libraryModel_ecore/LibraryModel.hpp"
#include "libraryModel_ecore/NamedElement.hpp"

using namespace ecore;
using namespace libraryModel_ecore;

class libraryModel_modelApi{
public:
    static std::shared_ptr<libraryModel_modelApi> eInstance(std::shared_ptr<libraryModel_ecoreFactory>& factory, std::shared_ptr<libraryModel_ecorePackage>& package);
    Any readValue(const crow::json::rvalue& content, const std::shared_ptr<ecore::EClass>& eClass);
    crow::json::wvalue writeValue(const Any& any);

private:
    libraryModel_modelApi(std::shared_ptr<libraryModel_ecoreFactory>& factory, std::shared_ptr<libraryModel_ecorePackage>& package);
    std::shared_ptr<libraryModel_ecoreFactory> m_factory;
    std::shared_ptr<libraryModel_ecorePackage> m_package;
    std::map<std::string,Any> m_objects{};
};