#!/usr/bin/python
#Filename:if.py
#while ... else...

number = 23
running = True

while running:
    guess = int(raw_input("Enter an integer: "))

    if guess == number:
        print"Congratulations,u guessed it."
        running = False
    elif guess < number:
        print"it is little higher than that."
    else:
        print"it is little lower than that."

else:
    print"The while loop is over"
print "Done"
