#include "header.h"
void List::print()
{
    node * temp = listleft;
    while(temp)
    {
        cout << "Номер станции  ";
        cout << "Название станции   ";
        cout << "Время отправления   ";
        cout << "Время в пути   ";
        cout << "Наличие билетов  ";
        cout << " Количество пассажиров  ";
        cout << " Вес груза";
        cout << endl;
        cout  << left << setw(20) << temp->data->number;
        cout  << left << setw(20) << temp->data->staton;
        cout  << left  << temp->data->start_time / 3600 << " : " << (temp->data->start_time % 3600) / 60 << " : " << setw(8) << ((temp->data->start_time % 3600) % 60);
        cout  << left << temp->data->road_time / 3600 << " : " << (temp->data->road_time % 3600) / 60 << " : " << setw(11) << ((temp->data->road_time % 3600) % 60);

        if (temp->data->type == 1)
        {
            cout  << left << setw(37) << temp->data->tickets;
            cout << temp->data->diff.weight;
        }
        else
        {
            cout  << left << setw(18) << temp->data->tickets;
            cout  << temp->data->diff.count_pasengers;
        }
        cout << endl;
        temp = temp->next;
    }
}
int List::deleteobj (int (*f) (datatype *, datatype *), datatype* abs)
    {
        int flag = 0;
        if (listleft != nullptr)
        {
            node * temp = listleft;
            while(temp)
            {
                if (f(temp->data, abs))
                {
                    int ok;
                    cout << "Номер станции  ";
                    cout << "Название станции   ";
                    cout << "Время отправления   ";
                    cout << "Время в пути   ";
                    cout << "Наличие билетов  ";
                    cout << " Количество пассажиров  ";
                    cout << " Вес груза";
                    cout << endl;
                    cout  << left << setw(20) << temp->data->number;
                    cout  << left << setw(20) << temp->data->staton;
                    cout  << left << setw(19) << temp->data->start_time;
                    cout  << left << setw(17) << temp->data->road_time;
                    if (temp->data->type == 1)
                    {
                        cout  << left << setw(37) << temp->data->tickets;
                        cout << temp->data->diff.weight;
                    }
                    else
                    {
                        cout  << left << setw(18) << temp->data->tickets;
                        cout  << temp->data->diff.count_pasengers;
                    }
                    cout << endl;
                    fill_data<int>("Удалить данную запись?(0/1)\n", ok, [](int &a){return a == 0 || a == 1 ;});
                    if (ok == 0)
                    {
                        temp = temp->next;
                        continue;
                    }
                    break;
                }
                temp = temp->next;
            }
            if (temp)
            {
                flag = 1;
                deletenode(temp);
            }
        }
        else
        {
            cout << "Список пуст\n";
        }
        if (flag == 1) return 1;
        return 0;
    }
List::List (const List &old)
    {
        datatype* datad;
        cout << "Запуск конструктора копирования\n";
        if (this == &old)
            return;
        this->listleft = nullptr;
        this->listright = nullptr;
        node * temp = old.listleft;
        while(temp)
        {
            datad = new(nothrow) datatype;
            if (datad == nullptr)
            {
                cout << "Ошибка выделения памяти\n";
                return ;
            }
            *datad = *temp->data;
            this->newnode(datad, nullptr);
            temp = temp->next;
        }
    }
List::List()
    {
        cout << "Запуск конструктора без параметров\n";
        listleft = nullptr;
        listright = nullptr;
    }
List::~List()
    {
        cout << "Запуск деструктора\n";
        if (listleft == nullptr)
        {
            cout << "left == nullptr\n";
            return;
        }
        node * temp = listleft;
        listleft = listleft->next;
        while(listleft)
        {
            delete temp->data;
            delete temp;
            temp = listleft;
            listleft = listleft->next;
        }
        delete temp->data;
        delete temp;
    }
