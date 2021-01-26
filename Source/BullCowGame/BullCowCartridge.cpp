// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); //Debug Line


}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    }
    else {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame() {
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = TEXT("cake");
    Lives = 4;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress Enter to continue..."));

    IsIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}


void UBullCowCartridge::ProcessGuess(FString Guess) {
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

    PrintLine(TEXT("Guess again, you have %i lives"), Lives);
}


bool UBullCowCartridge::IsIsogram(FString Word) const {

    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparison = Index + 1; Comparison <= Word.Len(); Comparison++) {

        }
    }
    return true;
}