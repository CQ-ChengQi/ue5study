// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

void UMenu::MenuSetup()
{
	// 将菜单添加到视口中
	AddToViewport();

	// 显示菜单
	SetVisibility(ESlateVisibility::Visible);

	const UWorld* World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (BtnHost != nullptr)
	{
		BtnHost->OnClicked.AddDynamic(this, &ThisClass::BtnHostClicked);
	}

	if (BtnJoin != nullptr)
	{
		BtnJoin->OnClicked.AddDynamic(this, &ThisClass::BtnJoinClicked);
	}
	return true;
}

void UMenu::BtnHostClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("BtnHost Clicked")));
	}

	if (MultiplayerSessionSubsystem != nullptr)
	{
		MultiplayerSessionSubsystem->CreateSession(4, "FreeForAll");
	}
}

void UMenu::BtnJoinClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("BtnJoin Clicked")));
	}
}
