#include "../include/FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

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
    // Check whether the existing file ends with a newline
    ifstream checkFile(QUESTION_FILE, ios::binary);

    if (checkFile)
    {
        checkFile.seekg(0, ios::end);

        streampos fileSize = checkFile.tellg();

        if (fileSize > 0)
        {
            checkFile.seekg(-1, ios::end);

            char lastCharacter;
            checkFile.get(lastCharacter);

            checkFile.close();

            // Add a newline if the file does not already have one
            if (lastCharacter != '\n')
            {
                ofstream newLineFile(QUESTION_FILE, ios::app);
                newLineFile << "\n";
                newLineFile.close();
            }
        }
        else
        {
            checkFile.close();
        }
    }

    // Open file in append mode
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
        {
            file << "~";
        }
    }

    file << "|"
         << question.getCorrectAnswer() << "|"
         << question.getCategory() << "|"
         << question.getDifficulty()
         << "\n";

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
    string difficulty,
    int totalQuestions,
    int correctAnswers,
    int wrongAnswers,
    double percentage,
    string result)
{
    ofstream file(RESULT_FILE, ios::app);

    if (!file)
    {
        cerr << "Error: Unable to open results file.\n";
        return;
    }

    file << username << "|"
         << category << "|"
         << difficulty << "|"
         << totalQuestions << "|"
         << correctAnswers << "|"
         << wrongAnswers << "|"
         << percentage << "|"
         << result
         << "\n";

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

void FileManager::viewQuizHistory(string username)
{
    ifstream file(RESULT_FILE);

    if (!file)
    {
        cout << "\nNo quiz history available.\n";
        return;
    }

    string line;
    bool found = false;
    int attemptNumber = 0;

    cout << "\n========================================\n";
    cout << "             QUIZ HISTORY\n";
    cout << "========================================\n";

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string savedUsername;
        string category;
        string difficulty;
        string totalQuestions;
        string correctAnswers;
        string wrongAnswers;
        string percentage;
        string result;

        stringstream ss(line);

        getline(ss, savedUsername, '|');
        getline(ss, category, '|');
        getline(ss, difficulty, '|');
        getline(ss, totalQuestions, '|');
        getline(ss, correctAnswers, '|');
        getline(ss, wrongAnswers, '|');
        getline(ss, percentage, '|');
        getline(ss, result, '|');

        if (savedUsername == username)
        {
            found = true;
            attemptNumber++;

            cout << "\nAttempt #" << attemptNumber << "\n";
            cout << "----------------------------------------\n";
            cout << "Category        : " << category << "\n";
            cout << "Difficulty      : " << difficulty << "\n";
            cout << "Total Questions : " << totalQuestions << "\n";
            cout << "Correct Answers : " << correctAnswers << "\n";
            cout << "Wrong Answers   : " << wrongAnswers << "\n";
            cout << "Percentage      : " << percentage << "%\n";
            cout << "Result          : " << result << "\n";
            cout << "----------------------------------------\n";
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nNo quiz attempts found.\n";
    }

    cout << "\n========================================\n";
}

void FileManager::viewPerformanceSummary(string username)
{
    ifstream file(RESULT_FILE);

    if (!file)
    {
        cout << "\nNo quiz results available.\n";
        return;
    }

    string line;

    int totalAttempts = 0;
    int passedQuizzes = 0;
    int failedQuizzes = 0;

    double totalPercentage = 0.0;
    double bestPercentage = 0.0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string savedUsername;
        string category;
        string difficulty;
        string totalQuestions;
        string correctAnswers;
        string wrongAnswers;
        string percentage;
        string result;

        stringstream ss(line);

        getline(ss, savedUsername, '|');
        getline(ss, category, '|');
        getline(ss, difficulty, '|');
        getline(ss, totalQuestions, '|');
        getline(ss, correctAnswers, '|');
        getline(ss, wrongAnswers, '|');
        getline(ss, percentage, '|');
        getline(ss, result, '|');

        if (savedUsername == username)
        {
            totalAttempts++;

            double percentageValue = stod(percentage);

            totalPercentage += percentageValue;

            if (percentageValue > bestPercentage)
            {
                bestPercentage = percentageValue;
            }

            if (result == "PASSED")
            {
                passedQuizzes++;
            }
            else if (result == "FAILED")
            {
                failedQuizzes++;
            }
        }
    }

    file.close();

    cout << "\n========================================\n";
    cout << "        PERFORMANCE SUMMARY\n";
    cout << "========================================\n";

    if (totalAttempts == 0)
    {
        cout << "\nNo quiz attempts found.\n";
        cout << "========================================\n";
        return;
    }

    double averagePercentage =
        totalPercentage / totalAttempts;

    cout << "Total Attempts    : " << totalAttempts << "\n";
    cout << "Passed Quizzes    : " << passedQuizzes << "\n";
    cout << "Failed Quizzes    : " << failedQuizzes << "\n";

    cout << fixed << setprecision(2);

    cout << "Average Percentage: "
         << averagePercentage << "%\n";

    cout << "Best Percentage   : "
         << bestPercentage << "%\n";

    cout << "========================================\n";
}

void FileManager::viewLeaderboard()
{
    ifstream file(RESULT_FILE);

    if (!file)
    {
        cout << "\nNo quiz results available.\n";
        return;
    }

    struct StudentScore
    {
        string username;
        double bestPercentage;
    };

    vector<StudentScore> leaderboard;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string username;
        string category;
        string difficulty;
        string totalQuestions;
        string correctAnswers;
        string wrongAnswers;
        string percentage;
        string result;

        stringstream ss(line);

        getline(ss, username, '|');
        getline(ss, category, '|');
        getline(ss, difficulty, '|');
        getline(ss, totalQuestions, '|');
        getline(ss, correctAnswers, '|');
        getline(ss, wrongAnswers, '|');
        getline(ss, percentage, '|');
        getline(ss, result, '|');

        double percentageValue = stod(percentage);

        bool found = false;

        for (auto& student : leaderboard)
        {
            if (student.username == username)
            {
                found = true;

                if (percentageValue > student.bestPercentage)
                {
                    student.bestPercentage = percentageValue;
                }

                break;
            }
        }

        if (!found)
        {
            StudentScore student;

            student.username = username;
            student.bestPercentage = percentageValue;

            leaderboard.push_back(student);
        }
    }

    file.close();

    sort(
        leaderboard.begin(),
        leaderboard.end(),
        [](const StudentScore& a, const StudentScore& b)
        {
            return a.bestPercentage > b.bestPercentage;
        }
    );

    cout << "\n========================================\n";
    cout << "              LEADERBOARD\n";
    cout << "========================================\n";

    if (leaderboard.empty())
    {
        cout << "\nNo quiz results available.\n";
        cout << "========================================\n";
        return;
    }

    cout << "\nRank\tUsername\tBest Score\n";
    cout << "----------------------------------------\n";

    int rank = 1;

    for (const auto& student : leaderboard)
    {
        cout << rank << "\t"
             << student.username << "\t\t"
             << fixed << setprecision(2)
             << student.bestPercentage << "%\n";

        rank++;
    }

    cout << "========================================\n";
}