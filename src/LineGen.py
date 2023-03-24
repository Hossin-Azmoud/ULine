from string import ascii_letters as ascii_
from random import randint
from sys import argv

argv       = argv[1:]
argc       = len(argv)
NL         = '\n'
FILE       = './OUT/test.txt'

print("LineGen.py <LineSize> <LineCount>")
if argc > 0:  LINE_SIZE  = int(argv[0])
else:         LINE_SIZE  = 100

if argc > 1:  LINE_COUNT = int(argv[1])
else:         LINE_COUNT = 50


#-----------LOOOPS-----------#

def main():
    print("/")
    print(f"Generating w: { LINE_SIZE }, h: { LINE_COUNT }")
    with open(FILE, 'w+') as f:
        for i in range(LINE_COUNT * LINE_SIZE):
            if i % LINE_SIZE == 0:
                f.write(NL)
            else:
                i = randint(0, len(ascii_) - 1)
                f.write(ascii_[i])

if __name__ == "__main__": main()
