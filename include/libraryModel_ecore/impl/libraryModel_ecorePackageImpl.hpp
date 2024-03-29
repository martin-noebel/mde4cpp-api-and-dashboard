//********************************************************************
//*    
//* Warning: This file was generated by ecore4CPP Generator
//*
//********************************************************************

#ifndef LIBRARYMODEL_ECOREPACKAGEIMPL_HPP
#define LIBRARYMODEL_ECOREPACKAGEIMPL_HPP

// namespace macro header include
#include "libraryModel_ecore/libraryModel_ecore.hpp"

#include "ecore/ecorePackage.hpp"
#include "ecore/impl/EPackageImpl.hpp"

#include "libraryModel_ecore/libraryModel_ecorePackage.hpp" 


namespace libraryModel_ecore 
{
	class Author;
	class Book;
	class LibraryModel;
	class NamedElement;
	class Picture;}

namespace ecore
{
	class ecoreFactory;
}

namespace libraryModel_ecore
{
	class LIBRARYMODEL_ECORE_API libraryModel_ecorePackageImpl : public ecore::EPackageImpl ,virtual public libraryModel_ecorePackage
	{
		private:    
			libraryModel_ecorePackageImpl(libraryModel_ecorePackageImpl const&) = delete;
			libraryModel_ecorePackageImpl& operator=(libraryModel_ecorePackageImpl const&) = delete;

		protected:
			libraryModel_ecorePackageImpl();

		public:
			virtual ~libraryModel_ecorePackageImpl();

			// Begin Class Author
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getAuthor_Class() const ;
			
			
			virtual std::shared_ptr<ecore::EReference> getAuthor_Attribute_library() const ;
			
			
			// End Class Author

			// Begin Class Book
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getBook_Class() const ;
			
			
			virtual std::shared_ptr<ecore::EReference> getBook_Attribute_authors() const ;
			virtual std::shared_ptr<ecore::EReference> getBook_Attribute_library() const ;
			virtual std::shared_ptr<ecore::EReference> getBook_Attribute_pictures() const ;
			
			
			// End Class Book

			// Begin Class LibraryModel
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getLibraryModel_Class() const ;
			
			
			virtual std::shared_ptr<ecore::EReference> getLibraryModel_Attribute_authors() const ;
			virtual std::shared_ptr<ecore::EReference> getLibraryModel_Attribute_book() const ;
			
			virtual std::shared_ptr<ecore::EOperation> getLibraryModel_Operation_printLibrary() const ;
			
			// End Class LibraryModel

			// Begin Class NamedElement
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getNamedElement_Class() const ;
			
			virtual std::shared_ptr<ecore::EAttribute> getNamedElement_Attribute_name() const ;
			
			
			
			// End Class NamedElement

			// Begin Class Picture
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getPicture_Class() const ;
			
			virtual std::shared_ptr<ecore::EAttribute> getPicture_Attribute_pageNumber() const ;
			
			virtual std::shared_ptr<ecore::EReference> getPicture_Attribute_book() const ;
			
			
			// End Class Picture

			
			// SubPackages Getters
			

		private:
			std::shared_ptr<ecore::EClass> m_author_Class = nullptr;std::shared_ptr<ecore::EClass> m_book_Class = nullptr;std::shared_ptr<ecore::EClass> m_libraryModel_Class = nullptr;std::shared_ptr<ecore::EClass> m_namedElement_Class = nullptr;std::shared_ptr<ecore::EClass> m_picture_Class = nullptr;
			
			std::shared_ptr<ecore::EAttribute> m_namedElement_Attribute_name = nullptr;std::shared_ptr<ecore::EAttribute> m_picture_Attribute_pageNumber = nullptr;
			std::shared_ptr<ecore::EReference> m_book_Attribute_authors = nullptr;std::shared_ptr<ecore::EReference> m_libraryModel_Attribute_authors = nullptr;std::shared_ptr<ecore::EReference> m_libraryModel_Attribute_book = nullptr;std::shared_ptr<ecore::EReference> m_picture_Attribute_book = nullptr;std::shared_ptr<ecore::EReference> m_book_Attribute_library = nullptr;std::shared_ptr<ecore::EReference> m_author_Attribute_library = nullptr;std::shared_ptr<ecore::EReference> m_book_Attribute_pictures = nullptr;
			std::shared_ptr<ecore::EOperation> m_libraryModel_Operation_printLibrary = nullptr;

			friend class libraryModel_ecorePackage;

			static bool isInited;
			static libraryModel_ecorePackage* create();
			bool isInitialized = false;
 			bool isCreated = false;

			virtual void init(std::shared_ptr<ecore::EPackage> package);

		public:
			void createPackageContents(std::shared_ptr<ecore::EPackage> package);
			void initializePackageContents();

		private:
			void createAuthorContent(std::shared_ptr<ecore::EPackage> package, std::shared_ptr<ecore::ecoreFactory> factory);
			void createBookContent(std::shared_ptr<ecore::EPackage> package, std::shared_ptr<ecore::ecoreFactory> factory);
			void createLibraryModelContent(std::shared_ptr<ecore::EPackage> package, std::shared_ptr<ecore::ecoreFactory> factory);
			void createNamedElementContent(std::shared_ptr<ecore::EPackage> package, std::shared_ptr<ecore::ecoreFactory> factory);
			void createPictureContent(std::shared_ptr<ecore::EPackage> package, std::shared_ptr<ecore::ecoreFactory> factory);
			void createPackageEDataTypes(std::shared_ptr<ecore::EPackage> package, std::shared_ptr<ecore::ecoreFactory> factory);

			void initializeAuthorContent();
			void initializeBookContent();
			void initializeLibraryModelContent();
			void initializeNamedElementContent();
			void initializePictureContent();
			void initializePackageEDataTypes();



	};
}
#endif /* end of include guard: LIBRARYMODEL_ECOREPACKAGEIMPL_HPP */
