#!bin/bash
./bin/ar_base.exe < data/in > data/out_ar_base
./bin/ar_undo_move.exe < data/in > data/out_ar_undo_move
./bin/ar_alpha_beta.exe < data/in > data/out_ar_alpha_beta
./bin/ar_move_order.exe < data/in > data/out_ar_move_order

./bin/bb_base.exe < data/in > data/out_bb_base
./bin/bb_undo_move.exe < data/in > data/out_bb_undo_move
./bin/bb_alpha_beta.exe < data/in > data/out_bb_alpha_beta
./bin/bb_move_order.exe < data/in > data/out_bb_move_order
