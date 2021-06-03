// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Pawns/BasicPawn.h"
#include "PlayerCameraController.generated.h"

// TODO: ��������� ����� ���� � PlayerCameraPawn (���������� � ������).
//		 � PlayerCameraController ������ ���������� ������ ���, ������������ �� �����������.
 

//					UE4 RTS Player Controller in C++ 
// https://www.youtube.com/watch?v=P8AR7OF7Vvc&ab_channel=TwoNeurons


UCLASS()
class ZOMBIEGAME_API APlayerCameraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerCameraController();

protected:
	// PlayerController interface
	virtual void SetupInputComponent() override;

	// TODO: ����������� ����� �����, ���� ���� �������, �� ������ �� ����������
	//		 ��������� �������: ����������� ����� �� PlayerCameraPawn, ������� ��������� ������ � OnTouchRelease.
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
	void SpawnActorUnderMouseCursor();
	void SpawnActorUnderTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SpawnActor(FHitResult HitResult);

private:
	FVector2D TouchLocation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = 0.5f, UIMax = 10.0f))
	float TouchMoveSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = 0.0f))
	FVector2D MoveLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class ABasicPawn> ActorToSpawn;

};
