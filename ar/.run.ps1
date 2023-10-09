Get-Content .\in\in | .\ar_base.exe | Out-File .\out\out_base
Get-Content .\in\in | .\ar_undo_move.exe | Out-File .\out\out_undo_move
Get-Content .\in\in | .\ar_alpha_beta.exe | Out-File .\out\out_alpha_beta
Get-Content .\in\in | .\ar_move_order.exe | Out-File .\out\out_move_orderw

$tmp = Read-Host "Press ENTER to exit "