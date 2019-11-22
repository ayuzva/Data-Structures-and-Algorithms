#!/usr/bin/python3

import sys, threading

sys.setrecursionlimit(10**7) # max depth of recursion
threading.stack_size(2**30)  # new thread will get stack of such size

def IsBinarySearchTree(tree):
  # Implement correct algorithm here
  if len(tree) == 1 or len(tree) == 0: #filters out 1 node and 0 node trees
    return True
  else:
    return DFSinOrder(tree,0,-1*((2**31)+1),(2**31)+1)

def DFSinOrder(tree,j,liml,limr):#j is the parent pointer
  if tree[j][1] != -1 :
    L=DFSinOrder(tree,tree[j][1],liml,tree[j][0])
  else:
    L=True
  parent=tree[j][0]
  if tree[j][2] !=-1:
    R=DFSinOrder(tree,tree[j][2],tree[j][0],limr)
  else:
    R=True

  if L and R and liml <= parent and parent < limr:
    return True
  else:
    return False

def main():
  nodes = int(sys.stdin.readline().strip())
  tree = []
  for i in range(nodes):
    tree.append(list(map(int, sys.stdin.readline().strip().split())))
  if IsBinarySearchTree(tree):
    print("CORRECT")
  else:
    print("INCORRECT")

threading.Thread(target=main).start()
