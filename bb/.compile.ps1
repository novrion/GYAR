g++ -O2 -o bb_base .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_base.cpp
g++ -O2 -o bb_undo_move .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_undo_move.cpp
g++ -O2 -o bb_alpha_beta .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_alpha_beta.cpp
g++ -O2 -o bb_move_order .\src\main.cpp .\src\board_move_order.cpp .\src\moves.cpp .\src\search_move_order.cpp