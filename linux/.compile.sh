#!bin/bash
g++ -O2 -o bin/ar_base src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_base.cpp
g++ -O2 -o bin/ar_undo_move src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_undo_move.cpp
g++ -O2 -o bin/ar_alpha_beta src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_alpha_beta.cpp
g++ -O2 -o bin/ar_move_order src/ar/main.cpp src/ar/board.cpp src/ar/moves.cpp src/ar/search_move_order.cpp

g++ -O2 -o bin/bb_base src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_base.cpp  
g++ -O2 -o bin/bb_undo_move src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_undo_move.cpp
g++ -O2 -o bin/bb_alpha_beta src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_alpha_beta.cpp
g++ -O2 -o bin/bb_move_order src/bb/main.cpp src/bb/board.cpp src/bb/moves.cpp src/bb/search_move_order.cpp
