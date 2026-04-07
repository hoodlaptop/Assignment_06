#include "../Public/MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

	// Set disappear timer if enabled via editor
	if (bShouldDisappear)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DisappearTimerHandle, this, &AMovingActor::Disappear, DisappearTime, false);
	}
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void AMovingActor::Move(float DeltaTime)
{
	if (!bIsActive) return;

	FVector CurrentLocation = GetActorLocation();
	float DistanceMoved = FVector::Dist(CurrentLocation, StartLocation);

	if (DistanceMoved >= MaxRange)
	{
		bMovingForward = !bMovingForward;
	}

	FVector Direction = bMovingForward ? GetActorForwardVector() : -GetActorForwardVector();
	SetActorLocation(CurrentLocation + Direction * MovingSpeed * DeltaTime);
}

void AMovingActor::Disappear()
{
	Destroy();
}

// Called from spawner to force enable disappear timer with a random time
void AMovingActor::SetupDisappearTimer(float Time)
{
	GetWorld()->GetTimerManager().SetTimer(
		DisappearTimerHandle, this, &AMovingActor::Disappear, Time, false);
}
