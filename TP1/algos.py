def counting_sort(arr, max_val):
    m = max_val + 1
    count = [0] * m  # init with zeros
    for a in arr:
        count[a] += 1  # count occurences
    i = 0
    for a in range(m):  # emit
        for c in range(count[a]):  # - emit 'count[a]' copies of 'a'
            arr[i] = a
            i += 1
    return arr


def insertion_sort(numList, first, last):
    for x in range(first, last + 1):
        key = numList[x]
        y = x - 1
        while y > -1 and numList[y] > key:
            numList[y + 1] = numList[y]
            y = y - 1
        numList[y + 1] = key
