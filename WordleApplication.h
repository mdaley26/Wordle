/*
 * Copyright (C) 2008 Emweb bv, Herent, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>


class WordleApplication : public Wt::WApplication
{
public:
  WordleApplication(const Wt::WEnvironment& env);
  std::string pickRandomWord();
  bool isFiveLetterAlphaString(const std::string& str);
  void resetApplication();
  

private:
  Wt::WLineEdit *userInput; // user input
  Wt::WText     *displayedText; // text to display to user
  int attempts;
  Wt::WText     *greeting_;
  void check(const std::string& randomWord);

};
