#!/usr/bin/python
#Filename:if.py

number = 23
guess = int(raw_input("Enter an integer: "))

if guess == number:
    print"Congratulations,u guessed it."
elif guess < number:
    print"it is little higher than that."
else:
    print"it is little lower than that."

print "Done"
