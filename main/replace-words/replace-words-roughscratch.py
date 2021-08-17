WORD_MARK = None

def build_trie(words):
    trie = {}
    
    for word in words:
        node = trie
        
        for ch in word:
            try:
                node = node[ch]
            except KeyError:
                child = {}
                node[ch] = child
                node = child
                
        node[WORD_MARK] = None
    
    return trie
