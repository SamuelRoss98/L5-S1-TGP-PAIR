// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameModeBase.h"

#include "Engine/World.h"
#include "CombatantPawn.h"
#include "CombatDecisionInterface.h"
#include "CombatPlayerController.h"
#include "CombatAIController.h"
#include "TGPPairGameInstance.h"

// Called when the game starts or when spawned
void ACombatGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnCombatants();
}

// Called every frame
void ACombatGameModeBase::Tick(float DeltaTime)
{
}

// Resets the combatants ready for a new round.
void ACombatGameModeBase::ResetForNewRound()
{
	UE_LOG(LogTemp, Error, TEXT("Reset for new round."))
	for (int i = 0; i < EnemyCombatants.Num(); ++i)
	{
		if (EnemyCombatants[i] != nullptr)
		{
			EnemyCombatants[i]->SetTurnTaken(false);
			EnemyCombatants[i]->MakeCombatDescision();
		}
	}

	if (PlayerCombatant != nullptr)
	{
		PlayerCombatant->SetTurnTaken(false);
		PlayerCombatant->MakeCombatDescision();
	}
}

// Called once all decisions are made to start simulating the actions.
void ACombatGameModeBase::SimulateNextAction()
{
	CheckForBattleFinish();

	if (!bBattleOver)
	{
		if (IsEndOfRound())
		{
			ResetForNewRound();
			return;
		}

		ACombatantPawn* NextToAct = GetNextCombatantToAct();
		if (NextToAct != nullptr)
		{
			if (!NextToAct->GetTurnTaken())
			{
				// Update the combat log to reflect the next action.
				FString ActionDesc = NextToAct->GetActionDescription(PlayerCombatant, EnemyCombatants);
				ACombatPlayerController* CombatPlayerController = Cast<ACombatPlayerController>(GetWorld()->GetFirstPlayerController());
				if (CombatPlayerController != nullptr)
					CombatPlayerController->UpdateCombatLogText(ActionDesc);

				if (NextToAct->IsDead())
					NextToAct->EndTurn();
				else
					NextToAct->TakeTurn();
			}
		}
	}
}

// Return the enemy combatant pawns.
TArray<ACombatantPawn*> ACombatGameModeBase::GetEnemies() const
{
	return EnemyCombatants;
}

// Returns the item data with the given name.
FNamedStatPack ACombatGameModeBase::GetItemFromName(FString name)
{
	TArray<FNamedStatPack*> outItems;
	ItemsDataTable->GetAllRows<FNamedStatPack>("GENERAL", outItems);

	for (int i = 0; i < outItems.Num(); ++i)
		if (outItems[i]->Name == name)
			return *outItems[i];

	return FNamedStatPack();
}

// Returns the items data table.
UDataTable* ACombatGameModeBase::GetItemsData() const 
{
	return ItemsDataTable;
}

// Returns the target of a given action.
ACombatantPawn* ACombatGameModeBase::GetActionTarget(bool bIsPlayer, FCombatAction Action)
{
	if (!bIsPlayer)
		return PlayerCombatant;

	else return EnemyCombatants[Action.TargetIndex];
}

// Called to check if the battle is complete.
void ACombatGameModeBase::CheckForBattleFinish()
{
	// Player is dead, loss.
	if (PlayerCombatant->IsDead())
		return HandleFinishLoss();

	// Check for any living enemy.
	bool bLivingEnemy = false;
	for (int i = 0; i < EnemyCombatants.Num(); ++i)
		if (!EnemyCombatants[i]->IsDead())
			bLivingEnemy = true;

	// No living enemies, player won.
	if (!bLivingEnemy)
		return HandleFinishVictory();
}

// Called regardless of victory or loss to complete shared tasks (hiding battle UI etc.).
void ACombatGameModeBase::HandleFinish()
{
	bBattleOver = true;

	// Notify player controller the battle is over.
	ACombatPlayerController* CombatPlayerController = Cast<ACombatPlayerController>(GetWorld()->GetFirstPlayerController());
	if (CombatPlayerController != nullptr)
		CombatPlayerController->EndOfBattle();
}

