// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "HTTPActor.generated.h"

UCLASS(BlueprintType)
class HTTP_NETWORK_API AHTTPActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHTTPActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RunHTTP(FString Url);

private:
	FHttpModule* Http;
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSucessfully);
	void OnGetUserInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void ParsingData(TSharedPtr<FJsonObject> JsonObject);
};
