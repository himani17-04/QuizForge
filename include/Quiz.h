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

    // Getters
    vector<Question> getQuestions() const;
    string getCategory() const;
    string getDifficulty() const;

    int getTotalQuestions() const;
    int getCorrectAnswers() const;
    int getWrongAnswers() const;

    // Quiz operations
    void startQuiz();
    void displayResult() const;

    // Score calculation
    double calculatePercentage() const;
};

#endif