// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraPawn.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
{
	// Create RootScene:
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// Create spring arm and attach it to RootScene:
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);

	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 2000.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.0f;

	// Create camera and attach it to SpringArm:
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Get new player controller
void APlayerCameraPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}


//void APlayerCameraPawn::OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
//{
//	UE_LOG(LogType, Log, TEXT("OnTouchReleased"));
//
//	// Delta vector between press and release
//	//FVector2D TouchDeltaRelease = FVector2D(PressTouchLocation.X - Location.X, PressTouchLocation.Y - Location.Y);
//	
//	FHitResult Hit;
//	bool bHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
//
//	//UE_LOG(LogTemp, Log, TEXT("bool "), FString::ToBool(bHit));
//	if (bHit)
//	{
//		DrawDebugBox(GetWorld(), Hit.Location, FVector(10), FColor::Red, true, 10, 0U, 10.f);
//		UE_LOG(LogTemp, Log, TEXT("DebugBox drawn in: %s"), *Hit.Location.ToString());
//	}
//
//
//}