// Called when the battle has finished with player victory.
void ACombatGameModeBase::HandleFinishVictory()
{
	HandleFinish();

	// Update won battles counter.
	UTGPPairGameInstance* GameInst = Cast<UTGPPairGameInstance>(GetGameInstance());
	if (GameInst != nullptr)
		GameInst->IncrementWonBattles();

	LoadEndOfBattleUI(true);
}

// Called when the battle has finished with player loss.
void ACombatGameModeBase::HandleFinishLoss()
{
	HandleFinish();
	LoadEndOfBattleUI(false);
}


// Returns a random character from the enemies data table.
FNamedStatPack ACombatGameModeBase::GetRandomCharacter()
{
	TArray<FNamedStatPack*> outItems;
	EnemiesDataTable->GetAllRows<FNamedStatPack>("GENERAL", outItems);

	int randomIndex = FMath::RandRange(0, outItems.Num() - 1);
	return *outItems[randomIndex];
}

// Returns the next combatant to act this round.
ACombatantPawn* ACombatGameModeBase::GetNextCombatantToAct() const
{
	ACombatantPawn * NextToAct = nullptr;
	int CurrentHighSpeed = -99999;

	for (int i = 0; i < AllCombatants.Num(); ++i)
	{
		if (AllCombatants[i]->GetStats().Speed > CurrentHighSpeed)
		{
			if (!AllCombatants[i]->GetTurnTaken())
			{
				CurrentHighSpeed = AllCombatants[i]->GetStats().Speed;
				NextToAct = AllCombatants[i];
			}
		}
	}

	return NextToAct;
}

// Returns true if all combatants have taken their turn.
bool ACombatGameModeBase::IsEndOfRound() const
{
	for (int i = 0; i < AllCombatants.Num(); ++i)
		if (!AllCombatants[i]->GetTurnTaken())
			return false;
	
	return true;
}

// Spawns combatants.
void ACombatGameModeBase::SpawnCombatants()
{
	// Check there are enough spawn locations given to spawn all combatants.
	if (EnemyCount + 1 > SpawnLocations.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("There are no enough spawn points to spawn the combatants."))
			return;
	}

	FVector SpawnLoc = FVector::ZeroVector;
	FRotator SpawnRot = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;

	// Spawn player.
	SpawnLoc = SpawnLocations[0];
	PlayerCombatant = Cast<ACombatantPawn>(GetWorld()->SpawnActor(CombatantClass, &SpawnLoc, &SpawnRot, SpawnParams));
	if (PlayerCombatant == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn the player combatant."))
			return;
	}
	AllCombatants.Add(PlayerCombatant);
	GetWorld()->GetFirstPlayerController()->SetPawn(PlayerCombatant);
	if (!PlayerCombatant->Initialize(FNamedStatPack(), true, Cast<ICombatDecisionInterface>(GetWorld()->GetFirstPlayerController())))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize the player combatant."))
			return;
	}

	// Spawn enemies.
	SpawnRot = FRotator(0.0f, 180.0f, 0.0f);
	for (int i = 0; i < EnemyCount; ++i)
	{
		// Create the enemy combatant.
		ACombatantPawn* NewEnemy = nullptr;
		SpawnLoc = SpawnLocations[i + 1];
		NewEnemy = Cast<ACombatantPawn>(GetWorld()->SpawnActor(CombatantClass, &SpawnLoc, &SpawnRot, SpawnParams));
		if (NewEnemy == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn an enemy combatant."))
				return;
		}

		// Create the AI controller.
		ACombatAIController* Controller = nullptr;
		Controller = Cast<ACombatAIController>(GetWorld()->SpawnActor(AIClass, &SpawnLoc, &SpawnRot, SpawnParams));
		if (Controller == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn an enemy combatant AI controller."))
				return;
		}
		Controller->SetPawn(NewEnemy);

		// Init the enemy combatant.
		if (!NewEnemy->Initialize(GetRandomCharacter(), false, Cast<ICombatDecisionInterface>(Controller)))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to initialize an enemy combatant."))
				return;
		}
		EnemyCombatants.Add(NewEnemy);
		AllCombatants.Add(NewEnemy);
	}

	StartNewRound();
}
