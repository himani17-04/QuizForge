# QuizForge - Online Quiz Application

## Project Overview

QuizForge is a console-based Online Quiz Application developed using C++.

The application allows students to register, log in, select quizzes based on category and difficulty, answer multiple-choice questions, and view their results.

An Admin module is also provided to manage quiz questions and view student performance.

---

## Features

### Student Module

- Student Registration
- Student Login
- Student Profile
- Category Selection
- Difficulty Selection
- Selection of Number of Questions
- Random Question Selection
- Multiple Choice Questions (MCQs)
- Automatic Answer Validation
- Score Calculation
- Percentage Calculation
- Pass/Fail Result
- Automatic Result Storage
- Student Logout

### Admin Module

- Admin Login
- Add Questions
- View Questions
- Update Questions
- Delete Questions
- View Student Results
- Admin Logout

---

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Standard Template Library (STL)
- VS Code
- Git & GitHub

---

## C++ Concepts Used

The project demonstrates the following C++ concepts:

- Classes and Objects
- Constructors
- Encapsulation
- Inheritance concepts
- Functions
- Vectors
- Strings
- File Handling
- Conditional Statements
- Loops
- Exception-free Input Validation
- Randomization
- STL Algorithms

---

## Project Structure

```text
QuizForge/
│
├── include/
│   ├── User.h
│   ├── Admin.h
│   ├── Question.h
│   ├── Quiz.h
│   └── FileManager.h
│
├── src/
│   ├── main.cpp
│   ├── User.cpp
│   ├── Admin.cpp
│   ├── Question.cpp
│   ├── Quiz.cpp
│   └── FileManager.cpp
│
├── data/
│   ├── users.txt
│   ├── questions.txt
│   └── results.txt
│
├── README.md
├── .gitignore
└── LICENSE