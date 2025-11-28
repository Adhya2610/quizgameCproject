# The Ultimate Quiz Game
# Overview

The Ultimate Quiz Game is a console-based quiz application written in C. It presents players with five levels of multiple-choice questions covering topics such as Bollywood, Indian history, riddles, general knowledge, and computer science. The program features a scoring system, timed questions, lifelines, and persistent high-score storage.

# Features
Quiz Levels

The game includes five themed levels, each containing ten questions:

Bollywood Bonanza

Echoes of India (History)

Mind Maze (Riddles)

WorldWatch (General Knowledge)

Code Chronicles (Computer Science)

# Question Structure

Each question provides four multiple-choice options. The answer order is randomized for each question to ensure varied gameplay.

# Scoring System

Correct answer: 1 point

Correct answer using the Double Points lifeline: 2 points

Incorrect answer: 0 points

Skipped question: 0 points

At the end of the game, an appreciation message is displayed based on the final score.

# Lifelines

Players have access to three lifelines per level, each usable once:

Skip: Moves directly to the next question without scoring.

Fifty-Fifty: Displays only the correct answer and one randomly chosen incorrect answer.

Double Points: Awards double points for the current question if answered correctly.

# Time Limit

Each question must be answered within 90 seconds. Exceeding the time limit results in the game terminating immediately.

# High Score System

The game loads and saves the highest score using a file named highscore.txt. If the player’s score exceeds the current high score, it is updated at the end of the game.

# Program Structure
Core Components
Question Data Model

A struct Question stores:

The question text

Four answer options

The index of the correct option

Quiz Bank

All questions are stored in a two-dimensional array categorized by level.

Lifeline Implementation

Lifeline logic is processed within the ask() function, which manages:

Option randomization

Lifeline selection and effects

Timer enforcement

Answer validation and scoring

High Score Management

Two functions handle high-score persistence:

saveHighscore() writes the new high score to a file.

loadHighscore() reads the current high score at startup.

Main Loop

The main() function:

Displays level headers

Iterates through all questions and levels

Tracks scoring and lifeline availability

Presents the final score and appreciation message

# File Structure:

quiz_game.c      
Source code implementation
highscore.txt  
Automatically created to store high scores
README.md   
Project documentation
