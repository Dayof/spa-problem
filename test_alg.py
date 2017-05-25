def checkIfSchoolHasVacancy(graph, t, s, v):
    for i in s:
        if graph[t][1] == graph[i][1] and v[i]:
            return s
    return -1


def spa_teacher(graph):
    tf, sf, vf = [0, 1, 2], [3, 4, 5], {3:2, 4:2, 5:2}
    ft = tf[0]
    while ft in tf and graph[ft][2]:
        vos = checkIfSchoolHasVacancy(graph, ft, graph[ft][2], vf)
        if vos > -1:
            vf[vos] -= 1
        else:
            pass

graph = {}
for i in range(6):
    line = list(map(str, input().split('|')))
    ent, cod, hab, adj = line[0], line[1], line[2], list(map(int, line[3].split()))
    graph[i] = (ent, hab, adj)

spa_teacher(graph)
