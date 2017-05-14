execute pathogen#infect()
syntax on
filetype plugin indent on
set laststatus=2
set hlsearch "highlight search"
set ic
"=============================================================="
let g:airline_powerline_fonts = 1   

let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#buffer_nr_show = 1
let g:airline_theme = "hybrid"
let g:airline#extensions#tabline#buffer_idx_mode = 1
nmap <leader>1 <Plug>AirlineSelectTab1
nmap <leader>2 <Plug>AirlineSelectTab2
nmap <leader>3 <Plug>AirlineSelectTab3
nmap <leader>4 <Plug>AirlineSelectTab4
nmap <leader>5 <Plug>AirlineSelectTab5
nmap <leader>6 <Plug>AirlineSelectTab6
nmap <leader>7 <Plug>AirlineSelectTab7
nmap <leader>8 <Plug>AirlineSelectTab8
nmap <leader>9 <Plug>AirlineSelectTab9
nmap <leader>- <Plug>AirlineSelectPrevTab
nmap <leader>+ <Plug>AirlineSelectNextTab

 if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif

" unicode symbols
let g:airline_left_sep = '»'
let g:airline_left_sep = '▶'
let g:airline_right_sep = '«'
let g:airline_right_sep = '◀'
let g:airline_symbols.linenr = '␊'
let g:airline_symbols.linenr = '␤'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.branch = '⎇'
let g:airline_symbols.paste = 'ρ'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.paste = '∥'
let g:airline_symbols.whitespace = 'Ξ'

" airline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.linenr = ''
"=============================================================="


set nocompatible
""source $VIMRUNTIME/vimrc_example.vim

"tex settings
" REQUIRED. This makes vim invoke Latex-Suite when you open a tex file.
filetype plugin on

" IMPORTANT: win32 users will need to have 'shellslash' set so that latex
" can be called correctly.
set shellslash

" IMPORTANT: grep will sometimes skip displaying the file name if you
" search in a singe file. This will confuse Latex-Suite. Set your grep
" program to always generate a file-name.
set grepprg=grep\ -nH\ $*




" OPTIONAL: Starting with Vim 7, the filetype of empty .tex files defaults to
" 'plaintex' instead of 'tex', which results in vim-latex not being loaded.
" The following changes the default filetype back to 'tex':

"In addition, the following settings could go in your ~/.vim/ftplugin/tex.vim file:

" TIP: if you write your \label's as \label{fig:something}, then if you
" type in \ref{fig: and press <C-n> you will automatically cycle through
" all the figure labels. Very useful!
"set iskeyword+=: commented out because it is bad in cpp or c

set nobk "??????"
" tab completion setting
set wildmode=longest,list,full
set wildmenu

set diffexpr=MyDiff()
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let eq = ''
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      let cmd = '""' . $VIMRUNTIME . '\diff"'
      let eq = '"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3 . eq
endfunction

"set guifont=Consolas:h14:cANSI
"    set guifont=Courier_New:h12:cANSI:cGB2312
"    set guifont=peep:h16

"set fileencodings=utf-8,chinese,latin-1

filetype indent on  "enables automatic indentation as you type.
set cindent
set tabstop=4 expandtab shiftwidth=4 smarttab softtabstop=0


set t_Co=256 "256 color"
""set t_AB=^[[48;5;%dm
""set t_AF=^[[38;5;%dm
  
""let g:hybrid_custom_term_colors = 1
if has('gui_running')
    "colorscheme railscasts2
    set guifont=Roboto\ Mono\ for\ Powerline\ 14
    "color_scheme fine_blue candycode"
  ""set guioptions-=T  " no toolbar
  ""set lines=50 columns=96 linespace=0
   " colorscheme lucius
   " set bg=light
   " let g:lucius_style="light"
   colorscheme neverland
else
    set bg=dark
    colorscheme hybrid
    ""colorscheme gruvbox 
endif

"colorscheme desertEx darkZ koehler evening

""let g:miniBufExplorerAutoStart = 1
""let g:miniBufExplBuffersNeeded = 2
noremap <TAB>      <C-W>w
 
"compilation related
"map <F5> : call CompileGcc()<CR>
"
"func! CompileGcc()
"exec "!g++ -Wl,-enable-auto-import % -g -o %<.exe"
"endfunc

"make
map <F5> :call Do_make()<CR>
function Do_make()
    set makeprg=make
    execute "silent make"
    execute "copen"
endfunction

" Shortcut to rapidly toggle, use col
"
" Use the same symbols as TextMate for tabstops and EOLs
set listchars=tab:▸\ ,eol:¬

nmap <F11> :SyntasticToggleMode<CR>


" code error checker 
"=========== syntastic =====================================
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:SyntasticToggleMode = 0
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
autocmd VimEnter * SyntasticToggleMode " disable syntastic by default
