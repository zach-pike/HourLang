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
            print(ascii(val));
        }
    }
}

hellow = ">[-]<[-]++++++++[->+++++++++<]>.----[--<+++>]<-.+++++++.><.+++.[-][[-]>[-]+++++++++[<+++++>-]<+...--------------.>++++++++++[<+++++>-]<.+++.-------.>+++++++++[<----->-]<.-.>++++++++[<+++++++>-]<++.-----------.--.-----------.+++++++.----.++++++++++++++.>++++++++++[<----->-]<..[-]++++++++++.[-]+++++++[.,]-]";

brainf(hellow);