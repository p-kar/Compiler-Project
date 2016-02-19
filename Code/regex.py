import re

def f7(seq):
    seen = set()
    seen_add = seen.add
    return [x for x in seq if not (x in seen or seen_add(x))]

file_name = './orig_grammar.txt'
with open (file_name, "r") as myfile:
    data = myfile.read()
searchobj = re.findall('<[a-z|A-Z]+>', data)
ans = f7(searchobj)
for s in ans:
    print s[1:-1].upper()