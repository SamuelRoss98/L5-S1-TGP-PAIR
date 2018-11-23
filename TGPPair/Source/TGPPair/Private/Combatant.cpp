// Fill out your copyright notice in the Description page of Project Settings.

#include "Combatant.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

#include "CombatantAIController.h"
#include "CombatantPlayerController.h"

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
void ACombatant::LoadCombatant(FCharacterProperties Properties, bool bPlayer)
{
	CharacterName = Properties.CharacterName;
	BaseCombatAttributes = Properties.CombatAttributes;
	CurrentCombatAttributes = BaseCombatAttributes;

	SpawnCombatantController(bPlayer);

	UE_LOG(LogTemp, Log, TEXT("Combatant loaded: %s"), *(Properties.CharacterName))
}

// Returns the interaction point Transform.
FTransform ACombatant::GetInteractionTransform() const
{
	return InteractionPoint->GetComponentTransform();
}

bool ACombatant::GetActedThisTurn() const
{
	return bActedThisTurn;
}

// Spawn the controller for this Combatant.
void ACombatant::SpawnCombatantController(bool bPlayer)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.OverrideLevel = GetLevel();

	if(bPlayer)
		CombatantController = GetWorld()->SpawnActor<ICombatantDecisionMaking>(CombatantPlayerControllerClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	else
		CombatantController = GetWorld()->SpawnActor<ICombatantDecisionMaking>(CombatantAIControllerClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (CombatantController != nullptr)
		Cast<AController>(CombatantController)->Possess(this);
}

