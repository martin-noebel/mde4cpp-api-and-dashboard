//********************************************************************
//*    
//* Warning: This file was generated by ecore4CPP Generator
//*
//********************************************************************

#ifndef ECORE_ETYPEDELEMENTETYPEDELEMENTIMPL_HPP
#define ECORE_ETYPEDELEMENTETYPEDELEMENTIMPL_HPP

//*********************************
// generated Includes

// namespace macro header include
#include "ecore/ecore.hpp" 

// model includes
#include "../ETypedElement.hpp"

#include "ecore/impl/ENamedElementImpl.hpp"

//*********************************
namespace ecore 
{
	class ECORE_API ETypedElementImpl : virtual public ENamedElementImpl, virtual public ETypedElement 
	{
		public: 
			ETypedElementImpl(const ETypedElementImpl & obj);
			virtual std::shared_ptr<ecore::EObject> copy() const = 0;
			ETypedElementImpl& operator=(ETypedElementImpl const&); 

		protected:
			friend class ecoreFactoryImpl;
			ETypedElementImpl();
			virtual std::shared_ptr<ecore::ETypedElement> getThisETypedElementPtr() const;
			virtual void setThisETypedElementPtr(std::weak_ptr<ecore::ETypedElement> thisETypedElementPtr);

			//Additional constructors for the containments back reference
			ETypedElementImpl(std::weak_ptr<ecore::EObject> par_eContainer);

		public:
			//destructor
			virtual ~ETypedElementImpl() = 0;
			
			//*********************************
			// Operations
			//*********************************
			
			//*********************************
			// Attribute Getters & Setters
			//*********************************
			virtual int getLowerBound() const ;
			virtual void setLowerBound (int _lowerBound);
			virtual bool isMany() const ;
			virtual bool isOrdered() const ;
			virtual void setOrdered (bool _ordered);
			virtual bool isRequired() const ;
			virtual void setRequired (bool _required);
			virtual bool isUnique() const ;
			virtual void setUnique (bool _unique);
			virtual int getUpperBound() const ;
			virtual void setUpperBound (int _upperBound);
			
			//*********************************
			// Reference Getters & Setters
			//*********************************
			virtual std::shared_ptr<ecore::EGenericType> getEGenericType() const ;
			virtual void setEGenericType(std::shared_ptr<ecore::EGenericType>) ;
			virtual std::shared_ptr<ecore::EClassifier> getEType() const ;
			virtual void setEType(std::shared_ptr<ecore::EClassifier>) ;
			
			//*********************************
			// Union Reference Getters
			//*********************************
			virtual std::shared_ptr<Union<ecore::EObject>> getEContentUnion() const ;
			
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
			virtual void resolveReferences(const int featureID, std::vector<std::shared_ptr<EObject> > references) ;
			virtual void save(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const ;
			virtual void saveContent(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const;

		protected:
			virtual std::shared_ptr<EClass> eStaticClass() const;

			//*********************************
			// EStructuralFeature Get/Set/IsSet
			//*********************************
			virtual Any eGet(int featureID, bool resolve, bool coreType) const ;
			virtual bool eSet(int featureID, Any newValue) ;
			virtual bool internalEIsSet(int featureID) const ;

			//*********************************
			// EOperation Invoke
			//*********************************
			virtual Any eInvoke(int operationID, std::shared_ptr<std::list<Any>> arguments) ;

		private:
			std::weak_ptr<ecore::ETypedElement> m_thisETypedElementPtr;
	};
}
#endif /* end of include guard: ECORE_ETYPEDELEMENTETYPEDELEMENTIMPL_HPP */
