def heap_height(size):
    height = 0

    width = 1
    while size > 0:
        height += 1
        size -= width
        width *= 2

    return height
