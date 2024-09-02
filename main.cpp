#include "header.h"
#include "source.cpp"
int main(int argc, char *argv[])
{
    setlocale(0, "rus");
    int (* com[21]) (datatype *, datatype *) = {cmp_numbers, cmp_stations, cmp_start_time, cmp_road_time, cmp_tickets, cmp_weight, cmp_count,
     notcmp_numbers, notcmp_stations, notcmp_start_time, notcmp_road_time, notcmp_tickets, notcmp_weight, notcmp_count,
                cmp_fornum, cmp_forstations, cmp_forstart_time, cmp_forroad_time, cmp_fortickets, cmp_forweight, cmp_forcount};
    List Main;
    File myfile;
    char ch;
    int menu, dmenu;
    string filename;
    if (argc > 1)//если пользователь задал имя сборке программы
    {
        filename = argv[1];
        ifstream fl;
        fl.open(filename);
        if (!fl.is_open())
        {
            cout << "Не удалось открыть файл, заданный  в параметрах сборки" << endl;
            return -1;
        }
        fl.close();
    }
    else
    {
        cout << "Введите название файла ";
        cin >> filename;
    }
    cout << "Открыт файл - " << filename << endl;
    myfile.Setnamefile(filename);
    myfile.readfile(Main);
    datatype dop;
    do
    {
        fill_data<int>("1 - Добавить элемент в список \n2 - Просмотр списка \n3 - Вывести номера поездов и время их отправления в определенный город в заданном временном интервале.\n4 - Получить информацию о наличии билетов на поезд с определенным номером.\n5 - Добавить новый элеменет в список.\n6 - Удаление элемента списка\n7 - Вывод списка целиком\n8 - Выход из меню\n", menu, [](int & a) {return a > 0 && a < 9;});
        switch(menu)
        {
            case 1:
            {
                dmenu = 0;
                do
                {
                    fill_data<int>("1 - Добавить элемент в начало списка 2 - Добавить элемент в конец списка 3 - выход из подменю ", dmenu, [](int &a) {return true ;});
                    switch(dmenu)
                    {
                        case 1:
                        {
                            Main.newnode((datatype *)fillobj(), Main.Getleft());//создаём новый объект и помещаем его в начало списка
                            cout << "Файл успешно добавлен с список\n";
                            break;
                        }
                        case 2:
                        {
                            Main.newnode((datatype *)fillobj(), nullptr);//создаём новый объект и помещаем его в конец списка
                            cout << "Файл успешно добавлен с список\n";
                            break;
                        }
                    }

                }
                while(dmenu != 3);
                break;
            }
            case 2:
            {
                if (!Main.Getleft())
                {
                    cout << "Файл пуст\n";
                    break;
                }
                dmenu = 0;
                do
                {
                    fill_data<int>("1 - сортировка по полю number(по возрастанию)\n2 - сортировка по полю staton(по возрастанию)\n3 - сортировка по полю start-time(по возрастанию)\n4 - сортировка по полю road_time(по возрастанию)\n5- сортировка по полю tickets(по возрастанию)\n6 - сортировка по полю weights (по возрастанию)\n7 - сортировка по полю count(по возрастанию)\n8 - сортировка по полю number(по убыванию)\n9 - сортировка по полю staton(по убыванию)\n10 - сортировка по полю start-time(по убыванию)\n 11 - сортировка по полю road_time(по убыванию)\n 12 - сортировка по полю tickets(по убыванию)\n 13 - сортировка по полю weight(по убыванию)\n 14 - сортировка по полю count(по убыванию)\n 15 - Выход\n", dmenu, [](int &a) {return a>=0 && a < 16;});
                    if (dmenu != 15) Main.showlist(com[dmenu-1]);
                }
                while(dmenu != 15);
                break;
            }
            case 3:
            {
                int tip;
                if (!Main.Getleft())
                {
                    cout << "Файл пуст\n";
                    break;
                }
                int lowdegree = 0, upperdegree = 0;
                char namestation[10];
                cout << "Введите нижнюю границу временного промежутка по формату часы - минуты - секунды " << endl;
                fill_data<int>("Часы\n", tip, [](int &a){return a >= 0 ;});
                lowdegree += tip * 3600;
                cout << endl;
                fill_data<int>("Минуты\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                lowdegree += tip * 60;
                cout << endl;
                fill_data<int>("Секунды\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                lowdegree += tip;
                cout << endl;
                cout << "Введите верхнюю границу временного промежутка " << endl;
                fill_data<int>("Часы\n", tip, [](int &a){return a >= 0 ;});
                upperdegree += tip * 3600;
                cout << endl;
                fill_data<int>("Минуты\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                upperdegree += tip * 60;
                cout << endl;
                fill_data<int>("Секунды\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                upperdegree += tip;
                cout << endl;
                cout << "Введите название станции ";
                cin >> namestation;
                cout << endl;
                findtrains(Main, lowdegree, upperdegree, namestation);
                system("pause");
                break;
            }
            case 4:
            {
                if (!Main.Getleft())
                {
                    cout << "Файл пуст\n";
                    break;
                }
                int numbe;
                fill_data<int>("Введите номер искомого поезда ", numbe, [](int & a){return true ;});
                cout << endl;
                get_inf(Main, numbe);
                break;
            }
            case 5:
            {
                dmenu = 0;
                do
                {
                    fill_data<int>("1 - сортировка по полю number(по возрастанию)\n 2 - сортировка по полю staton(по возрастанию)\n 3 - сортировка по полю start-time(по возрастанию)\n 4 - сортировка по полю road_time(по возрастанию)\n 5- сортировка по полю tickets(по возрастанию)\n 6 - сортировка по полю weights (по возрастанию)\n 7 - сортировка по полю count(по возрастанию)\n8 - сортировка по полю number(по убыванию)\n 9 - сортировка по полю staton(по убыванию)\n 10 - сортировка по полю start-time(по убыванию)\n 11 - сортировка по полю road_time(по убыванию)\n 12 - сортировка по полю tickets(по убыванию)\n 13 - сортировка по полю weight(по убыванию)\n 14 - сортировка по полю count(по убыванию)\n 15 - Выход\n", dmenu, [](int &a) {return a > 0 & a < 16;});
                    if (dmenu != 15)
                    {
                        Main.includeobject(com[dmenu - 1],fillobj());
                        cout << "Файл успешно добавлен\n";
                    }
                }
                while(dmenu != 15);
                break;
            }
            case 6:
            {
                if (!Main.Getleft())
                {
                    cout << "Файл пуст\n";
                    break;
                }
                dmenu = 0;
                int differ;
                string str;
                do
                {
                    fill_data<int>("1 - сравнение по номеру\n2 - сравнение по названию станции\n3 - сравнение по времени отбытия\n4 - сравнение по времени в движении\n5- сравнение по наличию билетов\n6 - сравнение по весу груза(в случае грузового поезда)\n7 - сравнение по количеству пассажиров(в случае с пассажиским поездом)\n8 - Выход", dmenu, [](int &a) {return a >= 0;});
                    switch(dmenu)
                    {
                        case 1:
                        {
                            fill_data<int>("Введите номер поезда, который хотите удалить\n", differ, [](int &a) {return true;});
                            dop.number = differ;
                            if (Main.deleteobj(com[14], &dop)) cout << "Запись о поезде с таким номером успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                        case 2:
                        {
                            fill_data<string>("Введите название станции, на которую едет поезд, который хотите удалить\n", str, [](string &a) {return true;});
                            strcmp(str.c_str(), dop.staton);
                            if (Main.deleteobj(com[15], &dop)) cout << "Запись о поезде с таким адресатом отправления успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                        case 3:
                        {
                            fill_data<int>("Введите время отправления поезда, который хотите удалить\n", differ, [](int &a) {return a > 0;});
                            dop.start_time = differ;
                            if (Main.deleteobj(com[16], &dop)) cout << "Запись о поезде с таким временем отправления успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                        case 4:
                        {
                            fill_data<int>("Введите продолжительность движения поезда, который хотите удалить\n", differ, [](int &a) {return a > 0;});
                            dop.road_time = differ;
                            if (Main.deleteobj(com[17], &dop)) cout << "Запись о поезде с такой продолжительностью движения успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                        case 5:
                        {
                            fill_data<int>("Есть ли билеты на поезд, который хотите удалить(введите число положительное число, если есть)\n", differ, [](int &a) {return true;});
                            if (differ > 1) differ = 1;
                            else differ = 0;
                            dop.tickets = differ;
                            if (Main.deleteobj(com[18], &dop)) cout << "Запись о поезде с учётом указанного наличия билетов успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                        case 6:
                        {
                            fill_data<int>("Введите количество пассажиров в пассажирском поезде, который хотите удалить\n", differ, [](int &a) {return a > 0;});
                            dop.diff.count_pasengers = differ;
                            if (Main.deleteobj(com[19], &dop)) cout << "Запись о поезде с учётом указанного наличия билетов успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                        case 7:
                        {
                            fill_data<int>("Введите вес груза в грузовом поезде, который хотите удалить\n", differ, [](int &a) {return a > 0;});
                            dop.diff.weight = differ;
                            if (Main.deleteobj(com[20], &dop)) cout << "Запись о поезде с учётом указанного наличия билетов успешно удалена\n";
                            else cout << "Достигнут конец списка\n";
                            break;
                        }
                    }
                }
                while(dmenu != 8);
                break;
            }
            case 7:
            {
                if (!Main.Getleft())
                {
                    cout << "Файл пуст\n";
                    break;
                }
                Main.print();
                break;
            }
        }
        while((ch = getchar())!='\n');
        system("cls");//очищаем экран перед выводом текста на следующей итерации
    }
    while(menu != 8);
    if (myfile.writefile(Main))
        cout << "Файл сохранён\n";
    else
        cout << "Файл не сохранён\n";
    return 0;
}
