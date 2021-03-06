// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "StatPack.generated.h"

USTRUCT(BlueprintType)
struct FStatPack
{
	GENERATED_USTRUCT_BODY()

public:
	FStatPack() :
		Health(0),
		Mana(0),
		MeleeAttack(0),
		MagicAttack(0),
		MeleeDefense(0),
		MagicDefense(0),
		Speed(0),
		Luck(0),
		Charisma(0),
		Value(0)
	{}

	FStatPack(int health, int mana, int meleeAtk, int meleeDef, int magicAtk, int magicDef, int speed, int luck, int charisma, int val) :
		Health(health),
		Mana(mana),
		MeleeAttack(meleeAtk),
		MagicAttack(magicAtk),
		MeleeDefense(meleeDef),
		MagicDefense(magicDef),
		Speed(speed),
		Luck(luck),
		Charisma(charisma),
		Value(val)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MeleeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MagicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MeleeDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MagicDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Luck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Charisma;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Value;
};