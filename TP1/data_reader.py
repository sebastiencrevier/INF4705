def read(file):
    with open(file) as f:
        content = f.readlines()
    content = [int(x.strip()) for x in content]
    return content
