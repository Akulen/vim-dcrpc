let s:rpc_file = '/tmp/dcrpc'

autocmd VimLeave * call system('rm -f ' . s:rpc_file)
autocmd VimLeave * call system('killall vim-dcrpc')

func dcrpc#WriteTmp(timer)
    call writefile([expand('%:t'), line('.'), line('$')], s:rpc_file)
endfunc

func dcrpc#StartDcrpc()
    call system('bash ' . expand('%:p:h') . '/../dcrpc.sh &')
    let s:dcrptimer = timer_start(5000, 'dcrpc#WriteTmp', {'repeat': -1})
endfunc

func dcrpc#StopDcrpc()
    call system('killall vim-dcrpc')
    call timer_stop(s:dcrptimer)
endfunc

command! StartDcrpc :call dcrpc#StartDcrpc()
command! StopDcrpc :call dcrpc#StopDcrpc()

if exists("g:dcrpc_autostart")
    if g:dcrpc_autostart == 1
        StartDcrpc
    endif
endif