int List::newnode(datatype *tipe, node * curr)
    {
        node * temp = new(nothrow) node;
        if (temp == nullptr)
        {
            cout << "Ошибка выделения памяти\n";
            return -1;
        }
        temp->data = tipe;
        if (curr != nullptr)
        {
            if (curr == listleft) //цепляем созданный узел у началу
            {
                temp->next = listleft;
                listleft->prev = temp;
                temp->prev = nullptr;
                listleft = temp;
            }
            else // вставляем созданный узел перед переданным указателем
            {
                curr->prev->next = temp;
                temp->prev = curr->prev;
                temp->next = curr;
                curr->prev = temp;
            }
        }
        else if (listright != nullptr)//проверка на пустоту списка если хотим прицепить узел в конец
        {
            listright->next = temp;
            temp->prev = listright;
            listright = temp;
            listright->next = nullptr;
        }
        else // список пуст
        {
            listleft = temp;
            listright = temp;
            listleft->prev = nullptr;
            listright->next = nullptr;
        }
        return 1;
    }
void List::includeobject(int (*f) (datatype *, datatype *), datatype *abse)
    {
        List exam;
        node * temp, * temp2;
        datatype * tmpl;
        if (listleft != nullptr)//если текущий список не пуст - копируем его в exam и добавляем новый элемент
        {
            node * temp = listleft;
            node * dtemp;
            tmpl = new datatype;
            *tmpl = *temp->data;
            exam.newnode(tmpl, nullptr);
            temp = temp->next;
            while(temp)
            {
                dtemp = exam.Getleft();
                while(dtemp && (f(temp->data, dtemp->data) == 1))
                {
                    dtemp = dtemp->next;
                }
                tmpl = new datatype;
                *tmpl = *temp->data;
                exam.newnode(tmpl, dtemp);
                temp = temp->next;
            }
            dtemp = exam.Getleft();
            while(dtemp && (f(dtemp->data, abse) == 1))
            {
                dtemp = dtemp->next;
            }
            exam.newnode(abse, dtemp);
        }
        else
        {
            exam.newnode(abse, nullptr);
            exam.listright = exam.listleft;
            exam.listleft->prev = nullptr;
            exam.listright->next = nullptr;
            *this = exam; // изменяем текущий список
            return;
        }
        *this = exam; // изменяем текущий список
        temp = exam.Getleft();
        temp2 = temp->next;
        delete temp;
        while(temp2)
        {
            temp = temp2;
            temp2 = temp2->next;
            delete temp;
        }
        exam.Setleft(nullptr); exam.Setright(nullptr); // обнуляем дескриптор, чтобы не удалить данные в деструкторе
    }
node * List::Getleft()
    {
        return listleft;
    }
node * List::Getright()
    {
        return listright;
    }
void List::Setleft(node * temp)
    {
        listleft = temp;
    }
void List::Setright(node * temp)
    {
        listright = temp;
    }
void List::deletenode(node * curr)
    {
        if (curr == listleft)
        {
            listleft = listleft->next;
            delete curr->data;
            delete curr;
        }
        else if (this->listright == this->listleft)
        {
            curr = listright;
            listleft = listright = nullptr;
            delete curr->data;
            delete curr;
        }
        else if(curr == listright)
        {
            listright = listright->prev;
            delete curr->data;
            delete curr;
        }
        else if (curr != nullptr)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr->data;
            delete curr;
        }
        else
        {
            cout << "Нельзя удалить нулевой указатель\n"; //??? Обычный пользователь не поймет что это
        }
    }
