#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

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

    // Full name validation
    cout << "Enter full name: ";
    getline(cin >> ws, fullName);

    while (fullName.empty())
    {
        cout << "Full name cannot be empty.\n";
        cout << "Enter full name: ";
        getline(cin >> ws, fullName);
    }

    // Username validation
    cout << "Enter username: ";
    getline(cin >> ws, username);

    while (username.empty())
    {
        cout << "Username cannot be empty.\n";
        cout << "Enter username: ";
        getline(cin >> ws, username);
    }

    // Check whether username contains spaces
    if (username.find(' ') != string::npos)
    {
        cout << "\nUsername cannot contain spaces.\n";
        cout << "Registration cancelled.\n";
        return;
    }

    // Check whether username already exists
    if (FileManager::usernameExists(username))
    {
        cout << "\nUsername already exists.\n";
        cout << "Please choose another username.\n";
        return;
    }

    // Password validation
    cout << "Enter password: ";
    cin >> password;

    if (password.length() < 6)
    {
        cout << "\nPassword must contain at least 6 characters.\n";
        cout << "Registration cancelled.\n";
        return;
    }

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

    cout << "\n========================================\n";
    cout << "       REGISTRATION SUCCESSFUL\n";
    cout << "========================================\n";
    cout << "Name     : " << fullName << "\n";
    cout << "Username : " << username << "\n";
    cout << "User ID  : " << newUserId << "\n";
    cout << "========================================\n";
}

// Student login
bool loginStudent(User& loggedInUser)
{
    cout << "\n========================================\n";
    cout << "            STUDENT LOGIN\n";
    cout << "========================================\n";

    string username;
    string password;

    // Username validation
    cout << "Enter username: ";
    getline(cin >> ws, username);

    while (username.empty())
    {
        cout << "Username cannot be empty.\n";
        cout << "Enter username: ";
        getline(cin >> ws, username);
    }

    // Password validation
    cout << "Enter password: ";
    getline(cin >> ws, password);

    while (password.empty())
    {
        cout << "Password cannot be empty.\n";
        cout << "Enter password: ";
        getline(cin >> ws, password);
    }

    // Load registered users
    vector<User> users = FileManager::loadUsers();

    // Validate login
    for (const User& user : users)
    {
        if (user.getUsername() == username &&
            user.validatePassword(password))
        {
            loggedInUser = user;

            cout << "\n========================================\n";
            cout << "           LOGIN SUCCESSFUL\n";
            cout << "========================================\n";
            cout << "Welcome, "
                 << user.getFullName()
                 << "!\n";

            return true;
        }
    }

    cout << "\n========================================\n";
    cout << "       INVALID LOGIN DETAILS\n";
    cout << "========================================\n";
    cout << "Invalid username or password.\n";

    return false;
}

void startStudentQuiz(const User& user)
{
    cout << "\n========================================\n";
    cout << "              START QUIZ\n";
    cout << "========================================\n";

    // Select category
    int categoryChoice;

    cout << "\nSelect Category:\n";
    cout << "1. C++\n";
    cout << "2. Java\n";
    cout << "3. Python\n";
    cout << "4. General Knowledge\n";

    cout << "\nEnter your choice: ";
    cin >> categoryChoice;

    string category;

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
            cout << "\nInvalid category choice.\n";
            return;
    }

    // Select difficulty
    int difficultyChoice;

    cout << "\nSelect Difficulty:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";

    cout << "\nEnter your choice: ";
    cin >> difficultyChoice;

    string difficulty;

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
            cout << "\nInvalid difficulty choice.\n";
            return;
    }

    // Load all questions
    vector<Question> allQuestions =
        FileManager::loadQuestions();

    // Filter questions
    vector<Question> availableQuestions;

    for (const Question& question : allQuestions)
    {
        if (question.getCategory() == category &&
            question.getDifficulty() == difficulty)
        {
            availableQuestions.push_back(question);
        }
    }

    // Check whether questions are available
    if (availableQuestions.empty())
    {
        cout << "\nNo questions available for:\n";
        cout << "Category   : " << category << "\n";
        cout << "Difficulty : " << difficulty << "\n";
        return;
    }

    cout << "\nQuestions available: "
         << availableQuestions.size() << "\n";

    // Ask number of questions
    int numberOfQuestions;

    cout << "\nHow many questions would you like to attempt? ";
    cin >> numberOfQuestions;

    // Validate question count
    while (numberOfQuestions < 1 ||
           numberOfQuestions > static_cast<int>(availableQuestions.size()))
    {
        cout << "Please enter a number between 1 and "
             << availableQuestions.size() << ": ";

        cin >> numberOfQuestions;
    }

    // Randomly shuffle questions
    random_device rd;
    mt19937 generator(rd());

    shuffle(
        availableQuestions.begin(),
        availableQuestions.end(),
        generator
    );

    // Select required number of questions
    vector<Question> selectedQuestions(
        availableQuestions.begin(),
        availableQuestions.begin() + numberOfQuestions
    );

    // Create quiz
    Quiz quiz(
        selectedQuestions,
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
}

