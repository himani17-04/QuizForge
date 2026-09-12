#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "User.h"
#include "Question.h"

using namespace std;

class FileManager
{
public:
    // User file operations
    static void saveUser(const User& user);
    static vector<User> loadUsers();

    // Question file operations
    static void saveQuestion(const Question& question);
    static vector<Question> loadQuestions();

    // Result file operations
    static void saveResult(string username,
                       string category,
                       string difficulty,
                       int totalQuestions,
                       int correctAnswers,
                       int wrongAnswers,
                       double percentage,
                       string result);

    // Check whether a username already exists
    static bool usernameExists(string username);
};

#endif