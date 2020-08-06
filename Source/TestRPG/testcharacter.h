// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "testcharacter.generated.h"

class UAnimMontage;
class USpringArmComponent;
class UCameraComponent;
class Atestweapon;


UCLASS()
class TESTRPG_API Atestcharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Atestcharacter();

protected:
	/* Root component for the follow camera */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	/* the camera that the player will view the game through */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Handles the forward and back movement  */
	void MoveForward(float AxisValue);
	/* Handles the right and left movement */
	void MoveRight(float AxisValue);
	/* Calls the attack function from weapon class and plays animation montage */
	void Attack();
	/* Will equipped the weapon we are overlapping with when mapped key is pressed */
	void EquippedPressed();
	/* Plays the attack montage */
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;

	/* Reference to our Weapon */
	UPROPERTY(BlueprintReadWrite)
	Atestweapon* Weapon;
	/* The weapon we will overlap with in order to equipped it */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	Atestweapon * ActiveOverlappingWeapon;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<Atestweapon> WeaponClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetEquippedWeapon(Atestweapon* WeaponToSet);

	FORCEINLINE void SetActiveOverlappingWeapon(Atestweapon * WeaponBase) { ActiveOverlappingWeapon = WeaponBase; }


};
