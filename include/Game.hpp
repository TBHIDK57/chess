#pragma once
template <typename TextureType>
class Game {
public:
    Game();
    void run();
    ~Game();
    void setUsernames(const std::string& white, const std::string& black);
    void setFilename(std::string& filename){FILENAME = filename;}
private:
    int currentMoveNumber = 0;
    static const int BOARD_SIZE = 8;
    static const int WINDOW_SIZE = 800;
    static const int SQUARE_SIZE = WINDOW_SIZE / BOARD_SIZE;
    std::string whitePlayerName, blackPlayerName, FILENAME, message;
    sf::Vector2i lastMovedPawn = {-1, -1};
    sf::RenderWindow window;
    TextureType whitePawnTexture, blackPawnTexture;
    TextureType whiteRookTexture, blackRookTexture;
    TextureType whiteKnightTexture, blackKnightTexture;
    TextureType whiteBishopTexture, blackBishopTexture;
    TextureType whiteQueenTexture, blackQueenTexture;
    TextureType whiteKingTexture, blackKingTexture;

    Piece<TextureType>*** board;
    bool isWhiteTurn = true;
    bool pieceSelected = false;
    bool gameOver = false;
    sf::Vector2i selectedPiecePos;

    void loadTextures();
    void initializeBoard();
    void drawBoard();
    void handleMouseClick(int x, int y);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    bool isKingInCheck(bool isWhiteKing);
    bool hasLegalMoves(bool isWhitePlayer);
    void promotePawn(int row, int col);
    void drawPiece(const Piece<TextureType>& piece, int row, int col);
    Piece<TextureType>* createPiece(typename Piece<TextureType>::PieceType type, bool isWhite) const;
    void saveGame(const std::string&) ;
    void loadGame(const std::string&, int);
    void removeFutureStates(const std::string& filename, int currentMove);
    
    template <typename T>
    friend std::ofstream& operator<<(std::ofstream& ofs, const Game<T>& game); 
    // {
    //     ofs.write(reinterpret_cast<const char*>(&game.isWhiteTurn), sizeof(game.isWhiteTurn));
    //     ofs.write(reinterpret_cast<const char*>(&game.lastMovedPawn), sizeof(game.lastMovedPawn));

    //     for (int i = 0; i < Game<TextureType>::BOARD_SIZE; ++i) {
    //         for (int j = 0; j < Game<TextureType>::BOARD_SIZE; ++j) {
    //             char pieceType = 'Z';
    //             bool isWhite = false;
    //             bool hasMoved = false;
    //             if (game.board[i][j]) {
    //                 pieceType = static_cast<char>(game.board[i][j]->getType());
    //                 isWhite = game.board[i][j]->isWhitePiece();
    //                 hasMoved = game.board[i][j]->hasMoved();
    //             }
    //             ofs.write(&pieceType, sizeof(pieceType));
    //             ofs.write(reinterpret_cast<const char*>(&isWhite), sizeof(isWhite));
    //             ofs.write(reinterpret_cast<const char*>(&hasMoved), sizeof(hasMoved));
    //         }
    //     }
    //     return ofs;
    // }

    // Operator overloading for reading game state
    template <typename T>
    friend std::ifstream& operator>>(std::ifstream& ifs, Game<T>& game);
    // {
    //     ifs.read(reinterpret_cast<char*>(&game.isWhiteTurn), sizeof(game.isWhiteTurn));
    //     ifs.read(reinterpret_cast<char*>(&game.lastMovedPawn), sizeof(game.lastMovedPawn));

    //     for (int i = 0; i < Game<TextureType>::BOARD_SIZE; ++i) {
    //         for (int j = 0; j < Game<TextureType>::BOARD_SIZE; ++j) {
    //             delete game.board[i][j];
    //             game.board[i][j] = nullptr;

    //             char pieceType;
    //             bool isWhite;
    //             bool hasMoved;
    //             ifs.read(&pieceType, sizeof(pieceType));
    //             ifs.read(reinterpret_cast<char*>(&isWhite), sizeof(isWhite));
    //             ifs.read(reinterpret_cast<char*>(&hasMoved), sizeof(hasMoved));

    //             if (pieceType != 'Z') {
    //                 game.board[i][j] = game.createPiece(
    //                     static_cast<typename Piece<TextureType>::PieceType>(pieceType),
    //                     isWhite
    //                 );
    //                 if (hasMoved) {
    //                     game.board[i][j]->setMoved();
    //                 }
    //             }
    //         }
    //     }
    //     return ifs;
    // }


};

#include "../src/Game.cpp"