// Admin - Add Question
void addQuestion()
{
    cout << "\n========================================\n";
    cout << "             ADD QUESTION\n";
    cout << "========================================\n";

    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    string category;
    string difficulty;
    char correctAnswer;

    // Get question details
    cout << "\nEnter question: ";
    getline(cin >> ws, questionText);

    cout << "Enter Option A: ";
    getline(cin >> ws, optionA);

    cout << "Enter Option B: ";
    getline(cin >> ws, optionB);

    cout << "Enter Option C: ";
    getline(cin >> ws, optionC);

    cout << "Enter Option D: ";
    getline(cin >> ws, optionD);

    // Get correct answer
    cout << "\nEnter correct answer (A/B/C/D): ";
    cin >> correctAnswer;

    correctAnswer = toupper(correctAnswer);

    while (correctAnswer != 'A' &&
           correctAnswer != 'B' &&
           correctAnswer != 'C' &&
           correctAnswer != 'D')
    {
        cout << "Invalid answer. Enter A, B, C or D: ";
        cin >> correctAnswer;

        correctAnswer = toupper(correctAnswer);
    }

    // Select category
    cout << "\nSelect category:\n";
    cout << "1. C++\n";
    cout << "2. Java\n";
    cout << "3. Python\n";
    cout << "4. General Knowledge\n";

    int categoryChoice;

    cout << "Enter category: ";
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

    // Select difficulty
    cout << "\nSelect difficulty:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";

    int difficultyChoice;

    cout << "Enter difficulty: ";
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

    // Load existing questions
    vector<Question> questions =
        FileManager::loadQuestions();

    // Generate new question ID
    int newQuestionId = 1;

    for (const Question& question : questions)
    {
        if (question.getQuestionId() >= newQuestionId)
        {
            newQuestionId =
                question.getQuestionId() + 1;
        }
    }

    // Create options vector
    vector<string> options =
    {
        optionA,
        optionB,
        optionC,
        optionD
    };

    // Create Question object
    Question newQuestion(
        newQuestionId,
        questionText,
        options,
        correctAnswer,
        category,
        difficulty
    );

    // Save question
    FileManager::saveQuestion(newQuestion);

    cout << "\n========================================\n";
    cout << "       QUESTION ADDED SUCCESSFULLY\n";
    cout << "========================================\n";

    cout << "Question ID : "
         << newQuestionId << "\n";

    cout << "Category    : "
         << category << "\n";

    cout << "Difficulty  : "
         << difficulty << "\n";

    cout << "========================================\n";
}

