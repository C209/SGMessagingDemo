// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ISGMessageBus.h"
#include "Common/SGMessageEndpoint.h"
#include "MessageBusType.h"
#include "MessageBusRequest.generated.h"

UCLASS()
class SGMESSAGINGDEMO_API AMessageBusRequest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMessageBusRequest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OnReply(const FTestReplyMessage& Message, const TSharedRef<ISGMessageContext, ESPMode::ThreadSafe>& Context);

public:
	/** Holds a pointer to the message bus. */
	TSharedPtr<ISGMessageBus, ESPMode::ThreadSafe> MessageBus;

	/** Holds the messaging endpoint. */
	TSharedPtr<FSGMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;
};
