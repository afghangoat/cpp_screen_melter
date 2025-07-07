# C++ screen melter

This is a simple screen melter for windows 10 using the win api.

A screen melter shifts each column of you screen down slowly, achieving a "melting" effect.

## Disclaimer

While this program itself is not malicious, it can be *really* annoying. Please don't start this on someone else's computer without consent.

## Usage

Run:
`g++ -o main.exe main.cpp -lgdi32 -luser32 -D_UNICODE -DUNICODE flags`
`main.exe`

For stopping, press `Alt+F4`