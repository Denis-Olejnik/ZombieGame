// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCameraController.generated.h"


UCLASS()
class ZOMBIEGAME_API APlayerCameraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerCameraController();

protected:
	// PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
	void SpawnActorUnderMouseCursor();
	void SpawnActorUnderTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SpawnActor(FVector SpawnLoc);

private:
	FVector2D TouchLocation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (UIMin = 0.5f, UIMax = 10.0f))
	float TouchMoveSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (UIMin = 0.0f))
	FVector2D MoveLimit;
};
