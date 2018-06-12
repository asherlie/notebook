# notebook
## usage:
anything written in the lines between the #if 0 and #endif in notebook.c will be pretty printed

if notebook.c has been edited without being recompiled, this program will refuse to print anything


there are two available flags:

#### -fa:
fill all
* ALL whitespace will be filled by the filler character
* if -fa is enabled, -fl will do nothing

#### -fl:
* leading whitespace will be filled by the filler character

the filler character is the first character of the first argument passed. if no argument is passed, the filler character is ' '

## examples:
to print notes with '/' as padding and fill all whitespace with padding character
`./nb / -fa`

`./nb -fl` will print notes with '-' as the fill char, filling leading and trailing whitespace on each line, but not filling space between words
