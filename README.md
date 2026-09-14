QuizForge — Online Quiz Application
1. Project Overview

QuizForge is a console-based Online Quiz Application developed using C++.

The application allows students to register, log in, take multiple-choice quizzes, receive results, view their quiz history, and check their overall performance.

An Admin module is also provided to manage quiz questions and view student results.

2. Features
2.1 Student Features
Student registration
Student login
Student profile
Password validation
Username uniqueness validation
Quiz category selection
Quiz difficulty selection
Random question selection
User-defined number of questions
Multiple-choice questions
Answer validation
Automatic score calculation
Percentage calculation
PASS/FAIL result
60-second quiz time limit
Quiz history
Attempt numbering
Performance summary
Student logout
2.2 Admin Features
Admin login
Admin dashboard
Add questions
View all questions
Update questions
Delete questions
View student results
Admin logout
3. Quiz Categories

The application currently supports:

C++
Java
Python
General Knowledge
4. Difficulty Levels

The application provides three difficulty levels:

Easy
Medium
Hard
5. Quiz Functionality

The student can:

Select a quiz category.
Select a difficulty level.
Select the number of questions.
Attempt randomly selected questions.
Submit answers using A/B/C/D.
Receive the score after completing the quiz.

The application automatically calculates the student's performance.

6. Quiz Timer

Each quiz has a time limit of:

60 seconds (1 minute)

The application uses the C++ chrono library to measure the elapsed quiz time.

If the time limit is reached between questions, the application displays a TIME IS UP message and ends the quiz.

Note: The current implementation checks the timer between questions rather than displaying a continuously updating countdown while the user is entering an answer.

7. Result System

After completing a quiz, the application calculates:

Total questions
Correct answers
Wrong answers
Percentage
PASS/FAIL status
Passing Criteria

The passing percentage is:

40%

Sample Result
========================================
              QUIZ RESULT
========================================
Category        : C++
Difficulty      : Easy
Total Questions : 5
Correct Answers : 4
Wrong Answers   : 1
Percentage      : 80.00%
Result          : PASSED
========================================
8. Quiz History

Students can view their previous quiz attempts from the Student Dashboard.

Each attempt displays:

Attempt number
Category
Difficulty
Total questions
Correct answers
Wrong answers
Percentage
Result
Sample Quiz History
========================================
             QUIZ HISTORY
========================================

Attempt #1
----------------------------------------
Category        : C++
Difficulty      : Easy
Total Questions : 5
Correct Answers : 4
Wrong Answers   : 1
Percentage      : 80.00%
Result          : PASSED
----------------------------------------

Attempt #2
----------------------------------------
Category        : Java
Difficulty      : Medium
Total Questions : 5
Correct Answers : 3
Wrong Answers   : 2
Percentage      : 60.00%
Result          : PASSED
----------------------------------------

========================================
9. Performance Summary

Students can view their overall performance from the Student Dashboard.

The performance summary contains:

Total quiz attempts
Passed quizzes
Failed quizzes
Average percentage
Best percentage
Sample Performance Summary
========================================
        PERFORMANCE SUMMARY
========================================
Total Attempts    : 5
Passed Quizzes    : 4
Failed Quizzes    : 1
Average Percentage: 72.50%
Best Percentage   : 90.00%
========================================
10. Admin Question Management

The Admin can manage quiz questions through the Admin Dashboard.

Available Operations
Add Question
View Questions
Update Question
Delete Question

Each question contains:

Question ID
Question text
Four options
Correct answer
Category
Difficulty
11. Student Authentication

The application provides a basic authentication system.

Student Registration

A new student can register by providing:

Full name
Username
Password

The application checks whether the username already exists.

Student Login

Registered students can log in using:

Username
Password
Admin Login

The Admin uses separate login credentials to access the Admin Dashboard.

12. Input Validation

The application validates user input in several areas:

