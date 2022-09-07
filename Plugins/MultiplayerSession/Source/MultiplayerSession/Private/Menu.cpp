// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "OnlineSessionSettings.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;

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

	if (MultiplayerSessionSubsystem != nullptr)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
		MultiplayerSessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
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

void UMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	MenuTearDown();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Session 创建成功")));
		}

		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			World->ServerTravel("/Game/TopDown/Maps/Lobby?listen");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Session 创建失败")));
		}
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful)
{
	if (MultiplayerSessionSubsystem == nullptr)
	{
		return;
	}

	for (auto Result : SessionResult)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue == MatchType)
		{
			MultiplayerSessionSubsystem->JoinSession(Result);
			return;
		}
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result, FString Address)
{
	if (MultiplayerSessionSubsystem != nullptr)
	{
		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController != nullptr)
		{
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}

void UMenu::BtnHostClicked()
{
	if (MultiplayerSessionSubsystem != nullptr)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenu::BtnJoinClicked()
{
	if (MultiplayerSessionSubsystem != nullptr)
	{
		MultiplayerSessionSubsystem->FindSession(10000);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	const UWorld* World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			const FInputModeGameOnly InputModData;
			PlayerController->SetInputMode(InputModData);
			// PlayerController->SetShowMouseCursor(false);
		}
	}
}
