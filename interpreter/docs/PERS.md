## Language Grammar

The following grammar is given in EBNF for the sake of easier understanding.
`*` is used to denote 0 or more instances of the preceding token.
`|` is used to denote or, for example if something can take a literal string OR a variable name as argument, it would be expressed as `string_literal|Identifier`



`testScript: VariableAssignment* RoutineDeclaration* TestDeclaration*`
`RoutineDeclaration: routine string_literal '{' Statement* '}'`
`TestDeclaration: test string_literal '{' Statement* '}'`

```
Statement:
  if ( Exp ) { Statement * }
  | if ( Exp ) { Statement * } else { Statement * }
  | VariableAssignment
  | call string_literal ;
  | loop Exp|forever { Statement* }
  | set-pin DOUT intLiteral|Identifier HIGH|LOW
  | set-pin AOUT intLiteral|Identifier intLiteral|Identifier
  | read-pin AIN|DIN intLiteral|Identifier
  | expect Exp ;
  | assert Exp ;
  | perrint Exp ;
  | print Exp ;
  | println Exp ;
  | perrintln Exp ;
  | send-msg hexLiteral|Identifier Exp ;
  | read-msg hexLiteral|Identifier ;
  | delay Exp ;
  | prompt string_literal ;
  | serial-tx Exp ;
  | serial-rx ;
  | exit ;
  | call string_literal ;
  | exit string_literal ;
  | Exp ++ ;
  | Exp -- ;
```

```
Exp:
  Exp ([+/-*<>])|GT|NE|GE|LE|LT|EQ|>=|<=|!=|==|&&|'||'|and|or Exp
  | Identifier
  | hexLiteral
  | string_literal
  | intLiteral
  | can_msg
  | [+=] Exp
  | ( Exp )

VariableAssignment;
  Identifier = Exp ;
  | Identifier [ Exp ] = Exp ;
  | Identifier . length = Exp ;

```


## Data Types
There are 3 data types supported:
`Integer:` An integer number
`String:` Any sort of string of characters enclosed by `''` or `""`
`CAN_Msg:` A series of integers separated by the `|` symbol. 
    - Example: `can_var = 00|42|69|A4;`
    - Bytes are represented as Hex literals without the preceding `0x` designator

Integers can be used as a form of implicit boolean type, so the following is correct and would function. The convention for boolean evaluation is the same as C/C++ style boolean evaluation based on ints

```
if (1)
{
  perrintln "Wow I'm so cool.";
}
else
{
  perrintln "Wow I wish I were cool. :(";
}

```



## Language Specifications

- logical lines are delimited by semicolons (due to windows using cr-lf)
- Spacing is ignored
- `//` or `#` style comments are allowed
- tests / routines cannot have the same names
- variables can be declared in a global or local scope
- There are only 2 scopes: global and routine/test level
- file extensions will be .pers (purdue electric racing script)
- a syntax checker will check syntax prior to execution 
- variable types need not be declared (i.e. no string, int, float, etc)
- scripts are case sensitive, with commands being lowercase and constants, e.g.  `(HIGH|LOW|DIN|DOUT|AIN|AOUT)` being uppercase
- variables are accessed by simply referencing the variable name e.g. `print varname;`
- The parser is a single pass parser, meaning that all routine declarations must be made prior to the one calling it, similar to C/C++
    - with this, the interpreter does not allow forward declarations / prototyping. It is not intended to be a full featured programming language, and as such having overly complex and interdependent code is discouraged
- tests are not callable from other tests / routines, but routines can be callable from other tests and routines
- string literals can be either "" or ''
- values which come in the form of a buffer (aka an array) will be converted to strings to be stored in the global response object
- overloading any globally defined variables is not allowed. All variable names must be unique
- global variables must be declared at the top of the file
- routines must be declared after global var decls, and before test decls
- CAN message objects have [] and .length operators
  - [] is used to access bytes at the specified index
  - .length is used to specify the DLC for a CAN frame
    - by default this will be assumed to be the number of bytes in the initial declaration


## Explanation of inbuilt functions

  - Routines are equivalent to a test, but have a different name for clarity
  - Routines are meant for performing non-testing operations (i.e. make no calls to EXPECT or ASSERT)
  - They are intended as a setup functionality, such as in the case of simulating part of the car but there is no terminus
  - Routines will NOT be executed by running the interpreter from the command line without explicitly passing the argument to do so





`send-msg`
  - can take up to 8 numbers, which equate to bytes, delimited by '|'
  - The data argument can be a variable, and the address can also be a variable


`read-msg `     
  - Will delay for 1 msec before fetching the most recent messages from a reader thread's cache
  - The information returned by this will be stored in a global static variable


`expect` (LT | GT | GE | LE | NE | EQ) ([0-9]+ | CAN-Msg) 
       ( and (LT | GT | GE | LE | NE | EQ) ([0-9]+ | CAN-Msg))* 
       ( or (LT | GT | GE | LE | NE | EQ) ([0-9]+ | CAN-Msg) )*

  - continue execution even if expectation is not met
  - will print out what the expected value was, and what was actually returned if the values do not match the expectation provided

`assert`  same syntax as expect
  - die if expectation not met 
  - only terminates the running operation i.e. the currently executing test. Will not terminate the interpreter or any subsequent tests
  - to be called after EXPECT
  - utilizes the "expectation" variable which is set by a prior call to EXPECT
    - calling ASSERT TRUE with no prior EXPECTS will result in script termination

