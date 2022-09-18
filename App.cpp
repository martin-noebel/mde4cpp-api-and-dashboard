#include <libraryModel_ecore/libraryModel_ecoreFactory.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/Server.hpp"
#include "./controller/TestController.h"
using namespace libraryModel_ecore;

class App {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8080, oatpp::network::Address::IP_4});
    }());
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());
    OATPP_CREATE_COMPONENT(std::shared_ptr<libraryModel_ecoreFactory>, factory)([] {
        return libraryModel_ecoreFactory::eInstance();
    }());
    OATPP_CREATE_COMPONENT(std::shared_ptr<std::vector<std::shared_ptr<EObject>>>, objects)([] {
        return std::shared_ptr<std::vector<std::shared_ptr<EObject>>>();
    }());
};

int main(int argc, const char * argv[]) {
    oatpp::base::Environment::init();
    App app;
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    router->addController(std::make_shared<TestController>());
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData())
    server.run();
    oatpp::base::Environment::destroy();
    return 0;
}