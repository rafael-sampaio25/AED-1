class node:
    def __init__(self, value = None): # START
        self.value = value
        self.leftChild = None
        self.rightChild = None

class binarySearchTree:
    def __init__(self): # START
        self.root = None

    def insert(self, value):
        if self.root == None:
            self.root = node(value) # FIRST NODE
        else:
            self._insert(value, self.root)

    def _insert(self, value, currentNode):
        if value < currentNode.value: # Smaller values to the left
            if currentNode.leftChild == None:
                currentNode.leftChild = node(value)
            else:
                self._insert(value, currentNode.leftChild)
        elif value > currentNode.value: # Greater values to the right
            if currentNode.rightChild == None:
                currentNode.rightChild = node(value)
            else:
                self._insert(value, currentNode.rightChild)
        else: # Cannot have equal values in tree
            print ("Value already in tree!")

    def printTree(self):
        if self.root != None: # My tree have values
            self._printTree(self.root)

    def _printTree(self, currentNode):
        if currentNode != None:
            self._printTree(currentNode.leftChild) # Recursivity
            print (str(currentNode.value))
            self._printTree(currentNode.rightChild) # Recursivity

    def height(self):
        if self.root != None:
            return self._height(self.root, 0) # Empty
        else:
            return 0

    def _height(self, currentNode, currentHeight):
        if currentNode == None: return currentHeight
        leftHeight = self._height(currentNode.leftChild, currentHeight + 1)
        rightHeight = self._height(currentNode.rightChild, currentHeight + 1)
        return max(leftHeight, rightHeight)

    def search(self, value):
        if self.root != None:
            return self._search(value, self.root)
        else:
            return False

    def _search(self, value, currentNode):
        if value == currentNode.value:
            return True
        elif value < currentNode.value and currentNode.leftChild != None:
            return self._search(value, currentNode.leftChild)
        elif value > currentNode.value and currentNode.rightChild != None:
            return self._search(value, currentNode.rightChild)
        return False

def fillTree(tree, nElements = 10, maxInt = 20):
    from random import randint
    for _ in range(nElements):
        currentElement = randint(0, maxInt)
        tree.insert(currentElement)
    return tree


tree = binarySearchTree()
tree = fillTree(tree)

tree.printTree()

print (f'Tree root: {tree.root.value}')
print (f"Tree Height: {tree.height()}")
aux = int(input("Type a value you want to search in tree: "))
if tree.search(aux):
    print(f'I found {aux}!')
else: print(f'I do not found {aux}.')
