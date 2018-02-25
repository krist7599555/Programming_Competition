import numpy as np
import copy
from collections import defaultdict
from itertools import product

def read_table(s): return [ln.split() for ln in s.split('\n') if ln.strip()]
def str_table(m, j = ''): return '\n'.join([j.join(ar) for ar in m])

#~ open_table = None
#~ def open(i, j):
	#~ if open_table[i][j] == 'x':
		#~ print('got a bomb', i, j)
		#~ raise Exception
	#~ return int(open_table[i][j])

def rref(mat):
	if not mat: 
		return mat
	r, c = len(mat), len(mat[0])
	x = -1
	for i in range(r):
		p = None
		x += 1
		while p is None and x < c:
			for i_ in range(i, r):
				if mat[i_][x]:
					p = i_
					break
			else:
				x += 1
		if x >= c: break
		mat[i], mat[p] = mat[p], mat[i]
		for i2 in range(r):
			if i2 != i:
				mat[i2] = mat[i2] * mat[i][x] - mat[i] * mat[i2][x]
	return mat


def get_valid_move(mat):
	dirct = np.delete(np.array(list(product([-1, 0, 1], [-1, 0, 1]))), 4, 0) # 8 dir
	r, c = len(mat), len(mat[0])
	bomb, free, data = [], [], []
	for i, j in product(range(r), range(c)):
		if mat[i][j].isdigit():
			nm = int(mat[i][j])
			ls = list()
			for ni, nj in np.array([i, j]) + dirct:
				if -1 < ni < r and -1 < nj < c:
					if mat[ni][nj] == 'x': nm -= 1
					if mat[ni][nj] == '?': ls.append((ni, nj))
			if nm < 0 or nm > len(ls):
				raise Exception
			if ls:
				if nm in [0, len(ls)]:
					prep = True
					for i, j in ls:
						[bomb, free][nm == 0].append(tuple([i, j]))
					continue
				data.append([(nm, i, j), ls])	
	return bomb, free, data

def solve(mat, n, get=open):
	# read matrix
	#~ print(str_table(mat), '\n')
	init_mat = np.array(mat)
	r, c = len(mat), len(mat[0])
	bomb, free, data = get_valid_move(mat)
	if bomb or free:
		for i, j in bomb: mat[i][j] = 'x'
		for i, j in free: mat[i][j] = str(get(i, j))
		return solve(mat, n, get)
	cmpss = set().union(*[set(t) for h, t in data])
	tp2x = {tp: i for i, tp in enumerate(cmpss)}
	x2tp = {i: tp for i, tp in enumerate(cmpss)}	
	
	# solve matrix row operator
	i_mat = list()
	for (vl, _, _), cod in data:
		tmp = [0] * len(cmpss)
		for tp in cod:
			tmp[tp2x[tp]] = 1
		i_mat.append(np.array(tmp + [vl]))
		
	# assign result
	for ar in rref(i_mat):
		if (ar < 0).any(): ar = -ar
		if (ar < 0).any() or (ar == 0).all(): continue
		x = bool(ar[-1] == ar[:-1].sum())
		y = bool(ar[-1] == 0)
		for k, vl in enumerate(ar[:-1]):
			if vl:
				i, j = x2tp[k]
				if x:
					mat[i][j] = 'x'
				elif y:
					mat[i][j] = str(get(i, j))
				
	if not np.array_equal(init_mat, np.array(mat)): return solve(mat, n, get)
	if (init_mat != '?').all(): return mat # get answer
	if (init_mat == 'y').any(): return mat # check recursive
	
	# spicial case
	print('init spi', str_table(init_mat), sep='\n\n', end='\n\n')
	spi_res = list()
	for (vl, i, j), cod in data:
		if vl == 1:
			for i, j in cod:
				tmp = copy.deepcopy(mat)
				tmp[i][j] = 'x'
				try:
					res = solve(copy.deepcopy(tmp), n, lambda *_: 'y')
					bmb = (np.array(res) == 'x').sum()
					nil = (np.array(res) == '?').sum()
					print('}}}')
					print(n, bmb, nil)
					print(str_table(tmp), '\n')
					if bmb > n: continue
					if nil > 3 and bmb == n: continue
					#if
					print('^^^ ok\n\n')
					spi_res.append(tmp)
				except:
					pass
			break
	print('special', len(spi_res), *map(str_table, spi_res), sep='\n\n', end='\n\n')
	
	if len(spi_res) != 1:
		raise Exception
	return solve(spi_res[0], n)
	
				
def solve_mine(mp, n):
	try:
		return str_table(solve(read_table(mp), n), ' ')
	except:
		return '?'

a = ["""
	? ? ? ? ? ?
	? ? ? ? ? ?
	? ? ? 0 ? ?
	? ? ? ? ? ?
	? ? ? ? ? ?
	0 0 0 ? ? ?
	""".strip(),
	"""
	1 x 1 1 x 1
	2 2 2 1 2 2
	2 x 2 0 1 x
	2 x 2 1 2 2
	1 1 1 1 x 1
	0 0 0 1 1 1
	""".strip()
]

