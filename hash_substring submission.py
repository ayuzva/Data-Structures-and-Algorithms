# python3
import random

def read_input():
    return (input().rstrip(), input().rstrip())

def print_occurrences(output):
    print(' '.join(map(str, output)))
#range(start(at),stop(before),incrementation)

def poly_hash(S,p,x):
    hash_value = 0
    for i in range(len(S)-1,-1,-1):
        hash_value = (hash_value*x + ord(S[i]))
        hash_value =(hash_value % p + p) % p
    return hash_value

def PrecomputeHashes(T,P_len,p,x):#Something wrong here probably
    H=[None]*(len(T)-P_len+1)
    S=T[(len(T)-P_len):len(T)]
    H[len(T)-P_len] = poly_hash(S,p,x)
    y=1
    for i in range(1,P_len+1):
        y=((y*x)%p+p)%p
    for i in range((len(T)-P_len-1),-1,-1):
        H[i]=((x*H[i+1] + ord(T[i]) - y*ord(T[i + P_len])) % p + p) % p    
    return H



def get_occurrences(pattern, text):
    result=[]
    p = 100000000007
    x = 1   #but technically should be random(1, p-1)
    #result#empty list
    pHash = poly_hash(pattern,p,x)
    H = PrecomputeHashes(text,len(pattern),p,x)
    for i in range(len(text)-len(pattern)+1):#for first test pHash is 292 and table results are in 19x range
        if pHash != H[i]:
            continue
        if text[i:(i+len(pattern))] == pattern: #during last testing this didn't go through so fix this
            result.append(i)
    return result
    #i for i in range(len(text) - len(pattern) + 1) if text[i:i + len(pattern)] == pattern

if __name__ == '__main__':
    print_occurrences(get_occurrences(*read_input()))#the * allows for arbitrary number of arguemnts

