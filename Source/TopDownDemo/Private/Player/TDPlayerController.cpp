// Fill out your copyright notice in the Description page of Project Settings.

#include "TDPlayerController.h"
#include "EnhancedActionKeyMapping.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "TDCharacter.h"
#include "TDInteractionComponent.h"
#include "TDInteractionInterface.h"

FName ATDPlayerController::InteractionComponentName = FName("PlayerInteractionComponent");

ATDPlayerController::ATDPlayerController()
{
	InteractionComponentClass = UTDInteractionComponent::StaticClass();
}

void ATDPlayerController::PreInitializeComponents()
{
	FindOrCreateComponents();
	Super::PreInitializeComponents();
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		FModifyContextOptions Options;
		Options.bForceImmediately = 1;
		
		Subsystem->AddMappingContext(InputContext, 1, Options);
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->ClearActionEventBindings();
		EnhancedInputComponent->ClearActionValueBindings();
		EnhancedInputComponent->ClearDebugKeyBindings();

		BindActions(InputContext);
	}
}

void ATDPlayerController::FindOrCreateComponents()
{
	/* Проверяем, имеется ли экземпляр компонента у контроллера.
	 * Если компонент валиден (имеется экземпляр блупринта), то перезаписываем поинтер.
	 * Если компонент не валиден, то создаем дефолтный по указанному в <имя компонента>Class классу и регистрируем его в
	 * контроллере. */
	
	InteractionComponent = GetComponentByClass<UTDInteractionComponent>();
	if (!InteractionComponent)
	{
		InteractionComponent = NewObject<UTDInteractionComponent>(this, InteractionComponentClass, InteractionComponentName);
		InteractionComponent->RegisterComponent();
	}
}

void ATDPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InteractionComponent->OnInteractionDelegate.AddUObject(this, &ATDPlayerController::OnInteraction);
}

void ATDPlayerController::BindActions(UInputMappingContext* Context)
{
	check(Context);

	/* Бинд функции для инпутов происходит по имени ассета, указанного в маппинге контекста. */
	
	const TArray<FEnhancedActionKeyMapping>& Mappings = Context->GetMappings();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (const FEnhancedActionKeyMapping& Keymapping : Mappings)
		{
			auto Action = Keymapping.Action;
			EnhancedInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, Action->GetFName());
		}
	}
}

void ATDPlayerController::IA_LeftClick(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

		if (!IsValid(InteractionComponent)) return;
		
		InteractionComponent->ProcessInteraction(HitResult);
	}
}

void ATDPlayerController::IA_RightClick(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	}
}

void ATDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ATDPlayerController::OnInteraction(AActor* TargetActor)
{
	GetTDCharacter()->ProcessInteraction(TargetActor);
}

ATDCharacter* ATDPlayerController::GetTDCharacter()
{
	return Cast<ATDCharacter>(GetCharacter());
}
