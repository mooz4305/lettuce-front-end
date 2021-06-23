# lettuce-front-end
A C++ front end for the Lettuce language (aka a "sugared-up" version of lambda calculus). 

### About the language
The Lettuce language is from the PL course at University of Colorado Boulder, though the untyped version of Lettuce with immutable variables is assumed here.
These are some elements of the language:
- literals: constants, `True `, `False`,
- binary and unary operators: `+`, `-`, `&`, `|`, and more,
- variable identifiers,
- variable assignment and scope: `let ___ be ___ in ___`,
- conditional branches:  `if ___ then ___ else ___`,
- function definitions, e.g. `function (x) x + 2`,
- function calls, e.g. `f(3)`.

### Using the Front End
The program converts raw text into a Lettuce expression (stored/represented as an abstract syntax tree). After compiling, use
- `./lfe -f <file_name>` to convert a file's text into an expression,
- `./lfe` to use console mode, to repeatedly enter text to convert into an expression.
 
### Things Learned
- how to make a front-end for a language, using C++,
  - tokenizing raw text into literals, keywords, and other syntactic elements of the language,
  - parsing tokens into expressions, reprsented by an abstract syntax tree (AST),
- applying the `unique_ptr<>` type (and the `memory` library) for memory management of the AST,
- utilizing Visual Studio for C++ development.

### Possible Directions
- improve language features:
  - add unary operators,
  - add a recursive function keyword and expression,
  - add types,
  - add mutable variables,
- improve front-end features:
  - throw and catch parsing errors instead of exiting program, 
  - implement type checker,
- build a back-end using LLVM Core libraries, so Lettuce can be compiled to machine-code.
