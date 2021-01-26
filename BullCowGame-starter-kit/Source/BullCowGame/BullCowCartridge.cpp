// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include "Math/UnrealMathUtility.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();


    Isograms = GetValidWords(Words);

    SetupGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); //Debug Line
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    }
    else {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame() {
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress Enter to continue..."));
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}


void UBullCowCartridge::ProcessGuess(const FString& Guess) {
    if (Guess == HiddenWord) {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (!IsIsogram(Guess)) {

        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }

    PrintLine(TEXT("You have lost a life"));
    --Lives;

    if (Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));

        EndGame();
        return;
    }

    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls ans %i Cows"),Score.Bulls,Score.Cows);
    PrintLine(TEXT("Guess again, you have %i lives"), Lives);
}

//check Isogram
bool UBullCowCartridge::IsIsogram(const FString& Word) const{

    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const{
    TArray<FString> ValidWords;
    for (FString Word:WordList) {
        if (Word.Len() >= 4 && Word.Len() <= 8&& IsIsogram(Word)) {
                ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess)const {

    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++) {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex]) {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++) {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex]) {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}