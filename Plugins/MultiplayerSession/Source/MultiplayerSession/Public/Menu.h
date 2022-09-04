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
	void MenuSetup();
protected:
	virtual bool Initialize() override;
private:
	UPROPERTY(meta=(BindWidget))
	UButton* BtnHost;

	UPROPERTY(meta=(BindWidget))
	UButton* BtnJoin;

	UFUNCTION()
	void BtnHostClicked();

	UFUNCTION()
	void BtnJoinClicked();

	UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;
};