`exit` 
  - pretty much just for debugging
  - will halt routine/test execution immediately

`prompt` 
  - this will print a message and block execution until the user continues

`call` 
  - this will only be useable to call routines

`serial-tx` 
  - writes the value specified to the global serial device location

`serial-rx`
  - reads from the global serial device and stores the response in the static
    response variable. Additionally will log to stdout / file output if
    global SERIAL_LOG_FILE is specified 



- a CAN reader thread will be constantly running in the background of the interpreter
- a global return variable will be auto-initialized to 0 at the beginning of every test routine. 
  - This variable will be set by performing a READ-X operation


- RETVAL will be a reserved keyword for the global static result variable
- the interpreter will be invokable by the GUI and from the command line (an additional command line executable will be compiled)


- It is not advised to make a routine call in the middle of test execution if the RETVAL is required for later usage, as this may cause overwriting of the value
- PERScript is spacing inconsiderate, meaning spacing is unimportant, so long as tokens are distinguishable 
- with the exception of RETVAL, all system defined global variables are to remain statically typed (i.e. SERIAL_LOG_FILE will always remain a string)

 
- interpreter will have the following command structure:
  perterpret <scriptname.pers> [(-V, --validate} | (-rt, --run-tests testlist) | (-rr, --run-routines routinelist)]| <-g dest> [-dev device] [-io device] [-v] [-l logfile]
    - `-dev`: generic serial device which serial-rx and serial-tx will send / receive from
    - `-io`: the device to be used as the IO platform (e.g. COM3, /dev/tty4, etc)
    - `-v --verbose`: enables verbose printing. If enabled, all script commands
                  supporting verbose printing will print to stdout
    - `-l --log filename`: specifies the file to log to. defaults to stdout
    - `-t, --test-output filename`: filename of where to put the test output
    - `-g, --generate-sample dest`: generate a sample script and put in in the supplied path. Users can specify the file name by specifying a whole (existing) path and appending the file's name to the path
    - `-V, --validate`: if this switch is passed, the interpreter will not execute. It will instead only perform syntax parsing and type checking. This is useful for checking scripts before actually running them if you don't want to run them.
    - `-T, --run-tests <test list ...>`: this is a list of tests to run if you don't want to run all of them
    - `-R, --run-routines`: This is a list of routines to run if you want to run any of them. Default behavior is to not run any.
      - For -R and -T, the order specified will be the order scripts are run in
    - `-b --baud`: the baud rate to use for the CAN device (only makes an impact on windows. If on Linux, use the `setup_can.sh` script). Defaults to 500kB
    - `--no-gpio`: Passing this switch will disable the requirement for selecting a serial GPIO device. Only use this if your script makes no calls to pin read or write functions. If one of these functions is called with this switch passed, an exception will be thrown and the program will terminate.



- Any devices which are communicating with the basic serial-tx/rx commands will need to send \r\n at the end of their message strings (for whatever reason Qt isn't emptying the buffers so it has to read all the things that it sent already possibly)



Adding Language Features
============================

TODO
https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwi7wem-gr3uAhXQK80KHS4YAzAQFjAFegQIBRAC&url=ftp%3A%2F%2Fftp.wayne.edu%2Fldp%2Fen%2FLex-YACC-HOWTO%2FLex-YACC-HOWTO-single.html&usg=AOvVaw1J-o-TSm9j18GTJWmV_1EI




Example Script
=============================
```
test "this is a test" {
  Var1 = "toast"

  set-pin DOUT 3 HIGH;
  delay 45;
  read-pin DIN 4 ;  // read-x would store return result in some static variable, 
                  // which would then be accessible forever by EXPECT and ASSERT

  VAR = RETVAL    // RESULT will be a reserved keyword for the global static result variable

  expect RETVAL GT 6;  // 
  prompt "Yo momma so fat that the tide comes in when she goes to the beach";

  loop 4 {
    perrint "OHHHHHH YOU JUST GOT REKT SON";
  }
}
```







Arduino Serial communication protocol
=====================================================

`GPIO_MAX` = max number of gpio pins on the Arduino

`DAC_MAX` = max number of pins on the i2c DAC breakout boards

`READ <TYPE> [PIN];`

  * `TYPE`: `ADC` | `GPIO`

    * `ADC`: This is not a readable value for the moment, as we don’t have any analog values being generated

    * `GPIO`: This is a simple GPIO read of the digital pins

  *   `PIN`: up to GPIO_MAX

  Upon receiving a `READ` request, the Arduino will reply with `<VALUE>';'`

`WRITE <TYPE> [PIN <VALUE>];`

  * `TYPE`: `DAC` | `GPIO`

    * `DAC`: Calls to the I2C DAC interface and writes <VALUE> to the DAC pin
    * `GPIO`: This is a simple GPIO write of the digital pins
  * `PIN`: up to DAC_MAX
  * `PIN`: up to GPIO_MA


Compiling
===

### Building on Windows
1. Install Qt Creator open source (Make sure to install Qt 5.15, not Qt 6. This code is untested on Qt 6 since it was only release a few months prior to the rollout of this system.)
2. Add `C:\Qt\Tools\mingw810_64\bin` to your path
3. Add `C:\Qt\5.15.2\mingw81_64\bin` to your path
4. Open the project in QtCreator and click on the hammer button to build it.

