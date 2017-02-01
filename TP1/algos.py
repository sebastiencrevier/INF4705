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


def insertion_sort(arr):
    for i in range(1, len(arr)):
        j = i - 1
        key = arr[i]
        while (arr[j] > key) and (j >= 0):
            arr[j + 1] = arr[j]
            j -= 1
            arr[j + 1] = key
    return arr
