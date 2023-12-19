import pandas as pd
import matplotlib.pyplot as plt

plt.style.use("ggplot")
plt.rcParams["figure.figsize"] = (6, 5)

def readFile(fname: str = 'table1.csv',
            inSep: str = ',',
            indexCol: str = "Date"):
    dataframe = pd.read_csv(fname, sep=inSep, index_col = indexCol)
    return dataframe

def printYearData(df, year: str, monthFrom: str, monthTo: str) -> None:
    print(df[year + "-" + monthFrom: year + "-" + monthTo])

def main():
    df = readFile()
    print(df)
    for year in range(2020, 2023):
        printYearData(df, str(year), '01', '12')
    # avg
    print('Среднее значение за все время производства\n')
    print(df.mean())
    
    print('----------------------------------------\n')


    for year in range(2020, 2023):
        tmp = df.loc[str(year) + '-01': str(year) + '-12'].sum()
        tmp.plot(title='Произведено автомобилей за %d г.' % year,
                  kind='bar')
        plt.figure()
    
    pd4 = df.mean().plot(
        title='Среднее число произведенных автомобилей в месяц',
        kind = 'bar')
    
    plt.show()


if __name__ == "__main__":
    main()