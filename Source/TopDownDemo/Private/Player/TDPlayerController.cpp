/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "TDPlayerController.h"
#include "EnhancedActionKeyMapping.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "TDCharacter.h"
#include "TDInteractionComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Player/TDPlayerHUD.h"

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
	InteractionComponent->OnActionDelegate.AddUObject(this, &ATDPlayerController::OnAction);
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
			EnhancedInputComponent->BindAction(Action, ETriggerEvent::Started, this, Action->GetFName());
			EnhancedInputComponent->BindAction(Action, ETriggerEvent::Completed, this, Action->GetFName());
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
	else
	{
		GetTDCharacter()->ForceStopShooting();
	}
}

void ATDPlayerController::IA_RightClick(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitResult.Location);
	}
}

void ATDPlayerController::IA_ToggleInventory(const FInputActionValue& Value)
{
	auto TopDownHUD = Cast<ATDPlayerHUD>(MyHUD);
	check(TopDownHUD);
	
	if (Value.Get<bool>())
	{
		TopDownHUD->ToggleInventory();
	}
}

void ATDPlayerController::IA_Reload(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetTDCharacter()->ReloadWeapon();
	}
}

void ATDPlayerController::IA_Heal(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetTDCharacter()->UseMedkit();
	}
}

void ATDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ATDPlayerController::OnInteraction(AActor* TargetActor)
{
	GetTDCharacter()->TryInteract(TargetActor);
}

void ATDPlayerController::OnAction()
{
	GetTDCharacter()->ChooseAction();
}

ATDCharacter* ATDPlayerController::GetTDCharacter()
{
	return Cast<ATDCharacter>(GetCharacter());
}
