//// Fill out your copyright notice in the Description page of Project Settings.
//#include "BullCowCartridge.h"
////#include "HiddenWordList.h"
//
//void UBullCowCartridge::BeginPlay() // When the game starts
//{
//	Super::BeginPlay();
//
//	Isograms = GetValidWords(Words);
//
//	SetUpGame();
//}
//
//void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
//{
//	if (bGameOver)
//	{
//		ClearScreen();
//		SetUpGame();
//	}
//	else // Check Player Guess
//	{
//		ProcessGuess(PlayerInput);
//	}
//}
//void UBullCowCartridge::SetUpGame()
//{
//	PrintLine(TEXT("Welcome to the game Ladies and Jets"));
//
//	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
//	Lives = HiddenWord.Len();
//	bGameOver = false;
//
//	//Welcome player
//	PrintLine(TEXT("Input Something %i characters long! \nPress Enter to continue"), HiddenWord.Len()); //Promt player for guess
//	PrintLine(TEXT("You have %i lives."), Lives);
//	//PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);  //Debug line
//}
//
//void UBullCowCartridge::EndGame()
//{
//	bGameOver = true;
//	PrintLine(TEXT("Press Enter to try again!"));
//}
//
//void UBullCowCartridge::ProcessGuess(const FString& Guess)
//{
//	if (Guess == HiddenWord)
//	{
//		PrintLine(TEXT("You Win!"));
//		EndGame();
//		return;
//	}
//
//	// Player Guess goes through checks
//	if (Guess.Len() != HiddenWord.Len())
//	{
//		PrintLine(TEXT("Your word is not the correct length.\nIt should be %i characters long. \nGive it another go."), HiddenWord.Len());
//		return;
//	}
//
//	if (!IsIsogram(Guess))
//	{
//		PrintLine(TEXT("No repeating letters! \nGuess Again"));
//		return;
//	}
//
//	//Remove lives from here out
//
//	if (Guess != HiddenWord)
//	{
//		PrintLine(TEXT("Sorry, thats not the right word.\nYou have lost a life!"));
//		PrintLine(TEXT("You have %i lives left"), --Lives);
//	}
//
//	if (Lives <= 0)
//	{
//		ClearScreen();
//		PrintLine(TEXT("You have no lives left."));
//		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
//		EndGame();
//		return;
//	}
//	//Show player Bulls and Cows
//	FBullCowCount Score = GetBullCows(Guess);
//
//	PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
//}
//
//bool UBullCowCartridge::IsIsogram(const FString& Word) const
//{
//	for (int32 Index = 0; Index < Word.Len(); Index++)
//	{
//		for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
//		{
//			if (Word[Index] == Word[Comparison])
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
//{
//	TArray<FString> ValidWords;
//
//	for (FString Word : WordList)
//	{
//		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
//		{
//			ValidWords.Emplace(Word);
//		}
//	}
//	return ValidWords;
//}
//
//FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
//{
//	FBullCowCount Count;
//
//	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
//	{
//		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
//		{
//			Count.Bulls++;
//			continue;
//		}
//
//		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
//		{
//			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
//			{
//				Count.Cows++;
//				break;
//			}
//		}
//	}
//	return Count;
//}