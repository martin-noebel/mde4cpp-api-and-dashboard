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

class ModelApi{
public:
    static std::shared_ptr<ModelApi> eInstance(std::shared_ptr<libraryModel_ecoreFactory>& factory);
    crow::json::wvalue writeValue(const std::shared_ptr<Any>& any);
    std::shared_ptr<Any> readValue(const crow::json::rvalue& content, const long& metaElementId);

private:
    explicit ModelApi(std::shared_ptr<libraryModel_ecoreFactory>& factory);
    template <typename T> T convert_to(const crow::json::rvalue& value);
    bool keyIsAvailable(const crow::json::rvalue& content, const std::string& key);
    std::shared_ptr<libraryModel_ecoreFactory> m_factory;
    std::map<std::string,std::shared_ptr<Any>> m_objects{};
};