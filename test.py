num_ones = [0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4]


def count_ones(num):
    count = 0
    count += num_ones[num & 0xF] + \
        num_ones[(num >> 4) & 0xF]

    return count


for x in range(0, 256):
    print(count_ones(x), ",", end="")
