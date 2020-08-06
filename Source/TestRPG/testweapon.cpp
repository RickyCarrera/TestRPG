// Fill out your copyright notice in the Description page of Project Settings.


#include "testweapon.h"
#include "testcharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Atestweapon::Atestweapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(RootComp);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(RootComp);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	WeaponMesh->SetupAttachment(RootComp);

}

// Called when the game starts or when spawned
void Atestweapon::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &Atestweapon::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &Atestweapon::OnOverlapEnd);
}

// Called every frame
void Atestweapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Attack();
}

void Atestweapon::Attack()
{
	AController* OwningPawn = GetOwningController();
	if (!OwningPawn)
	{
		return;
	}

	FVector StartPoint = WeaponMesh->GetSocketLocation("BaseSocket");
	FVector EndPoint = WeaponMesh->GetSocketLocation("TipSocket");

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	bool HitSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Params);
	if (HitSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("This was hit %s"), *HitResult.GetActor()->GetName());
	}
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1.0, 0, 2.0);
}

void Atestweapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		Atestcharacter* Main = Cast<Atestcharacter>(OtherActor);
		if (Main)
		{
			Main->SetActiveOverlappingWeapon(this);
		}
	}
}

void Atestweapon::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		Atestcharacter* Main = Cast<Atestcharacter>(OtherActor);
		if (Main)
		{
			Main->SetActiveOverlappingWeapon(nullptr);
		}
	}
}

void Atestweapon::Equip(Atestcharacter * Character)
{
	if (Character)
	{
		GetOwningController();
		WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		WeaponMesh->SetSimulatePhysics(false);
		// Attach Weapon to the socket on the character.
		const USkeletalMeshSocket* SocketToAttach = Character->GetMesh()->GetSocketByName("WeaponSocket");
		if (SocketToAttach)
		{
			SocketToAttach->AttachActor(this, Character->GetMesh());
			Character->SetEquippedWeapon(this);
			Character->SetActiveOverlappingWeapon(nullptr);
		}
	}
}

AController *Atestweapon::GetOwningController() const
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (!OwningPawn)
	{
		return nullptr;
	}
	return OwningPawn->GetController();
}