void List::showlist(int (*f) (datatype *, datatype*))
    {
        setlocale(0, "rus");
        int i = 0, flag = 0, k = 0, max_len = 0;
        char c;
        int ch;
        node * temp = listleft, * temp2;
        List exam;
        node * dtemp;
        exam.newnode(temp->data, nullptr);
        temp = temp->next;
        while(temp)
        {
            dtemp = exam.Getleft();
            while(dtemp && (f(temp->data, dtemp->data) == 1))
            {
                dtemp = dtemp->next;
            }
            exam.newnode(temp->data, dtemp);
            temp = temp->next;
        }
        temp = exam.Getleft();
        while(temp)
        {
            temp = temp->next;
            max_len++;
        }
        temp = exam.Getleft();
        do
        {
            system("cls");
            cout << "Листание с помощью символов: '1',  '2', для остановки ввести 0" << endl;
            cin >> ch;
            if (ch != 1 && ch != 2 && ch != 0) cin.setstate(ios_base::failbit);
            while((c = getchar())!='\n');
            while(cin.fail())
            {
                cin.clear();
                cout << "Листание с помощью символов: '1',  '2', для остановки ввести 0" << endl;
                cin >> ch;
                if (ch != 1 && ch != 2 && ch != 0) cin.setstate(ios_base::failbit);
                while((c = getchar())!='\n');
            }
            if (ch == 1 && k <= max_len)
            {
                k += STEP;
            }
            else if (ch == 2 && k >= 5)
            {
                k -= STEP;
            }
            else if (ch == 0)
            {
                flag = 1;
                k = 0;
            }
            if (k != 0)     //По-хорошему списку должно быть все равно, что за данные в нем хранятся...
            {
                cout << "Номер станции  ";
                cout << "Название станции   ";
                cout << "Время отправления   ";
                cout << "Время в пути   ";
                cout << "Наличие билетов  ";
                cout << " Количество пассажиров  ";
                cout << " Вес груза";
                cout << endl;
            }
            i = 0;
            temp = exam.Getleft();
            while(i++ < k - STEP)
                temp = temp->next;
            i = 0;
            while(temp && k)
            {
                if (i == STEP) break;
                cout  << left << setw(20) << temp->data->number;
                cout  << left << setw(15) << temp->data->staton;
                cout  << left  << temp->data->start_time / 3600 << " : " << (temp->data->start_time % 3600) / 60 << " : " << setw(11) << ((temp->data->start_time % 3600) % 60);
                cout  << left << temp->data->road_time / 3600 << " : " << (temp->data->road_time % 3600) / 60 << " : " << setw(11) << ((temp->data->road_time % 3600) % 60);
                if (temp->data->type == 1)
                {
                    cout  << left << setw(37) << temp->data->tickets;
                    cout << temp->data->diff.weight;
                }
                else
                {
                    cout  << left << setw(18) << temp->data->tickets;
                    cout  << temp->data->diff.count_pasengers;
                }
                cout << endl;
                temp = temp->next;
                i++;
            }
            system("pause");
        }
        while(flag != 1);
            /*node * temp = Getleft();
            while(temp)
            {
                cout << "Номер станции  ";
                cout << "Название станции   ";
                cout << "Время отправления   ";
                cout << "Время в пути   ";
                cout << "Наличие билетов  ";
                cout << " Количество пассажиров  ";
                cout << " Вес груза";
                cout << endl;
                cout  << left << setw(20) << temp->data->number;
                cout  << left << setw(20) << temp->data->staton;
                cout  << left << setw(19) << temp->data->start_time;
                cout  << left << setw(17) << temp->data->road_time;
                if (temp->data->type == 1)
                {
                    cout  << left << setw(37) << temp->data->tickets;
                    cout << temp->data->diff.weight;
                }
                else
                {
                    cout  << left << setw(18) << temp->data->tickets;
                    cout  << temp->data->diff.count_pasengers;
                }
                cout << endl;
                temp = temp->next;
            }*/
        temp = exam.Getleft();
        temp2 = temp->next;
        delete temp;
        while(temp2)
        {
            temp = temp2;
            temp2 = temp2->next;
            delete temp;
        }
        exam.Setleft(nullptr);
        exam.Setright(nullptr);
    }
