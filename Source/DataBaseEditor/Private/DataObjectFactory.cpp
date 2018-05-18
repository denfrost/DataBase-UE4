#include "DataObjectFactory.h"
#include "DataObject.h"

UDataObjectFactory::UDataObjectFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UDataObject::StaticClass();
	bText = true;
	bEditorImport = true;
	// Tells the Editor which file types we can import
	Formats.Add(TEXT("uej;uej files"));
}

UDataObjectFactory::~UDataObjectFactory()
{

}

UObject* UDataObjectFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UDataObject* DataObject = nullptr;
	if (ensure(UDataObject::StaticClass() == InClass))
	{
		DataObject = NewObject<UDataObject>(InParent, InName, Flags);
		return DataObject;
	}
	return nullptr;
}

UObject* UDataObjectFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UDataObject* DataObject = nullptr;
	if (ensure(UDataObject::StaticClass() == InClass))
	{
		DataObject = NewObject<UDataObject>(InParent, InName, Flags);
		return DataObject;
	}
	return nullptr;
}

bool UDataObjectFactory::DoesSupportClass(UClass* Class)
{
	return false;
}

bool UDataObjectFactory::FactoryCanImport(const FString& Filename)
{
	return true;
}


