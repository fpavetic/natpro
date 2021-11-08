# https://suncobraniranje.phishar.com/
#
# OMP_NUM_THREADS=8; time python3 ./suncobraniranje.py

from sklearn.neighbors import KDTree
import math
import numpy as np
import os
from queue import PriorityQueue
import sys

lines = []
f = open("/home/fpavetic/Downloads/suncobraniranje_ulazni_podaci", "r")
lines = f.readlines()

n = int(lines[0])
lines = lines[1:]

assert len(lines) == n

test_set = 2

if test_set == 0: # small test
    lines = lines[-1000:]
    n = len(lines)
elif test_set == 1: # medium test
    lines = lines[-10000:]
    n = len(lines)

points = np.zeros((n, 2), dtype=int)
for i in range(len(lines)):
    coords = [int(x) for x in lines[i].split(" ")]
    points[i][0] = coords[0]
    points[i][1] = coords[1]

print (points)

kdt = KDTree(points, leaf_size=30, metric='euclidean')
K=2
dist, idx = kdt.query(points, k=K)
print (dist, idx)

min_dist = 1000000000
max_dist = 0

for i in range(n):
    assert idx[i, 0] == i
    min_dist = min(min_dist, dist[i][1])
    max_dist = max(max_dist, dist[i][1])

print (f'min_dist={min_dist} max_dist={max_dist}')

def Area(r):
    return r*r*math.pi

assert K >= 2
col_next = [1] * n
col_last = [0] * n
assignment = [-1] * n
total_area = 0
in_degree = [0] * n
out_degree = [0] * n

points_per_cluster = []
for i in range(n):
    points_per_cluster.append([])

def Priority(in_degree, distance):
    if in_degree == 0:
        return -1000000000 * distance
    return -distance

for i in range(n):
    j = idx[i][1]
    # i->j kad je je nabliza tocki i
    out_degree[i] += 1
    in_degree[j] += 1

pq = PriorityQueue()
for i in range(n):
    pq.put((Priority(in_degree[i], dist[i][1]), i))

while not pq.empty():
    (priority, i) = pq.get()

    if assignment[i] != -1:
        continue

    j = idx[i][1]
    if in_degree[i] != 0 and assignment[j] != -1:
        continue

    assert i != j
    assignment[i] = i
    assignment[j] = i
    points_per_cluster[i].append((points[i][0], points[i][1], i))
    points_per_cluster[i].append((points[j][0], points[j][1], j))

    k = idx[j][1]
    in_degree[k] -= 1
    pq.put((Priority(in_degree[k], dist[k][1]), k))

for i in range(n):
    if assignment[i] == -1:
        assignment[i] = i
        j = idx[i, 1]
        points_per_cluster[i].append((points[i, 0], points[i, 1], i))
        points_per_cluster[i].append((points[j, 0], points[j, 1], j))

print (total_area)
not_covered = 0
num_single = 0
for i in range(len(assignment)):
    if assignment[i] == -1:
        print (f'{i} not covered.')
        not_covered += 1
    if len(points_per_cluster[i]) == 1:
        num_single += 1

print ('not_covered: ', not_covered)
print ('num_single: ', num_single)

radius_per_cluster = []
cluster_centers = []

def bbox_center(pp):
    min_x = 1000000000
    max_x = 0
    min_y = 1000000000
    max_y = 0
    for p in pp:
        min_x = min(min_x, p[0])
        max_x = max(max_x, p[0])
        min_y = min(min_y, p[1])
        max_y = max(max_y, p[1])
    return (0.5*(min_x+max_x), 0.5*(min_y+max_y))

for i in range(n):
    radius_per_cluster.append(0)
    cluster_centers.append((0, 0))
    if len(points_per_cluster[i]) == 0:
        continue

    points_per_cluster[i] = list(set(points_per_cluster[i]))
    center_x, center_y = bbox_center(points_per_cluster[i])

    for point in points_per_cluster[i]:
        dx = point[0] - center_x
        dy = point[1] - center_y
        d = math.sqrt(dx*dx + dy*dy)
        if d > radius_per_cluster[i]:
            radius_per_cluster[i] = d
            cluster_centers[i] = (center_x, center_y)

suma_povrsina = math.pi*sum(r*r for r in radius_per_cluster)
print (suma_povrsina)

m = 0
for i in range(n):
    if len(points_per_cluster[i]) > 0:
        m += 1

f = open(f'/home/fpavetic/suncobraniranje/rjesenje-{suma_povrsina}.txt', "w")
f.write(f'{m}\n')
for i in range(n):
    if len(points_per_cluster[i]) > 0:
        f.write(str(f'{cluster_centers[i][0]} {cluster_centers[i][1]} {radius_per_cluster[i]}\n'))
        f.write(str(f'{len(points_per_cluster[i])}\n'))
        for point in points_per_cluster[i]:
            f.write(str(f'{point[2]+1}\n'))
        m -= 1
f.close()
print (m)
assert m == 0
