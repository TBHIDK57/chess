#pragma once
#include "chess.hpp"
#include <unistd.h>


template <typename TextureType>
void Game<TextureType>::setUsernames(const std::string& white, const std::string& black){
    whitePlayerName = white;
    blackPlayerName = black;
}

template <typename TextureType>
std::ofstream& operator<<(std::ofstream& ofs, const Game<TextureType>& game) {
    ofs.write(reinterpret_cast<const char*>(&game.isWhiteTurn), sizeof(game.isWhiteTurn));
    ofs.write(reinterpret_cast<const char*>(&game.lastMovedPawn), sizeof(game.lastMovedPawn));

    for (int i = 0; i < Game<TextureType>::BOARD_SIZE; ++i) {
        for (int j = 0; j < Game<TextureType>::BOARD_SIZE; ++j) {
            char pieceType = 'Z';
            bool isWhite = false;
            bool hasMoved = false;
            if (game.board[i][j]) {
                pieceType = static_cast<char>(game.board[i][j]->getType());
                isWhite = game.board[i][j]->isWhitePiece();
                hasMoved = game.board[i][j]->hasMoved();
            }
            ofs.write(&pieceType, sizeof(pieceType));
            ofs.write(reinterpret_cast<const char*>(&isWhite), sizeof(isWhite));
            ofs.write(reinterpret_cast<const char*>(&hasMoved), sizeof(hasMoved));
        }
    }
    return ofs;
}

template <typename TextureType>
std::ifstream& operator>>(std::ifstream& ifs, Game<TextureType>& game) {
    ifs.read(reinterpret_cast<char*>(&game.isWhiteTurn), sizeof(game.isWhiteTurn));
    ifs.read(reinterpret_cast<char*>(&game.lastMovedPawn), sizeof(game.lastMovedPawn));

    for (int i = 0; i < Game<TextureType>::BOARD_SIZE; ++i) {
        for (int j = 0; j < Game<TextureType>::BOARD_SIZE; ++j) {
            delete game.board[i][j];
            game.board[i][j] = nullptr;

            char pieceType;
            bool isWhite;
            bool hasMoved;
            ifs.read(&pieceType, sizeof(pieceType));
            ifs.read(reinterpret_cast<char*>(&isWhite), sizeof(isWhite));
            ifs.read(reinterpret_cast<char*>(&hasMoved), sizeof(hasMoved));

            if (pieceType != 'Z') {
                game.board[i][j] = game.createPiece(
                    static_cast<typename Piece<TextureType>::PieceType>(pieceType),
                    isWhite
                );
                if (hasMoved) {
                    game.board[i][j]->setMoved();
                }
            }
        }
    }
    return ifs;
}
template std::ofstream& operator<<(std::ofstream& ofs, const Game<sf::Texture>& game);
template std::ifstream& operator>>(std::ifstream& ifs, Game<sf::Texture>& game);

template <typename TextureType>
void Game<TextureType>::saveGame(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing");
    }

    file << *this;

    if (!file) {
        throw std::runtime_error("Error writing board state");
    }
    file.close();

    removeFutureStates(filename, currentMoveNumber);
}


template <typename TextureType>
void Game<TextureType>::loadGame(const std::string& filename, int moveNumber) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Unable to open file for reading");
    }

    std::streampos fileSize = file.tellg();
    std::streampos stateSize = sizeof(isWhiteTurn) + sizeof(lastMovedPawn) +
        BOARD_SIZE * BOARD_SIZE * (sizeof(char) + 2 * sizeof(bool));
    int totalMoves = fileSize / stateSize;

    if (moveNumber < 0 || moveNumber >= totalMoves) {
        moveNumber = totalMoves - 1; // Load the latest state if invalid number provided
    }

    std::streampos pos = moveNumber * stateSize;
    file.seekg(pos);

    file >> *this;

    if (!file) {
        throw std::runtime_error("Error reading board state");
    }

    currentMoveNumber = moveNumber;
}

template <typename TextureType>
void Game<TextureType>::removeFutureStates(const std::string& filename, int currentMove) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        throw std::runtime_error("Unable to open file for reading and writing");
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    std::streampos stateSize = sizeof(isWhiteTurn) + sizeof(lastMovedPawn) +
                               BOARD_SIZE * BOARD_SIZE * (sizeof(char) + 2 * sizeof(bool));
    int totalMoves = fileSize / stateSize;

    if (currentMove < totalMoves - 1) {
        // Truncate the file to remove future states
        std::streampos newSize = (currentMove + 1) * stateSize;
        
        file.close();  // Close the file before truncating


            truncate(filename.c_str(), newSize);

    }
}

