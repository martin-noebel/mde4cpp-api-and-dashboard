//********************************************************************
//*    
//* Warning: This file was generated by ecore4CPP Generator
//*
//********************************************************************

#ifndef LIBRARYMODEL_ECOREPACKAGE_HPP
#define LIBRARYMODEL_ECOREPACKAGE_HPP

// namespace macro header include
#include "libraryModel_ecore/libraryModel_ecore.hpp"

#include "ecore/EPackage.hpp"

namespace ecore 
{
	class EAttribute;
	class EReference;
	class EDataType;
	class EGenericType;
	class EStringToStringMapEntry;
	class EOperation;
	class EClass;
	class EAnnotation;
}

namespace libraryModel_ecore 
{
	class Author;
	class Book;
	class LibraryModel;
	class NamedElement;
	class Picture;
}
 
namespace libraryModel_ecore 
{
	/*!
	The Metamodel Package for the libraryModel_ecore metamodel. This package is used to enable the reflection of model elements. It contains all model elements
	which were described in an ecore file.
	*/
	
	class LIBRARYMODEL_ECORE_API libraryModel_ecorePackage : virtual public ecore::EPackage 
	{
		private:    
			libraryModel_ecorePackage(libraryModel_ecorePackage const&) = delete;
			libraryModel_ecorePackage& operator=(libraryModel_ecorePackage const&) = delete;

		protected:
			libraryModel_ecorePackage(){}

		public:
			//static variables
			static const std::string eNAME;
			static const std::string eNS_URI;
			static const std::string eNS_PREFIX;

			// Begin Class Author
			//Class and Feature IDs 
			static const unsigned long AUTHOR_CLASS = 512601281;
			static const unsigned int AUTHOR_CLASS_FEATURE_COUNT = 2;
			static const unsigned int AUTHOR_CLASS_OPERATION_COUNT = 0;
			
			static const unsigned long AUTHOR_ATTRIBUTE_LIBRARY = 1119226733;
			
			
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getAuthor_Class() const = 0;
			
			
			virtual std::shared_ptr<ecore::EReference> getAuthor_Attribute_library() const = 0;
			
			
			// End Class Author


			// Begin Class Book
			//Class and Feature IDs 
			static const unsigned long BOOK_CLASS = 1651020936;
			static const unsigned int BOOK_CLASS_FEATURE_COUNT = 4;
			static const unsigned int BOOK_CLASS_OPERATION_COUNT = 0;
			
			static const unsigned long BOOK_ATTRIBUTE_AUTHORS = 2131964251;
			static const unsigned long BOOK_ATTRIBUTE_LIBRARY = 1004468946;
			static const unsigned long BOOK_ATTRIBUTE_PICTURES = 1563353560;
			
			
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getBook_Class() const = 0;
			
			
			virtual std::shared_ptr<ecore::EReference> getBook_Attribute_authors() const = 0;
			virtual std::shared_ptr<ecore::EReference> getBook_Attribute_library() const = 0;
			virtual std::shared_ptr<ecore::EReference> getBook_Attribute_pictures() const = 0;
			
			
			// End Class Book


			// Begin Class LibraryModel
			//Class and Feature IDs 
			static const unsigned long LIBRARYMODEL_CLASS = 1802231003;
			static const unsigned int LIBRARYMODEL_CLASS_FEATURE_COUNT = 2;
			static const unsigned int LIBRARYMODEL_CLASS_OPERATION_COUNT = 1;
			
			static const unsigned long LIBRARYMODEL_ATTRIBUTE_AUTHORS = 249338550;
			static const unsigned long LIBRARYMODEL_ATTRIBUTE_BOOK = 1544868496;
			
			static const unsigned int LIBRARYMODEL_OPERATION_PRINTLIBRARY = 1310111868;
			
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getLibraryModel_Class() const = 0;
			
			
			virtual std::shared_ptr<ecore::EReference> getLibraryModel_Attribute_authors() const = 0;
			virtual std::shared_ptr<ecore::EReference> getLibraryModel_Attribute_book() const = 0;
			
			virtual std::shared_ptr<ecore::EOperation> getLibraryModel_Operation_printLibrary() const = 0;
			
			// End Class LibraryModel


			// Begin Class NamedElement
			//Class and Feature IDs 
			static const unsigned long NAMEDELEMENT_CLASS = 5815454;
			static const unsigned int NAMEDELEMENT_CLASS_FEATURE_COUNT = 1;
			static const unsigned int NAMEDELEMENT_CLASS_OPERATION_COUNT = 0;
			static const unsigned long NAMEDELEMENT_ATTRIBUTE_NAME = 1957408610;
			
			
			
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getNamedElement_Class() const = 0;
			
			virtual std::shared_ptr<ecore::EAttribute> getNamedElement_Attribute_name() const = 0;
			
			
			
			// End Class NamedElement


			// Begin Class Picture
			//Class and Feature IDs 
			static const unsigned long PICTURE_CLASS = 6098234;
			static const unsigned int PICTURE_CLASS_FEATURE_COUNT = 3;
			static const unsigned int PICTURE_CLASS_OPERATION_COUNT = 0;
			static const unsigned long PICTURE_ATTRIBUTE_PAGENUMBER = 2018757679;
			
			static const unsigned long PICTURE_ATTRIBUTE_BOOK = 1332323388;
			
			
			//Class and Feature Getter
			virtual std::shared_ptr<ecore::EClass> getPicture_Class() const = 0;
			
			virtual std::shared_ptr<ecore::EAttribute> getPicture_Attribute_pageNumber() const = 0;
			
			virtual std::shared_ptr<ecore::EReference> getPicture_Attribute_book() const = 0;
			
			
			// End Class Picture

			
			

			

			//Singleton Instance and Getter
			private:
				static std::shared_ptr<libraryModel_ecorePackage> instance;
			public:
				static std::shared_ptr<libraryModel_ecorePackage> eInstance();
	};
}
#endif /* end of include guard: LIBRARYMODEL_ECOREPACKAGE_HPP */
