# -*- coding:utf-8 -*-

mat = 'abcesfcsadee'
target = 'bcced'
snake = []


def Try(level):
    if level>= len(target):
        return True
    for d in [-row, row, -1, 1]:
        snake.append(mat[mat[level-1]+d])