b = ["""
	0 ? ?
	0 ? ?
	""".strip(),
	"""
	0 1 x
	0 1 1
	""".strip()
]
c = ["""
	? ? ? ? 0 0 0
	? ? ? ? 0 ? ?
	? ? ? 0 0 ? ?
	? ? ? 0 0 ? ?
	0 ? ? ? 0 0 0
	0 ? ? ? 0 0 0
	0 ? ? ? 0 ? ?
	0 0 0 0 0 ? ?
	0 0 0 0 0 ? ?
	""".strip(),
	"""
	1 x x 1 0 0 0
	2 3 3 1 0 1 1
	1 x 1 0 0 1 x
	1 1 1 0 0 1 1
	0 1 1 1 0 0 0
	0 1 x 1 0 0 0
	0 1 1 1 0 1 1
	0 0 0 0 0 1 x
	0 0 0 0 0 1 1
	""".strip()
]

d = ["""
	? ? 0 ? ? ? 0 0 ? ? ? 0 0 0 0 ? ? ? 0
	? ? 0 ? ? ? 0 0 ? ? ? 0 0 0 0 ? ? ? ?
	? ? 0 ? ? ? ? ? ? ? ? 0 0 0 0 ? ? ? ?
	0 ? ? ? ? ? ? ? ? ? ? 0 0 0 0 0 ? ? ?
	0 ? ? ? ? ? ? ? ? ? 0 0 0 0 0 0 0 0 0
	0 ? ? ? 0 0 0 ? ? ? 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 ? ? ? ? ? ? ? 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 ? ? ? ? 0 0 0 0 0
	0 0 ? ? ? 0 ? ? ? 0 ? ? ? ? 0 0 0 0 0
	0 0 ? ? ? ? ? ? ? 0 0 0 0 0 0 ? ? ? 0
	0 0 ? ? ? ? ? ? ? ? ? 0 0 0 0 ? ? ? 0
	0 0 0 0 ? ? ? ? ? ? ? 0 0 0 0 ? ? ? 0
	0 0 0 0 0 ? ? ? ? ? ? 0 0 0 0 0 ? ? ?
	0 0 ? ? ? ? ? ? 0 0 0 0 0 0 0 0 ? ? ?
	0 0 ? ? ? ? ? ? ? 0 0 0 0 0 0 0 ? ? ?
	0 0 ? ? ? ? ? ? ? ? 0 0 0 0 0 0 0 ? ?
	0 0 0 0 0 0 ? ? ? ? 0 0 0 ? ? ? 0 ? ?
	0 0 0 ? ? ? ? ? ? ? 0 0 0 ? ? ? ? ? ?
	0 0 0 ? ? ? ? ? 0 0 0 ? ? ? ? ? ? ? ?
	0 0 0 ? ? ? ? ? 0 0 0 ? ? ? 0 ? ? ? ?
	0 0 0 0 ? ? ? ? ? ? ? ? ? ? 0 ? ? ? ?
	0 0 0 0 ? ? ? ? ? ? ? ? ? ? 0 ? ? ? ?
	0 0 0 0 ? ? ? ? ? ? ? ? ? ? 0 ? ? ? ?
	""".strip(),
	"""
	1 1 0 1 1 1 0 0 1 1 1 0 0 0 0 1 1 1 0
	x 1 0 1 x 1 0 0 2 x 2 0 0 0 0 1 x 2 1
	1 1 0 2 3 3 1 1 3 x 2 0 0 0 0 1 2 x 1
	0 1 1 2 x x 1 2 x 3 1 0 0 0 0 0 1 1 1
	0 1 x 2 2 2 1 3 x 3 0 0 0 0 0 0 0 0 0
	0 1 1 1 0 0 0 2 x 2 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 1 1 1 1 2 2 1 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 1 x x 1 0 0 0 0 0
	0 0 1 1 1 0 1 1 1 0 1 2 2 1 0 0 0 0 0
	0 0 1 x 2 1 3 x 2 0 0 0 0 0 0 1 1 1 0
	0 0 1 1 2 x 3 x 3 1 1 0 0 0 0 1 x 1 0
	0 0 0 0 1 2 3 2 2 x 1 0 0 0 0 1 1 1 0
	0 0 0 0 0 1 x 1 1 1 1 0 0 0 0 0 1 1 1
	0 0 1 1 2 2 2 1 0 0 0 0 0 0 0 0 1 x 1
	0 0 1 x 2 x 2 1 1 0 0 0 0 0 0 0 1 1 1
	0 0 1 1 2 1 3 x 3 1 0 0 0 0 0 0 0 1 1
	0 0 0 0 0 0 2 x x 1 0 0 0 1 1 1 0 1 x
	0 0 0 1 1 1 1 2 2 1 0 0 0 1 x 1 1 2 2
	0 0 0 1 x 3 2 1 0 0 0 1 1 2 1 1 1 x 2
	0 0 0 1 2 x x 1 0 0 0 1 x 1 0 1 2 3 x
	0 0 0 0 1 2 2 1 1 1 1 1 1 1 0 1 x 3 2
	0 0 0 0 1 1 1 1 2 x 1 1 1 1 0 2 3 x 2
	0 0 0 0 1 x 1 1 x 2 1 1 x 1 0 1 x 3 x
	""".strip()
]

