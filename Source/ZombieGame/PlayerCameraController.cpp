// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "PlayerCameraPawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

APlayerCameraController::APlayerCameraController()
	:
	TouchMoveSensitivity(5.0f),
	MoveLimit(FVector2D(2400.0f, 2400.0f))
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	//SetInputMode(FInputModeGameOnly());
}

void APlayerCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("SpawnActor", IE_Pressed, this, &APlayerCameraController::);
	InputComponent->BindAction("SpawnActor", IE_Released, this, &APlayerCameraController::SpawnActorUnderMouseCursor);

	// support touch
	InputComponent->BindTouch(IE_Pressed, this, &APlayerCameraController::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerCameraController::OnTouchMove);
}

void APlayerCameraController::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerCameraController::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	// Delta move
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

	// Apply sensitivity to touch:
	TouchDeltaMove = TouchDeltaMove * TouchMoveSensitivity;

	// Camera move restrictions on the map.
	FVector NewLocation = GetPawn()->GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y * -1.0f, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X, -MoveLimit.X, MoveLimit.X);

	GetPawn()->SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerCameraController::SpawnActorUnderMouseCursor()
{
	FHitResult HitResult;
	
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something. Try to spawn
		SpawnActor(HitResult);
	}
}

void APlayerCameraController::SpawnActorUnderTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);
	FHitResult HitResult;

	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something. Try to spawn
		SpawnActor(HitResult);
	}
}

void APlayerCameraController::SpawnActor(FHitResult HitResult)
{
	FVector SpawnLoc(HitResult.ImpactPoint);
	FRotator SpawnRot(0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	if (IsValid(ActorToSpawn))
	{
		DrawDebugBox(GetWorld(), SpawnLoc, FVector(40.0f), FColor::Red, false, 10.0f, 0U, 3.0f);

		// TODO: Разобраться почему Pawn появляется по пояс в полу.
		//		 Возможное решение: брать высоту капсулы, делить её на половину и прибавлять к SpawnLoc.
		
		// TODO: Исправить баг, когда pawn можно заспавнить на крыше. Реализовать проверку поверхности?
		

		// TOOO: Вселять AIControllerPawn в текущий эктор.
		// 
		
		// TODO: Сделать Teams для павнов. 
		//		 Ссылка: https://www.youtube.com/watch?v=Il5bqRy3Z2w&ab_channel=TwoNeurons
		
		ABasicPawn* NewPawn = GetWorld()->SpawnActor<ABasicPawn>(ActorToSpawn, SpawnLoc, SpawnRot, SpawnParams);

		if (IsValid(NewPawn))
		{
			UE_LOG(LogTemp, Log, TEXT("Pawn %s spawned in %s"), *NewPawn->GetName(), *SpawnLoc.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Pawn not spawned! "));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn not spawned! PawnToSpawn is not valid"));
	}
	
}


