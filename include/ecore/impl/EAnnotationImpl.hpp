//********************************************************************
//*    
//* Warning: This file was generated by ecore4CPP Generator
//*
//********************************************************************

#ifndef ECORE_EANNOTATIONEANNOTATIONIMPL_HPP
#define ECORE_EANNOTATIONEANNOTATIONIMPL_HPP

//*********************************
// generated Includes

// namespace macro header include
#include "ecore/ecore.hpp" 

// model includes
#include "../EAnnotation.hpp"

#include "ecore/impl/EModelElementImpl.hpp"

//*********************************
namespace ecore 
{
	class ECORE_API EAnnotationImpl : virtual public EModelElementImpl, virtual public EAnnotation 
	{
		public: 
			EAnnotationImpl(const EAnnotationImpl & obj);
			virtual std::shared_ptr<ecore::EObject> copy() const;
			EAnnotationImpl& operator=(EAnnotationImpl const&); 

		protected:
			friend class ecoreFactoryImpl;
			EAnnotationImpl();
			virtual std::shared_ptr<ecore::EAnnotation> getThisEAnnotationPtr() const;
			virtual void setThisEAnnotationPtr(std::weak_ptr<ecore::EAnnotation> thisEAnnotationPtr);

			//Additional constructors for the containments back reference
			EAnnotationImpl(std::weak_ptr<ecore::EObject> par_eContainer);
			//Additional constructors for the containments back reference
			EAnnotationImpl(std::weak_ptr<ecore::EModelElement> par_eModelElement);

		public:
			//destructor
			virtual ~EAnnotationImpl();
			
			//*********************************
			// Operations
			//*********************************
			
			//*********************************
			// Attribute Getters & Setters
			//*********************************
			virtual std::shared_ptr<std::map < std::string, std::string>> getDetails() const ;
			virtual void setDetails (std::shared_ptr<std::map < std::string, std::string>> _details);
			virtual std::string getSource() const ;
			virtual void setSource (std::string _source);
			
			//*********************************
			// Reference Getters & Setters
			//*********************************
			virtual std::shared_ptr<Subset<ecore::EObject, ecore::EObject>> getContents() const ;
			virtual std::weak_ptr<ecore::EModelElement> getEModelElement() const ;
			virtual void setEModelElement(std::weak_ptr<ecore::EModelElement>) ;
			virtual std::shared_ptr<Bag<ecore::EObject>> getReferences() const ;
			
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
			virtual void resolveReferences(const int featureID, std::vector<std::shared_ptr<EObject> > references) ;
			virtual void save(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const ;
			virtual void saveContent(std::shared_ptr<persistence::interfaces::XSaveHandler> saveHandler) const;

		protected:
			virtual std::shared_ptr<EClass> eStaticClass() const;

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
			std::weak_ptr<ecore::EAnnotation> m_thisEAnnotationPtr;
	};
}
#endif /* end of include guard: ECORE_EANNOTATIONEANNOTATIONIMPL_HPP */
