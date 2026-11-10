#include "Random.h"
#include <iostream>
#include <utility>
#include <vector>

namespace WordList {
const std::vector<const char *> words{"mystery",   "broccoli",  "account",
                                      "almost",    "spaghetti", "opinion",
                                      "beautiful", "distance",  "luggage"};

std::string_view selectAWord() {
  return words.at(Random::get(0, static_cast<int>(words.size()) - 1));
}
} // namespace WordList

char userInputLetter() {
  bool valid{false};
  while (!valid) {
    std::cout << "Enter your next letter: ";
    char userLetter{};
    std::cin >> userLetter;
    userLetter = static_cast<char>(std::tolower(userLetter));
    if (userLetter >= 'a' && userLetter <= 'z') {
      return userLetter;
    } else {
      std::cout << "Not a valid letter." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

void wordAsUnderscores(std::string_view& input, std::string& output) {
  for (char c : input) {
    output.push_back('_');
  }
}

void createGuessLeftVisual(int guessesLeft, std::string& output) {
  for (int i {0}; i < guessesLeft; ++i) {
    output.push_back('+');
  }
}

void introduction () {
  std::cout << "Welcome to C++man (a variant of Hangman)" << std::endl;
  std::cout << "To win: guess the word. To lose: run out of pluses."
            << std::endl
            << std::endl;
}


void playGame() {
  std::string_view currentWord{WordList::selectAWord()};
  std::string wordAsUnderscore{};
  wordAsUnderscores(currentWord, wordAsUnderscore);
  char userLetter{};
  int guessesLeft{6};
  std::string guessesLeftVisual {};
  createGuessLeftVisual(guessesLeft, guessesLeftVisual);

  introduction();

  while (true) {
    std::cout << "The word: " << wordAsUnderscore << "   Wrong guesses: " << guessesLeftVisual << std::endl;

    userLetter = userInputLetter();

    if (currentWord.find(userLetter) != std::string_view::npos) {
      std::cout << "Yes, '" << userLetter << "' is in the word!" << std::endl;
      for (std::size_t i {0}; i < currentWord.size(); ++i) {
        if (currentWord.at(i) == userLetter) {
          wordAsUnderscore.at(i) = userLetter;
        }
      }
    } else {
      std::cout << "No, '" << userLetter << "' is not in the word!" << std::endl;
      guessesLeftVisual.at(guessesLeft - 1) = userLetter;
      guessesLeft--;
      if (guessesLeft == 0) {
        std::cout << "You lost!  The word was:" << currentWord << std::endl;
        break;
      }
    }
    if (wordAsUnderscore.find('_') == std::string_view::npos) {
      std::cout << "You Win!  The word was:" << currentWord << std::endl;
      break;
    }
  }
}

int main() {
  playGame();

  return 0;
}
