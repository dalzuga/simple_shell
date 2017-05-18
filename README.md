# Simple Shell

A simple UNIX shell written in C.

# Compile

To compile, run `make`. Alternatively, use the full compilation command:

```
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

# Running

To run, use `./shell` in the same way you would use `bash`.

## Example:

```
daniel@ubuntu:~/simple_shell$ ./shell
($) ls
shell
($) ls -alh
total 24K
drwxrwxr-x  2 daniel daniel 4.0K May 17 16:57 .
drwxr-xr-x 22 daniel daniel 4.0K May 17 16:57 ..
-rwxrwxr-x  1 daniel daniel  14K May 17 16:57 shell
($)
```