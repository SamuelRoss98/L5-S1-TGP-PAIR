// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameMode.h"

#include "Engine/World.h"

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SpawnCombatants();
}

void ACombatGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ACombatGameMode::SpawnCombatants()
{
	FActorSpawnParameters Params;

	FVector PlayerSpawn = FVector(0.0f, 300.0f, 0.0f);
	FVector EnemySpawn = FVector(0.0f, -300.0f, 0.0f);
	FRotator SpawnRot = FRotator::ZeroRotator;

	Player = Cast<ACombatant>(GetWorld()->SpawnActor(PlayerClass, &PlayerSpawn, &SpawnRot, Params));
	Enemy = Cast<ACombatant>(GetWorld()->SpawnActor(EnemyClass, &EnemySpawn, &SpawnRot, Params));
}


