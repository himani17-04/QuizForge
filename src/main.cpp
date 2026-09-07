#include <iostream>
#include <vector>
#include <string>

#include "../include/User.h"
#include "../include/Question.h"
#include "../include/Quiz.h"
#include "../include/FileManager.h"

using namespace std;

// Student registration
void registerStudent()
{
    cout << "\n========================================\n";
    cout << "        STUDENT REGISTRATION\n";
    cout << "========================================\n";

    string fullName;
    string username;
    string password;

    cout << "Enter full name: ";
    getline(cin >> ws, fullName);

    cout << "Enter username: ";
    cin >> username;

    // Check whether username already exists
    if (FileManager::usernameExists(username))
    {
        cout << "\nUsername already exists.\n";
        cout << "Please choose another username.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Generate user ID
    vector<User> users = FileManager::loadUsers();

    int newUserId = 1;

    if (!users.empty())
    {
        newUserId = users.back().getUserId() + 1;
    }

    User newUser(
        newUserId,
        username,
        password,
        fullName
    );

    FileManager::saveUser(newUser);

    cout << "\nRegistration successful!\n";
    cout << "Your User ID is: " << newUserId << "\n";
}

// Student login
bool loginStudent(User& loggedInUser)
{
    cout << "\n========================================\n";
    cout << "            STUDENT LOGIN\n";
    cout << "========================================\n";

    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    vector<User> users = FileManager::loadUsers();

    for (const User& user : users)
    {
        if (user.getUsername() == username &&
            user.validatePassword(password))
        {
            loggedInUser = user;

            cout << "\nLogin successful!\n";
            cout << "Welcome, "
                 << user.getFullName()
                 << "!\n";

            return true;
        }
    }

    cout << "\nInvalid username or password.\n";

    return false;
}

void startStudentQuiz(const User& user)
{
    cout << "\n========================================\n";
    cout << "              START QUIZ\n";
    cout << "========================================\n";

    string category;
    string difficulty;

    cout << "\nAvailable Categories:\n";
    cout << "1. C++\n";
    cout << "2. Java\n";
    cout << "3. Python\n";
    cout << "4. General Knowledge\n";

    int categoryChoice;

    cout << "\nSelect category: ";
    cin >> categoryChoice;

    switch (categoryChoice)
    {
        case 1:
            category = "C++";
            break;

        case 2:
            category = "Java";
            break;

        case 3:
            category = "Python";
            break;

        case 4:
            category = "General Knowledge";
            break;

        default:
            cout << "\nInvalid category.\n";
            return;
    }

    cout << "\nAvailable Difficulties:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";

    int difficultyChoice;

    cout << "\nSelect difficulty: ";
    cin >> difficultyChoice;

    switch (difficultyChoice)
    {
        case 1:
            difficulty = "Easy";
            break;

        case 2:
            difficulty = "Medium";
            break;

        case 3:
            difficulty = "Hard";
            break;

        default:
            cout << "\nInvalid difficulty.\n";
            return;
    }

    // Load all questions from file
    vector<Question> allQuestions =
        FileManager::loadQuestions();

    // Store matching questions
    vector<Question> quizQuestions;

    for (const Question& question : allQuestions)
    {
        if (question.getCategory() == category &&
            question.getDifficulty() == difficulty)
        {
            quizQuestions.push_back(question);
        }
    }

    if (quizQuestions.empty())
    {
        cout << "\nNo questions available for this category "
             << "and difficulty.\n";
        return;
    }

    cout << "\nQuestions found: "
         << quizQuestions.size() << "\n";

    // Create quiz
    Quiz quiz(
        quizQuestions,
        category,
        difficulty
    );

    // Start quiz
    quiz.startQuiz();

    // Save result
    FileManager::saveResult(
        user.getUsername(),
        category,
        quiz.getTotalQuestions(),
        quiz.getCorrectAnswers(),
        quiz.getWrongAnswers(),
        quiz.calculatePercentage()
    );

    cout << "\nYour result has been saved successfully.\n";
}

// Student dashboard
void studentDashboard(const User& user)
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "          STUDENT DASHBOARD\n";
        cout << "========================================\n";

        cout << "Welcome, "
             << user.getFullName()
             << "!\n\n";

        cout << "1. Start Quiz\n";
        cout << "2. View Profile\n";
        cout << "3. Logout\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                startStudentQuiz(user);
                break;

            case 2:
                user.displayUser();
                break;

            case 3:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 3);
}

bool loginAdmin()
{
    cout << "\n========================================\n";
    cout << "              ADMIN LOGIN\n";
    cout << "========================================\n";

    string username;
    string password;

    cout << "Enter admin username: ";
    cin >> username;

    cout << "Enter admin password: ";
    cin >> password;

    // Default admin credentials
    const string ADMIN_USERNAME = "admin";
    const string ADMIN_PASSWORD = "admin123";

    if (username == ADMIN_USERNAME &&
        password == ADMIN_PASSWORD)
    {
        cout << "\nAdmin login successful!\n";
        return true;
    }

    cout << "\nInvalid admin username or password.\n";
    return false;
}

void adminDashboard()
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "            ADMIN DASHBOARD\n";
        cout << "========================================\n";

        cout << "1. Add Question\n";
        cout << "2. View Questions\n";
        cout << "3. Update Question\n";
        cout << "4. Delete Question\n";
        cout << "5. View Student Results\n";
        cout << "6. Logout\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "\nAdd Question module will be connected here.\n";
                break;

            case 2:
                cout << "\nView Questions module will be connected here.\n";
                break;

            case 3:
                cout << "\nUpdate Question module will be connected here.\n";
                break;

            case 4:
                cout << "\nDelete Question module will be connected here.\n";
                break;

            case 5:
                cout << "\nView Results module will be connected here.\n";
                break;

            case 6:
                cout << "\nLogging out from admin account...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 6);
}

int main()
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "              QUIZFORGE\n";
        cout << "        Online Quiz Application\n";
        cout << "========================================\n";

        cout << "1. Student Registration\n";
        cout << "2. Student Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerStudent();
                break;

            case 2:
            {
                User loggedInUser;

                if (loginStudent(loggedInUser))
                {
                    studentDashboard(loggedInUser);
                }

                break;
            }

            case 3:
            {
                if (loginAdmin())
                {
                    adminDashboard();
                }

                break;
            }

            case 4:
                cout << "\nThank you for using QuizForge!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}