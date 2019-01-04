// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPlayer.h"

// Set the values of the CombatPlayer.
void UCombatPlayer::SetValues(FString name, int availableSkillPoints, int overallLevel, int expAtLevel, int manaSkill, int strengthSkill, int luckSkill, int defenseSkill, int speedSkill)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting level val: %s"), *FString::FromInt(overallLevel))
	PlayerName = name;
	AvailableSkillPoints = availableSkillPoints;
	OverallLevel = overallLevel;
	ExpEarnedAtCurrentLevel = expAtLevel;
	SkillLevelMana = manaSkill;
	SkillLevelDefense = defenseSkill;
	SkillLevelLuck = luckSkill;
	SkillLevelSpeed = speedSkill;
	SkillLevelStrength = strengthSkill;
}

// Returns the players name.
FString UCombatPlayer::GetPlayerName() const
{
	return PlayerName;
}

// Returns the amount of available (unspent) skillpoints.
int UCombatPlayer::GetAvailableSkillPoints()
{
	return AvailableSkillPoints;
}

// Returns the player stat pack based on their level/skills.
FStatPack UCombatPlayer::GetPlayerStatPack() const
{
	FStatPack Stats = FStatPack();

	Stats.Health = 90 + (10 * OverallLevel);
	Stats.Mana = 30 + (5 * SkillLevelMana);
	Stats.Luck = 4 * SkillLevelLuck;
	Stats.Speed = 3 * SkillLevelSpeed;
	Stats.MeleeAttack = 500 + (3 * SkillLevelStrength);
	Stats.MeleeDefense = 2 * SkillLevelDefense;

	return Stats;
}

// Called to award the player exp.
void UCombatPlayer::AwardExp(int Amount)
{
	FString print = FString::FromInt(Amount);
	UE_LOG(LogTemp, Warning, TEXT("Player was awarded %s exp."), *print)

	if (Amount < GetExpToNextLevel())
		ExpEarnedAtCurrentLevel += Amount;

	else if (Amount == GetExpToNextLevel())
		LevelUp();

	else
	{
		Amount -= GetExpToNextLevel();
		LevelUp();
		AwardExp(Amount);
	}
}

// Returns the amount of exp between two levels [a < b].
int UCombatPlayer::GetExpBetweenLevels(int a, int b)
{
	if (a >= b)
		return 0;

	return ExpFunction(b) - ExpFunction(a);
}

// Returns the amount of exp needed to level up.
int UCombatPlayer::GetExpToNextLevel()
{
	return GetExpBetweenLevels(OverallLevel, OverallLevel + 1) - ExpEarnedAtCurrentLevel;
}

// Returns how much experience the player has at their current level.
int UCombatPlayer::GetExpEarnedAtCurrentLevel()
{
	return ExpEarnedAtCurrentLevel;
}

// Returns the players current level.
int UCombatPlayer::GetOverallLevel()
{
	return OverallLevel;
}

// Returns the level of a requested skill.
int UCombatPlayer::GetSkillLevel(EPlayerSkillType Type)
{
	switch (Type)
	{
	case EPlayerSkillType::Mana:
		return SkillLevelMana;
	case EPlayerSkillType::Luck:
		return SkillLevelLuck;
	case EPlayerSkillType::Strength:
		return SkillLevelStrength;
	case EPlayerSkillType::Defense:
		return SkillLevelDefense;
	case EPlayerSkillType::Speed:
		return SkillLevelSpeed;
	default:
		return 0;
	}
}

// Increases the players level.
void UCombatPlayer::LevelUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Player levelled up!"))
	OverallLevel++;
	ExpEarnedAtCurrentLevel = 0;
	AvailableSkillPoints++;
}

// Function used to calculate exp between levels.
int UCombatPlayer::ExpFunction(int level)
{
	float exp = 100.0f + (25.0f * FMath::Pow((float)level, 1.64f));
	return (int)exp;
}