// Admin - Update Question
void updateQuestion()
{
    cout << "\n========================================\n";
    cout << "            UPDATE QUESTION\n";
    cout << "========================================\n";

    vector<Question> questions =
        FileManager::loadQuestions();

    if (questions.empty())
    {
        cout << "\nNo questions available.\n";
        return;
    }

    int questionId;

    cout << "\nEnter Question ID to update: ";
    cin >> questionId;

    bool found = false;

    for (Question& question : questions)
    {
        if (question.getQuestionId() == questionId)
        {
            found = true;

            cout << "\nCurrent Question:\n";
            question.displayQuestion();

            string questionText;
            string optionA;
            string optionB;
            string optionC;
            string optionD;
            string category;
            string difficulty;
            char correctAnswer;

            cout << "\nEnter new question: ";
            getline(cin >> ws, questionText);

            cout << "Enter new Option A: ";
            getline(cin >> ws, optionA);

            cout << "Enter new Option B: ";
            getline(cin >> ws, optionB);

            cout << "Enter new Option C: ";
            getline(cin >> ws, optionC);

            cout << "Enter new Option D: ";
            getline(cin >> ws, optionD);

            cout << "\nEnter new correct answer (A/B/C/D): ";
            cin >> correctAnswer;

            correctAnswer = toupper(correctAnswer);

            while (correctAnswer != 'A' &&
                   correctAnswer != 'B' &&
                   correctAnswer != 'C' &&
                   correctAnswer != 'D')
            {
                cout << "Invalid answer. Enter A, B, C or D: ";
                cin >> correctAnswer;

                correctAnswer = toupper(correctAnswer);
            }

            cout << "\nSelect new category:\n";
            cout << "1. C++\n";
            cout << "2. Java\n";
            cout << "3. Python\n";
            cout << "4. General Knowledge\n";

            int categoryChoice;

            cout << "Enter category: ";
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

            cout << "\nSelect new difficulty:\n";
            cout << "1. Easy\n";
            cout << "2. Medium\n";
            cout << "3. Hard\n";

            int difficultyChoice;

            cout << "Enter difficulty: ";
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

            vector<string> options =
            {
                optionA,
                optionB,
                optionC,
                optionD
            };

            // Update the question
            question.setQuestionText(questionText);
            question.setOptions(options);
            question.setCorrectAnswer(correctAnswer);
            question.setCategory(category);
            question.setDifficulty(difficulty);

            break;
        }
    }

    if (!found)
    {
        cout << "\nQuestion with ID "
             << questionId
             << " was not found.\n";

        return;
    }

    // Rewrite the complete questions file
    ofstream file("data/questions.txt");

    if (!file)
    {
        cout << "\nError: Unable to update questions file.\n";
        return;
    }

    for (const Question& question : questions)
    {
        vector<string> options =
            question.getOptions();

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
    }

    file.close();

    cout << "\n========================================\n";
    cout << "       QUESTION UPDATED SUCCESSFULLY\n";
    cout << "========================================\n";
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

    // Username validation
    cout << "Enter admin username: ";
    getline(cin >> ws, username);

    while (username.empty())
    {
        cout << "Admin username cannot be empty.\n";
        cout << "Enter admin username: ";
        getline(cin >> ws, username);
    }

    // Password validation
    cout << "Enter admin password: ";
    getline(cin >> ws, password);

    while (password.empty())
    {
        cout << "Admin password cannot be empty.\n";
        cout << "Enter admin password: ";
        getline(cin >> ws, password);
    }

    // Default admin credentials
    const string ADMIN_USERNAME = "admin";
    const string ADMIN_PASSWORD = "admin123";

    if (username == ADMIN_USERNAME &&
        password == ADMIN_PASSWORD)
    {
        cout << "\n========================================\n";
        cout << "        ADMIN LOGIN SUCCESSFUL\n";
        cout << "========================================\n";

        return true;
    }

    cout << "\n========================================\n";
    cout << "       INVALID ADMIN CREDENTIALS\n";
    cout << "========================================\n";
    cout << "Invalid admin username or password.\n";

    return false;
}

