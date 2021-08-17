#!/usr/bin/env python3

MAX_STATION = 19

def validate_station(name, station):
    if not 0 <= station <= MAX_STATION:
        raise ValueError('%s out of range: no station %d' % (name, station))

def validate_direction(direction):
    if len(direction) != 1 or direction not in 'DU':
        raise ValueError('direction out of range: no direction "%s"'
                         % direction)

def validate_stations_and_direction(src, dest, direction):
    validate_station('src', src)
    validate_station('dest', dest)
    validate_direction(direction)

def compute_wait_time(src, dest, direction):
    validate_stations_and_direction(src, dest, direction)

    delta = dest - src
    if direction == 'D':
        if delta <= 0:
            return -delta # move down to destination directly
        else:
            return src + dest # move down to 0, then up to destination
    elif direction == 'U':
        if delta >= 0:
            return delta # move up to destination directly
        else:
            # move up to the highest station, then down to destination
            return (MAX_STATION - src) + (MAX_STATION - dest)


FINAL_DESTINATION = 11
assert 0 <= FINAL_DESTINATION <= MAX_STATION

for _ in range(int(input())):
    srcstr, direction = input().split()
    print(compute_wait_time(int(srcstr), FINAL_DESTINATION, direction))
