# 🎮 Tic Tac Toe – Console Game in C++ (with AI using Minimax)
A console-based Tic Tac Toe game developed in C++ using Object-Oriented Programming (OOP) principles. This project also integrates the Minimax algorithm with alpha-beta pruning for implementing an unbeatable AI opponent.

# 📌 Features
Play against another human or AI

Smart AI using Minimax algorithm

Clean and intuitive console interface

Fully object-oriented code using:

Abstraction

Encapsulation

Inheritance

Polymorphism

# 🧠 OOP Concepts Applied
This project demonstrates all four pillars of OOP in C++:

# ✅ 1. Abstraction:

The game hides complex internal logic using well-defined classes like GameBoard, Player, and TicTacToe.

The user interacts with the game through a simple interface without needing to understand the internal logic.

# ✅ 2. Encapsulation:

Each class encapsulates its data and behavior.

For example, GameBoard manages the board state, move logic, and win/draw checking—all hidden behind public methods like placeMove(), checkForWins(), etc.

# ✅ 3. Inheritance:

The abstract Player class provides a common interface for both HumanPlayer and AIPlayer, allowing polymorphic behavior in the game loop.

class Player
{
public:
    virtual void makeMove(GameBoard &board) = 0;
};

# ✅ 4. Polymorphism:

Run-time polymorphism is achieved using virtual functions and smart pointers (unique_ptr<Player>) to handle dynamic dispatch between human and AI players seamlessly.

currentPlayer->makeMove(board);

# 🧠 AI Implementation – Minimax Algorithm with Alpha-Beta Pruning
The AI opponent (AIPlayer) uses the Minimax algorithm, a classic decision-making strategy used in two-player games like Tic Tac Toe.

# 🧮 Working:
AI simulates all possible future moves recursively.

It assumes the opponent plays optimally.

Scores are assigned based on win/loss/draw outcomes.

The AI chooses the move with the maximum score (best-case outcome).

# 🔧 Optimization: Alpha-Beta Pruning

Alpha and Beta values help eliminate unnecessary branches.

Significantly improves performance by pruning paths that won’t affect the final decision.

# 🧠 AI Score Logic:

Outcome	Score
AI wins	10 - depth
Draw	0
Loss	depth - 10

# 🖥️ How to Play

Run the program

Choose whether to play against another human or AI.

Input a number from 1 to 9 to place your move (see board numbering):

  1 | 2 | 3
  4 | 5 | 6
  7 | 8 | 9

# 🛠️ Technologies Used

Language: C++

Concepts: OOP, Minimax Algorithm, Alpha-Beta Pruning

Compiler: Any standard C++ compiler (G++, Clang++, etc.)

# 📸 Preview

![image](https://github.com/user-attachments/assets/e5920df5-49ed-4bb5-9b32-2fd5d012930a)

![image](https://github.com/user-attachments/assets/b7a2077e-0700-45b0-a80b-0bee679d1169)

![image](https://github.com/user-attachments/assets/78cf9412-5405-4323-a82c-b42ae81f150f)




# 🙌 Contributions
Feel free to fork the repository and suggest improvements or enhancements via pull requests!
