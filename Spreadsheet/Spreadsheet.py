class Spreadsheet:
    def __init__(self):
        self.formulas = {}
        self.visiting = set() 
        
    def set(self, cell, formula):
        self.formulas[cell] = formula
    
    def get(self, cell):
        if cell not in self.formulas:
            return 0
        if cell in self.visiting:
            return None
        
        self.visiting.add(cell) 
        tokens = self.formulas[cell].split()
        total = int(tokens[0])
        for i in range(1, len(tokens), 2): 
            if total is None:
                break 
            op = tokens[i]
            num = self._value(tokens[i + 1])
            if num is None:
                total = None
                break
            if op == "+":
                total += num
            else:
                total -= num
        self.visiting.remove(cell) 
        return total 

    def _value(self, token):
        if token[0].isalpha(): 
            return self.get(token)
        return int(token) 
    
