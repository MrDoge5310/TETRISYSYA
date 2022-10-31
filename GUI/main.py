from tkinter import *
from tkinter import messagebox


def calculate(weight, height):
    height = height / 100
    bmi = weight / (height * height)
    bmi = round(bmi, 1)
    if bmi < 18.5:
        messagebox.showinfo('Результат:', f'ИМТ = {bmi} соответствует недостаточному весу')
    elif (bmi > 18.5) and (bmi < 24.9):
        messagebox.showinfo('Результат:', f'ИМТ = {bmi} соответствует нормальному весу')
    elif (bmi > 24.9) and (bmi < 29.9):
        messagebox.showinfo('Результат:', f'ИМТ = {bmi} соответствует избыточному весу')
    else:
        messagebox.showinfo('Результат:', f'ИМТ = {bmi} соответствует ожирению')


def check():
    hg = height_input.get()
    kg = weight_input.get()
    if not hg.isdigit() or not kg.isdigit():
        messagebox.showinfo('ERROR', f'Введено неверное значение')
        height_input.delete(0, END)
        weight_input.delete(0, END)
    else:
        calculate(int(kg), int(hg))


window = Tk()
window.title("Индекс массы тела")
window.geometry('500x300')

frame = Frame(window, padx=10, pady=10)
frame.pack(expand=TRUE)

height_label = Label(frame, text='Введите рост:')
height_label.grid(row=3, column=1)

weight_label = Label(frame, text='Введите вес:')
weight_label.grid(row=4, column=1)

height_input = Entry(frame)
height_input.grid(row=3, column=2)

weight_input = Entry(frame)
weight_input.grid(row=4, column=2)

calc_button = Button(frame, text='Расчитать...', command=check)
calc_button.grid(row=5, column=1)

window.mainloop()
