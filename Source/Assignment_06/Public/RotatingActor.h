#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class ASSIGNMENT_06_API ARotatingActor : public AActor
{
	GENERATED_BODY()

public:
	ARotatingActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingActor|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingActor|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingActor|Movement")
	float RotateSpeed = 90.0f;

	// Controls whether the actor rotates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingActor|Timer")
	bool bIsActive = true;

	// If true, the actor will disappear after DisappearTime seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingActor|Timer")
	bool bShouldDisappear = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatingActor|Timer")
	float DisappearTime = 3.0f;

	// Call this after spawn to enable the disappear timer with a custom time
	void SetupDisappearTimer(float Time);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Rotate(float DeltaTime);
	void Disappear();

	FTimerHandle DisappearTimerHandle;
};
