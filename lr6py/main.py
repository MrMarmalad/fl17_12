import pandas as pd
import PySimpleGUI as gui


def main():
    monospace_font = ("Liberation Mono", 8)
    gui.set_options(font=monospace_font)
    layout = [
    [gui.Text("Файл в формате CSV:"), gui.InputText(), gui.FileBrowse()], # values[0]
    [gui.Text("Индексный столбец"), gui.InputText(default_text="Date")], # values[1]
    [gui.Text("Разделитель"), gui.InputText(default_text=',')], # values[2]
    [gui.Text("Статистика за годы (Формат ввода: ГГГГ-ГГГГ или ГГГГ)"), gui.InputText('2020-2023')], # values[3]
    [gui.Text("Поиск по определенному столбцу"), gui.InputText()], # values[4]
    [gui.Output(size=(180,30))], 
    [gui.Submit(), gui.Cancel()]
]
    
    window = gui.Window("Лабораторная работа №6", layout, size=(640, 640))
    # gui.show_debugger_popout_window()
    while True:
        event, values = window.read() # Чтение действий пользователя
        # print ("\n------- Debug: ", event, values,"\n") # Печать для отладки
    
        if event in ("Exit", "Cancel", None): # Отработка команды на завершение работы
            break
        if event == "Submit": # Отработка команды на обработку данных:
            print("_____________________________")
            # print("test")
            fname = values[0]
            indexCol = values[1]
            sep = values[2]
            df = readFile(fname, sep, indexCol)
            print(df)

            years = str(values[3])
            print(len(years))
            # # try:
            if (len(years) == 4):
                print(1)
                yearFrom = int(years[0:4])
                yearTo = yearFrom + 1
                print(yearFrom)
                print(yearTo)
            if (len(years) == 9):
                print(2)
                yearFrom = int(years[0:4])
                yearTo = int(years[5:10])
                print(yearFrom)
                print(yearTo)
            # for year in range(yearFrom, yearTo):
            #     tmp = df.loc[str(year) + '-01': str(year) + '-12'].sum()
            #     print(tmp)

    window.close()


def readFile(fname: str = 'table1.csv',
            inSep: str = ',',
            indexCol: str = "Date"):
    dataframe = pd.read_csv(fname, sep=inSep, index_col = indexCol)
    return dataframe

if __name__ == "__main__":
    main()