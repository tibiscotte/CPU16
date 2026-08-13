#!/usr/bin/env python3

import sys

if len(sys.argv) < 3:
    print("Usage: TheAsm <input_file> <output_file>")
    sys.exit(1)

path = sys.argv[1]
output = sys.argv[2]

regs = [
    "a",
    "b",
    "c",
    "d",
    "w",
    "x",
    "y",
    "z",
    "sp",
    "bp",
    "ip",
    "fl"
]

OPCODES_CONFIG = {
    "hlt":   (0x00, 0),
    "mov":   (0x01, 2),
    "add":   (0x02, 2),
    "sub":   (0x03, 2),
    "xor":   (0x04, 2),
    "or":    (0x05, 2),
    "inc":   (0x06, 1),
    "dec":   (0x07, 1),
    "jmp":   (0x08, 1),
    "jie":   (0x09, 1),
    "jig":   (0x0A, 1),
    "jil":   (0x0B, 1),
    "jeg":   (0x0C, 1),
    "jel":   (0x0D, 1),
    "jne":   (0x0E, 1),
    "cmp":   (0x0F, 2),
    "call":  (0x10, 1),
    "ret":   (0x11, 0),
    "push":  (0x12, 1),
    "pop":   (0x13, 1),
    "ldram": (0x14, 2),
    "ldvrm": (0x15, 2),
    "int":   (0x16, 1),
    "mul":   (0x17, 2)
}

TYPES = {
    "reg": 0x00,
    "val": 0x01,
    "adr": 0x02,
    "ptr": 0x03
}

JUMP_INSTRUCTIONS = {
    "jmp",
    "jie",
    "jig",
    "jil",
    "jeg",
    "jel",
    "jne",
    "call"
}

MODE_ENDIAN = "big"

labels = {}


def get_type(type_name):
    return TYPES.get(type_name.lower())


def encode_value(value):
    return (value & 0xFFFF).to_bytes(
        2,
        byteorder=MODE_ENDIAN
    )


def encode_argument(argument, argument_type, labels):
    argument = argument.lower()

    if argument_type == 0x00:
        if argument not in regs:
            raise ValueError(
                f"Registre inconnu '{argument}'"
            )
        return regs.index(argument)

    if argument_type == 0x03:
        if argument not in regs:
            raise ValueError(
                f"Registre inconnu '{argument}'"
            )
        return regs.index(argument)

    if argument.startswith("."):
        if argument not in labels:
            raise ValueError(
                f"Label inconnu '{argument}'"
            )
        return labels[argument]

    return int(argument, 0)


rom_address = 0

with open(path, "r") as file:
    for line_num, line in enumerate(file, 1):
        line = line.split("#")[0].strip()

        if not line:
            continue

        tokens = line.replace(",", " ").split()

        if not tokens:
            continue

        first = tokens[0].lower()

        if first.startswith("."):
            label = first.rstrip(":")

            if label in labels:
                print(
                    f"Erreur Ligne {line_num} : "
                    f"Label déjà défini '{label}'"
                )
                sys.exit(1)

            labels[label] = rom_address
            continue

        instr = first

        if instr not in OPCODES_CONFIG:
            print(
                f"Erreur Ligne {line_num} : "
                f"Instruction inconnue '{instr}'"
            )
            sys.exit(1)

        opcode, nb_args = OPCODES_CONFIG[instr]

        rom_address += 2 + (nb_args * 2)


print("Labels :")

for label, address in labels.items():
    print(
        f"  {label} = 0x{address:04X}"
    )


content = bytearray()

with open(path, "r") as file:
    for line_num, line in enumerate(file, 1):
        line = line.split("#")[0].strip()

        if not line:
            continue

        tokens = line.replace(",", " ").split()

        if not tokens:
            continue

        instr = tokens[0].lower()

        if instr.startswith("."):
            continue

        if instr not in OPCODES_CONFIG:
            print(
                f"Erreur Ligne {line_num} : "
                f"Instruction inconnue '{instr}'"
            )
            sys.exit(1)

        opcode, nb_args = OPCODES_CONFIG[instr]

        if instr in JUMP_INSTRUCTIONS:
            if len(tokens) == 2 and tokens[1].startswith("."):
                argument = tokens[1].lower()

                try:
                    address = encode_argument(
                        argument,
                        0x01,
                        labels
                    )
                except ValueError as error:
                    print(
                        f"Erreur Ligne {line_num} : "
                        f"{error}"
                    )
                    sys.exit(1)

                content.append(opcode)
                content.append(0x10)
                content.extend(
                    encode_value(address)
                )

                continue

        content.append(opcode)

        if nb_args == 0:
            content.append(0x00)
            continue

        if len(tokens) > 1:
            type1_name = tokens[1].lower()
        else:
            type1_name = ""

        type1 = get_type(type1_name)

        if type1 is None:
            print(
                f"Erreur Ligne {line_num} : "
                f"Type d'argument invalide "
                f"'{type1_name}'"
            )
            sys.exit(1)

        if nb_args == 2:
            if len(tokens) > 2:
                type2_name = tokens[2].lower()
            else:
                type2_name = ""

            type2 = get_type(type2_name)

            if type2 is None:
                print(
                    f"Erreur Ligne {line_num} : "
                    f"Type d'argument invalide "
                    f"'{type2_name}'"
                )
                sys.exit(1)
        else:
            type2 = 0x00

        type_byte = (type1 << 4) | type2
        content.append(type_byte)

        if nb_args == 2:
            argument1_index = 3
        else:
            argument1_index = 2

        try:
            argument1 = tokens[argument1_index]

            value1 = encode_argument(
                argument1,
                type1,
                labels
            )

            content.extend(
                encode_value(value1)
            )

        except IndexError:
            print(
                f"Erreur Ligne {line_num} : "
                f"Argument 1 manquant"
            )
            sys.exit(1)

        except ValueError as error:
            print(
                f"Erreur Ligne {line_num} : "
                f"{error}"
            )
            sys.exit(1)

        if nb_args == 2:
            try:
                argument2 = tokens[4]

                value2 = encode_argument(
                    argument2,
                    type2,
                    labels
                )

                content.extend(
                    encode_value(value2)
                )

            except IndexError:
                print(
                    f"Erreur Ligne {line_num} : "
                    f"Argument 2 manquant"
                )
                sys.exit(1)

            except ValueError as error:
                print(
                    f"Erreur Ligne {line_num} : "
                    f"{error}"
                )
                sys.exit(1)


with open(output, "wb") as out_file:
    out_file.write(content)

print(
    f"Compilation réussie : "
    f"{len(content)} octets générés dans '{output}'."
)