#include "LavaFloor.h"

#include "GameFramework/Character.h"

ALavaFloor::ALavaFloor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);
	
	LavaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LavaMesh"));
	LavaMesh->SetupAttachment(SceneRoot);
	LavaMesh->SetGenerateOverlapEvents(true);
}

void ALavaFloor::BeginPlay()
{
	Super::BeginPlay();
	LavaMesh->OnComponentBeginOverlap.AddDynamic(this, &ALavaFloor::OnLavaOverlap);
}

void ALavaFloor::OnLavaOverlap(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		Character->Destroy();
	}
}

