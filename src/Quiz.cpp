#include "../include/Quiz.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Default constructor
Quiz::Quiz()
{
    category = "";
    difficulty = "";
    totalQuestions = 0;
    correctAnswers = 0;
    wrongAnswers = 0;
}

// Parameterized constructor
Quiz::Quiz(vector<Question> questionList,
           string quizCategory,
           string quizDifficulty)
{
    questions = questionList;
    category = quizCategory;
    difficulty = quizDifficulty;

    totalQuestions = questions.size();
    correctAnswers = 0;
    wrongAnswers = 0;
}

// Setters

void Quiz::setQuestions(vector<Question> questionList)
{
    questions = questionList;
    totalQuestions = questions.size();
}

void Quiz::setCategory(string quizCategory)
{
    category = quizCategory;
}

void Quiz::setDifficulty(string quizDifficulty)
{
    difficulty = quizDifficulty;
}

// Getters

vector<Question> Quiz::getQuestions() const
{
    return questions;
}

string Quiz::getCategory() const
{
    return category;
}

string Quiz::getDifficulty() const
{
    return difficulty;
}

int Quiz::getTotalQuestions() const
{
    return totalQuestions;
}

int Quiz::getCorrectAnswers() const
{
    return correctAnswers;
}

int Quiz::getWrongAnswers() const
{
    return wrongAnswers;
}

// Start quiz

void Quiz::startQuiz()
{
    if (questions.empty())
    {
        cout << "\nNo questions available for this quiz.\n";
        return;
    }

    correctAnswers = 0;
    wrongAnswers = 0;
    totalQuestions = questions.size();

    cout << "\n========================================\n";
    cout << "              QUIZ STARTED\n";
    cout << "========================================\n";
    cout << "Category   : " << category << "\n";
    cout << "Difficulty : " << difficulty << "\n";
    cout << "Questions  : " << totalQuestions << "\n";
    cout << "========================================\n";

    for (size_t i = 0; i < questions.size(); i++)
    {
        cout << "\nQuestion " << i + 1
             << " of " << totalQuestions << "\n";

        questions[i].displayQuestion();

        char answer;

        cout << "\nEnter your answer (A/B/C/D): ";
        cin >> answer;

        answer = toupper(answer);

        while (answer != 'A' &&
               answer != 'B' &&
               answer != 'C' &&
               answer != 'D')
        {
            cout << "Invalid answer. Please enter A, B, C or D: ";
            cin >> answer;
            answer = toupper(answer);
        }

        if (questions[i].checkAnswer(answer))
        {
            cout << "Correct!\n";
            correctAnswers++;
        }
        else
        {
            cout << "Wrong answer.\n";
            cout << "Correct answer: "
                 << questions[i].getCorrectAnswer() << "\n";

            wrongAnswers++;
        }
    }

    displayResult();
}

// Calculate percentage

double Quiz::calculatePercentage() const
{
    if (totalQuestions == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(correctAnswers)
            / totalQuestions) * 100.0;
}

// Display result

void Quiz::displayResult() const
{
    double percentage = calculatePercentage();

    cout << "\n========================================\n";
    cout << "              QUIZ RESULT\n";
    cout << "========================================\n";

    cout << "Category        : " << category << "\n";
    cout << "Difficulty      : " << difficulty << "\n";
    cout << "Total Questions : " << totalQuestions << "\n";
    cout << "Correct Answers : " << correctAnswers << "\n";
    cout << "Wrong Answers   : " << wrongAnswers << "\n";

    cout << fixed << setprecision(2);
    cout << "Percentage      : " << percentage << "%\n";

    if (percentage >= 40)
    {
        cout << "Result          : PASSED\n";
    }
    else
    {
        cout << "Result          : FAILED\n";
    }

    cout << "========================================\n";
}