#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DataObject.h"
#include "HttpGet.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHTTPResponse, FJsonData, Json, FString, msg);


USTRUCT(BlueprintType)
struct FHttpHeader
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http")
		FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http")
		FString Value;
};


UCLASS()
class UHttpGET : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()


public:
	void Start(FString URL, const TArray<FHttpHeader>& Headers);

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UHttpGET* GetRequest( FString URL, const TArray<FHttpHeader>& Headers);

	UPROPERTY(BlueprintAssignable)
		FHTTPResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FHTTPResponse OnFail;

	/** Handles image requests coming from the web */
	void HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

};