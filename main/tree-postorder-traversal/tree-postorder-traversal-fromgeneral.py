class Node:
    def __init__(self, info):
        self.info = info
        self.left = None
        self.right = None
        self.level = None

    def __str__(self):
        return str(self.info)

class BinarySearchTree:
    def __init__(self):
        self.root = None

    def create(self, val):
        if self.root == None:
            self.root = Node(val)
        else:
            current = self.root

            while True:
                if val < current.info:
                    if current.left:
                        current = current.left
                    else:
                        current.left = Node(val)
                        break
                elif val > current.info:
                    if current.right:
                        current = current.right
                    else:
                        current.right = Node(val)
                        break
                else:
                    break

def dfs(root, f_pre, f_in, f_post):
    post = None
    stack = []

    while root or stack:
        # Traverse left as far as possible, doing the preorder task.
        while root:
            f_pre(root.info)
            stack.append(root)
            root = root.left

        cur = stack[-1]

        if cur.right is None or cur.right is not post:
            # The right subtree is not yet visited. Do the inorder task.
            f_in(cur.info)

        if cur.right is None or cur.right is post:
            # The right subtree is explored. Do the postorder task and retreat.
            post = cur
            f_post(post.info)
            del stack[-1]
        else:
            # The right subtree is nonempty and unexplored. Go there next.
            root = cur.right

def noop(_info):
    pass

def display(info):
    print(info, end=' ')

def preOrder(root):
    dfs(root, display, noop, noop)

def inOrder(root):
    dfs(root, noop, display, noop)

def postOrder(root):
    dfs(root, noop, noop, display)


tree = BinarySearchTree()
t = int(input())

arr = list(map(int, input().split()))

for i in range(t):
    tree.create(arr[i])

postOrder(tree.root)
