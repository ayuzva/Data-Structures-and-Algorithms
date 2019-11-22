# python3

import sys, threading
sys.setrecursionlimit(10**6) # max depth of recursion
threading.stack_size(2**27)  # new thread will get stack of such size

#__init(self)__ if anything

class TreeOrders:
  def __init__(self):
    self.stack = []

  def read(self):
    self.n = int(sys.stdin.readline()) #number of vertices
    self.key = [0 for i in range(self.n)]
    self.left = [0 for i in range(self.n)]
    self.right = [0 for i in range(self.n)]
    for i in range(self.n):
      [a, b, c] = map(int, sys.stdin.readline().split())#capturing ket left and right
      self.key[i] = a
      self.left[i] = b
      self.right[i] = c

  def inOrder(self):
    self.result = []#list of keyes in order
    # Finish the implementation
    # You may need to add a new recursive method to do that
    self.DFSinOrder(0)
    return self.result

  def DFSinOrder(self,j):
    if j == -1:
      return
    if self.left[j] == -1 and self.right[j] == -1:
      self.result.append(self.key[j])
      return
    self.DFSinOrder(self.left[j])
    self.result.append(self.key[j])
    self.DFSinOrder(self.right[j])
    return

  def preOrder(self):
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that
    self.DFSpreOrder(0)
    return self.result

  def DFSpreOrder(self,j):
    if j == -1:
      return
    if self.left[j] == -1 and self.right[j] == -1:
      self.result.append(self.key[j])
      return
    self.result.append(self.key[j])
    self.DFSpreOrder(self.left[j])
    self.DFSpreOrder(self.right[j])
    return

  def postOrder(self):
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that
    self.DFSpostOrder(0)    
    return self.result

  def DFSpostOrder(self,j):
    if j == -1:
      return
    if self.left[j] == -1 and self.right[j] == -1:
      self.result.append(self.key[j])
      return
    self.DFSpostOrder(self.left[j])
    self.DFSpostOrder(self.right[j])
    self.result.append(self.key[j])
    return


def main():
	tree = TreeOrders()
	tree.read()
	print(" ".join(str(x) for x in tree.inOrder()))
	print(" ".join(str(x) for x in tree.preOrder()))
	print(" ".join(str(x) for x in tree.postOrder()))

threading.Thread(target=main).start()
