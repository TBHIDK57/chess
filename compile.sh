echo "> Bishop.cpp"
g++ -c src/Bishop.cpp -o obj/Bishop.o 
echo "> Game.cpp"
g++ -c src/Game.cpp -o obj/Game.o 
echo "> King.cpp"
g++ -c src/King.cpp -o obj/King.o 
echo "> Knight.cpp"
g++ -c src/Knight.cpp -o obj/Knight.o 
echo "> Pawn.cpp"
g++ -c src/Pawn.cpp -o obj/Pawn.o 
echo "> Piece.cpp"
g++ -c src/Piece.cpp -o obj/Piece.o 
echo "> Queen.cpp"
g++ -c src/Queen.cpp -o obj/Queen.o 
echo "> Rook.cpp"
g++ -c src/Rook.cpp -o obj/Rook.o 
echo "> Dialogbox.cpp"
g++ -c src/DialogBox.cpp -o obj/DialogBox.o 
echo "> main.cpp"
g++ -c src/main.cpp -o obj/main.o 
echo "> Login.cpp"
g++ -c src/login.cpp -o obj/Login.o `wx-config --cxxflags --libs` 
echo "> Database.cpp"
g++ -c src/Database.cpp -o obj/Database.o 
echo "> chess_game"
g++ obj/main.o obj/Login.o obj/DialogBox.o obj/Bishop.o obj/Game.o obj/King.o obj/Knight.o obj/Pawn.o obj/Rook.o obj/Database.o  -o chess_game `wx-config --cxxflags --libs` -I/usr/include/mysql -L/usr/lib -lmysqlclient -lsfml-graphics -lsfml-window -lsfml-system 
