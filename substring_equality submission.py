# python3

import sys

class Solver:
	def __init__(self, s):
		self.s = s.strip('\n')
		self.h1=[0]*(len(self.s)+1)
		self.h2=[0]*(len(self.s)+1)
		self.m1=(pow(10,9))+7
		self.m2=(pow(10,9))+9
		self.x1=1 #but should really be random
		self.x2=9

	def ask(self, a, b, l): #if equal return true
		z=pow(self.x1,l,self.m1)#taking modulus while taking power is faster 
		x=pow(self.x2,l,self.m2)
		if (self.h1[a+l]-z*self.h1[a])%self.m1 == (self.h1[b+l]-z*self.h1[b])%self.m1 : 
			if (self.h2[a+l]-x*self.h2[a])%self.m2 == (self.h2[b+l]-x*self.h2[b])%self.m2 :
				return True
		return False #s[a:a+l] == s[b:b+l]

	def precomp_hash(self):
		for i in range(1,len(self.s)+1):#should add self here i think
			self.h1[i] = (self.x1 * self.h1[i-1]+ord(self.s[i-1])) % self.m1

		for i in range(1,len(self.s)+1):
			self.h2[i] = (self.x2 * self.h2[i-1]+ord(self.s[i-1])) % self.m2

s = sys.stdin.readline() #string
q = int(sys.stdin.readline()) #number of queries
solver = Solver(s)
solver.precomp_hash()
for i in range(q):
	a, b, l = map(int, sys.stdin.readline().split())
	print("Yes" if solver.ask(a, b, l) else "No")
