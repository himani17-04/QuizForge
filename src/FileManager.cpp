#include "../include/FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// File paths
const string USER_FILE = "data/users.txt";
const string QUESTION_FILE = "data/questions.txt";
const string RESULT_FILE = "data/results.txt";

// ==================== USER OPERATIONS ====================

// Save a user to users.txt
void FileManager::saveUser(const User& user)
{
    ofstream file(USER_FILE, ios::app);

    if (!file)
    {
        cerr << "Error: Unable to open users file.\n";
        return;
    }

    file << user.getUserId() << "|"
         << user.getUsername() << "|"
         << user.getPassword() << "|"
         << user.getFullName() << "\n";

    file.close();
}

// Load all users
vector<User> FileManager::loadUsers()
{
    vector<User> users;

    ifstream file(USER_FILE);

    if (!file)
    {
        return users;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id;
        string username;
        string password;
        string fullName;

        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, fullName, '|');

        User user(
            stoi(id),
            username,
            password,
            fullName
        );

        users.push_back(user);
    }

    file.close();

    return users;
}

// ==================== QUESTION OPERATIONS ====================

// Save a question
void FileManager::saveQuestion(const Question& question)
{
    ofstream file(QUESTION_FILE, ios::app);

    if (!file)
    {
        cerr << "Error: Unable to open questions file.\n";
        return;
    }

    vector<string> options = question.getOptions();

    file << question.getQuestionId() << "|"
         << question.getQuestionText() << "|";

    for (size_t i = 0; i < options.size(); i++)
    {
        file << options[i];

        if (i < options.size() - 1)
            file << "~";
    }

    file << "|"
         << question.getCorrectAnswer() << "|"
         << question.getCategory() << "|"
         << question.getDifficulty() << "\n";

    file.close();
}

// Load all questions
vector<Question> FileManager::loadQuestions()
{
    vector<Question> questions;

    ifstream file(QUESTION_FILE);

    if (!file)
    {
        return questions;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id;
        string questionText;
        string optionsText;
        string correctAnswer;
        string category;
        string difficulty;

        getline(ss, id, '|');
        getline(ss, questionText, '|');
        getline(ss, optionsText, '|');
        getline(ss, correctAnswer, '|');
        getline(ss, category, '|');
        getline(ss, difficulty, '|');

        vector<string> options;

        stringstream optionStream(optionsText);
        string option;

        while (getline(optionStream, option, '~'))
        {
            options.push_back(option);
        }

        Question question(
            stoi(id),
            questionText,
            options,
            correctAnswer[0],
            category,
            difficulty
        );

        questions.push_back(question);
    }

    file.close();

    return questions;
}

// ==================== RESULT OPERATIONS ====================

// Save quiz result
void FileManager::saveResult(
    string username,
    string category,
    int totalQuestions,
    int correctAnswers,
    int wrongAnswers,
    double percentage)
{
    ofstream file(RESULT_FILE, ios::app);

    if (!file)
    {
        cerr << "Error: Unable to open results file.\n";
        return;
    }

    file << username << "|"
         << category << "|"
         << totalQuestions << "|"
         << correctAnswers << "|"
         << wrongAnswers << "|"
         << percentage << "\n";

    file.close();
}

// ==================== USERNAME CHECK ====================

// Check if username already exists
bool FileManager::usernameExists(string username)
{
    vector<User> users = loadUsers();

    for (const User& user : users)
    {
        if (user.getUsername() == username)
        {
            return true;
        }
    }

    return false;
}