PATH_COMPONENT_PATTERN = re.compile(r'[^/]+')

TRIE_CHAIN_TERMINATOR = None

def _trie():
    return collections.defaultdict(_trie)

def build_trie(paths):
    root = _trie()

    for path in paths:
        node = root
        for chain_link in PATH_COMPONENT_PATTERN.findall(path):
            node = node[chain_link]
        node[TRIE_CHAIN_TERMINATOR] = path

    return root

def stored_prefixes(root):
    prefixes = []
    
    def dfs(node):
        path = node.get(TRIE_CHAIN_TERMINATOR)

        if path is None:
            for child in node.values():
                dfs(child)
        else:
            prefixes.append(path)

    dfs(root)
    return prefixes

class Solution:
    def removeSubfolders(self, folder_paths: List[str]) -> List[str]:
        return stored_prefixes(build_trie(folder_paths))
