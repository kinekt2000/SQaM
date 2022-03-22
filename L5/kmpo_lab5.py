import numpy as np

X_uniform = np.random.uniform(0, 20, 18)
X_uniform = np.sort(X_uniform)
# print(X_uniform)

t = np.random.uniform(0, 1, 18)
X_exp = -np.log(t)/0.1
X_exp = np.sort(X_exp)
# print(X_exp)

t = np.random.uniform(0, 1, 24)
X_rel = 8*np.sqrt(-2*np.log(t))
X_rel = np.sort(X_rel)
# print(X_rel)


def process(arr):

    print("Dataset: ")
    print("--------------")
    for (i, v) in enumerate(arr):
        print(i+1, round(v, 3))

    i_arr = np.arange(1, len(arr)+1)
    A = np.sum(arr * i_arr)/np.sum(arr)
    n = len(arr)
    print('-------------')
    print("A =", round(A, 3))
    print("A > (n+1)/2", A, (n+1)/2, A > (n+1)/2)

    f_m = []
    g_m = []
    delta_fg = []
    for m in range(n+1, n+1+6):
        f_m.append(
            np.sum(1/(m-i_arr))
        )
        g_m.append(n/(m-A))

        delta_fg.append(abs(f_m[-1]-g_m[-1]))

    print("\nF, G, |F-G| Table:")
    print('------------')
    for (i, row) in enumerate(zip(f_m, g_m, delta_fg)):
        print(n+i+1, *map(lambda r: round(r, 3), row))
    print('------------')

    min_m = n + np.argmin(delta_fg) + 1
    B = min_m - 1
    print("Min m at ", min_m)
    print("B =", B)

    K = n/np.sum((B-i_arr+1)*arr)
    print("K =", round(K, 3))
    print('-------------')

    next_arr = []
    print("Next dataset:")
    i = n+1
    while len(next_arr) == 0 or next_arr[-1] != np.inf:
        next_arr.append(1/(K*(B-(i-1))))
        print(i, round(next_arr[-1], 3))
        i += 1

    next_arr = next_arr[:-1]

    print("Total test time:", round(sum(arr) + sum(next_arr), 3))

process(X_rel)
