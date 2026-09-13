#ifndef QUIZ_H
#define QUIZ_H

#include <vector>
#include <string>

#include "Question.h"

using namespace std;

class Quiz
{
private:
    vector<Question> questions;
    string category;
    string difficulty;

    int totalQuestions;
    int correctAnswers;
    int wrongAnswers;

    // Quiz time limit in seconds
    int timeLimit;

public:
    // Default constructor
    Quiz();

    // Parameterized constructor
    Quiz(vector<Question> questionList,
         string quizCategory,
         string quizDifficulty);

    // Setters
    void setQuestions(vector<Question> questionList);
    void setCategory(string quizCategory);
    void setDifficulty(string quizDifficulty);
    void setTimeLimit(int seconds);

    // Getters
    vector<Question> getQuestions() const;
    string getCategory() const;
    string getDifficulty() const;

    int getTotalQuestions() const;
    int getCorrectAnswers() const;
    int getWrongAnswers() const;
    int getTimeLimit() const;

    // Quiz operations
    void startQuiz();
    void displayResult() const;

    // Score calculation
    double calculatePercentage() const;
};

#endif