List& List::operator= (List& old)
    {
        datatype * datap;
        if (this == &old)
            return old;
        node * temp;
        temp = old.listleft;
        if (this->listleft)// если список не пуст удаляем его
        {
            temp = this->listleft;
            this->listleft = this->listleft->next;
            while(temp->next)
            {
                delete temp->data;
                delete temp;
                temp = this->listleft;
                this->listleft = this->listleft->next;
            }
            delete temp->data;
            delete temp;
            this->listleft = nullptr;
            this->listright = nullptr;
        }
        temp = old.listleft;
        temp = old.listleft;
        while(temp)
        {
            datap = new(nothrow) datatype;
            if (datap == nullptr)
            {
                cout << "Ошибка выделения памяти\n";
                throw domain_error("memory allocation error");
            }
            *datap = *temp->data;
            this->newnode(datap, nullptr);
            temp = temp->next;
        }
        return *this;
    }
void File::Setnamefile(string name)
    {
        namefile = name;
    }
void File::readfile(List & temp)
    {
        ifstream file;
        file.open(namefile);
        datatype *data;
        data = new(nothrow) datatype;
        if (data == nullptr)
        {
            cout << "Ошибка выделения памяти\n";
            return;
        }
        if (!file.is_open())
        {
            temp.Setleft(nullptr);
            temp.Setright(nullptr);
        }
        while(file.read((char *)data, sizeof(datatype)))
        {
            temp.newnode(data, nullptr);
            data = new(nothrow) datatype;
            if (data == nullptr)
            {
                cout << "Ошибка выделения памяти\n";
                return ;
            }
        }
        file.close();
    }
int File::writefile(List& beg)
    {
        ofstream file;
        file.open(namefile);
        if (!file.is_open())
        {
            cout << "Не удалось открыть файл для записи в него списка\n";
            return 0;
        }
        node * temp = beg.Getleft();
        while(temp)
        {
            if (file.write((char *)temp->data, sizeof(datatype)))
                temp = temp->next;
            else
                return 0;
        }
        return 1;
    }

