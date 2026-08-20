# CPU16

```text
int val 0 = reset
int val 1 = update bus.vram
int val 2 = copy ram into gpu vram
int val 3 = get key (wait for key) (a is the key)
int val 4 = is key pressed (a is the bool and b the key)
int val 5 = read a byte in a sector (a is the sector and b the address of the byte)
int val 6 = same as last for write but c is the value
int val 7 = load the file for the next sector (a is the id of the file)
int val 8 = put the file in the sector (a is the sector)
int val 9 = go to a sector (a is also the sector)
int val 10 = write a char of mvac (My Version of the ASCII Code, a is the char)
int val 11 = set the cursor pos (c is the pos)
int val 12 = reset the vram

MVAC:
0 -> 25 = "a" -> "z"
26 -> 35 = "1" -> "0"
36 = ","
37 = "."
38 = " "
39 = "/"
40 = "["
41 = "]"
42 = "\"
43 = "bcksp"
44 = "lgui"
45 = "rtrn"
46 = "_"
47 = "-"
48 = "<"
49 = ">"
50 = 
51 = 
52 = 
53 = 
54 = 
55 = 
56 = 
57 = 
58 = 
59 = 
60 = 
61 = 
62 = 
63 = 
64 = 

instruction list:
hlt, no args, stop the program
mov, 2 args, mov in a register a value or a register
add, 2 args, add a register with a value or a register
sub, 2 args, sub a register with a value or a register
xor, 2 args, xor a register with a value or a register
or, 2 args, or a register with a value or a register
inc, 1 arg, inc a register
dec, 1 arg, dec a register
jmp, 1 arg, set the value of the instruction pointer (you can also use a label .name)
jie, 1 arg, jump if equal
jig, 1 arg, jump if greater
jil, 1 arg, jump if less
jeg, 1 arg, jump if equal or greater
jel, 1 arg, jump if equal or less
cmp, 2 args, compare two values ​​or registers
call, 1 arg, jump and store the current IP address in the push list
ret, no args, return to the last value stored in pop
push, 1 arg, push a register or a value in the push list
pop, 1 arg, store in a register last value stored in push list
ldram, 2 args, store a value in an ram address or store in a register a value of the ram
ldvrm, 2 args, store a value in an vram address
int, 1 arg, execute an interruption
mul, 2 args, mul a register with a value or a register

args types list:
val = int value (0, 1, 2, 3, 4, ..., 65535)
reg = register name (a, b, c, d, w, x, y, z)
ptr = use a register like an address
adr = addresses for ldram ans ldvrm

how to compile:
TheAsm <your_input_file.theasm> <your_output_file.the>

how to run:
./cpu16 <bool debug ("t" or "f")> <boot_file.the> (<- optional if you already dejine the boot code)
```