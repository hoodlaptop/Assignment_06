#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LavaFloor.generated.h"

UCLASS()
class ASSIGNMENT_06_API ALavaFloor : public AActor
{
	GENERATED_BODY()
	
public:
	ALavaFloor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LavaFloor|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LavaFloor|Components")
	UStaticMeshComponent* LavaMesh;

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void OnLavaOverlap(
		  UPrimitiveComponent* OverlappedComp,
		  AActor* OtherActor,
		  UPrimitiveComponent* OtherComp,
		  int32 OtherBodyIndex,
		  bool bFromSweep,
		  const FHitResult& SweepResult);
};
