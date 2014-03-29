#!/usr/bin/python
#filename list.py
#run list.py

#list: [] dictionayr: {}

li = ["lee","boy","28"]
print "li is ",li

print "li[0] is  ",li[0]
print "li[2] is  ",li[2]
print "li[-1] is ",li[-1]
print "li[-2] is ",li[-2]
print "li[0:2] is",li[0:2]
print "li[:1] is ",li[:1]
print "li[1:] is ",li[1:]
print "li[:] is  ",li[:]

li.append("gl")
print "li is",li

li.insert(1,"zongliang")
print "li is",li

li.extend([1,2,3])
print "li is",li
print "li[6] is",li[6]

print "boy is ",li.index("boy")
print "b in li ","b" in li

li.remove("gl")
print "li is",li

print "pop is ",li.pop()
print "li is",li

li +=  ["gl"]
print "li is",li
