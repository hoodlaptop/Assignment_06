#pragma once

#include "CoreMinimal.h"
#include "RotatingActor.h"
#include "MovingActor.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class ASSIGNMENT_06_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformSpawner();

	UPROPERTY(EditAnywhere, Category = "Spawner|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	TSubclassOf<ARotatingActor> RotatingActorClass;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	TSubclassOf<AMovingActor> MovingActorClass;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	int32 SpawnCount = 5;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	float SpawnRangeXY = 1000.0f;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	float SpawnInterval = 3.0f;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnPlatform();
	
	FTimerHandle SpawnTimerHandle;
};
