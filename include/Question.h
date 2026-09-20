#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>

using namespace std;

class Question
{
private:
    int questionId;
    string questionText;
    vector<string> options;
    char correctAnswer;
    string category;
    string difficulty;

public:
    // Constructor
    Question();

    // Parameterized constructor
    Question(int id, string text, vector<string> opts,
             char answer, string cat, string diff);

    // Setters
    void setQuestionId(int id);
    void setQuestionText(string text);
    void setOptions(vector<string> opts);
    void setCorrectAnswer(char answer);
    void setCategory(string cat);
    void setDifficulty(string diff);

    // Getters
    int getQuestionId() const;
    string getQuestionText() const;
    vector<string> getOptions() const;
    char getCorrectAnswer() const;
    string getCategory() const;
    string getDifficulty() const;

    // Display question
    void displayQuestion() const;
    void displayQuestion(int questionNumber) const;

    // Check answer
    bool checkAnswer(char answer) const;
};

#endif