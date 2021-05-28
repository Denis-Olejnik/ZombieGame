// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraPawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
	:
	TouchMoveSensitivity(5.0f),
	MoveLimit(FVector2D(2400.0f, 2400.0f))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// Create spring arm and setup it:
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 2000.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	// Camera lag enables smooth panning
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Get new player controller
void APlayerCameraPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
	
	if (PlayerController)
	{
		// This allows the cursor to be displayed:
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}

// Called when the game starts or when spawned
void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void APlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerCameraPawn::OnTouchPress);

	InputComponent->BindTouch(IE_Repeat, this, &APlayerCameraPawn::OnTouchMove);
}


// Touch controls
void APlayerCameraPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	// Delta move:
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

	// Apply sensitivity to touch:
	TouchDeltaMove = TouchDeltaMove * TouchMoveSensitivity;

	// Camera move restrictions on the map.
	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y * -1.0f, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X, -MoveLimit.X, MoveLimit.X);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerCameraPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);
}
