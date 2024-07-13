# C++ Chess Game

![image_2024-07-13_090715790](https://github.com/user-attachments/assets/ec90c511-a95a-4ad1-8b8a-de77219c4a0d)


This is a chess game implemented in C++ using the SFML library for graphics and MySQL for user authentication. The game features a graphical user interface, move validation, and the ability to save and load game states. This project is designed for Linux systems.

## OOP Features

- Inheritence
- Abstraction
- Polymorphism
- Encapsulation
- Composition
- Operator Overloading
- Templates

## Game Features

- Graphical user interface using SFML
- User authentication system using MySQL database
- Move validation for all chess pieces
- Ability to save and load game states
- Support for special moves like castling and en passant
- Pawn promotion
- Check and checkmate detection

## Dependencies

- C++ compiler with C++11 support
- SFML library
- MySQL server
- MySQL Connector/C++ (not required to be installed separately on most Linux distributions)

## Project Structure

- `main.cpp`: Entry point of the application
- `Game.cpp`: Main game logic
- `Piece.cpp`: Base class for chess pieces
- `[PieceName].cpp`: Individual piece classes (e.g., Pawn.cpp, Rook.cpp, etc.)
- `Database.cpp`: Handles database operations for user authentication
- `Login.cpp`: Manages the login system

## Installation

To compile and run the game, follow these steps:

1. **Ensure you have all the necessary dependencies installed:**
   
   - C++ Compiler: Ensure you have a C++ compiler with C++11 support. You can install `g++` if you don't have it:
     ```sh
     sudo apt-get update
     sudo apt-get install g++
     ```

   - SFML Library: Install the SFML library for graphical rendering. You can follow these steps to install SFML:
     ```sh
     sudo apt-get update
     sudo apt-get install libsfml-dev
     ```

   - MySQL Server: Install the MySQL server for database management:
     ```sh
     sudo apt-get install mysql-server
     ```

   - MySQL Connector/C++: Install the MySQL Connector/C++ to connect your application to the MySQL database (not required to be installed separately on most Linux distributions):
     ```sh
     sudo apt-get install libmysqlcppconn-dev
     ```

2. **Clone this repository to your local machine:**
   ```sh
   git clone https://github.com/IlluminateDreamer/chess.git
   cd chess
   ```
3. **Compile and run the code:**
   ```sh
   bash compile.sh
   sudo ./chess_game
   ```

## Setting Up the MySQL Database

Before running the game, you need to set up the MySQL database:

1. Log in to your MySQL server.
   ```sh
   sudo mysql -u root
   ```
2. Create a new database named 'chess':
    ```sql
    CREATE DATABASE chess;
    ```

3. Use the 'chess' database:
    ```sql
    USE chess;
    ```

4. Create the 'users' table with the following structure:
    ```sql
    CREATE TABLE users (
      id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
      player1 VARCHAR(255) NOT NULL UNIQUE,
      player1_password VARCHAR(255) NOT NULL,
      player2 VARCHAR(255) NOT NULL UNIQUE,
      player2_password VARCHAR(255) NOT NULL
    );
    ```
## Known Issues and Limitations

- Template Usage: The project uses C++ templates with sf::Texture. While this allows for potential future expansion to support custom textures, it currently adds unnecessary complexity to the code as sf::Texture is used throughout the program.
- Custom Texture Support: Using custom textures may cause errors in functions like loadFromFile. Additional error handling and modifications would be needed to fully support custom textures.
- Template Complexity: The use of templates increases the complexity of the code without providing significant benefits in the current implementation.
- Linux-Specific: This project is currently designed and tested for Linux systems only.

## Future Improvements

- Optimize template usage
- Enhance error handling for custom textures
- Implement a more robust game state saving system
- Cross-platform compatibility

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
