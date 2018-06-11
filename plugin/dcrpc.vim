let s:rpc_file = '/tmp/dcrpc'
let s:file_dir = expand('<sfile>:p:h')

autocmd VimLeave * call system('rm -f ' . s:rpc_file)

func dcrpc#WriteTmp(timer)
    call writefile(['Line ' . line('.') . ' of ' . line('$'), 'Editing ' . expand('%:t')], s:rpc_file)
endfunc

func dcrpc#StartDcrpc()
    call system('bash ' . s:file_dir . '/../dcrpc.sh &')
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