template <typename TextureType>
void Game<TextureType>::loadTextures() {

    if (!whitePawnTexture.loadFromFile("assets/images/PawnW.png") ||
        !blackPawnTexture.loadFromFile("assets/images/PawnB.png") ||
        !whiteRookTexture.loadFromFile("assets/images/RookW.png") ||
        !blackRookTexture.loadFromFile("assets/images/RookB.png") ||
        !whiteKnightTexture.loadFromFile("assets/images/KnightW.png") ||
        !blackKnightTexture.loadFromFile("assets/images/KnightB.png") ||
        !whiteBishopTexture.loadFromFile("assets/images/BishopW.png") ||
        !blackBishopTexture.loadFromFile("assets/images/BishopB.png") ||
        !whiteQueenTexture.loadFromFile("assets/images/QueenW.png") ||
        !blackQueenTexture.loadFromFile("assets/images/QueenB.png") ||
        !whiteKingTexture.loadFromFile("assets/images/KingW.png") ||
        !blackKingTexture.loadFromFile("assets/images/KingB.png")) {
        throw std::runtime_error("Error loading textures");
    }
}
template <typename TextureType>
void Game<TextureType>::initializeBoard() {
    board = new Piece<TextureType>**[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[i] = new Piece<TextureType>*[BOARD_SIZE]();
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[1][i] = new Pawn<TextureType>(blackPawnTexture, false);
        board[6][i] = new Pawn<TextureType>(whitePawnTexture, true);
    }
    board[0][0] = new Rook<TextureType>(blackRookTexture, false);
    board[0][7] = new Rook<TextureType>(blackRookTexture, false);
    board[7][0] = new Rook<TextureType>(whiteRookTexture, true);
    board[7][7] = new Rook<TextureType>(whiteRookTexture, true);
    board[0][1] = new Knight<TextureType>(blackKnightTexture, false);
    board[0][6] = new Knight<TextureType>(blackKnightTexture, false);
    board[7][1] = new Knight<TextureType>(whiteKnightTexture, true);
    board[7][6] = new Knight<TextureType>(whiteKnightTexture, true);
    board[0][2] = new Bishop<TextureType>(blackBishopTexture, false);
    board[0][5] = new Bishop<TextureType>(blackBishopTexture, false);
    board[7][2] = new Bishop<TextureType>(whiteBishopTexture, true);
    board[7][5] = new Bishop<TextureType>(whiteBishopTexture, true);
    board[0][3] = new Queen<TextureType>(blackQueenTexture, false);
    board[7][3] = new Queen<TextureType>(whiteQueenTexture, true);
    board[0][4] = new King<TextureType>(blackKingTexture, false);
    board[7][4] = new King<TextureType>(whiteKingTexture, true);
}

template <typename TextureType>
void Game<TextureType>::drawBoard() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color(255, 206, 158));
            } else {
                square.setFillColor(sf::Color(209, 139, 71));
            }
            window.draw(square);
            if (board[row][col] != nullptr) {
                drawPiece(*board[row][col], row, col);
            }
        }
    }
}

template <typename TextureType>
void Game<TextureType>::handleMouseClick(int x, int y) {
    int row = y / SQUARE_SIZE;
    int col = x / SQUARE_SIZE;
    if (pieceSelected) {
        if (movePiece(selectedPiecePos.x, selectedPiecePos.y, row, col)) {
            isWhiteTurn = !isWhiteTurn;
            currentMoveNumber++;
            saveGame(FILENAME + ".dat");
        }
        pieceSelected = false;
    } else {
        if (board[row][col] != nullptr && board[row][col]->isWhitePiece() == isWhiteTurn) {
            selectedPiecePos = sf::Vector2i(row, col);
            pieceSelected = true;
        }
    }
}

