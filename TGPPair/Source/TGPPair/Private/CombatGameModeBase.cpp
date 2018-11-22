// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameModeBase.h"

#include "Combatant.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"

// Called when the game starts or when spawned
void ACombatGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SpawnCombatants();
	
	TArray<FName> Names = CombatantDataTable->GetRowNames();
	for (int i = 0; i < Names.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Names[i].ToString()))
	}
}

// Called every frame
void ACombatGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

// Spawns the combatants.
void ACombatGameModeBase::SpawnCombatants()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRot = FRotator::ZeroRotator;

	ACombatant * NewCombatant = nullptr;
	
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPointA, &SpawnRot, SpawnParams));
	if (NewCombatant)
		AllCombatants.Add(NewCombatant);
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPointB, &SpawnRot, SpawnParams));
	if (NewCombatant)
		AllCombatants.Add(NewCombatant);
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPointC, &SpawnRot, SpawnParams));
	if (NewCombatant)
		AllCombatants.Add(NewCombatant);
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPointD, &SpawnRot, SpawnParams));
	if (NewCombatant)
		AllCombatants.Add(NewCombatant);
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPointE, &SpawnRot, SpawnParams));
	if (NewCombatant)
		AllCombatants.Add(NewCombatant);
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPointF, &SpawnRot, SpawnParams));
	if (NewCombatant)
		AllCombatants.Add(NewCombatant);
}

