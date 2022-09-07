// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerSessionSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForALl")));
protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result,FString Address);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
private:
	UPROPERTY(meta=(BindWidget))
	UButton* BtnHost;

	UPROPERTY(meta=(BindWidget))
	UButton* BtnJoin;

	UFUNCTION()
	void BtnHostClicked();

	UFUNCTION()
	void BtnJoinClicked();

	void MenuTearDown();

	UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;

	int32 NumPublicConnections{4};
	FString MatchType{TEXT("FreeForAll")};
};
