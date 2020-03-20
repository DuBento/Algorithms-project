from parse import compile

f = open("experimental/resultados", "r")
p_content = compile("real\t0m{}s")

# while line = f.readline()

for line in f.readlines():
    print(p_content.parse(line)[0])
