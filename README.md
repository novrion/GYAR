# GYAR
A dipoma project by Elias and Arvid in NA21MA at Norra Real gymnasium in Stockholm\
The purpose of the research is to determine how effective different optimization techniques are for minimax chess engines\
Undo move, alpha beta pruning, and move order optimizations were tested on a two dimensional 8x8 32-bit signed integer array represented engine and a 13 64-bit unsigned integer (bitboard) represented engine\
# Abbreviations
**ar** = array represented chess engine\
**bb** = bitboard respresented chess engine\
**base** = engine without optimizations\
**undo_move** = engine with undo move optimization\
**alpha_beta** = engine with alpha beta pruning optimization\
**move_order** = engine with move order and alpha beta pruning optimizations\
# Data
The chess positions executed are located in **bot/data/in**\
The final result is located in **bot/data/out**\
Specific results for each execution are stored in **bot/data/out_x** (x = name of engine)\
# Engine Source Code
Located in **bot/src/ar** and **bot/src/bb** respectively\
**search**: Minimax search algorithm, evaluation, user interface\
**board**: Board initialization, make move, undo move\
**moves**: Move generation\
**macros**: Library inclusion, constants, macros\
# Other Code
**.compile.sh**: Compiles the engines\
**.run.sh**: Executes the engines\
**.assemble.sh**: Compiles the results\
**analysis.cpp**: Compilation and calculation of average standard deviations and relative differences (used by .assemble.sh)\
# Other
**technical-specification**: Technical specifications of machine, operating system, and compilation\
**pseudocode**: Pseudocode of the minimax algorithm with different optimizations (solely alpha beta pruning optimization is achieved by removing SortMVVLVA() from the alpha beta pruning and move order optimizations pseudocode)\