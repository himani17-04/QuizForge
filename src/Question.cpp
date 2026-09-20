#include "../include/Question.h"
#include <iostream>
#include <cctype>

using namespace std;

// Default constructor
Question::Question()
{
    questionId = 0;
    questionText = "";
    correctAnswer = ' ';
    category = "";
    difficulty = "";
}

// Parameterized constructor
Question::Question(int id, string text, vector<string> opts,
                   char answer, string cat, string diff)
{
    questionId = id;
    questionText = text;
    options = opts;
    correctAnswer = answer;
    category = cat;
    difficulty = diff;
}

// Setters

void Question::setQuestionId(int id)
{
    questionId = id;
}

void Question::setQuestionText(string text)
{
    questionText = text;
}

void Question::setOptions(vector<string> opts)
{
    options = opts;
}

void Question::setCorrectAnswer(char answer)
{
    correctAnswer = answer;
}

void Question::setCategory(string cat)
{
    category = cat;
}

void Question::setDifficulty(string diff)
{
    difficulty = diff;
}

// Getters

int Question::getQuestionId() const
{
    return questionId;
}

string Question::getQuestionText() const
{
    return questionText;
}

vector<string> Question::getOptions() const
{
    return options;
}

char Question::getCorrectAnswer() const
{
    return correctAnswer;
}

string Question::getCategory() const
{
    return category;
}

string Question::getDifficulty() const
{
    return difficulty;
}

// Display question

void Question::displayQuestion() const
{
    cout << "\n----------------------------------------\n";
    cout << "Question " << questionId << ": "
         << questionText << "\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < options.size(); i++)
    {
        cout << char('A' + i) << ". "
             << options[i] << "\n";
    }

    cout << "\nCategory   : " << category << "\n";
    cout << "Difficulty : " << difficulty << "\n";
}

void Question::displayQuestion(int questionNumber) const
{
    cout << "\n----------------------------------------\n";
    cout << "Question " << questionNumber << ": "
         << questionText << "\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < options.size(); i++)
    {
        cout << char('A' + i) << ". "
             << options[i] << "\n";
    }

    cout << "\nCategory   : " << category << "\n";
    cout << "Difficulty : " << difficulty << "\n";
}

// Check answer

bool Question::checkAnswer(char answer) const
{
    return toupper(answer) == toupper(correctAnswer);
}