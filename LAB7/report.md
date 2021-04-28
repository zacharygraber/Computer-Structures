# Lab 7 Report

### Phase 1
------------------------
<ol>
<li>**Solution**: "Wow! Brazil is big."</li>
<li>**How I solved**: I opened the file in radare2, listed all functions with `afl`, and saw that there was a `sym.phase_1`. I seeked to it with `s main`, then went into visual mode with `Vpp`. It was then that I saw a big, fat, red string next to the `lea` instruction right before a `call sym.strings_not_equal` then soon after a jump to `call sym.explode_bomb`. I figured that making the strings match would skip the `jne` and it did.</li> 
