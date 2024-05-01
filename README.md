# COMP2113-Course-Project-Chen-Yushu-Sudoku-

##Group menber: Chen Yushu 3035829508

1. Introduction and Discription

  1.1 Brief Introduction
  My game is inspired by the famous game Sudoku. In my game, there is a gameboard with four rows and four columns, constructing a 4*4 square and totally 16 numbers. In this project, I designed   a cpp code to complete the game. A gameboard with numbers and blanks will be generated for players to fill in numbers 1 to 4.  After solving the gameboard, players should make sure that each   raw, column and each 2*2 block at the corner are exactly filled with numbers from 1 to 4, otherwise they are not able to win the game. I also wrote a Sudoku with 9*9 gameboard but it seems     to take too much time to run. I have included a test version of it.

  1.2 Game Discription
  Players start with a 4*4 gameboard with randomly about 6-8 numbers given. Therefore, players should complete the remaining 8-10 empty squares. The completion rules are below:
  1. Numbers can be used are 1,2,3,4.
  2. In each row, players must use each number once.
  3. In each column, players must use each number once.
  4. In top-left, top-right, bottom-left and bottom-right 2*2 squares, players must use each number once.

2. Code Description
   2.1 When each game starts, my code will generates a random gameboard. The numbers in each square are random and the position of empty squares are random. However, in each initial state, I make sure that the gameboard is solvable.
   2.2 For each gameboard, I use an array to store it. The array has 4 rows and 4 columns.
   2.3 I use dynamic memory management to form my initial gameboard. I use lists. Using this dynamic memory manegement is to make sure my initial gameboard is solvable because is not every random full gameboard can make sure every row, column and small 2*2 square has no repeated number.
   2.4 When game begins, I will output a gameboard with a few blank squares. Then I will let players to input orders and numbers. When players fill in a number, I will print an updated gameboard. When players want to change a number in a particular position, I allowed them to input the cordinate and change the number. And when the game is completed, my program will ask players whether to end the game or play again.
   2.5 In cpp documents, I write comments to explain my logic.

3. Quick Start
   
   
   

   



