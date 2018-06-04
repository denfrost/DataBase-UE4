#include "HttpGet.h"
#include "DataObject.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"

UHttpGET::UHttpGET(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}

void UHttpGET::Start(FString URL, const TArray<FHttpHeader>& Headers)
{
#if !UE_SERVER
	// Create the Http request and add to pending request list
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpGET::HandleRequest);
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	for (auto& Header : Headers)
	{
		HttpRequest->SetHeader(Header.Key, Header.Value);
	}
	HttpRequest->ProcessRequest();
#else
	// On the server we don't execute fail or success we just don't fire the request.
	RemoveFromRoot();
#endif
}

UHttpGET* UHttpGET::GetRequest(FString URL, const TArray<FHttpHeader>& Headers)
{
	UHttpGET* DownloadTask = NewObject<UHttpGET>();
	DownloadTask->Start(URL,Headers);

	return DownloadTask;
}

void UHttpGET::HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded && HttpResponse.IsValid() && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		FJsonData Json;
		Json.Json = MakeShareable(new FJsonObject());
		TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(JsonReader, Json.Json) && Json.Json.IsValid())
		{
			OnSuccess.Broadcast(Json, HttpResponse->GetContentAsString());
			return;
		}
		OnFail.Broadcast(FJsonData::GetDefault(), "Error: Deserialize");
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Request Code Error: %i"), HttpResponse->GetResponseCode());
	OnFail.Broadcast(FJsonData::GetDefault(), HttpResponse->GetContentAsString());
}

