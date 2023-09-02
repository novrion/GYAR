g++ -O2 -o bb_base .\main.cpp .\board.cpp .\moves.cpp .\search_base.cpp
g++ -O2 -o bb_undo_move .\main.cpp .\board.cpp .\moves.cpp .\search_undo_move.cpp
g++ -O2 -o bb_alpha_beta .\main.cpp .\board.cpp .\moves.cpp .\search_alpha_beta.cpp
g++ -O2 -o bb_move_order .\main.cpp .\board.cpp .\moves.cpp .\search_move_order.cpp