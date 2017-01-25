from data_reader import read
from arg_parser import parse_arguments
import re
import time

ns = parse_arguments()

array = read(ns.file)
maxval = int(re.search(r'(.*)_(.*)_(.*)', ns.file, re.M | re.I).group(2))

start_time = time.perf_counter()

m = maxval + 1
count = [0] * m  # init with zeros
for a in array:
    count[a] += 1  # count occurences
i = 0
for a in range(m):  # emit
    for c in range(count[a]):  # - emit 'count[a]' copies of 'a'
        array[i] = a
        i += 1

end_time = time.perf_counter()

if ns.p:
    for el in array:
        print(el)

if ns.t:
    print("%s" % (end_time - start_time))
