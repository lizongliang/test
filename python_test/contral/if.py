#!/usr/bin/python
#Filename:if.py

i = 9
j = 10
n = 11
m = 12

if i == j:
    print "i = j",i,j
elif i > j:
    print "big i is",i
else:
    print "big j is",j


if i < j \
    and n > m:
    print "j is ",j,"n is ",n
elif i < j and n < m:
    print "j is ",j,"m is",m
else:
    print i,j,n,m

print "Done"
