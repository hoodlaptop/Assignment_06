#include "../Public/PlatformSpawner.h"

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle, this, &APlatformSpawner::SpawnPlatform, SpawnInterval, true);
}

void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformSpawner::SpawnPlatform()
{
	for (int i = 0; i < SpawnCount; ++i)
	{
		float RandX = FMath::RandRange(-SpawnRangeXY, SpawnRangeXY);
		float RandY = FMath::RandRange(-SpawnRangeXY, SpawnRangeXY);
		
		FVector SpawnLocation = GetActorLocation() + FVector(RandX, RandY, 0.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		// Spawn RotatingActor
		ARotatingActor* Rotating = GetWorld()->SpawnActor<ARotatingActor>(
			RotatingActorClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		if (Rotating)
		{
			Rotating->RotateSpeed = FMath::RandRange(30.0f, 180.0f);
			Rotating->SetupDisappearTimer(FMath::RandRange(1.0f, 5.0f));
		}
		
		// Spawn MovingActor
		AMovingActor* Moving = GetWorld()->SpawnActor<AMovingActor>(
			MovingActorClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (Moving)
		{
			Moving->MovingSpeed = FMath::RandRange(100.0f, 500.0f);
			Moving->MaxRange = FMath::RandRange(300.0f, 1000.0f);
			Moving->SetupDisappearTimer(FMath::RandRange(1.0f, 5.0f));
		}
	}
}

