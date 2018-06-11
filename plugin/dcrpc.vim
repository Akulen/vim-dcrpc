let g:rpc_file = '/tmp/dcrpc'

autocmd VimLeave * call system('rm -f ' . g:rpc_file)

func dcrpc#WriteTmp(timer)
    call writefile([expand('%:t'), line('.'), line('$')], g:rpc_file)
endfunc

func dcrpc#StartDcrpc()
    echo 'bash ' . expand('<sfile>:p:h') . '/../dcrpc.sh &'
    call system('bash ' . expand('<sfile>:p:h') . '/../dcrpc.sh &')
    let g:dcrpctimer = timer_start(5000, 'dcrpc#WriteTmp', {'repeat': -1})
endfunc

func dcrpc#StopDcrpc()
    :call timer_stop(g:dcrpctimer)
    call system('rm -f ' . g:rpc_file)
endfunc

command! StartDcrpc :call dcrpc#StartDcrpc()
command! StopDcrpc :call dcrpc#StopDcrpc()
