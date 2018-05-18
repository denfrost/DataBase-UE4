#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataObjectFactory.generated.h"

UCLASS()
class UDataObjectFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDataObjectFactory();
	virtual ~UDataObjectFactory();

	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

	/** Returns whether or not the given class is supported by this factory. */
	virtual bool DoesSupportClass(UClass* Class) override;

	/** Returns true if this factory can deal with the file sent in. */
	virtual bool FactoryCanImport(const FString& Filename) override;
	// End UFactory Interface

};
