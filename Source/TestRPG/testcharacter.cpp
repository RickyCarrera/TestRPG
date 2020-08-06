// Fill out your copyright notice in the Description page of Project Settings.


#include "testcharacter.h"

// Sets default values
Atestcharacter::Atestcharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Atestcharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Atestcharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Atestcharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

