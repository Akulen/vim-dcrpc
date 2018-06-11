let s:rpc_file = '/tmp/dcrpc'

autocmd VimLeave * call system('rm -f ' . s:rpc_file)

command! StartDcrpc :call dcrpc#StartDcrpc()
command! StopDcrpc :call dcrpc#StopDcrpc()

if exists("g:dcrpc_autostart")
    if g:dcrpc_autostart == 1
        StartDcrpc
    endif
endif
