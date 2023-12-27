# GYAR
A dipoma project by Elias and Arvid in NA21MA at Norra Real gymnasium in Stockholm\
The purpose of the research is to determine how effective different optimization techniques are for minimax chess engines\
Undo move, alpha beta pruning, and move order optimizations were tested on a two dimensional 8x8 32-bit signed integer array represented engine and a 13 64-bit unsigned integer (bitboard) represented engine
# Abbreviations
**ar** = array represented chess engine\
**bb** = bitboard respresented chess engine\
**base** = engine without optimizations\
**undo_move** = engine with undo move optimization\
**alpha_beta** = engine with alpha beta pruning optimization\
**move_order** = engine with move order and alpha beta pruning optimizations
# Result
![average-relative-speed-ar](https://github.com/novrion/GYAR/assets/128396601/26925c01-3908-4c60-881e-0e48ed7986fe)
![average-relative-speed-bb](https://github.com/novrion/GYAR/assets/128396601/afc93b66-86b8-425f-8df5-4ae340d64679)
# Optimizations
**Undo move** optimization relies on passing chess positions as references instead of copies. Since copying chess positions can be slow, reversing a chess move after returning from a deeper search instead may decrease execution time.\
**Alpha beta** pruning optimization stores the best result the opponent can already achieve during search. Any positions that result in anything better can therefore be disregarded. Since less position need to be searched, the execution time decreases.\
**Move order** optimization heuristically orders the search to optimize the amount of positions alpha beta pruning can disregard. Specifically, this investigation uses MVVLVA (Most Valuable Victim - Least Valuable Aggressor) ordering to search moves that use less valuable pieces to capture more valuable piece first.
# Data
The chess positions executed are located in **bot/data/in**\
The final result is located in **bot/data/out**\
Specific results for each execution are stored in **bot/data/out_x** (x = name of engine)
# Engine Source Code
Located in **bot/src/ar** and **bot/src/bb** respectively\
**search**: Minimax search algorithm, evaluation, user interface\
**board**: Board initialization, make move, undo move\
**moves**: Move generation\
**macros**: Library inclusion, constants, macros
# Other Code
**.compile.sh**: Compiles the engines\
**.run.sh**: Executes the engines\
**.assemble.sh**: Compiles the results\
**analysis.cpp**: Compilation and calculation of average standard deviations and relative differences (used by .assemble.sh)
# Other
**technical-specification**: Technical specifications of machine, operating system, and compilation\
**pseudocode**: Pseudocode of the minimax algorithm with different optimizations (solely alpha beta pruning optimization is achieved by removing SortMVVLVA() from the alpha beta pruning and move order optimizations pseudocode)
