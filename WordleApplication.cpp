#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <Wt/WApplication.h>
#include <iostream>
#include <string>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "WordleApplication.h"

Wt::WContainerWidget *container;

WordleApplication::WordleApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{
  attempts = 6;
  setTitle("Wordle Game");                            // application title
  std::string randomWord = pickRandomWord();
  root()->addWidget(std::make_unique<Wt::WText>("Enter your word: ")); // show some text

  userInput = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow text input
  userInput->setFocus();                              // give focus

  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Guess")); // create a button
  button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

  root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line break
  displayedText = root()->addWidget(std::make_unique<Wt::WText>()); // empty text


  button->clicked().connect([this, randomWord]() {
    this->check(randomWord);
  });

  userInput->enterPressed().connect(std::bind(&WordleApplication::check, this, randomWord));


  button->clicked().connect([=]() {
      std::cerr << userInput->text() << std::endl;

  });
}
bool WordleApplication::isFiveLetterAlphaString(const std::string& str) {
    // Check the length of the string
    if (str.length() != 5) {
        return false; // Length is not 5
    }

    // Check if each character is an upper or lowercase letter
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false; // Character is not a letter
        }
    }

    return true; // The string meets the criteria
}

std::string WordleApplication::pickRandomWord()
{
  std::ifstream file("words.txt"); // open file
  std::vector<std::string> words; // create empty vector
  std::string word; // line by line each word in the file
  while (file >> word) {
      words.push_back(word);
  }
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random index to pick a word
  int randomIndex = std::rand() % words.size();

  return words[randomIndex];
}

void WordleApplication::check(const std::string& randomWord)
{
  std::cout << randomWord << "\n";
  std::string userGuess = userInput->text().toUTF8(); // userGuess in string format
  for (char &c : userGuess) {
        c = std::tolower(c); // Convert the character to lowercase
    }
  
  bool validGuess = isFiveLetterAlphaString(userGuess);
  if (validGuess == false) {
    return;
  }
  
  std::set <std::string> letterSet = {};

  for (int i = 0; i < randomWord.length(); ++i){
    std::string letter = randomWord.substr(i, 1);
    letterSet.insert(letter);
  }
  
  attempts = attempts - 1;
  for (size_t i = 0; i < userGuess.length(); ++i) {

      std::string userGuessChar = userGuess.substr(i, 1); // get character

      int numCount = letterSet.count(userGuessChar);
      if (numCount == 0) {
        auto character = root()->addWidget(std::make_unique<Wt::WText>(userGuessChar));
      }  
      else if (userGuess[i] == randomWord[i]) {
        // make colour green
        auto character = root()->addWidget(std::make_unique<Wt::WText>("<span style= 'color: green;'>" + userGuessChar + "</span>"));
      }
      else {
        // make colour red
        auto character = root()->addWidget(std::make_unique<Wt::WText>("<span style= 'color: red;'>" + userGuessChar + "</span>"));
      }
      
  }
  auto lineBreak = root()->addWidget(std::make_unique<Wt::WBreak>()); // line break
  // check if two string are equal
  if (userGuess.compare(randomWord) == 0) {
    auto message = root()->addWidget(std::make_unique<Wt::WText>("Congrats, you have guessed correctly."));
    Wt::WPushButton* refreshButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Restart"));
        // Connect a JavaScript function to the button's click event
    refreshButton->clicked().connect([=] {
        // Execute JavaScript to force page refresh
        doJavaScript("location.reload(true);");
    });
  }


  if (attempts == 0) {
    auto message = root()->addWidget(std::make_unique<Wt::WText>("You have ran out of attempts."));
    //button->clicked().connect(this, &WordleApplication::resetApplication);
    Wt::WPushButton* refreshButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Restart"));
        // Connect a JavaScript function to the button's click event
    refreshButton->clicked().connect([=] {
        // Execute JavaScript to force page refresh
        doJavaScript("location.reload(true);");
    });
  }    
  
}




