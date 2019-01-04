// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPlayer.h"

// Returns the player stat pack based on their level/skills.
FStatPack UCombatPlayer::GetPlayerStatPack() const
{
	FStatPack Stats = FStatPack();

	Stats.Health = 90 + (10 * OverallLevel);
	Stats.Mana = 30 + (5 * SkillInvestmentMana);
	Stats.Luck = 4 * SkillInvestmentLuck;
	Stats.Speed = 3 * SkillInvestmentSpeed;
	Stats.MeleeAttack = 5 + (3 * SkillInvestmentStrength);
	Stats.MeleeDefense = 2 * SkillInvestmentDefense;

	return Stats;
}

// Called to award the player exp.
void UCombatPlayer::AwardExp(int Amount)
{
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

// Increases the players level.
void UCombatPlayer::LevelUp()
{
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

