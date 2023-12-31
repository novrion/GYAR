#!bin/bash
g++ -std=c++17 -O2 -o bin/ar_base.exe src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_base.cpp
g++ -std=c++17 -O2 -o bin/ar_undo_move.exe src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_undo_move.cpp
g++ -std=c++17 -O2 -o bin/ar_alpha_beta.exe src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_alpha_beta.cpp
g++ -std=c++17 -O2 -o bin/ar_move_order.exe src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_move_order.cpp

g++ -std=c++17 -O2 -o bin/bb_base.exe src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_base.cpp  
g++ -std=c++17 -O2 -o bin/bb_undo_move.exe src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_undo_move.cpp
g++ -std=c++17 -O2 -o bin/bb_alpha_beta.exe src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_alpha_beta.cpp
g++ -std=c++17 -O2 -o bin/bb_move_order.exe src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_move_order.cpp
