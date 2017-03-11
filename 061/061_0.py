def calc_numbers(start, end, proc):
    n = 1
    out = []
    while True:
        z = proc(n)
        if z >= start and z < end: out.append(z)
        if z >= end: return out
        n += 1

p3 = calc_numbers(1000, 10000, lambda n : n * (n + 1) / 2)
p4 = calc_numbers(1000, 10000, lambda n : n * n)
p5 = calc_numbers(1000, 10000, lambda n : n * (3 * n - 1) / 2)
p6 = calc_numbers(1000, 10000, lambda n : n * (2 * n - 1))
p7 = calc_numbers(1000, 10000, lambda n : n * (5 * n - 3) / 2)
p8 = calc_numbers(1000, 10000, lambda n : n * (3 * n - 2))


def find_loop(lists, start, end, found_numbers = []):
    if len(lists) == 1 and start * 100 + end in lists[0]:
        found_numbers += [start * 100 + end]
        print found_numbers, sum(found_numbers)
        return
    
    for cur_list in lists:
        for c in cur_list:
            if c / 100 == start:
                lists_copy = lists[0:]
                lists_copy.remove(cur_list)
                find_loop(lists_copy, c % 100, end, found_numbers + [c])

for n in p8:
    print n
    find_loop([p3, p4, p5, p6, p7], n % 100, n / 100)
