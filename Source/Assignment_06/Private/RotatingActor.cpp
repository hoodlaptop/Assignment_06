#include "../Public/RotatingActor.h"

ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();

	// Set disappear timer if enabled via editor
	if (bShouldDisappear)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DisappearTimerHandle, this, &ARotatingActor::Disappear, DisappearTime, false);
	}
}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(DeltaTime);
}

void ARotatingActor::Rotate(float DeltaTime)
{
	if (!bIsActive) return;

	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));
}

void ARotatingActor::Disappear()
{
	Destroy();
}

// Called from spawner to force enable disappear timer with a random time
void ARotatingActor::SetupDisappearTimer(float Time)
{
	GetWorld()->GetTimerManager().SetTimer(
		DisappearTimerHandle, this, &ARotatingActor::Disappear, Time, false);
}
