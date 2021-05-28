// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCameraPawn.generated.h"

UCLASS()
class ZOMBIEGAME_API APlayerCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void PossessedBy(AController* NewController) override;

	APlayerController* PlayerController;

	FVector2D MoveLimit;
private:

	FVector2D TouchLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls", meta = (UIMin = 0.5f, UIMax = 10.0f))
	float TouchMoveSensitivity;
};
