# S9-RFID-ISO15693-Python
Python library for YiQing/Fongwah S9
![S9-01](https://user-images.githubusercontent.com/8759458/220318857-a2faf4f5-200c-4147-a048-e9c209086840.jpg)

I needed to read and write to a ISO15693 RFID chip and bought this reader/writer off amazon: https://www.amazon.de/dp/B07MZ47R8Z/

It came with an SDK with lots of code examples, but none for python, so i came up with these 2 scripts for reading and writing to the card.
Depending on the RFID chip you are reading/writing to, you may have a different block size, mine had 4 bytes per block.

Only tested on windows via import of dll for now but the SDK also comes with precompiled .so files for linux, and i'm guessing the functions are similar.

