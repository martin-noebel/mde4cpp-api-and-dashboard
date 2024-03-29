//********************************************************************
//*    
//* Warning: This file was generated by ecore4CPP Generator
//*
//********************************************************************

#ifndef LIBRARYMODEL_ECORE_NAMEDELEMENTNAMEDELEMENTIMPL_HPP
#define LIBRARYMODEL_ECORE_NAMEDELEMENTNAMEDELEMENTIMPL_HPP

//*********************************
// generated Includes

// namespace macro header include
#include "libraryModel_ecore/libraryModel_ecore.hpp" 

// model includes
#include "../NamedElement.hpp"


#include "ecore/impl/EModelElementImpl.hpp"

//*********************************
namespace libraryModel_ecore 
{
	class LIBRARYMODEL_ECORE_API NamedElementImpl : virtual public ecore::EModelElementImpl,
virtual public NamedElement 
	{
		public: 
			NamedElementImpl(const NamedElementImpl & obj);
			virtual std::shared_ptr<ecore::EObject> copy() const;
			NamedElementImpl& operator=(NamedElementImpl const&); 

		protected:
			friend class libraryModel_ecoreFactoryImpl;
			NamedElementImpl();
			virtual std::shared_ptr<libraryModel_ecore::NamedElement> getThisNamedElementPtr() const;
			virtual void setThisNamedElementPtr(std::weak_ptr<libraryModel_ecore::NamedElement> thisNamedElementPtr);


		public:
			//destructor
			virtual ~NamedElementImpl();
			
			//*********************************
			// Operations
			//*********************************
			
			//*********************************
			// Attribute Getters & Setters
			//*********************************
			virtual std::string getName() const ;
			virtual void setName (std::string _Name);
			
			//*********************************
			// Reference Getters & Setters
			//*********************************
			
			//*********************************
			// Union Reference Getters
			//*********************************
			
			//*********************************
			// Container Getter
			//*********************************
			virtual std::shared_ptr<ecore::EObject> eContainer() const ; 

			//*********************************
			// Persistence Functions
			//*********************************
			virtual void load(std::shared_ptr<persistence::interfaces::XLoadHandler> loadHandler) ;
			virtual void loadAttributes(std::shared_ptr<persistence::interfaces::XLoadHandler> loadHandler, std::map<std::string, std::string> attr_list);
			virtual void loadNode(std::string nodeName, std::shared_ptr<persistence::interfaces::XLoadHandler> loadHandler);
			virtual void resolveReferences(const int featureID, std::vector<std::shared_ptr<ecore::EObject> > references) ;
			virtual void save(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const ;
			virtual void saveContent(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const;

		protected:
			virtual std::shared_ptr<ecore::EClass> eStaticClass() const;

			//*********************************
			// EStructuralFeature Get/Set/IsSet
			//*********************************
			virtual std::shared_ptr<Any> eGet(int featureID, bool resolve, bool coreType) const ;
			virtual bool eSet(int featureID, std::shared_ptr<Any> newValue) ;
			virtual bool internalEIsSet(int featureID) const ;

			//*********************************
			// EOperation Invoke
			//*********************************
			virtual std::shared_ptr<Any> eInvoke(int operationID, std::shared_ptr<Bag<Any>> arguments) ;

		private:
			std::weak_ptr<libraryModel_ecore::NamedElement> m_thisNamedElementPtr;
	};
}
#endif /* end of include guard: LIBRARYMODEL_ECORE_NAMEDELEMENTNAMEDELEMENTIMPL_HPP */