// Admin - Delete Question
void deleteQuestion()
{
    cout << "\n========================================\n";
    cout << "            DELETE QUESTION\n";
    cout << "========================================\n";

    vector<Question> questions =
        FileManager::loadQuestions();

    if (questions.empty())
    {
        cout << "\nNo questions available.\n";
        return;
    }

    int questionId;

    cout << "\nEnter Question ID to delete: ";
    cin >> questionId;

    bool found = false;

    for (auto it = questions.begin();
         it != questions.end();
         ++it)
    {
        if (it->getQuestionId() == questionId)
        {
            found = true;

            cout << "\nQuestion found:\n";
            it->displayQuestion();

            char confirmation;

            cout << "\nAre you sure you want to delete "
                 << "this question? (Y/N): ";
            cin >> confirmation;

            confirmation = toupper(confirmation);

            if (confirmation != 'Y')
            {
                cout << "\nDelete operation cancelled.\n";
                return;
            }

            // Remove question from vector
            questions.erase(it);

            break;
        }
    }

    if (!found)
    {
        cout << "\nQuestion with ID "
             << questionId
             << " was not found.\n";

        return;
    }

    // Rewrite questions.txt without deleted question
    ofstream file("data/questions.txt");

    if (!file)
    {
        cout << "\nError: Unable to update questions file.\n";
        return;
    }

    for (const Question& question : questions)
    {
        vector<string> options =
            question.getOptions();

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
    }

    file.close();

    cout << "\n========================================\n";
    cout << "       QUESTION DELETED SUCCESSFULLY\n";
    cout << "========================================\n";
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
                addQuestion();
                break;

            case 2:
            {
                vector<Question> questions =
                FileManager::loadQuestions();

                cout << "\n========================================\n";
                cout << "            ALL QUESTIONS\n";
                cout << "========================================\n";

                if (questions.empty())
                {
                    cout << "\nNo questions available.\n";
                    break;
                }

                for (const Question& question : questions)
                {
                    cout << "\nQuestion ID : "<< question.getQuestionId() << "\n";

                    cout << "Question    : "<< question.getQuestionText() << "\n";

                    vector<string> options = question.getOptions();

                    for (size_t i = 0; i < options.size(); i++)
                    {
                        cout << char('A' + i)<< ". " << options[i] << "\n";
                    }

                    cout << "Correct     : "<< question.getCorrectAnswer() << "\n";

                    cout << "Category    : "<< question.getCategory() << "\n";

                    cout << "Difficulty  : "<< question.getDifficulty() << "\n";

                    cout << "----------------------------------------\n";
                }
                break;
            }

            case 3:
                updateQuestion();
                break;

            case 4:
                deleteQuestion();
                break;

            case 5:
{
    cout << "\n========================================\n";
    cout << "          STUDENT RESULTS\n";
    cout << "========================================\n";

    ifstream file("data/results.txt");

    if (!file)
    {
        cout << "\nNo student results available.\n";
        break;
    }

    string line;
    bool hasResults = false;

    cout << "\nUsername\tCategory\tTotal\tCorrect\tWrong\tPercentage\n";
    cout << "------------------------------------------------------------------\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        hasResults = true;

        string username;
        string category;
        string totalQuestions;
        string correctAnswers;
        string wrongAnswers;
        string percentage;

        stringstream ss(line);

        getline(ss, username, '|');
        getline(ss, category, '|');
        getline(ss, totalQuestions, '|');
        getline(ss, correctAnswers, '|');
        getline(ss, wrongAnswers, '|');
        getline(ss, percentage, '|');

        cout << username << "\t\t"
             << category << "\t"
             << totalQuestions << "\t"
             << correctAnswers << "\t"
             << wrongAnswers << "\t"
             << percentage << "%\n";
    }

    file.close();

    if (!hasResults)
    {
        cout << "\nNo student results available.\n";
    }

    break;
}

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

        // Validate menu input
        while (!(cin >> choice))
        {
            cout << "\nInvalid input. Please enter a number.\n";
            cout << "Enter your choice: ";

            cin.clear();
            cin.ignore(10000, '\n');
        }

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
                cout << "\nInvalid choice. Please enter a number between 1 and 4.\n";
        }

    } while (choice != 4);

    return 0;
}