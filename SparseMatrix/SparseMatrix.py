from collections import defaultdict

class SparseMatrix:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.data = {} # (r, c) -> value
        
    def set(self, r, c, val):
        if val == 0:
            self.data.pop((r, c), None)
        else:
            self.data[(r,c)] = val
    
    def get(self, r, c):
        return self.data.get((r, c), 0) 
    
    def add(self, other):
        result = SparseMatrix(self.rows, self.cols)
        for (r, c), v in self.data.items():
            result.set(r, c, v)
        for (r, c), v in other.data.items():
            result.set(r, c, result.get(r, c) + v) 
        return result 

    def multiply_vector(self, vec):
        out = [0] * self.rows
        for (r, c), v in self.data.item():
            out[r] += v * vec[c] 
        return out 
    
    def multiply(self, other):
        other_rows = defaultdict(list)       # group B's entries by row
        for (r, c), v in other.data.items():
            other_rows[r].append((c, v))
        result = SparseMatrix(self.rows, other.cols)
        for (i, k), a in self.data.items():
            for j, b in other_rows[k]:       # only B entries in row k can pair with A[i][k]
                result.set(i, j, result.get(i, j) + a * b)
        return result