int cmp_fornum(datatype * a, datatype * b)
{
    return a->number == b->number;
}
int cmp_forroad_time(datatype * a, datatype * b)
{
    return a->road_time == b->road_time;
}
int cmp_forstart_time(datatype * a, datatype * b)
{
    return a->start_time == b->start_time;
}
int cmp_forstations(datatype * a, datatype * b)
{
    return !strcmp(a->staton, b->staton);
}
int cmp_fortickets(datatype * a, datatype * b)
{
    return a->tickets == b->tickets;
}
int cmp_forweight(datatype * a, datatype * b)
{
    return a->diff.weight == b->diff.weight;
}
int cmp_forcount (datatype * a, datatype * b)
{
    return a->diff.count_pasengers == b->diff.count_pasengers;
}
int cmp_numbers(datatype * data1, datatype * data2)
{
    return (data1->number >= data2->number) + (data1->number == data2->number);
}
int cmp_count(datatype * data1, datatype * data2)
{
    return (data1->diff.count_pasengers >= data2->diff.count_pasengers) + (data1->diff.count_pasengers == data2->diff.count_pasengers);
}
int cmp_weight(datatype * data1, datatype * data2)
{
    return (data1->diff.weight >= data2->diff.weight) + (data1->diff.weight == data2->diff.weight);
}
int cmp_stations(datatype * data1, datatype * data2)
{
    return (strlen(data1->staton) >= strlen(data2->staton)) + (strlen(data1->staton) == strlen(data2->staton));
}
int cmp_start_time(datatype * data1, datatype * data2)
{
    return (data1->start_time >= data2->start_time) + (data1->start_time == data2->start_time);
}
int cmp_road_time(datatype * data1, datatype * data2)
{
    return (data1->road_time >= data2->road_time) + (data1->road_time == data2->road_time);
}
int cmp_tickets(datatype * data1, datatype * data2)
{
    return (data1->tickets >= data2->tickets) + (data1->tickets == data2->tickets);
}
int notcmp_numbers(datatype * data1, datatype * data2)
{
    return !(data1->number >= data2->number);
}
int notcmp_stations(datatype * data1, datatype * data2)
{
    return !(strlen(data1->staton) >= strlen(data2->staton));
}
int notcmp_start_time(datatype * data1, datatype * data2)
{
    return !(data1->start_time >= data2->start_time);
}
int notcmp_count(datatype * data1, datatype * data2)
{
    return !(data1->diff.count_pasengers >= data2->diff.count_pasengers);
}
int notcmp_weight(datatype * data1, datatype * data2)
{
    return !(data1->diff.weight >= data2->diff.weight);
}
int notcmp_road_time(datatype * data1, datatype * data2)
{
    return !(data1->road_time >= data2->road_time);
}
int notcmp_tickets(datatype * data1, datatype * data2)
{
    return !(data1->tickets >= data2->tickets);
}
void get_inf(List &temp, int numer)
{
    char flag = 0;
    node * terter = temp.Getleft();
    while(terter)
    {
        if (terter->data->number == numer && terter->data->tickets == 1)
        {
            cout << "На поезд с данным номером есть билеты\n";
            flag = 1;
        }
        terter = terter->next;
    }
    if (flag == 0)
    {
        cout << "На указанный поезд нет билетов или не удалось найти этот поезд\n";
    }
}
void findtrains(List temp, int lowdegree, int upperdegree, const char * townname)
{
    node * tpler = temp.Getleft();
    char flag = 0;
    while(tpler)
    {
        if ((tpler->data->start_time > lowdegree) && (tpler->data->start_time < upperdegree) && !strcmp(townname, tpler->data->staton))
        {
            cout << "Поезд под номером " << tpler->data->number << " отправляется в указанный город в указанном промежутке времени\n";
            flag = 1;
        }
        else if (((tpler->data->start_time <= lowdegree) || (tpler->data->start_time >= upperdegree)) && !strcmp(townname, tpler->data->staton))
        {
            cout << "Данный поезд отправляется в другой промежуток времени\n";
            flag = 1;
        }
        tpler = tpler->next;
    }

    if (flag == 0) cout << "По запросу ничего не найдено\n";
}
node * addobj(List &dat, datatype *datar)
{
    node * temp = new(nothrow) node;
    temp->data = datar;
    temp->next = dat.listleft;
    temp->prev = nullptr;
    dat.listleft = temp;
    return temp;
}
datatype* fillobj()
{
    datatype* temp = new(nothrow) datatype;
    int tip;
    char ch;
    unsigned int pace;
    cout << "Введите номер станции ";
    cin >> temp->number;
    if (temp->number < 0)
        cin.setstate(ios_base::failbit);
    cout << endl;
    while((ch = getchar())!='\n');
    while(cin.fail())
    {
       cin.clear();
       cout << "Введите номер станции ";
       cin >> temp->number;
       while((ch = getchar())!='\n');
       if (temp->number < 0)
            cin.setstate(ios_base::failbit);
       cout << endl;
    }
    cout << "Введите название станции ";
    SetConsoleCP(1251);
    cin >> temp->staton;
    SetConsoleCP(866);
    cout << endl;
    while((ch = getchar())!='\n');
    while(cin.fail())
    {
       cin.clear();
       cout << "Введите название станции ";
       SetConsoleCP(1251);//изменяю кодировки для корректного ввода русского текста
       cin >> temp->staton;
       SetConsoleCP(866);//возвращаю прежню кодировку
       while((ch = getchar())!='\n');
       cout << endl;
    }
    temp->start_time = 0;
    cout << "Введите время отправления поезда по формату часы - минуты - секунды " << endl;
    fill_data<int>("Часы\n", tip, [](int &a){return a >= 0 ;});
    temp->start_time += tip * 3600;
    cout << endl;
    fill_data<int>("Минуты\n", tip, [](int &a){return a >= 0 && a < 60 ;});
    temp->start_time += tip * 60;
    cout << endl;
    fill_data<int>("Секунды\n", tip, [](int &a){return a >= 0 && a < 60;});
    temp->start_time += tip;
    cout << endl;
    temp->road_time = 0;
    cout << "Введите время движения поезда по формату часы - минуты - секунды " << endl;
    fill_data<int>("Часы\n", tip, [](int &a){return a >= 0 ;});
    temp->road_time += tip * 3600;
    cout << endl;
    fill_data<int>("Минуты\n", tip, [](int &a){return a >= 0 && a < 60 ;});
    temp->road_time += tip * 60;
    cout << endl;
    fill_data<int>("Секунды\n", tip, [](int &a){return a >= 0 && a < 60 ;});
    temp->road_time += tip;
    cout << endl;
    cout << "Есть ли билеты на этот поезд(>=1 - есть <0 - нет) ";
    cin >> pace;
    cout << endl;
    while((ch = getchar())!='\n');
    while(cin.fail())
    {
       cin.clear();
       cout << "Есть ли билеты на этот поезд(>=1 - есть <0 - нет) ";
       cin >> pace;
       while((ch = getchar())!='\n');
       cout << endl;
    }
    if (pace >= 1)
        temp->tickets = 1;
    else
        temp->tickets = 0;
    cout << "Какой тип поезда вас интересует 0 - пассажирский 1 - грузовой ";
    cin >> tip;
    if (tip != 0 && tip != 1)
        cin.setstate(ios_base::failbit);
    cout << endl;
    while((ch = getchar())!='\n');
    while(cin.fail())
    {
        cin.clear();
        cout << "Какой тип поезда вас интересует 0 - пассажирский 1 - грузовой ";
        cin >> tip;
        while((ch = getchar())!= '\n');
        if ((tip != 0) && (tip != 1))
            cin.setstate(ios_base::failbit);
        cout << endl;
    }
    temp->type = tip;
    if (tip == 0)
    {
        cout << "Сколько пассажиров в этом поезде? ";
        cin >> temp->diff.count_pasengers;
        if (temp->diff.count_pasengers < 0)
            cin.setstate(ios_base::failbit);
        while((ch = getchar())!='\n');
        cout << endl;
        while(cin.fail())
        {
           cin.clear();
           cout << "Сколько пассажиров в этом поезде? ";
           cin >> temp->diff.count_pasengers;
           if (temp->diff.count_pasengers < 0)
            cin.setstate(ios_base::failbit);
           while((ch = getchar())!='\n');
           cout << endl;
        }
    }
    else
    {
        cout << "Сколько составляет вес груза в этом поезде ";
        cin >> temp->diff.weight;
        if (temp->diff.weight < 0)
            cin.setstate(ios_base::failbit);
        while((ch = getchar())!='\n');
        cout << endl;
        while(cin.fail())
        {
           cin.clear();
           cout << "Сколько составляет вес груза в этом поезде ";
           cin >> temp->diff.weight;
           if (temp->diff.weight < 0)
            cin.setstate(ios_base::failbit);
           while((ch = getchar())!='\n');
           cout << endl;
        }
    }
    return temp;
}
template <typename T>
void fill_data(string str, T &temp, function<bool(T&)> f)
{
    char c;
    cout << str << endl;
    cin >> temp;
    if (!f(temp))
        cin.setstate(ios_base::failbit);
    while((c = getchar()) != '\n');
    while(cin.fail())
    {
        cin.clear();
        cout << str << endl;
        cin >> temp;
        if (!f(temp))
            cin.setstate(ios_base::failbit);
        while((c = getchar()) != '\n');
    }
}
template void fill_data(string str, int &temp, function<bool(int&)> f);
template void fill_data(string str, char &temp, function<bool(char&)> f);
template void fill_data(string str, string &temp, function<bool(string&)> f);
