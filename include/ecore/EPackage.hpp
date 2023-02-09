//********************************************************************
//*    
//* Warning: This file was generated by ecore4CPP Generator
//*
//********************************************************************

#ifndef ECORE_EPACKAGE_HPP
#define ECORE_EPACKAGE_HPP


#include <memory>
#include <string>
// forward declarations
template<class T> class Bag; 
template<class T, class ... U> class Subset;


//*********************************
// generated Includes
#include <map> // used for Persistence
#include <vector> // used for Persistence
namespace persistence
{
	namespace interfaces
	{
		class XLoadHandler; // used for Persistence
		class XSaveHandler; // used for Persistence
	}
}

namespace ecore
{
	class ecoreFactory;
}

//Forward Declaration for used types 
namespace ecore 
{
	class EAnnotation;
	class EClassifier;
	class EFactory;
}

// namespace macro header include
#include "ecore/ecore.hpp"

// base class includes
#include "ecore/ENamedElement.hpp"




//*********************************
namespace ecore 
{
	
	class ECORE_API EPackage : virtual public ENamedElement
	{
		public:
 			EPackage(const EPackage &) {}

		protected:
			EPackage(){}
			//Additional constructors for the containments back reference
			EPackage(std::weak_ptr<ecore::EObject> par_eContainer);

			//Additional constructors for the containments back reference
			EPackage(std::weak_ptr<ecore::EPackage> par_eSuperPackage);

		public:
			virtual std::shared_ptr<ecore::EObject> copy() const = 0;

			//destructor
			virtual ~EPackage() {}

			//*********************************
			// Operations
			//*********************************
			virtual std::shared_ptr<ecore::EClassifier> getEClassifier(std::string name) const = 0;

			//*********************************
			// Attribute Getters & Setters
			//*********************************
			virtual std::string getNsPrefix() const = 0;
			virtual void setNsPrefix (std::string _nsPrefix)= 0;
			virtual std::string getNsURI() const = 0;
			virtual void setNsURI (std::string _nsURI)= 0;

			//*********************************
			// Reference Getters & Setters
			//*********************************
			virtual std::shared_ptr<Subset<ecore::EClassifier, ecore::EObject>> getEClassifiers() const = 0;
			virtual std::shared_ptr<ecore::EFactory> getEFactoryInstance() const = 0;
			virtual void setEFactoryInstance(std::shared_ptr<ecore::EFactory>) = 0;
			virtual std::shared_ptr<Bag<ecore::EPackage>> getESubpackages() const = 0;
			virtual std::weak_ptr<ecore::EPackage> getESuperPackage() const = 0;

			//*********************************
			// Union Reference Getters
			//*********************************

			//*********************************
			// Container Getter
			//*********************************
			virtual std::shared_ptr<ecore::EObject> eContainer() const = 0; 

			//*********************************
			// Persistence Functions
			//*********************************
			virtual void load(std::shared_ptr<persistence::interfaces::XLoadHandler> loadHandler) = 0;
			virtual void resolveReferences(const int featureID, std::vector<std::shared_ptr<EObject> > references) = 0;
			virtual void save(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const = 0;

		protected:
			//*********************************
			// Attribute Members
			//*********************************
			std::string m_nsPrefix= "";
			std::string m_nsURI= "";
			
			//*********************************
			// Reference Members
			//*********************************
			mutable std::shared_ptr<Subset<ecore::EClassifier, ecore::EObject>> m_eClassifiers;
			std::shared_ptr<ecore::EFactory> m_eFactoryInstance;
			mutable std::shared_ptr<Bag<ecore::EPackage>> m_eSubpackages;
			std::weak_ptr<ecore::EPackage> m_eSuperPackage;
	};
}
#endif /* end of include guard: ECORE_EPACKAGE_HPP */
