import numpy as np


def add_dimension(array, size, in_front=False):
    arrays = [array for _ in range(size)]
    axis = 0 if in_front else len(array.shape)
    return np.stack(arrays, axis=axis)


a = np.zeros(1, int)
a = add_dimension(a, 4)
a = add_dimension(a, 2)

print(a[0])
