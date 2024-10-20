AUTOSTART

// 64 x 128 display shows 8 lines of 20 characters per line.
// 17 characters per line are visible through the Engine House window.

#if 1

//                     1         2
//            12345678901234567890
SCREEN(0, 0, "ABCDEFGHIJKLMNOPQRST")
SCREEN(0, 1, "UVWXYZ              ")
SCREEN(0, 2, "abcdefghijklmnopqrst")
SCREEN(0, 3, "uvwxyz              ")
SCREEN(0, 4, "0123456789          ")
SCREEN(0, 5, "!\"#$%&'()*+,-./     ")
SCREEN(0, 6, ":;<=>?@[\\]^_{|}\x7e\x7f   ")
SCREEN(0, 7, "|__________________|")

#elif 0

SCREEN(0, 0, "")
SCREEN(0, 1, "")
SCREEN(0, 2, "")
SCREEN(0, 3, "")
SCREEN(0, 4, "")
SCREEN(0, 5, "")
SCREEN(0, 6, "")
SCREEN(0, 7, "")

DELAY(1000)

// Demonstrate weirdness if a line is "cleared" by writing an empty string to
// it. Note in the following five SCREEN calls that lines 0, 1, and 2 are as
// expected, but line 4 moves up to line 3 and line 6 moves up to line 4. The
// space on line 1 is necessary to keep line 2 from moving up:
//   +--------
// 0 | A
// 1 |
// 2 | B
// 3 | C
// 4 | D
// 5 |
// 6 |
// 7 |
//   +--------
SCREEN(0, 0, "A")
SCREEN(0, 1, " ")
SCREEN(0, 2, "B")
SCREEN(0, 4, "C")
SCREEN(0, 6, "D")

#else

// Entire screen white
//                                                 1                                       2
//             1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0
SCREEN(0, 0, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 1, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 2, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 3, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 4, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 5, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 6, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")
SCREEN(0, 7, "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB")

#endif

DONE
