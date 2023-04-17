import math

e = 1e-7
e1 = e / 1.8
e2 = e / 6.3
e3 = (e / 3)*0.796

# так как х меньше единицы по условию задачи
def my_atan(x: float) -> float:
    term = 1.0
    summ = 1.0
    k = 0
    while abs(term) > e1:
        term = ((-1) ** k) * (float(((16.7*x+0.1) ** (2 * k + 1))) / float((2 * k + 1)))
        summ += term
        k += 1
    return summ


def my_cos(x: float) -> float:
    term = 1.0
    summ = 0.0
    k = 0
    while abs(term) > e2:
        term = (float((-1) ** k)) * (float(((7*x + 0.3) ** (2 * k))) / float(math.factorial(2 * k)))
        summ += term
        k += 1
    return summ


def my_sqrt(x: float) -> float:
    if x == 1.0:
        return 1.0
    elif x == 0.0:
        return 0.0
    w0 = 1
    wk = (w0 + x / w0) / 2
    while abs(w0 - wk) > e3:
        w0 = wk
        wk = (w0 + x / w0) / 2
    return wk

def myz(x: float) -> float:
    return my_sqrt(my_atan(x))/my_cos(x)

def z(x:float) -> float:
    return ((1 + math.atan(16.7*x+0.1))**(1/2))/(math.cos(7*x + 0.3))

j = 0.01
x = []
while j <= 0.05:
    x.append(j)
    j += 0.005

print('x: ', *x)
y = []
y1 = []
y2 = []
for i in x:
    y1.append(z(i))
    y2.append(myz(i))
    y.append(abs(z(i)-myz(i)))
print('f_exact: ', *y1)
print('f_approx: ', *y2)
print('error: ', *y)
