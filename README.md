# What is 21sh
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](http://forthebadge.com/images/badges/built-with-love.svg)](http://forthebadge.com)

21sh is a bash-styled shell project completely written from scratch in C with very limited access to libraries and tools.

# The learning goals of the project:
- Learn a lot more about the inner workings of the UNIX system.
- Learn about the different type of shell implementations.
- Learn what a lexer is and how to write it.
- Learn what a parser is and how to write it.
- Learn how to write nice and clean code.
- To create a stable and complete UNIX shell.

# Functionality
1. Error monitoring without using `errno`.
2. Prompt display.
3. Complete management of input.
4. (Multiline) line edition.
5. Redirection with the following operators:
   * `>`
   * `>>`
   * `<`
   * `<<`
   * `>&`
   * `<&`
7. Control operators:
   * `|`
   * `||`
   * `&&`
   * `;`
8. Quoting managment `"`, `'`, and `\`.
9. Basic parameter expansion.
10. Command history
11. Autocomplete
12. Builtins:
   *  `echo`
   *  `cd`
   *  `env`
   *  `setenv`
   *  `unsetenv`
   *  `exit`
   * `type`
# Installing and running 21sh
Install:
```
make && make clean
```

Run:
```
./21sh
```
# Authors
[Volkov Ilya][https://github.com/volkov7]
[Alex Buyanov][https://github.com/SoliddSnake]
