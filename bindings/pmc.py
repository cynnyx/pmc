import pmc
b = pmc.PMC("pmc -f ../data/sample.mtx -a 0 -h 0")
b.run()
c = b.maxClique
print("MaxClique is:")
for elem in c:
    print(str(elem))