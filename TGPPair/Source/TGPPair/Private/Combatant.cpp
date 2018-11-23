// Fill out your copyright notice in the Description page of Project Settings.

#include "Combatant.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACombatant::ACombatant()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("CombatantStaticMesh");
	InteractionPoint = CreateDefaultSubobject<USceneComponent>("InteractionPoint");

	RootComponent = Mesh;
	InteractionPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACombatant::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Initialize this combatant with a CharacterProperties structure.
void ACombatant::LoadCombatant(FCharacterProperties Properties)
{
	CharacterName = Properties.CharacterName;
	BaseCombatAttributes = Properties.CombatAttributes;
	CurrentCombatAttributes = BaseCombatAttributes;

	UE_LOG(LogTemp, Log, TEXT("Combatant loaded: %s"), *(Properties.CharacterName))
}

// Returns the interaction point Transform.
FTransform ACombatant::GetInteractionTransform() const
{
	return InteractionPoint->GetComponentTransform();
}

