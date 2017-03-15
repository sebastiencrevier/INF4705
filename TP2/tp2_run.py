import argparse
from tp2 import main


def parse_arguments():
    parser = argparse.ArgumentParser()

    parser.add_argument('file')
    parser.add_argument('-a')
    parser.add_argument('-t', action='store_true')
    parser.add_argument('-p', action='store_true')

    namespace = parser.parse_args()
    return namespace


ns = parse_arguments()
main(ns.file, ns.a, ns.t, ns.p)