template <typename TextureType>
bool Game<TextureType>::movePiece(int startRow, int startCol, int endRow, int endCol) {
    Piece<TextureType>* piece = board[startRow][startCol];
    if (piece && piece->isValidMove(startRow, startCol, endRow, endCol, board)) {
    // Store the current board state
    Piece<TextureType>* tempBoard[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            tempBoard[i][j] = board[i][j];
        }
    }
    // Perform the move
    Piece<TextureType>* captured = board[endRow][endCol];
    board[endRow][endCol] = piece;
    board[startRow][startCol] = nullptr;
    // Handle en passant
    if (piece->getType() == Piece<TextureType>::PieceType::Pawn) {
        Pawn<TextureType>* pawn = static_cast<Pawn<TextureType>*>(piece);
        if (std::abs(startCol - endCol) == 1 && captured == nullptr) {
            // En passant capture
            if (lastMovedPawn.x == endRow + (piece->isWhitePiece() ? 1 : -1) && lastMovedPawn.y == endCol) {
                delete board[lastMovedPawn.x][lastMovedPawn.y];
                board[lastMovedPawn.x][lastMovedPawn.y] = nullptr;
            }
        }
        pawn->move(startRow, startCol, endRow, endCol, board);
        // Update lastMovedPawn
        if (std::abs(startRow - endRow) == 2) {
            lastMovedPawn = {endRow, endCol};
        } else {
            lastMovedPawn = {-1, -1}; // Reset if it's not a two-square move
        }
    } else {
        lastMovedPawn = {-1, -1}; // Reset for non-pawn moves
    }
        // Handle castling
        if (piece->getType() == Piece<TextureType>::PieceType::King) {
            King<TextureType>* king = static_cast<King<TextureType>*>(piece);
            if (std::abs(startCol - endCol) == 2) {
                king->performCastling(startRow, startCol, endCol, board);
            }
        }



        // Check if the move puts the current player in check
        if (isKingInCheck(isWhiteTurn)) {
            // Revert the move
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    board[i][j] = tempBoard[i][j];
                }
            }
            return false;
        }
        // Handle pawn promotion
        if (piece->getType() == Piece<TextureType>::PieceType::Pawn && (endRow == 0 || endRow == 7)) {
            promotePawn(endRow, endCol);
        }
        piece->setMoved();
        // Check for checkmate or stalemate
        bool opponentInCheck = isKingInCheck(!isWhiteTurn);

        if (!hasLegalMoves(!isWhiteTurn)) {
            if (opponentInCheck) {
                message = (isWhiteTurn ? whitePlayerName : blackPlayerName) + " wins by checkmate!";
            } else {
                message = "Stalemate! The game is a draw.";
            }
            
            gameOver = true; // Set the flag to indicate the game is over
        } else if (opponentInCheck) {
            std::cout << (isWhiteTurn ? "Black" : "White") << " is in check!" << std::endl;
        }
        if (captured) {
            delete captured;
        }
        return true;
    }
    return false;
}

