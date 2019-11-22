# python3

import sys
from math import floor
from collections import namedtuple

'''
def solve(s, t):
	ans = Answer(0, 0, 0)
	for i in range(len(s)):
		for j in range(len(t)):
			for l in range(min(len(s) - i, len(t) - j) + 1):
				if (l > ans.len) and (s[i:i+l] == t[j:j+l]):
					ans = Answer(i, j, l)
	return ans
'''
def poly_hash(S,p,x):
    hash_value = 0
    for i in range(len(S)-1,-1,-1):
        hash_value = (hash_value*x + ord(S[i]))
        hash_value = (hash_value % p + p) % p
    return hash_value

def precompute_hashes(T,P_len,p):#hashed to substrings of certain length
	x=263	#problem with random x # not anymore fixed it
	H=[None]*(len(T)-P_len+1)
	S=T[(len(T)-P_len):len(T)]
	H[len(T)-P_len] = poly_hash(S,p,x)
	y=1
	for i in range(1,P_len+1):
	    y=((y*x)%p +p)%p
	for i in range((len(T)-P_len-1),-1,-1):
		H[i]=((x*H[i+1] + ord(T[i]) - (y*ord(T[i + P_len])))%p + p) % p    
	return H

def rolling_hash(s,t,m):
	p1=1000000007
	p2=1000004249
	p3=1000008397
	if len(s) < len(t):
		h1=precompute_hashes(s,m,p1)#h1 will contain the shorter string, the has table will be based on this
		h2=precompute_hashes(t,m,p1)
		h3=precompute_hashes(s,m,p2)#h1 will contain the shorter string, the has table will be based on this
		h4=precompute_hashes(t,m,p2)
		h5=precompute_hashes(s,m,p3)#h1 will contain the shorter string, the has table will be based on this
		h6=precompute_hashes(t,m,p3)
	else:
		h1=precompute_hashes(t,m,p1)
		h2=precompute_hashes(s,m,p1)
		h3=precompute_hashes(t,m,p2)
		h4=precompute_hashes(s,m,p2)
		h5=precompute_hashes(t,m,p3)
		h6=precompute_hashes(s,m,p3)

	hash_dict1={}
	for i in range(len(h1)):#creates a hash table
		hash_dict1[h1[i]]=i

	hash_dict2={}
	for i in range(len(h3)):#creates a hash table
		hash_dict2[h3[i]]=i

	hash_dict3={}
	for i in range(len(h5)):#creates a hash table
		hash_dict3[h5[i]]=i

	for i in range(len(h2)):
		if (h2[i] in hash_dict1) and (h4[i] in hash_dict2) and (h6[i] in hash_dict3):
			return True, hash_dict1[h2[i]],i
	return False,-1,-1

def solve(s,t):
	#use a binary search principle to test halves of string for match and precomputed has lookup
	#check binary search algo. We are using 2 hases per string for extra collision avoidance
	left = 0
	right = min(len(s),len(t))
	ans = Answer(0,0,0)# a tuple lookup
	while left <= right:
		mid=floor((left+right)/2)
		exists,i,j=rolling_hash(s,t,mid)

		if exists :
			left = mid + 1
			ans = Answer(i, j, mid)# a tuple lookup
		else:
			right = mid - 1

	if len(s) >= len(t):
		ans=Answer(ans.j,ans.i,ans.len)
	return ans


if __name__ == '__main__':
	Answer = namedtuple('answer_type', 'i j len')
	for line in sys.stdin.readlines():
		#line=input().rstrip('\n')
		s, t = line.split()
		ans = solve(s, t)#call to the solution
		print(ans.i, ans.j, ans.len)#lookup from tuple
