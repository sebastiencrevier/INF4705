import argparse


def parse_arguments():
    parser = argparse.ArgumentParser()

    parser.add_argument('file')
    parser.add_argument('-t', action='store_true')
    parser.add_argument('-p', action='store_true')

    namespace = parser.parse_args()
    return namespace
