#include "include/crow_all.h"
#include "libraryModel_ecore/libraryModel_ecoreFactory.hpp"
#include "ecore/EObject.hpp"

using namespace ecore;
using namespace libraryModel_ecore;
using namespace std;

shared_ptr<libraryModel_ecoreFactory> factory = libraryModel_ecoreFactory::eInstance();
map<string,shared_ptr<EObject>> objects{};

int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Mde4cpp-Api and -Dashboard Home!!!";
    });

    app.port(8080).multithreaded().run();
}
