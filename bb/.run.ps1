Get-Content .\in\in | .\bb_base.exe | Out-File .\out\out_base
Get-Content .\in\in | .\bb_undo_move.exe | Out-File .\out\out_undo_move
Get-Content .\in\in | .\bb_alpha_beta.exe | Out-File .\out\out_alpha_beta
Get-Content .\in\in | .\bb_move_order.exe | Out-File .\out\out_move_order