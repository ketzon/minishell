if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <C-G>S <Plug>ISurround
imap <C-G>s <Plug>Isurround
imap <C-S> <Plug>Isurround
nmap - <Plug>VinegarUp
nmap <p <Plug>(unimpaired-put-below-leftward)
nmap <P <Plug>(unimpaired-put-above-leftward)
nmap <s <Plug>(unimpaired-enable)
nmap =p <Plug>(unimpaired-put-below-reformat)
nmap =P <Plug>(unimpaired-put-above-reformat)
nmap =s <Plug>(unimpaired-toggle)
nmap >p <Plug>(unimpaired-put-below-rightward)
nmap >P <Plug>(unimpaired-put-above-rightward)
nmap >s <Plug>(unimpaired-disable)
xmap S <Plug>VSurround
nmap [xx <Plug>(unimpaired-xml-encode-line)
xmap [x <Plug>(unimpaired-xml-encode)
nmap [x <Plug>(unimpaired-xml-encode)
nmap [uu <Plug>(unimpaired-url-encode-line)
xmap [u <Plug>(unimpaired-url-encode)
nmap [u <Plug>(unimpaired-url-encode)
nmap [CC <Plug>(unimpaired-string-encode-line)
xmap [C <Plug>(unimpaired-string-encode)
nmap [C <Plug>(unimpaired-string-encode)
nmap [yy <Plug>(unimpaired-string-encode-line)
xmap [y <Plug>(unimpaired-string-encode)
nmap [y <Plug>(unimpaired-string-encode)
nmap [P <Plug>(unimpaired-put-above)
nmap [p <Plug>(unimpaired-put-above)
nmap [o <Plug>(unimpaired-enable)
xmap [e <Plug>(unimpaired-move-selection-up)
nmap [e <Plug>(unimpaired-move-up)
nmap [  <Plug>(unimpaired-blank-up)
omap [n <Plug>(unimpaired-context-previous)
xmap [n <Plug>(unimpaired-context-previous)
nmap [n <Plug>(unimpaired-context-previous)
nmap [f <Plug>(unimpaired-directory-previous)
nmap [<C-T> <Plug>(unimpaired-ptprevious)
nmap [ <Plug>(unimpaired-ptprevious)
nmap [T <Plug>(unimpaired-tfirst)
nmap [t <Plug>(unimpaired-tprevious)
nmap [<C-Q> <Plug>(unimpaired-cpfile)
nmap [ <Plug>(unimpaired-cpfile)
nmap [Q <Plug>(unimpaired-cfirst)
nmap [q <Plug>(unimpaired-cprevious)
nmap [<C-L> <Plug>(unimpaired-lpfile)
nmap [ <Plug>(unimpaired-lpfile)
nmap [L <Plug>(unimpaired-lfirst)
nmap [l <Plug>(unimpaired-lprevious)
nmap [B <Plug>(unimpaired-bfirst)
nmap [b <Plug>(unimpaired-bprevious)
nmap [A <Plug>(unimpaired-first)
nmap [a <Plug>(unimpaired-previous)
noremap \m :silent! :make! | :redraw!
noremap \cw :botright :cw
nmap ]xx <Plug>(unimpaired-xml-decode-line)
xmap ]x <Plug>(unimpaired-xml-decode)
nmap ]x <Plug>(unimpaired-xml-decode)
nmap ]uu <Plug>(unimpaired-url-decode-line)
xmap ]u <Plug>(unimpaired-url-decode)
nmap ]u <Plug>(unimpaired-url-decode)
nmap ]CC <Plug>(unimpaired-string-decode-line)
xmap ]C <Plug>(unimpaired-string-decode)
nmap ]C <Plug>(unimpaired-string-decode)
nmap ]yy <Plug>(unimpaired-string-decode-line)
xmap ]y <Plug>(unimpaired-string-decode)
nmap ]y <Plug>(unimpaired-string-decode)
nmap ]P <Plug>(unimpaired-put-below)
nmap ]p <Plug>(unimpaired-put-below)
nmap ]o <Plug>(unimpaired-disable)
xmap ]e <Plug>(unimpaired-move-selection-down)
nmap ]e <Plug>(unimpaired-move-down)
nmap ]  <Plug>(unimpaired-blank-down)
omap ]n <Plug>(unimpaired-context-next)
xmap ]n <Plug>(unimpaired-context-next)
nmap ]n <Plug>(unimpaired-context-next)
nmap ]f <Plug>(unimpaired-directory-next)
nmap ]<C-T> <Plug>(unimpaired-ptnext)
nmap ] <Plug>(unimpaired-ptnext)
nmap ]T <Plug>(unimpaired-tlast)
nmap ]t <Plug>(unimpaired-tnext)
nmap ]<C-Q> <Plug>(unimpaired-cnfile)
nmap ] <Plug>(unimpaired-cnfile)
nmap ]Q <Plug>(unimpaired-clast)
nmap ]q <Plug>(unimpaired-cnext)
nmap ]<C-L> <Plug>(unimpaired-lnfile)
nmap ] <Plug>(unimpaired-lnfile)
nmap ]L <Plug>(unimpaired-llast)
nmap ]l <Plug>(unimpaired-lnext)
nmap ]B <Plug>(unimpaired-blast)
nmap ]b <Plug>(unimpaired-bnext)
nmap ]A <Plug>(unimpaired-last)
nmap ]a <Plug>(unimpaired-next)
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
xmap gS <Plug>VgSurround
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
xmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nmap yo <Plug>(unimpaired-toggle)
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nnoremap <silent> <Plug>unimpairedTPNext :exe "p".(v:count ? v:count : "")."tnext"
nnoremap <silent> <Plug>unimpairedTPPrevious :exe "p".(v:count ? v:count : "")."tprevious"
nnoremap <silent> <Plug>(unimpaired-ptnext) :exe v:count1 . "ptnext"
nnoremap <silent> <Plug>(unimpaired-ptprevious) :exe v:count1 . "ptprevious"
nnoremap <silent> <Plug>unimpairedTLast :exe "".(v:count ? v:count : "")."tlast"
nnoremap <silent> <Plug>unimpairedTFirst :exe "".(v:count ? v:count : "")."tfirst"
nnoremap <silent> <Plug>unimpairedTNext :exe "".(v:count ? v:count : "")."tnext"
nnoremap <silent> <Plug>unimpairedTPrevious :exe "".(v:count ? v:count : "")."tprevious"
nnoremap <Plug>(unimpaired-tlast) :=v:count ? v:count . "trewind" : "tlast"
nnoremap <Plug>(unimpaired-tfirst) :=v:count ? v:count . "trewind" : "tfirst"
nnoremap <silent> <Plug>(unimpaired-tnext) :exe "".(v:count ? v:count : "")."tnext"
nnoremap <silent> <Plug>(unimpaired-tprevious) :exe "".(v:count ? v:count : "")."tprevious"
nnoremap <silent> <Plug>unimpairedQNFile :exe "".(v:count ? v:count : "")."cnfile"zv
nnoremap <silent> <Plug>unimpairedQPFile :exe "".(v:count ? v:count : "")."cpfile"zv
nnoremap <silent> <Plug>(unimpaired-cnfile) :exe "".(v:count ? v:count : "")."cnfile"zv
nnoremap <silent> <Plug>(unimpaired-cpfile) :exe "".(v:count ? v:count : "")."cpfile"zv
nnoremap <silent> <Plug>unimpairedQLast :exe "".(v:count ? v:count : "")."clast"zv
nnoremap <silent> <Plug>unimpairedQFirst :exe "".(v:count ? v:count : "")."cfirst"zv
nnoremap <silent> <Plug>unimpairedQNext :exe "".(v:count ? v:count : "")."cnext"zv
nnoremap <silent> <Plug>unimpairedQPrevious :exe "".(v:count ? v:count : "")."cprevious"zv
nnoremap <Plug>(unimpaired-clast) :=v:count ? v:count . "cc" : "clast"zv
nnoremap <Plug>(unimpaired-cfirst) :=v:count ? v:count . "cc" : "cfirst"zv
nnoremap <silent> <Plug>(unimpaired-cnext) :exe "".(v:count ? v:count : "")."cnext"zv
nnoremap <silent> <Plug>(unimpaired-cprevious) :exe "".(v:count ? v:count : "")."cprevious"zv
nnoremap <silent> <Plug>unimpairedLNFile :exe "".(v:count ? v:count : "")."lnfile"zv
nnoremap <silent> <Plug>unimpairedLPFile :exe "".(v:count ? v:count : "")."lpfile"zv
nnoremap <silent> <Plug>(unimpaired-lnfile) :exe "".(v:count ? v:count : "")."lnfile"zv
nnoremap <silent> <Plug>(unimpaired-lpfile) :exe "".(v:count ? v:count : "")."lpfile"zv
nnoremap <silent> <Plug>unimpairedLLast :exe "".(v:count ? v:count : "")."llast"zv
nnoremap <silent> <Plug>unimpairedLFirst :exe "".(v:count ? v:count : "")."lfirst"zv
nnoremap <silent> <Plug>unimpairedLNext :exe "".(v:count ? v:count : "")."lnext"zv
nnoremap <silent> <Plug>unimpairedLPrevious :exe "".(v:count ? v:count : "")."lprevious"zv
nnoremap <Plug>(unimpaired-llast) :=v:count ? v:count . "ll" : "llast"zv
nnoremap <Plug>(unimpaired-lfirst) :=v:count ? v:count . "ll" : "lfirst"zv
nnoremap <silent> <Plug>(unimpaired-lnext) :exe "".(v:count ? v:count : "")."lnext"zv
nnoremap <silent> <Plug>(unimpaired-lprevious) :exe "".(v:count ? v:count : "")."lprevious"zv
nnoremap <silent> <Plug>unimpairedBLast :exe "".(v:count ? v:count : "")."blast"
nnoremap <silent> <Plug>unimpairedBFirst :exe "".(v:count ? v:count : "")."bfirst"
nnoremap <silent> <Plug>unimpairedBNext :exe "".(v:count ? v:count : "")."bnext"
nnoremap <silent> <Plug>unimpairedBPrevious :exe "".(v:count ? v:count : "")."bprevious"
nnoremap <Plug>(unimpaired-blast) :=v:count ? v:count . "buffer" : "blast"
nnoremap <Plug>(unimpaired-bfirst) :=v:count ? v:count . "buffer" : "bfirst"
nnoremap <silent> <Plug>(unimpaired-bnext) :exe "".(v:count ? v:count : "")."bnext"
nnoremap <silent> <Plug>(unimpaired-bprevious) :exe "".(v:count ? v:count : "")."bprevious"
nnoremap <silent> <Plug>unimpairedALast :exe "".(v:count ? v:count : "")."last"
nnoremap <silent> <Plug>unimpairedAFirst :exe "".(v:count ? v:count : "")."first"
nnoremap <silent> <Plug>unimpairedANext :exe "".(v:count ? v:count : "")."next"
nnoremap <silent> <Plug>unimpairedAPrevious :exe "".(v:count ? v:count : "")."previous"
nnoremap <Plug>(unimpaired-last) :=v:count ? v:count . "argument" : "last"
nnoremap <Plug>(unimpaired-first) :=v:count ? v:count . "argument" : "first"
nnoremap <silent> <Plug>(unimpaired-next) :exe "".(v:count ? v:count : "")."next"
nnoremap <silent> <Plug>(unimpaired-previous) :exe "".(v:count ? v:count : "")."previous"
nnoremap <silent> <Plug>SurroundRepeat .
nmap <silent> <Plug>CommentaryUndo :echoerr "Change your <Plug>CommentaryUndo map to <Plug>Commentary<Plug>Commentary"
xnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
map <F1> :Stdheader
imap S <Plug>ISurround
imap s <Plug>Isurround
imap  <Plug>Isurround
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autowrite
set background=dark
set backspace=indent,eol,start
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=fr
set hidden
set history=200
set nomodeline
set operatorfunc=<SNR>24_go
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,~/.vim/pack/tpope/start/vim-vinegar,~/.vim/pack/tpope/start/unimpaired,~/.vim/pack/tpope/start/surround,~/.vim/pack/tpope/start/fugitive,~/.vim/pack/tpope/start/commentary,/var/lib/vim/addons,/etc/vim,/usr/share/vim/vimfiles,/usr/share/vim/vim82,/usr/share/vim/vim82/pack/dist/opt/termdebug,/usr/share/vim/vimfiles/after,/etc/vim/after,/var/lib/vim/addons/after,~/.vim/after
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set noswapfile
set tabstop=4
" vim: set ft=vim :
