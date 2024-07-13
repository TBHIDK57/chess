#pragma once
template <typename TextureType>
class Piece {
public:
    enum class PieceType {
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };


    virtual ~Piece() = default;
    Piece(const TextureType& texture, bool isWhite);
    virtual void move(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) {}
    void setTexture(const TextureType& texture);
    const sf::Sprite& getSprite() const { return sprite; }

    void setPosition(float x, float y) { sprite.setPosition(x, y); }

    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const = 0;

    bool isWhitePiece() const { return isWhite; }

    virtual PieceType getType() const = 0;

    bool hasMoved() const { return moved; }

    void setMoved() { moved = true; }

    bool operator==(const Piece& other) const {
        return (other.isWhitePiece() == this->isWhitePiece());
    }



protected:

    bool isPathClear(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const;

private:

    sf::Sprite sprite;
    bool isWhite;
    bool moved;
};

#include "../src/Piece.cpp"
