// Fill out your copyright notice in the Description page of Project Settings.


#include "testcharacter.h"
#include "testweapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
Atestcharacter::Atestcharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void Atestcharacter::BeginPlay()
{
	Super::BeginPlay();

	// attachs to weapon to the socket when game starts.
	Weapon = GetWorld()->SpawnActor<Atestweapon>(WeaponClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
	
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

	PlayerInputComponent->BindAxis("MoveForward", this, &Atestcharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Atestcharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &Atestcharacter::Attack);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &Atestcharacter::EquippedPressed);

}

void Atestcharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void Atestcharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}


void Atestcharacter::SetEquippedWeapon(Atestweapon * WeaponToSet)
{
	if (Weapon)
	{
		Weapon->Destroy(); // if a weapon is already equipped destroy it and replace with new weapon.
	}
	Weapon = WeaponToSet;
}

void Atestcharacter::Attack()
{
	if (Weapon)
	{
		PlayAnimMontage(AttackMontage);
		Weapon->Attack();
	}
}

void Atestcharacter::EquippedPressed()
{
	if (ActiveOverlappingWeapon)
	{
		Atestweapon* weapon = Cast<Atestweapon>(ActiveOverlappingWeapon);
		if (weapon)
		{
			weapon->Equip(this);
			SetActiveOverlappingWeapon(nullptr);
		}
	}
}