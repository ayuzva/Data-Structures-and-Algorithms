# python3
import random

class Database:
    def __init__(self, row_counts):
        self.row_counts = row_counts
        self.max_row_count = max(row_counts) #max number in the list
        n_tables = len(row_counts) #length
        self.ranks = [1] * n_tables #Creates a list of that many elements
        self.parents = list(range(n_tables))

    def merge(self, dst, src):

        while self.row_counts[dst] == 0 and dst != self.get_parent(dst) :
            dst=self.get_parent(dst)
        
        while self.row_counts[src] == 0 and src != self.get_parent(src):
            src=self.get_parent(src)

        if dst != src :
            if self.ranks[dst] >= self.ranks[src]:
                self.row_counts[dst]+=self.row_counts[src]
                self.row_counts[src]=0
                self.parents[src]=dst
                self.ranks[dst]=self.ranks[dst]+self.ranks[src]
                self.max_row_count=max(self.max_row_count,self.row_counts[dst])
                
            else:
                self.row_counts[src]+=self.row_counts[dst]
                self.row_counts[dst]=0
                self.parents[dst]=src
                self.ranks[src]=self.ranks[src]+self.ranks[dst]
                self.max_row_count=max(self.max_row_count,self.row_counts[src])
        return

    def get_parent(self, table):#index of the table unit
        # find parent and compress path
        return self.parents[table]


def main():
    n_tables, n_queries = map(int, input().split())
    counts = list(map(int, input().split()))
    assert len(counts) == n_tables
        
    db = Database(counts)
    for i in range(n_queries):
        dst, src = map(int, input().split())
        db.merge(dst - 1, src - 1)
        print(db.max_row_count)

if __name__ == "__main__":
    main()
