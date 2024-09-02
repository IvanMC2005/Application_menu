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
    if (argc > 1)//���� ������������ ����� ��� ������ ���������
    {
        filename = argv[1];
        ifstream fl;
        fl.open(filename);
        if (!fl.is_open())
        {
            cout << "�� ������� ������� ����, ��������  � ���������� ������" << endl;
            return -1;
        }
        fl.close();
    }
    else
    {
        cout << "������� �������� ����� ";
        cin >> filename;
    }
    cout << "������ ���� - " << filename << endl;
    myfile.Setnamefile(filename);
    myfile.readfile(Main);
    datatype dop;
    do
    {
        fill_data<int>("1 - �������� ������� � ������ \n2 - �������� ������ \n3 - ������� ������ ������� � ����� �� ����������� � ������������ ����� � �������� ��������� ���������.\n4 - �������� ���������� � ������� ������� �� ����� � ������������ �������.\n5 - �������� ����� �������� � ������.\n6 - �������� �������� ������\n7 - ����� ������ �������\n8 - ����� �� ����\n", menu, [](int & a) {return a > 0 && a < 9;});
        switch(menu)
        {
            case 1:
            {
                dmenu = 0;
                do
                {
                    fill_data<int>("1 - �������� ������� � ������ ������ 2 - �������� ������� � ����� ������ 3 - ����� �� ������� ", dmenu, [](int &a) {return true ;});
                    switch(dmenu)
                    {
                        case 1:
                        {
                            Main.newnode((datatype *)fillobj(), Main.Getleft());//������ ����� ������ � �������� ��� � ������ ������
                            cout << "���� ������� �������� � ������\n";
                            break;
                        }
                        case 2:
                        {
                            Main.newnode((datatype *)fillobj(), nullptr);//������ ����� ������ � �������� ��� � ����� ������
                            cout << "���� ������� �������� � ������\n";
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
                    cout << "���� ����\n";
                    break;
                }
                dmenu = 0;
                do
                {
                    fill_data<int>("1 - ���������� �� ���� number(�� �����������)\n2 - ���������� �� ���� staton(�� �����������)\n3 - ���������� �� ���� start-time(�� �����������)\n4 - ���������� �� ���� road_time(�� �����������)\n5- ���������� �� ���� tickets(�� �����������)\n6 - ���������� �� ���� weights (�� �����������)\n7 - ���������� �� ���� count(�� �����������)\n8 - ���������� �� ���� number(�� ��������)\n9 - ���������� �� ���� staton(�� ��������)\n10 - ���������� �� ���� start-time(�� ��������)\n 11 - ���������� �� ���� road_time(�� ��������)\n 12 - ���������� �� ���� tickets(�� ��������)\n 13 - ���������� �� ���� weight(�� ��������)\n 14 - ���������� �� ���� count(�� ��������)\n 15 - �����\n", dmenu, [](int &a) {return a>=0 && a < 16;});
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
                    cout << "���� ����\n";
                    break;
                }
                int lowdegree = 0, upperdegree = 0;
                char namestation[10];
                cout << "������� ������ ������� ���������� ���������� �� ������� ���� - ������ - ������� " << endl;
                fill_data<int>("����\n", tip, [](int &a){return a >= 0 ;});
                lowdegree += tip * 3600;
                cout << endl;
                fill_data<int>("������\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                lowdegree += tip * 60;
                cout << endl;
                fill_data<int>("�������\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                lowdegree += tip;
                cout << endl;
                cout << "������� ������� ������� ���������� ���������� " << endl;
                fill_data<int>("����\n", tip, [](int &a){return a >= 0 ;});
                upperdegree += tip * 3600;
                cout << endl;
                fill_data<int>("������\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                upperdegree += tip * 60;
                cout << endl;
                fill_data<int>("�������\n", tip, [](int &a){return a >= 0 && a < 60 ;});
                upperdegree += tip;
                cout << endl;
                cout << "������� �������� ������� ";
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
                    cout << "���� ����\n";
                    break;
                }
                int numbe;
                fill_data<int>("������� ����� �������� ������ ", numbe, [](int & a){return true ;});
                cout << endl;
                get_inf(Main, numbe);
                break;
            }
            case 5:
            {
                dmenu = 0;
                do
                {
                    fill_data<int>("1 - ���������� �� ���� number(�� �����������)\n 2 - ���������� �� ���� staton(�� �����������)\n 3 - ���������� �� ���� start-time(�� �����������)\n 4 - ���������� �� ���� road_time(�� �����������)\n 5- ���������� �� ���� tickets(�� �����������)\n 6 - ���������� �� ���� weights (�� �����������)\n 7 - ���������� �� ���� count(�� �����������)\n8 - ���������� �� ���� number(�� ��������)\n 9 - ���������� �� ���� staton(�� ��������)\n 10 - ���������� �� ���� start-time(�� ��������)\n 11 - ���������� �� ���� road_time(�� ��������)\n 12 - ���������� �� ���� tickets(�� ��������)\n 13 - ���������� �� ���� weight(�� ��������)\n 14 - ���������� �� ���� count(�� ��������)\n 15 - �����\n", dmenu, [](int &a) {return a > 0 & a < 16;});
                    if (dmenu != 15)
                    {
                        Main.includeobject(com[dmenu - 1],fillobj());
                        cout << "���� ������� ��������\n";
                    }
                }
                while(dmenu != 15);
                break;
            }
            case 6:
            {
                if (!Main.Getleft())
                {
                    cout << "���� ����\n";
                    break;
                }
                dmenu = 0;
                int differ;
                string str;
                do
                {
                    fill_data<int>("1 - ��������� �� ������\n2 - ��������� �� �������� �������\n3 - ��������� �� ������� �������\n4 - ��������� �� ������� � ��������\n5- ��������� �� ������� �������\n6 - ��������� �� ���� �����(� ������ ��������� ������)\n7 - ��������� �� ���������� ����������(� ������ � ����������� �������)\n8 - �����", dmenu, [](int &a) {return a >= 0;});
                    switch(dmenu)
                    {
                        case 1:
                        {
                            fill_data<int>("������� ����� ������, ������� ������ �������\n", differ, [](int &a) {return true;});
                            dop.number = differ;
                            if (Main.deleteobj(com[14], &dop)) cout << "������ � ������ � ����� ������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
                            break;
                        }
                        case 2:
                        {
                            fill_data<string>("������� �������� �������, �� ������� ���� �����, ������� ������ �������\n", str, [](string &a) {return true;});
                            strcmp(str.c_str(), dop.staton);
                            if (Main.deleteobj(com[15], &dop)) cout << "������ � ������ � ����� ��������� ����������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
                            break;
                        }
                        case 3:
                        {
                            fill_data<int>("������� ����� ����������� ������, ������� ������ �������\n", differ, [](int &a) {return a > 0;});
                            dop.start_time = differ;
                            if (Main.deleteobj(com[16], &dop)) cout << "������ � ������ � ����� �������� ����������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
                            break;
                        }
                        case 4:
                        {
                            fill_data<int>("������� ����������������� �������� ������, ������� ������ �������\n", differ, [](int &a) {return a > 0;});
                            dop.road_time = differ;
                            if (Main.deleteobj(com[17], &dop)) cout << "������ � ������ � ����� ������������������ �������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
                            break;
                        }
                        case 5:
                        {
                            fill_data<int>("���� �� ������ �� �����, ������� ������ �������(������� ����� ������������� �����, ���� ����)\n", differ, [](int &a) {return true;});
                            if (differ > 1) differ = 1;
                            else differ = 0;
                            dop.tickets = differ;
                            if (Main.deleteobj(com[18], &dop)) cout << "������ � ������ � ������ ���������� ������� ������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
                            break;
                        }
                        case 6:
                        {
                            fill_data<int>("������� ���������� ���������� � ������������ ������, ������� ������ �������\n", differ, [](int &a) {return a > 0;});
                            dop.diff.count_pasengers = differ;
                            if (Main.deleteobj(com[19], &dop)) cout << "������ � ������ � ������ ���������� ������� ������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
                            break;
                        }
                        case 7:
                        {
                            fill_data<int>("������� ��� ����� � �������� ������, ������� ������ �������\n", differ, [](int &a) {return a > 0;});
                            dop.diff.weight = differ;
                            if (Main.deleteobj(com[20], &dop)) cout << "������ � ������ � ������ ���������� ������� ������� ������� �������\n";
                            else cout << "��������� ����� ������\n";
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
                    cout << "���� ����\n";
                    break;
                }
                Main.print();
                break;
            }
        }
        while((ch = getchar())!='\n');
        system("cls");//������� ����� ����� ������� ������ �� ��������� ��������
    }
    while(menu != 8);
    if (myfile.writefile(Main))
        cout << "���� �������\n";
    else
        cout << "���� �� �������\n";
    return 0;
}
