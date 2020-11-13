import os
import shutil
import numpy as np
import matplotlib.pyplot as plt
import pylab
from mpl_toolkits.mplot3d import Axes3D


def data_input():
    distance = []
    energy_input = []
    data_inp = open('potential.dat')
    for line in data_inp:
        distance.append(float(line.split()[0]))
        energy_input.append(float(line.split()[1]))
    data_inp.close()
    return distance, energy_input


def check_NaN(par):
    fort7 = open('fort.7', 'r')
    if fort7.read().count(par) == 0:
        fort7.close()
        return True


def fort7():
    fort7 = open('fort.7', 'r')
    fort7_str = fort7.readlines()
    dd = float(fort7_str[1].split('dd=')[1].replace('D', 'E'))
    De = round(float(fort7_str[2].split()[0].replace('D', 'E')), 3)
    Re = round(float(fort7_str[3].split()[0].replace('D', 'E')), 3)
    fort7.close()
    return dd, De, Re



def fort8(start, end, dr, r):
    fort8_file = open('fort.8', 'r')
    fort8_str = fort8_file.read()
    fort8_dat = fort8_str.splitlines()[4:]
    distance8 = []
    energy8 = []
    for line in fort8_dat[(r - start) / dr:(r - end) / dr]:
        if line.split()[1] != 'Infinity':
            distance8.append(float(line.split()[0]))
            energy8.append(float(line.split()[1].replace('D', 'E')))
            # if listTMP_8[0] == start:  # начало
            #     distance8.append(listTMP_8[0])
            #     energy8.append(listTMP_8[1])
            # elif listTMP_8[0] != end and listTMP_8[0] > start:  # всё, что между началом и концом
            #     distance8.append(listTMP_8[0])
            #     energy8.append(listTMP_8[1])
            # elif listTMP_8[0] == end:  # считана последняя точка и цикл закончен
            #     distance8.append(listTMP_8[0])
            #     energy8.append(listTMP_8[1])
            #     break
    return distance8, energy8


def difference_dat(distance, energy_input, distance8, energy8):  # для получения MDC без явного подсчёта по формуле
    difference = []
    for i in range(len(distance)):
        for j in range(len(distance8)):
            if round(distance[i], 2) == distance8[j]:  # выбираем из всех точек fort.8 те, которые были даны в эт.ф.
                DC = energy8[j] - energy_input[i]
                difference.append(abs(DC))
    return round(max(difference), 3)


def plot_ext(distance_ext, energy_ext, name):  # ф-ция для построения на нормальном уч-ке отдельная, т.к. нужны нач.т-ки
    plt.plot(distance_ext, energy_ext, '-', c='b')
    plt.xlabel('r, Å')
    plt.ylabel('V, 1/см')
    plt.savefig(name)
    # plt.close()


def plot(distance8, energy8, distance, energy_input):  # ф-я для построения на +-inf
    plt.plot(distance, energy_input, 'o', c='c')
    plt.plot(distance8, energy8, '-', c='b')
    plt.xlabel('r, Å')
    plt.ylabel('V, 1/см')
    plt.savefig(os.path.join(path, 'U(r)8.png'))
    plt.close()


def moving(path):  # перемещение в нужную папку  файлов
    shutil.move('fort.8', path)
    shutil.move('fort.7', path)
    shutil.move('out.txt', path)
    shutil.move('data_betaFit.dat', path)


def makeData():  # создание матриц для q и n
    x = np.arange(1, 9, 1)
    y = np.arange(1, 9, 1)
    xgrid, ygrid = np.meshgrid(x, y)
    return xgrid, ygrid


def three_d_plot(par, name):  # построение и сохранение
    q, n = makeData()
    fig = pylab.figure()
    axes = Axes3D(fig)
    axes.plot_surface(q, n, par)
    pylab.savefig(name)
    pylab.close()
    # shutil.move(name, r'Re_p 0, De0, Vmin0\Итог')


De = np.zeros((8, 8))  # заготовки для таблиц
MDC = np.zeros((8, 8))
dd = np.zeros((8, 8))
Re = np.zeros((8, 8))
NPR = 591  # параметры для вывода в fort.8
r = 0.1  # (можно попробовать сделать их ввод при запуске)
dr = 0.01
distance, energy_input = data_input()  # считывание первоначальных точек
data_input1 = open('data_betaFit1.dat', 'r')  # счит-е эталонного файла
for q in range(1, 9):
    for n in range(1, 9):
        data_input = open('data_betaFit.dat', 'a')  # создание вводного файл
        shutil.copy('data_betaFit1.dat', 'data_betaFit.dat')
        data_input.write('\n' + str(q) + ' 0 0 ' + str(n) + ' 0' + '\n' + str(NPR) + ' ' + str(r) + ' ' + str(dr))
        data_input.close()
        data_input1.close()
        folder_name_1 = 'Re_p 0, De0, Vmin0'
        folder_name_2 = 'q = {}\q = {}, n = {}'.format(q, q, n)
        path = os.path.join(folder_name_1, folder_name_2)
        if os.path.exists(path) == False:
            os.makedirs(path)
        os.system('betaFit.exe <data_betaFit.dat >out.txt')
        # moving(path)
        if check_NaN('NaN') == True and check_NaN('Infinity') == True:  # проверка на возможность аппроксимации
            dd[q - 1][n - 1], De[q - 1][n - 1], Re[q - 1][n - 1] = fort7()  # считывание параметров из fort.7
            distance8, energy8 = fort8(1.3, 4, dr, r)  # счит-е т-к для графика на начальном участке
            distance_minf, energy_minf = fort8(0.1, 2, dr, r)  # счит-е т-к на -inf
            distance_pinf, energy_pinf = fort8(3.95, 6, dr, r)  # счит-е т-к на +inf
            MDC[q - 1][n - 1] = difference_dat(distance, energy_input, distance8, energy8)  # получение MDC
            plot(distance8, energy8, distance, energy_input)
            plot_ext(distance_minf, energy_minf,
                     os.path.join(path, 'U(r)_minf.png'))  # построение графиков и их сохранение
            plot_ext(distance_pinf, energy_pinf, os.path.join(path, 'U(r)_pinf.png'))
        else:  # если аппр-я не удалась, то можно передать NaN или 0 (я покажу оба варианта)
            dd[q - 1][n - 1] = np.max(np.abs(dd))
            De[q - 1][n - 1] = np.max(np.abs(De))
            MDC[q - 1][n - 1] = np.max(np.abs(MDC))
            Re[q - 1][n - 1] = np.max(np.abs(Re))

# os.makedirs(r'Re_p 0, De0, Vmin0\Итог')  # создание папки для результатов
np.savetxt(r'Re_p 0, De0, Vmin0\Итог\table_dd.txt', dd)  # сохранение таблиц
np.savetxt(r'Re_p 0, De0, Vmin0\Итог\table_MDC.txt', MDC)
np.savetxt(r'Re_p 0, De0, Vmin0\Итог\table_De.txt', De)
np.savetxt(r'Re_p 0, De0, Vmin0\Итог\table_Re.txt', Re)
three_d_plot(dd, 'dd(q, n).png')  # построение поверхностей
three_d_plot(MDC, 'MDC(q, n).png')
three_d_plot(De, 'De(q, n).png')
three_d_plot(Re, 'Re(q, n).png')

print(np.argmin(dd))
print(np.min(np.abs(De)))
print(np.argmin(MDC))
print(np.min(Re))