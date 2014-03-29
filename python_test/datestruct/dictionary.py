#!/usr/bin/python
#filename dictionary.py
#run python dictionary.py

d = {"name":"lee","sex":"boy","age":"28"}
print d

print d["age"]

d["age"] = 27
print d["age"]

d["company"] = "gl"
print d

d[1] = 1
print d

del d[1]
print d

d.clear()
print d
