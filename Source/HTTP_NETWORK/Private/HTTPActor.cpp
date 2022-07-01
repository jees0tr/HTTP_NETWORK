// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPActor.h"

// Sets default values
AHTTPActor::AHTTPActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AHTTPActor::BeginPlay()
{
	Super::BeginPlay();
}

void AHTTPActor::RunHTTP(FString Url)
{
	//FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &AHTTPActor::OnResponseReceived);
	//Request->SetURL("127.0.0.1:8080");
	//Request->SetURL(Url);
	//Request->SetVerb("GET");
	//Request->ProcessRequest();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	//기존에 가입되지 않은 경우 신규 가입 페이지로 연결
	if (Url.IsEmpty())	
	{
		//Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::);
		//Request->SetURL("http://localhost:3000//");
	}
	//기존에 가입된 회원의 경우 로그인 처리 진행
	else
	{
		Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnGetUserInfoResponse);
		//Request->SetURL(FString::Printf(TEXT("http:/localhost:3000//api/get/demo"), *Url));
		const FString URL = "http://localhost:3000/api/get/demo";
		Request->SetURL(*URL);
	}

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

// Called every frame
void AHTTPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHTTPActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSucesfully)
{
	UE_LOG(LogTemp, Display, TEXT("Response &s"), *Response->GetContentAsString());
}

void AHTTPActor::OnGetUserInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;

	if (Response->GetResponseCode() == 200)
	{
		const FString ResponseBody = Response->GetContentAsString();
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			ParsingData(JsonObject);
		}
	}
	else
	{
		// TODO: trigger error
		//UE_LOG(LogTemp, Display, TEXT("Error occured : &d"), Response->GetResponseCode());
	}
}

void AHTTPActor::ParsingData(TSharedPtr<FJsonObject> JsonObject)
{
	FString message = JsonObject->GetStringField("message");

	UE_LOG(LogTemp, Display, TEXT("message : &s"), *message);
}