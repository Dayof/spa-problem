import copy

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

def spa_teacher(t, s):
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
    run = True

    # while there is a free teacher on Tf and this teacher still have a
    # school to go
    while run:
        if not graph[ft][1] and Tf:
            ft = Tf[0]
            Tf.remove(ft)
            continue
        elif not Tf:
            break
        run = True if Tf else False

        # get first school of Tf
        fs = graph[ft][1][0]

        # assign this teacher temporary on a school
        last_match = (ft, fs)
        final_match.append(last_match)
        # delete this school preference on the teacher preference list
        graph[ft][1].remove(fs)
        # decrease one vacancy of that school
        Vs[fs] -= 1

        # check if school vacancy is over subscribed
        if Vs[fs] < 0:
            # get worst teacher
            wt = worstTeacher(final_match, fs, graph[fs][1])
            # print('under ', wt, graph[fs][1], fs, final_match)
            if wt > -1:
                # delete the worst teacher temporary assigned
                final_match.remove((wt, fs))
                # put this teacher back on the free list of teachers
                Tf.append(wt)
                # remove this teacher from the preference of that school
                graph[fs][1].remove(wt)
                # increase one vancacy of that school
                Vs[fs] += 1
            else:
                # if on the final match there is no teacher of the preference of
                # that school, delete the last one
                final_match.remove(last_match)
                # put this last back on the free list of teachers
                Tf.append(last_match[0])
                # increase one vancacy of that school
                Vs[fs] += 1


        # check if school vacancy is full
        if Vs[fs] == 0:
            # get worst teacher
            wt = worstTeacher(final_match, fs, graph[fs][1])
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
        if Tf:
            ft = Tf[0]
            Tf.remove(ft)

    # print(graph[ft][1], ft, Tf)
    return final_match

graph = {}
for i in range(int(input())):
    line = list(map(str, input().split('|')))
    ent, cod, adj = line[0], line[1], list(map(int, line[2].split()))
    graph[i] = (ent, adj)

# stub2: 99, 150
# stub: 6, 9
# stub3 and stub6: 5, 10
# stub4: 4, 8
# stub5: 3, 6
cp_graph = copy.deepcopy(graph)
result = spa_teacher(99, 150)
schools = set([j[1] for j in result])
teachers = set([j[0] for j in result])
schools = sorted(schools)
count1, count2, count3, count4, count5 = 0, 0, 0, 0, 0
tps = {}
print('--- Set of teachers assigned ---\n', teachers)
print('--- Set of schools assigned ---\n', schools)
print('--- Professors per school ---')
for i in schools:
    tps[i] = [j[0] for j in result if j[1] == i]
print(tps)
for i in result:
    # print(i[1], cp_graph[i[0]][1][0])
    if i[1] == cp_graph[i[0]][1][0]:
        count1 += 1
    elif i[1] == cp_graph[i[0]][1][1]:
        count2 += 1
    elif i[1] == cp_graph[i[0]][1][2]:
        count3 += 1
    elif i[1] == cp_graph[i[0]][1][3]:
        count4 += 1
    elif i[1] == cp_graph[i[0]][1][1]:
        count5 += 1
print('--- Schools with one teacher ---')
schools_one = [key for key, value in tps.items() if len(value) == 1]
print(schools_one)
print('--- Free teachers ---')
free_t = [i for i in range(100) if i not in teachers]
print(free_t)
print('--- Exist free schools which any free teacher want to go? ---')
answer = False
for i in free_t:
    for j in schools_one:
        if j in cp_graph[i][1]:
            answer = False
            print('Yes, school %s can employ teacher %s' % (j, i))
if not answer:
    print('No!')
print('---- Result ----\n', result, '\nperfect match for %s teachers' % (count1), '\nc2: %s | c3: %s | c4: %s | c5: %s ' % (count2, count3, count4, count5), '\nteachers assigned: ', len(teachers), '\nschools assigned: ', len(schools))
