# vim-dcrpc

![demo pic](https://gitlab.com/betseg/vim-dcrpc/raw/master/pics/demo.png)

# Discord Rich Presence for Vim

Because why not?

# Installation

Didn't try but *should* work with all plugin managers. Just install this like you install other plugins. Then run `make` in the directory the plugin was installed in.

# Usage

To start:

```
:StartDcrpc
```

To stop:

```
:StopDcrpc
```

To automatically start the plugin everytime Vim is started, put this in your `.vimrc`:

```
let g:dcrpc_autostart = 1
```
