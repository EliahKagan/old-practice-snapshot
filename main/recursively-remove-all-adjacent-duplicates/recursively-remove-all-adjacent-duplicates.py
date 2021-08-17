import re

pattern = re.compile(r'(.)\1+')

for t in xrange(int(raw_input())):
    text = raw_input().strip()
    length = len(text)
    
    while True:
        text = pattern.sub('', text)
        
        if length == len(text):
            break
        
        length = len(text)
    
    print text
