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
	virtual void PossessedBy(AController* NewController) override;

	// Player controller of this pawn
	APlayerController* PlayerController;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	// =============== These settings have been transferred to the controller =============== //
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Controls", meta = (UIMin = 0.5f, UIMax = 10.0f))
	//float TouchMoveSensitivity;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|AreaSettings", meta = (UIMin = 0.0f))
	//FVector2D MoveLimit;
};