Main menu
Student registration
Student login
Admin login
Student dashboard
Admin dashboard
Quiz category
Quiz difficulty
Number of quiz questions
MCQ answers

Invalid inputs are rejected and the user is asked to enter a valid value.

13. Data Storage

QuizForge uses text files for persistent data storage.

data/
├── users.txt
├── questions.txt
└── results.txt
users.txt

Stores registered student information.

questions.txt

Stores:

Question ID
Question text
Options
Correct answer
Category
Difficulty
results.txt

Stores student quiz results including:

Username
Category
Difficulty
Total questions
Correct answers
Wrong answers
Percentage
Result
14. Technologies Used
C++
Object-Oriented Programming (OOP)
File Handling
STL Vector
Random Number Generation
C++ Chrono Library
VS Code
Git
GitHub
15. C++ Concepts Used

The project demonstrates the following C++ concepts:

Classes and Objects
Encapsulation
Constructors
Getters and Setters
Member Functions
vector
Strings
File Input/Output
Input Validation
Loops
Conditional Statements
Functions
References
const
Randomization
chrono
Header Files
Separate .h and .cpp files
16. Project Structure
QuizForge/
│
├── include/                       # Header Files
│   ├── User.h
│   ├── Admin.h
│   ├── Question.h
│   ├── Quiz.h
│   └── FileManager.h
│
├── src/                           # Source Files
│   ├── main.cpp
│   ├── User.cpp
│   ├── Admin.cpp
│   ├── Question.cpp
│   ├── Quiz.cpp
│   └── FileManager.cpp
│
├── data/                          # Data Files
│   ├── users.txt
│   ├── questions.txt
│   └── results.txt
│
├── README.md
├── .gitignore
└── LICENSE
17. Application Flow
                         QuizForge
                            |
              +-------------+-------------+
              |                           |
           Student                       Admin
              |                           |
       +------+------+             +------+------+
       |      |      |             |      |      |
   Register Login Profile        Add    View   Update/Delete
              |                   Questions    Questions
              |                       |
              v                       v
       Student Dashboard       Student Results
              |
      +-------+---------+
      |       |         |
     Quiz   History  Performance
      |
      v
 Start Quiz
      |
      v
Category Selection
      |
      v
Difficulty Selection
      |
      v
Number of Questions
      |
      v
Random Questions
      |
      v
60-Second Timer
      |
      v
Answer Questions
      |
      v
Score Calculation
      |
      v
PASS / FAIL
      |
      v
Save Result
18. How to Run
Prerequisites

Install the following:

C++ compiler such as G++
VS Code
Git
Step 1: Open the Project

Open the QuizForge folder in VS Code.

Step 2: Open Terminal

Open the VS Code terminal in the project directory.

Step 3: Compile the Project

Run:

g++ src/main.cpp src/Question.cpp src/Quiz.cpp src/User.cpp src/Admin.cpp src/FileManager.cpp -o QuizForge
Step 4: Run the Application

On Windows:

.\QuizForge.exe
19. Admin Login

For the current development version:

Username: admin
Password: admin123
20. Sample Student Account

For testing purposes:

Username: prachi123
Password: 12345
21. Objective

The main objective of QuizForge is to demonstrate the development of a structured C++ application using Object-Oriented Programming and File Handling.

The project focuses on:

User authentication
Quiz management
Question management
Automated evaluation
Persistent data storage
Result management
Quiz history
Student performance tracking
22. Future Enhancements

Possible future improvements include:

Live countdown timer
Leaderboard
More quiz categories
More questions
Question search and filtering
Student password change
Admin password management
Improved console UI
Database integration
Graphical User Interface (GUI)
Online/cloud-based quiz support
23. Project Status

Status: Completed Academic Project

The current version includes:

Student authentication
Quiz functionality
Question management
Result management
Quiz history
Attempt numbering
Performance summary
60-second quiz timer
Input validation
24. Author

Himani Raut

B.Tech. Information Technology