e = ["""
	0 0 0 0 0 0 0 0 ? ? ? ? ? 0 ? ? ? 0 ? ? ?
	0 0 0 0 0 0 0 0 ? ? ? ? ? 0 ? ? ? ? ? ? ?
	0 0 0 0 0 0 0 0 0 0 ? ? ? 0 ? ? ? ? ? ? ?
	0 0 0 0 0 ? ? ? 0 0 ? ? ? 0 ? ? ? ? ? ? 0
	? ? 0 0 0 ? ? ? 0 ? ? ? ? 0 0 ? ? ? ? ? ?
	? ? 0 0 0 ? ? ? 0 ? ? ? 0 0 0 ? ? ? ? ? ?
	? ? ? 0 0 0 0 0 0 ? ? ? 0 0 0 0 0 0 ? ? ?
	? ? ? 0 0 0 0 0 0 0 ? ? ? ? 0 0 ? ? ? 0 0
	? ? ? 0 0 0 0 0 0 0 ? ? ? ? 0 0 ? ? ? 0 0
	""".strip(),
	"""
	0 0 0 0 0 0 0 0 1 x x 2 1 0 1 x 1 0 1 2 x
	0 0 0 0 0 0 0 0 1 2 3 x 1 0 2 2 2 1 2 x 2
	0 0 0 0 0 0 0 0 0 0 2 2 2 0 1 x 1 1 x 2 1
	0 0 0 0 0 1 1 1 0 0 1 x 1 0 1 2 2 2 1 1 0
	1 1 0 0 0 1 x 1 0 1 2 2 1 0 0 1 x 1 1 1 1
	x 1 0 0 0 1 1 1 0 1 x 1 0 0 0 1 1 1 1 x 1
	2 2 1 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 1 1 1
	1 x 1 0 0 0 0 0 0 0 1 2 2 1 0 0 1 1 1 0 0
	1 1 1 0 0 0 0 0 0 0 1 x x 1 0 0 1 x 1 0 0
	""".strip()
]

f = ['''
	0 0 0 0 0 0 0 ? ? ?
	? ? ? ? ? ? 0 ? ? ?
	? ? ? ? ? ? 0 ? ? ?
	? ? ? ? ? ? 0 ? ? ?
	0 0 ? ? ? ? ? ? 0 0
	0 0 ? ? ? ? ? ? ? ?
	0 0 ? ? ? ? ? ? ? ?
	0 0 0 0 ? ? ? ? ? ?
	0 0 0 0 ? ? ? ? ? ?
	0 0 0 ? ? ? ? 0 0 0
	0 0 0 ? ? ? ? 0 0 0
	0 0 0 ? ? ? ? 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	? ? 0 ? ? ? 0 0 0 0
	? ? 0 ? ? ? 0 0 0 0
	? ? ? ? ? ? ? ? ? 0
	? ? ? ? ? ? ? ? ? ?
	? ? ? ? ? ? ? ? ? ?
	0 0 ? ? ? 0 0 ? ? ?
	0 0 ? ? ? ? ? ? ? ?
	0 0 ? ? ? ? ? ? ? ?
	0 0 0 0 0 ? ? ? ? ?
	'''.strip(),
	'''
	0 0 0 0 0 0 0 1 1 1
	1 1 1 1 1 1 0 2 x 2
	1 x 2 2 x 1 0 2 x 2
	1 1 2 x 2 1 0 1 1 1
	0 0 2 2 2 1 1 1 0 0
	0 0 1 x 1 1 x 2 1 1
	0 0 1 1 2 2 2 3 x 2
	0 0 0 0 1 x 1 2 x 2
	0 0 0 0 1 1 1 1 1 1
	0 0 0 1 2 2 1 0 0 0
	0 0 0 1 x x 1 0 0 0
	0 0 0 1 2 2 1 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	1 1 0 1 1 1 0 0 0 0
	x 1 0 1 x 1 0 0 0 0
	2 3 1 3 2 2 1 1 1 0
	x 2 x 2 x 1 1 x 2 1
	1 2 1 2 1 1 1 2 x 1
	0 0 1 1 1 0 0 1 1 1
	0 0 1 x 1 1 1 2 2 2
	0 0 1 1 1 1 x 2 x x
	0 0 0 0 0 1 1 2 2 2
	'''.strip()
] # can be answer
 
for fst, snd in map(globals().get, 'abcdef'):
	open_table = read_table(snd)
	print('sol', str_table(read_table(snd), ' '), sep='\n')
	print('out', solve_mine(fst, snd.count('x')), sep='\n')

