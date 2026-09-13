#include "../include/Quiz.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <chrono>

using namespace std;

// Default constructor
Quiz::Quiz()
{
    category = "";
    difficulty = "";
    totalQuestions = 0;
    correctAnswers = 0;
    wrongAnswers = 0;

    // Default time limit: 60 seconds (1 minute)
    timeLimit = 60;
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

    // Default time limit: 60 seconds (1 minute)
    timeLimit = 60;
}

// ==================== SETTERS ====================

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

void Quiz::setTimeLimit(int seconds)
{
    if (seconds > 0)
    {
        timeLimit = seconds;
    }
}

// ==================== GETTERS ====================

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

int Quiz::getTimeLimit() const
{
    return timeLimit;
}

// ==================== START QUIZ ====================

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
    cout << "Time Limit : " << timeLimit / 60 << " seconds\n";
    cout << "========================================\n";

    // Start timer
    auto startTime = chrono::steady_clock::now();

    for (size_t i = 0; i < questions.size(); i++)
    {
        // Check elapsed time before displaying the next question
        auto currentTime = chrono::steady_clock::now();

        auto elapsedSeconds =
            chrono::duration_cast<chrono::seconds>(
                currentTime - startTime
            ).count();

        if (elapsedSeconds >= timeLimit)
        {
            cout << "\n========================================\n";
            cout << "             TIME IS UP!\n";
            cout << "========================================\n";
            cout << "The quiz time limit has been reached.\n";
            break;
        }

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
            cout << "\nInvalid answer.\n";
            cout << "Please enter only A, B, C or D: ";

            cin.clear();
            cin.ignore(10000, '\n');

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

// ==================== CALCULATE PERCENTAGE ====================

double Quiz::calculatePercentage() const
{
    if (totalQuestions == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(correctAnswers)
            / totalQuestions) * 100.0;
}

// ==================== DISPLAY RESULT ====================

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