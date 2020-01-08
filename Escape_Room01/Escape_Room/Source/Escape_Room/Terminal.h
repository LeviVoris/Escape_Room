// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework\Actor.h"
#include "Terminal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTextUpdateSignature, FString, Text);

struct FKey;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_ROOM_API UTerminal : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "Terminal")
		FTextUpdatesSignature TextUpdate;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FString GetScreenText() const;

	UFUNCTION(BlueprintCallable)
		void ActiveTerminal();

	UFUNCTION(BlueprintCallable)
		void DeactiveTerminal() const;

	void PrintLine(const FString& Line);
	void ClearScreen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame
	void OnKeyDown(FKey Key);
	TArray<FString> WrapLines(const TArray<FStirng>& Lines const);
	void Truncate(TArray<FStirng>& Lines) const;
	FStirng JoinWithNewline(const TArray<FString>& Lines) const;
	void AcceptInputLine();
	void BackSpace();
	FStirng GetKeyString(FKey Key) const;
	void UpdateText();

	UPROPERTY(EditAnywhere)
		int32 MaxLines = 10;

	UPROPERTY(EditAnywhere)
		int32 MaxColums = 70;

	TArray<FStirng> Buffer;
	FString InputLine;

	int32 PressedBindingIndex;
	int32 RepeatBeingingIndex;

		
};
