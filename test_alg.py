def worstTeacher(s, t):
    if graph[t][1] != graph[s][1]:
        return True
    elif s not in graph[t][2]:
        return True
    else:
        return False

def spa_teacher(graph):
    tf, sf, vf = [0, 1, 2], [3, 4, 5], {3:2, 4:2, 5:2}
    ft = tf[0]
    final_match = {}
    while ft in tf and graph[ft][2]:
        fst = graph[ft][2][0]
        final_match[fst] = [ft]
        vf[fst] -= 1
        # school is over subscribed
        if vf[fst] < 0:
            removed = False
            for j in final_match[fst]:
                result = worstTeacher(fst, j)
                if result:
                    final_match[fst].remove(j)
                    removed = True
                    vf[fst] += 1
                    break

            if not removed:
                final_match[fst].remove(j)
        # school is full
        if vf[fst] == 0:
            pass

graph = {}
for i in range(6):
    line = list(map(str, input().split('|')))
    ent, cod, hab, adj = line[0], line[1], line[2], list(map(int, line[3].split()))
    graph[i] = (ent, hab, adj)

spa_teacher(graph)
