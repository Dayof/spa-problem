# worst teacher means the last temporary assignment on the prefered
# list of the school
def worstTeacher(final_match, school, school_pref_list):
    big_index = -1
    index_to_look = [j[0] for j in final_match if j[1] == school]

    for i in index_to_look:
        if i in school_pref_list:
            ind = school_pref_list.index(i)
            if ind > big_index:
                big_index = ind

    return school_pref_list[big_index] if big_index > -1 else -1

def spa_teacher(graph, t, s):
    # Tf: teachers free list
    # Sf: schools free list
    # Vs: list of vacancies of each school
    Tf, Sf, Vs = list(range(t)), list(range(t, s)), {}

    for i in range(t, s):
        Vs[i] = 2

    # list of tuples of the final maximum bipartide matching
    final_match = []

    # first free teacher to test
    ft = Tf[0]
    Tf.remove(ft)

    # while there is a free teacher on Tf and this teacher still have a
    # school to go
    while Tf and graph[ft][1]:
        # get first school of Tf
        fs = graph[ft][1][0]

        # assign this teacher temporary on a school
        final_match.append((ft, fs))
        # delete this school preference on the teacher preference list
        graph[ft][1].remove(fs)
        # decrease one vacancy of that school
        Vs[fs] -= 1

        # check if school vacancy is over subscribed
        if Vs[fs] < 0:
            # get worst teacher
            wt = worstTeacher(final_match, fs, graph[fs][1])
            # print('under ', wt, fs)
            if wt > -1:
                # delete the worst teacher temporary assigned
                final_match.remove((wt, fs))
                # put this teacher back on the free list of teachers
                Tf.append(wt)
                # remove this teacher from the preference of that school
                graph[fs][1].remove(wt)
                # increase one vancacy of that school
                Vs[fs] += 1

        # check if school vacancy is full
        if Vs[fs] == 0:
            # get worst teacher
            wt = worstTeacher(final_match, fs, graph[fs][1])
            # print(wt)
            if wt > -1:
                index_wt = graph[fs][1].index(wt) + 1
                wt_sucessors = graph[fs][1][index_wt:]
                # print('full ', wt, wt_sucessors)
                if wt_sucessors:
                    for i in wt_sucessors:
                        # remove teachers sucessors after the index of the worst
                        # teacher on the school preference list
                        if i in graph[fs][1]:
                            graph[fs][1].remove(i)
                        # also, remove this school preferenre on the teachers
                        # removed preference list
                        if fs in graph[i][1]:
                            graph[i][1].remove(fs)

        # get next free teacher on ft
        ft = Tf[0]
        Tf.remove(ft)


    return final_match

graph = {}
for i in range(int(input())):
    line = list(map(str, input().split('|')))
    ent, cod, adj = line[0], line[1], list(map(int, line[2].split()))
    graph[i] = (ent, adj)

# 99, 150
# 6, 9
# print(graph)
print(spa_teacher(graph, 6, 9))
