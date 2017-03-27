import numpy as np


def add_dimension(array, size, in_front=False):
    arrays = [array for _ in range(size)]
    axis = 0 if in_front else len(array.shape)
    return np.stack(arrays, axis=axis)

a = np.random.randn(3, 4)
b = add_dimension(a, 10)

print(b.shape)
