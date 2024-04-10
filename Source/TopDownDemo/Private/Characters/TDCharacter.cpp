// Fill out your copyright notice in the Description page of Project Settings.

#include "TDCharacter.h"
#include "TDHealthComponent.h"
#include "TDInteractionInterface.h"
#include "TDInventoryComponent.h"
#include "TDWeaponComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Equipment/TDEquipmentComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Objects/TDMedObject.h"

FName ATDCharacter::InventoryComponentName = FName("CharacterInventoryComp");
FName ATDCharacter::EquipmentComponentName = FName("CharacterEquipmentComp");
FName ATDCharacter::WeaponComponentName = FName("CharacterWeaponComp");
FName ATDCharacter::HealthComponentName = FName("CharacterHealthComp");

ATDCharacter::ATDCharacter()
{
	InventoryComponentClass = UTDInventoryComponent::StaticClass();
	EquipmentComponentClass = UTDEquipmentComponent::StaticClass();
	WeaponComponentClass = UTDWeaponComponent::StaticClass();
	HealthComponentClass = UTDHealthComponent::StaticClass();
	
	PrimaryActorTick.bCanEverTick = true;
}

void ATDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (WeaponComponent && WeaponComponent->bIsShooting)
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetHitResultUnderCursor().Location);
		SetActorRotation(FRotator(0.0f, TargetRotation.Yaw, 0.0f));
	}
}

void ATDCharacter::PreInitializeComponents()
{
	FindOrCreateComponents();
	Super::PreInitializeComponents();
}

void ATDCharacter::FindOrCreateComponents()
{
	/* Проверяем, имеется ли экземпляр компонента у персонажа.
	 * Если компонент валиден (имеется экземпляр блупринта), то перезаписываем поинтер.
	 * Если компонент не валиден, то создаем дефолтный по указанному в <имя компонента>Class классу и регистрируем его у
	 * персонажа. */

	InventoryComponent = GetComponentByClass<UTDInventoryComponent>();
	if (!InventoryComponent)
	{
		InventoryComponent = NewObject<UTDInventoryComponent>(this, InventoryComponentClass, InventoryComponentName);
		InventoryComponent->RegisterComponent();
	}
	
	EquipmentComponent = GetComponentByClass<UTDEquipmentComponent>();
	if (!EquipmentComponent)
	{
		EquipmentComponent = NewObject<UTDEquipmentComponent>(this, EquipmentComponentClass, EquipmentComponentName);
		EquipmentComponent->RegisterComponent();
	}

	WeaponComponent = GetComponentByClass<UTDWeaponComponent>();
	if (!WeaponComponent)
	{
		WeaponComponent = NewObject<UTDWeaponComponent>(this, WeaponComponentClass, WeaponComponentName);
		WeaponComponent->RegisterComponent();
	}
	
	HealthComponent = GetComponentByClass<UTDHealthComponent>();
	if (!HealthComponent)
	{
		HealthComponent = NewObject<UTDHealthComponent>(this, HealthComponentClass, HealthComponentName);
		HealthComponent->RegisterComponent();
	}
}

FHitResult ATDCharacter::GetHitResultUnderCursor()
{
	FHitResult HitResult;
	Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	return HitResult;
}

void ATDCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	check(EquipmentComponent);
	EquipmentComponent->InitEquipment();

	check(WeaponComponent);
	WeaponComponent->InitWeaponComponent(this);

	check(HealthComponent);
	HealthComponent->OnOwnerDiedDelegate.AddUObject(this, &ATDCharacter::OnCharacterDead);
	HealthComponent->InitHealthComponent(bIsDead);
}

void ATDCharacter::TryInteract(AActor* WithActor)
{
	check(WithActor);
	
	TargetToInteract = WithActor;

	/* Расчитаем дистанцию до предмета на плоскости XY, и, если она больше указанной, подходим к предмету на минимальное
	 * расстояние. */
	float Distance = FVector::Dist2D(GetActorLocation(), TargetToInteract->GetActorLocation());
	if (Distance > 100.0f)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), TargetToInteract.Get());
		
		FollowingComponent = GetController()->GetComponentByClass<UPathFollowingComponent>();
		if (FollowingComponent.IsValid() && FollowingComponent->GetStatus() == EPathFollowingStatus::Moving)
		{
			/* Биндимся к делегату остановки для последующего интеракшена. */
			StopMovingDelegate = FollowingComponent->OnRequestFinished.AddUObject(this, &ATDCharacter::InteractAfterMoving);
		}
	}
	else
	{
		ProcessInteraction();
	}
}

void ATDCharacter::ChooseAction()
{
	if (IsArmed())
	{
		WeaponComponent->StartShot();
	}
}

void ATDCharacter::ForceStopShooting()
{
	if (WeaponComponent && WeaponComponent->bIsShooting)
	{
		WeaponComponent->StopShot();
	}
}

void ATDCharacter::ProcessInteraction()
{
	ITDInteractionInterface* InteractingActor = Cast<ITDInteractionInterface>(TargetToInteract);
	check(InteractingActor);

	InteractingActor->OnInteraction(this);
	TargetToInteract.Reset();
}

void ATDCharacter::InteractAfterMoving(FAIRequestID RequestID, const FPathFollowingResult& FollowResult)
{
	/* Удаляем связанный делегат и вызываем интеракшн. */
	FollowingComponent->OnRequestFinished.Remove(StopMovingDelegate);
	ProcessInteraction();
}

float ATDCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	HealthComponent->TakeDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ATDCharacter::OnCharacterDead()
{
	bIsDead = true;
}

void ATDCharacter::ReloadWeapon()
{
	if (IsArmed())
	{
		WeaponComponent->StartReload();
	}
}

bool ATDCharacter::IsArmed()
{
	return WeaponComponent && WeaponComponent->HasHandedWeapon();
}

int ATDCharacter::GetAmmoInWeapon()
{
	return WeaponComponent->GetAmmoInWeapon();
}

void ATDCharacter::UseMedkit()
{
	auto Medkit = InventoryComponent->FindMedkit();
	if (!Medkit)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Medkit is not found in your inventory!")), true, false);
		return;
	}
	
	if (HealthComponent->IsHealthMaximum())
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Health is full!")), true, false);
		return;
	}
	
	HealthComponent->RestoreHealth(Cast<UTDMedObject>(Medkit)->GetHealValue());
	InventoryComponent->RemoveItem(Medkit);
}

float ATDCharacter::GetHealthPercent()
{
	float HealthValue = HealthComponent->GetHealth();
	float MaxHealthValue = HealthComponent->GetMaxHealth();

	return HealthValue / MaxHealthValue;
}