template <typename TextureType>
bool Game<TextureType>::isKingInCheck(bool isWhiteKing) {
    // Find the king
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] && board[i][j]->getType() == Piece<TextureType>::PieceType::King &&
                board[i][j]->isWhitePiece() == isWhiteKing) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }
    // Check if any opponent piece can attack the king
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] && board[i][j]->isWhitePiece() != isWhiteKing) {
                if (board[i][j]->isValidMove(i, j, kingRow, kingCol, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename TextureType>
bool Game<TextureType>::hasLegalMoves(bool isWhitePlayer) {
    for (int startRow = 0; startRow < BOARD_SIZE; ++startRow) {
        for (int startCol = 0; startCol < BOARD_SIZE; ++startCol) {
            if (board[startRow][startCol] && board[startRow][startCol]->isWhitePiece() == isWhitePlayer) {
                for (int endRow = 0; endRow < BOARD_SIZE; ++endRow) {
                    for (int endCol = 0; endCol < BOARD_SIZE; ++endCol) {
                        if (board[startRow][startCol]->isValidMove(startRow, startCol, endRow, endCol, board)) {
                            // Try the move
                            Piece<TextureType>* temp = board[endRow][endCol];
                            board[endRow][endCol] = board[startRow][startCol];
                            board[startRow][startCol] = nullptr;
                            bool inCheck = isKingInCheck(isWhitePlayer);
                            // Undo the move
                            board[startRow][startCol] = board[endRow][endCol];
                            board[endRow][endCol] = temp;
                            if (!inCheck) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
template <typename TextureType>
void Game<TextureType>::promotePawn(int row, int col) {
    // For simplicity, we'll always promote to a Queen
    delete board[row][col];
    board[row][col] = new Queen<TextureType>(
        board[row][col]->isWhitePiece() ? whiteQueenTexture : blackQueenTexture,
        board[row][col]->isWhitePiece()
    );
}

template <typename TextureType>
void Game<TextureType>::drawPiece(const Piece<TextureType>& piece, int row, int col) {
    // Example implementation; customize as per your Piece class structure
    sf::Sprite sprite;
    switch (piece.getType()) {
        case Piece<TextureType>::PieceType::Pawn:
            sprite.setTexture(piece.isWhitePiece() ? whitePawnTexture : blackPawnTexture);
            break;
        case Piece<TextureType>::PieceType::Rook:
            sprite.setTexture(piece.isWhitePiece() ? whiteRookTexture : blackRookTexture);
            break;
        case Piece<TextureType>::PieceType::Knight:
            sprite.setTexture(piece.isWhitePiece() ? whiteKnightTexture : blackKnightTexture);
            break;
        case Piece<TextureType>::PieceType::Bishop:
            sprite.setTexture(piece.isWhitePiece() ? whiteBishopTexture : blackBishopTexture);
            break;
        case Piece<TextureType>::PieceType::Queen:
            sprite.setTexture(piece.isWhitePiece() ? whiteQueenTexture : blackQueenTexture);
            break;
        case Piece<TextureType>::PieceType::King:
            sprite.setTexture(piece.isWhitePiece() ? whiteKingTexture : blackKingTexture);
            break;
        default:
            // Handle default case or throw an error
            break;
    }
    sprite.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
    sprite.setScale(0.2f, 0.2f); // Adjust scale as needed
    window.draw(sprite);
}

template <typename TextureType>
Piece<TextureType>* Game<TextureType>::createPiece(typename Piece<TextureType>::PieceType type, bool isWhite) const {
    switch (type) {
        case Piece<TextureType>::PieceType::Pawn:
            return new Pawn<TextureType>(isWhite ? whitePawnTexture : blackPawnTexture, isWhite);
        case Piece<TextureType>::PieceType::Rook:
            return new Rook<TextureType>(isWhite ? whiteRookTexture : blackRookTexture, isWhite);
        case Piece<TextureType>::PieceType::Knight:
            return new Knight<TextureType>(isWhite ? whiteKnightTexture : blackKnightTexture, isWhite);
        case Piece<TextureType>::PieceType::Bishop:
            return new Bishop<TextureType>(isWhite ? whiteBishopTexture : blackBishopTexture, isWhite);
        case Piece<TextureType>::PieceType::Queen:
            return new Queen<TextureType>(isWhite ? whiteQueenTexture : blackQueenTexture, isWhite);
        case Piece<TextureType>::PieceType::King:
            return new King<TextureType>(isWhite ? whiteKingTexture : blackKingTexture, isWhite);
        default:
            throw std::runtime_error("Unknown piece type");
    }
}

template <typename TextureType>
Game<TextureType>::Game() {
    
}

template <typename TextureType>
void Game<TextureType>::run() {
    window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess Game");
    loadTextures();
    initializeBoard();
    
    try {

        loadGame(FILENAME + ".dat", -1);  // Load the latest move
        std::cout << "Loaded saved game state." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "No saved game found or error loading game. Starting new game." << std::endl;
        currentMoveNumber = 0;
    }

    while (window.isOpen() && !gameOver) {
        sf::Event event;
        while (window.pollEvent(event) && !gameOver) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::S:
                        try {
                            saveGame(FILENAME + ".dat");
                            std::cout << "Game saved successfully." << std::endl;
                        } catch (const std::exception& e) {
                            std::cerr << "Error saving game: " << e.what() << std::endl;
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (currentMoveNumber > 0 && !isKingInCheck(isWhiteTurn)) {
                            currentMoveNumber--;
                            loadGame(FILENAME + ".dat", currentMoveNumber);
                            std::cout << "Moved to previous state: " << currentMoveNumber << std::endl;
                        }
                        break;
                    case sf::Keyboard::Right:
                        try {
                            loadGame(FILENAME + ".dat", currentMoveNumber + 1);
                            currentMoveNumber++;
                            std::cout << "Moved to next state: " << currentMoveNumber << std::endl;
                        } catch (const std::exception& e) {
                            std::cout << "No next move available." << std::endl;
                        }
                        break;
                }
            }
        }
        window.clear(sf::Color::White);
        drawBoard();
        window.display();
    }

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf")) {
        std::cerr << "Failed to load font from file!" << std::endl;
    } else {
        DialogBox dialogBox(message, font);
        dialogBox.show();
    }
    window.close();
}

template <typename TextureType>
Game<TextureType>::~Game() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}
