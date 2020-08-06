// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "testweapon.generated.h"

class Atestcharacter;
class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class TESTRPG_API Atestweapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Atestweapon();
	/* Handles the line tracing of our weapon */
	void Attack();
	/* Triggers equip event when character overlaps with the weapon */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/* Trigger events after the character is no longer overlapping with the weapon */
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void Equip(Atestcharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	/* Will be the parent to which everything will be attach to */
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	/* Collision that will trigger the OnOverlapBegin and OnOverlapEnd */
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	USphereComponent* CollisionSphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	AController * GetOwningController() const;

};
