#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class ASSIGNMENT_06_API AMovingActor : public AActor
{
	GENERATED_BODY()

public:
	AMovingActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Movement")
	float MovingSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Movement")
	float MaxRange = 500.0f;

	// Controls whether the actor moves
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Timer")
	bool bIsActive = true;

	// If true, the actor will disappear after DisappearTime seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Timer")
	bool bShouldDisappear = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingActor|Timer")
	float DisappearTime = 3.0f;

	// Call this after spawn to enable the disappear timer with a custom time
	void SetupDisappearTimer(float Time);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Move(float DeltaTime);
	void Disappear();

	bool bMovingForward = true;
	FVector StartLocation;
	FTimerHandle DisappearTimerHandle;
};
