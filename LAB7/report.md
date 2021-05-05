# Lab 7 Report

### Phase 1
------------------------
**Solution**: `Wow! Brazil is big.`

**How I solved**: I opened the file in radare2, listed all functions with `afl`, and saw that there was a `sym.phase_1`. I seeked to it with `s main`, then went into visual mode with `Vpp`. It was then that I saw a big, fat, red string next to the `lea` instruction right before a `call sym.strings_not_equal` then soon after a jump to `call sym.explode_bomb`. I figured that making the strings match would skip the `jne` and it did.


### Phase 2
------------------------
**Solution**: `2 3 5 9 17 33`

**How I solved**: This one was pretty much just given away in the LAB7 video on Canvas.


### Phase 3
------------------------
**Solution**: `E"Ojuzldef`

**How I solved**: Looking at the assembly for the phase 3 function, the first thing I noticed was the `call sym.string_length`. I poked around with that for a bit and assumed that it checks the length of the string; since there's a comparison to `eax` directly after, I figured that it saves the length in eax. I noticed that a way to avoid the first `call sym.explode_bomb` is to jump if `eax == 0xa`, so I came to the conclusion that my solution must be 10 characters long. I spent quite a while inspecting the values of different things and eventually noticed a loop with the condition `ebx > eax` (with `eax` clearly just being an accumulator that increments by 1 every loop); I found that `ebx` was 10, giving me: 
```c
for (int i = 0; i < 10; i++) {
  ...
}
```
I then went over the condition for the bomb being triggered down here, and found out that the `call` is skipped if and only if `esi == 1` at the end of the loop. `esi` starts as `1` and `edi` starts as `0`, but in the loop a mistake will cause `esi` to be overwritten to `edi`'s value, so 0, meaning that the bomb will explode. The "mistake" happens when `ecx != edx`. I now knew:
```c
for (int i = 0; i < 10; i++) {
  if (ecx != edx)
    esi = 0;
}
if (esi != 1)
  // Explode bomb!
```

At this point it just became a matter of figuring out what `ecx` and `edx` were. After playing around testing the values of everything, I found a few things: `r9` was the string "B.Disraeli" and `rbp` was my input. Given that I had a loop looping 10 times and I knew my input needed to be 10 characters, I figured that each iteration was checking one character at a time. Since I knew that I need `ecx == edx`, and I knew that `ecx` was just the byte in r9 offset by the index, I knew that for character `i` I needed to have `"B.Disraeli"[i] = edx`. Making similar deductions I eventually found the answer: `i'th char of r9 = (i'th char of rbp)⊕(i*4'th byte of r8)`; I knew from probing with `px 64 @ ...` the values of `r9` and `r8`, so I just needed to solve for the char in `rbp` at each value of `i`. I converted everything to binary and solved:
```
  ???????? ???????? ???????? ???????? ???????? ???????? ???????? ???????? ???????? ????????    <--- (The solution)
  00000111 00001100 00001011 00000011 00000110 00001000 00001101 00000001 00001001 00001111 ⊕  <--- (Corresponding bytes of r8)
  -----------------------------------------------------------------------------------------
  01000010 00101110 01000100 01101001 01110011 01110010 01100001 01100101 01101100 01101001     <--- ("B.Disraeli")
```
The resulting binary converted to ASCII text is `E"Ojuzldef`.

### Phase 4
------------------------
**Solution**: `5 -465`

**How I solved**: I noticed three calls to `sym.explode_bomb` that I wanted to avoid. In order to avoid the first one, I saw that I would need to **not** satisfy `eax <= 1`. This comparison was right after a call to `sscanf`, so my guess was that `eax` was the return value of `sscanf`, which is the number of fields converted. I tried with a couple of inputs, and found that when giving a single non-number string (e.g. "ABCD") `eax` was 0, and if I gave a number (e.g. 10) `eax` was 1. That told me that the function was looking for at least 2 numbers. 

After learning that, the what the inputs actually *were* fell into place. I saw that the next call to explode the bomb happened if a "jump if above" was triggered. In order to avoid that, I needed to avoid the condition that `dword[var_ch] > 7`. I wasn't sure what `dword[var_ch]` was, but I just guessed that the first number needed to be less than 7, and that worked.

For the second input, I put in a random number and stepped forward all the way up until the last explosion call. I saw that I needed `eax == dword[rsp + 8]` in order to avoid the call. I dumped the value at `rsp + 8` and noticed that it was my second input. Then, I found that `eax` was `0xfffffe2f`. Because of all the leading `f`s (1s in binary), I was suspicious that this was a two's complement number. The corresponding number was -465. I tried that for my second input and it worked.
