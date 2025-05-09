#pragma once
template <typename TextureType>
class Bishop : public Piece<TextureType> {
public:
    using Piece<TextureType>::Piece;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const override;
    typename Piece<TextureType>::PieceType getType() const override;
};
#include "../src/Bishop.cpp"

