let g:rpc_file = '/tmp/dcrpc'

autocmd VimEnter * call system('bash ' . expand('<sfile>:p:h') . '/../dcrpc.sh &')
autocmd VimLeave * call system('rm -f ' . g:rpc_file)

func DcRpc(timer)
    call writefile([expand('%:t'), line('.'), line('$')], g:rpc_file)
endfunc

let timer = timer_start(5000, 'DcRpc', {'repeat': -1})
