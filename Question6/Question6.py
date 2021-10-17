#!/bin/python3

#I think this needs to run in c


def addTuple(t1, t2):
    return [t1i + t2i for t1i, t2i in zip(t1, t2)]


def compareTuple(t1, t2):
    return all([t1i <= t2i for t1i, t2i in zip(t1, t2)])

 
def theHackathon(n, m, a, b, f, s, t):
    # Participant code here
    people = {}
    groups = {}
    max_dep = f, s, t
    for i in range(n):
        inputdata = input().split()
        name = inputdata[0]
        people[name] = i

        dep = [0, 0, 0]
        dep[int(inputdata[1]) - 1] = 1
        groups[i] = [[name], dep]

    def mergeGroups(g1, g2):
        if g1 != g2:
            group1 = groups[g1]
            group2 = groups[g2]

            addedTuples = addTuple(group1[1], group2[1])

            if(len(group1[0]) + len(group2[0]) <= b and compareTuple(addedTuples, max_dep)):
                groups[g1] = [group1[0] + group2[0], addedTuples]
                for name in group2[0]:
                    people[name] = g1

                del groups[g2]

    for i in range(m):
        r1, r2 = input().split()
        mergeGroups(people[r1], people[r2])

    maxlen = a
    namesToPrint = []

    for group in groups.values():
        glen = len(group[0])
        if glen > maxlen:
            maxlen = glen
            namesToPrint = group[0]
        elif glen == maxlen:
            namesToPrint += group[0]

    if not len(namesToPrint):
        print("no groups")

    else:
        namesToPrint.sort()
        for name in namesToPrint:
            print(name)


if __name__ == '__main__':
    inputdata = input().split()

    n = int(inputdata[0])

    m = int(inputdata[1])

    a = int(inputdata[2])

    b = int(inputdata[3])

    f = int(inputdata[4])

    s = int(inputdata[5])

    t = int(inputdata[6])

    theHackathon(n, m, a, b, f, s, t)
