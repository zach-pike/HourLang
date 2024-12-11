map = array(
    " ",
    "!",
    "'",
    "#",
    "$",
    "%",
    "&",
    "'",
    "(",
    ")",
    "*",
    "+",
    "`",
    "-",
    ".",
    "/",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    ":",
    ";",
    "<",
    "=",
    ">",
    "?",
    "@",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "[",
    "/",
    "]",
    "^",
    "_",
    "`",
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
    "{",
    "|",
    "}",
    "~"
);

function brainf(code) {
    memory = [];
    memptr = 0;

    stack = [];

    for(i = 0; i<100; i += 1;) {
        memory = append(memory, 0);
    }

    for (i = 0; i<size(code); i += 1;) {
        c = get(code, i);

        if (c == ">") {
            memptr += 1;
        } else if (c == "<") {
            memptr -= 1;
        } else if (c == "[") {
            val = get(memory, memptr);

            if (val) {
                stack = append(stack, i);
            } else {
                bc = 1;
                k = 0;
                
                for (k=i+1; bc > 0; k += 1;) {
                    if (get(code, k) == "[") {
                        bc += 1;
                    } else if (get(code, k) == "]") {
                        bc -= 1;
                    }
                }

                i = k - 1;
            }

        } else if (c == "]") {
            val = get(memory, memptr);

            if (val) {
                i = get(stack, size(stack) - 1);
            } else {
                stack = pop(stack);
            }
        } else if (c == "+") {
            val = get(memory, memptr);
            memory = set(memory, memptr, val + 1);
        } else if (c == "-") {
            val = get(memory, memptr);
            memory = set(memory, memptr, val - 1);
        } else if (c == ".") {
            val = get(memory, memptr);
            print(get(map, val - 32));
        }
    }
}

hellow = ">[-]<[-]++++++++[->+++++++++<]>.----[--<+++>]<-.+++++++.><.+++.[-][[-]>[-]+++++++++[<+++++>-]<+...--------------.>++++++++++[<+++++>-]<.+++.-------.>+++++++++[<----->-]<.-.>++++++++[<+++++++>-]<++.-----------.--.-----------.+++++++.----.++++++++++++++.>++++++++++[<----->-]<..[-]++++++++++.[-]+++++++[.,]-]";

brainf(hellow);