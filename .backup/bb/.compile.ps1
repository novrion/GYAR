g++ -O2 -o bb_base .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_base.cpp
g++ -O2 -o bb_undo_move .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_undo_move.cpp
g++ -O2 -o bb_alpha_beta .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_alpha_beta.cpp
g++ -O2 -o bb_move_order .\src\main.cpp .\src\board.cpp .\src\moves.cpp .\src\search_move_order.cpp

Get-Content -Path .\in\in | bb_base | Out-File -Path .\out\out
Get-Content -Path .\in\in | bb_undo_move | Out-File -Path .\out\out
Get-Content -Path .\in\in | bb_alpha_beta | Out-File -Path .\out\out
Get-Content -Path .\in\in | bb_move_order | Out-File -Path .\out\out