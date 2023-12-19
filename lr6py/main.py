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
    [gui.Text("Месяцы для подсчета (MM-ММ)"), gui.InputText(default_text="01-12")], #values 4
    # [gui.Text("Поиск по определенному столбцу"), gui.InputText()], # values[5]
    [gui.Output(size=(180,30))], 
    [gui.Submit(), gui.Cancel()]]
    
    window = gui.Window("Лабораторная работа №6", layout, size=(640, 640))
    try:
        while True:
            event, values = window.read() # Чтение действий пользователя
            # print ("\n------- Debug: ", event, values,"\n") # Печать для отладки
        
            if event in ("Exit", "Cancel", None): # Отработка команды на завершение работы
                break
            if event == "Submit": # Отработка команды на обработку данных:
                print("_____________________________")
                fname = values[0]
                indexCol = values[1]
                sep = values[2]
                successReading = True
                try:
                    df = readFile(fname, sep, indexCol)
                    print(df)
                except Exception:
                    print("Не удалось считать файл.\nНекорректно введены данные.")
                    continue

                years = str(values[3])
                try:
                    if (len(years) == 4):
                        yearFrom = int(years[0:4])
                        yearTo = yearFrom + 1
                    if (len(years) == 9):
                        yearFrom = int(years[0:4])
                        yearTo = int(years[5:10])
                        if yearFrom > yearTo or yearFrom <= 0 or yearTo <= 0:
                            raise Exception("Неправильно введен диапазон лет")
                except Exception:
                    print("Год введен не в формате ГГГГ-ГГГГ или ГГГГ")
                    continue
                
                try:
                    months = values[4]
                
                    monthFrom = months[0:2]
                    monthTo = months[3:5]
                    if int(monthFrom) > int(monthTo) or int(monthFrom) < 0 or int(monthTo) < 0 or len(months) != 5:
                        raise Exception("Неправильно введены месяцы (%d %d)" % (monthFrom, monthTo))
                except Exception:
                    print("Месяцы введены не в формате ММ-ММ")
                    continue
                

                print("Обрабатываются данные с %d г." % yearFrom)
                print("До %d г." %  yearTo)

                for year in range(yearFrom, yearTo):
                    tmp = df.loc["%d-%s" % (year, monthFrom): "%d-%s" % (year, monthTo)].sum()#str(year) + '-' + str(monthFrom): str(year) + '-' + str(monthTo)].sum()
                    print('Произведено автомобилей за %d г.' % year)
                    print(tmp)
                    print('\n')
                    
                print('Среднее число за указанный период:')
                print(df.loc["%d-%s" % (yearFrom, monthFrom): "%d-%s" % (yearTo-1, monthTo)].mean())

    except Exception as e:
        gui.popup_error_with_traceback(e)
    window.close()


def readFile(fname: str = 'table1.csv',
            inSep: str = ',',
            indexCol: str = "Date"):
    dataframe = pd.read_csv(fname, sep=inSep, index_col = indexCol)
    return dataframe

if __name__ == "__main__":
    main()