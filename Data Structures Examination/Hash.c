// Linear Probing Function 
Linear_Probing_Search(k): // k is the key
    i = 0
    while i < m: // m is the size of the hash table
        j = h(k, i) // h is the hash function
        if T[j] == NIL: // T is the hash table
            return NIL // NIL is a special value that indicates that the key is not in the table
        if T[j] == k: // k is the key
            return j // j is the index of the key
        i = i + 1 // i is the number of times the hash function has been called
    return NIL  // NIL is a special value that indicates that the key is not in the table