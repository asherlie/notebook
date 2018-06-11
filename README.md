# notebook
anything written in the lines between the #if 0 and #endif in notebook.c will be pretty printed

if notebook.c has been edited without being recompiled, this program will refuse to print anything

lines will be padded with the first character of the first argument passed. if no argument is passed, whitespace will be used

## usage:
to print notes with '/' as padding and fill all whitespace with padding character
`./nb / -fa`

`./nb -fa` will print notes with '-' as padding and fill all whitespace with padding character
