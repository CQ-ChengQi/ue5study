// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "GameFramework/Character.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "StudyCharacter.generated.h"

UCLASS(Blueprintable)
class AStudyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AStudyCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	/** 创建 Session */
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();

	/** 加入 Session */
	UFUNCTION(BlueprintCallable)
	void JoinGameSession();

	/** 创建 Game Session 成功后调用此方法 */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/** 加入 Game Session 后调用此方法 */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinSessionCompleteResultType);

	/** 查找 Game Session 后调用此方法 */
	void OnFindSessionsComplete(bool bWasSuccessful);
private:
	/** 创建 Session 成功委托事件 */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	/** 加入 Session 成功委托事件 */
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	/** 查找 Session 成功委托事件 */
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	/** Game Session 查找对象 */
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
