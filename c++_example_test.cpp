#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// Course��
class Course{
    public:
        int CourseId;   //��ʾ�γ̱��
        string courseName;  //��ʾ�γ�����
        int credit; //��ʾ�γ̵�ѧ��
        Course(int CourseId, string courseName, int credit){
            this -> CourseId = CourseId;
            this -> courseName = courseName;
            this -> credit = credit;
        }   //���캯�������γ�
};

// Person��
class Person{
    public:
        string name;    //����
        int age;    //����
        Person(string name, int age){
            this -> name = name;
            this -> age = age;
        }   //���캯������������Ϣ
};

// Teacher��
class Teacher : virtual public Person{
    public:    
        int teacherId;  //��ʾ��ʦID
        int *TeachCourse;   //��ʦ�����ڿγ�ID�ļ���
        int TeachCourseNum; //��ʦ�����ڿγ̵�����
        Teacher(string name, int age, int teacherId, int n) : Person(name, age){
            this -> teacherId = teacherId;
            this -> TeachCourse = new int[n];
            this -> TeachCourseNum = n;
        }   //������ʦ��Ϣ
        void teach(){
            cout << "I am a teacher, I teach my student." << endl;
        }
        void setCourseId(Course course){
            for ( int i = 0; i < this -> TeachCourseNum; i++ ) {
                if ( this -> TeachCourse[i] == 0 ) {
                    this -> TeachCourse[i] = course.CourseId;
                    break;
                }
            }
        }   //������ʦ�����γ�
};

// Student��
class Student : virtual public Person{
    public:
        int number; //ѧ��ѧ��
        static int courseCount; //��ѡ�γ̵���Ŀ
        static int courseCredit;    //��ѡ�γ̵�ѧ��
        int *myCourses; //�����ѡ�γ̵�id������
        int minCourseNum;   //ÿѧ������ѡ�εĿγ�����
        Student(string name, int age, int number, int n) : Person(name, age){
            this -> number = number;
            this -> myCourses = new int[n];
            this -> minCourseNum = n;
        }   //����ѧ����Ϣ
        void selectCourse(Course course){
            if ( courseCount < this -> minCourseNum ) {
                this -> myCourses[courseCount] = course.CourseId;
                courseCount++;
                courseCredit += course.credit;
            }
        }   //ѡ��
        void deleteCourse(Course course){
            for ( int i = 0; i < courseCount; i++ ) {
                if ( this -> myCourses[i] == course.CourseId ) {
                    for ( int j = i + 1; j < courseCount; j++ ) {
                        this -> myCourses[j-1] = this -> myCourses[j];
                    }
                    courseCount--;
                    courseCredit -= course.credit;
                    break;
                }
            }
        }   //�˿�
        bool judge(){
            return courseCount >= 5;
        }   //�ж�ѧ����ѧ���Ƿ����ɿγ�
        int creditSum(){
            return courseCredit;
        }
};

int Student::courseCount = 0, Student::courseCredit = 0;   //����ѧ����ʼѡ��������ѧ��Ϊ0

// TeachingAssistant��
class TeachingAssistant : public Teacher, public Student{
    public:
        TeachingAssistant(string name, int age, int teacherId, int n, int number, int m) : 
            Person(name, age), Teacher(name, age, teacherId, n), Student(name, age, number, m){}
        void teach(){
            cout << "I am a teaching assistant, I help my teacher teach his students." << endl;
        }
        void selectCourse(Teacher t){
            cout << "���Ѿ�ѡ������" << t.name << "��ʦ�Ŀγ����̡�" << endl;
        }
        void deleteCourse(Teacher t){
            cout << "���Ѿ��˳�����" << t.name << "��ʦ�Ŀγ����̡�" << endl;
        }
};

int main(){
    // ����΢���֣�����������Ӣ�������ƣ������������ſγ�(��ţ��γ����ƣ�ѧ��)
    Course Calculus(1, "Calculus", 6);
    Course HumanCivilization(2, "HumanCivilization", 1);
    Course English(3, "English", 4);
    Course Programming(4, "Programming", 4);
    Course MilitaryTheory(5,"MilitaryTheory", 2);

    // ������ʦ����(���������䣬�̹��ţ����ڿγ�����)
    Teacher t1("Mr.Tang", 35, 101, 3);
    Teacher t2("Mr.Chen", 29, 102, 2);
    Teacher t3("Ms.Wei", 30, 103, 2);
    Teacher t4("Mr.Su", 29, 104, 2);

    // �����γ�id
    t1.setCourseId(Calculus);
    t1.setCourseId(English);
    t1.setCourseId(Programming);
    t2.setCourseId(MilitaryTheory);
    t2.setCourseId(Programming);
    t3.setCourseId(HumanCivilization);
    t3.setCourseId(MilitaryTheory);
    t4.setCourseId(HumanCivilization);
    t4.setCourseId(English);

    // ����ѧ������(���������䣬ѧ�ţ�ÿѧ��ѡ����Ŀ)
    Student s1("JKwang", 18, 1025, 5);
    Student s2("ZTcheng", 22, 1001, 5);

    cout << "��ӭ����ѡ��ϵͳ, �뿪ʼ���ѡ��" << endl;
    Sleep(500);
    cout << "������ѧ��: ";
    int stid;
    string stName;
    cin >> stid;
    Sleep(500);
    while ( stid <= 1000 || stid >= 1100 ) {
        cout << "��Ч��ѧ��, �������������ѧ��: ";
        cin >> stid;
        Sleep(500);
    }
    switch (stid) {
        case 1025:
            stName = "JKwang";
            break;
        case 1001:
            stName = "ZTcheng";
            break;
        default:
            break;
    }

    cout << "���ڽ�������ʶ��, ���Ժ�" << endl;
    for ( int i = 0; i < 4; i++ ) {
        cout << "... ";
        Sleep(500);
    }
    cout << endl << "ʶ��ɹ�, ��ӭ��, " << stName << endl;
    Sleep(500);
    bool running = true;
    while (running) {
        cout << "��ѡ���ܱ��:" << endl;
        cout << "1.��ʼѡ��" << endl;
        cout << "2.�鿴��ѧ���Ƿ����ɿγ�" << endl;
        cout << "3.�γ�����" << endl;
        cout << "4.�˳�ϵͳ" << endl;
        int opt, cnt = 0;
        cin >> opt;
        cout << "���Ժ�... ";
        for ( int i = 0; i < 3; i++ ) {
            cout << "... ";
            Sleep(500);
        }
        cout << endl;
        switch (opt) {
            case 1: {
                do {
                    // ѡ��
                    cout << "������γ̱����ѡ��γ�: " << endl;
                    cout << "1.Calculus" << endl;
                    cout << "2.HumanCivilization" << endl;
                    cout << "3.English" << endl;
                    cout << "4.Programming" << endl;
                    cout << "5.MilitaryTheory" << endl;
                    int courseNum;
                    cin >> courseNum;
                    switch (courseNum) {
                        case 1:
                            if ( stid == 1025 ) {
                                s1.selectCourse(Calculus);
                            } else if ( stid == 1001 ) {
                                s2.selectCourse(Calculus);
                            }
                            break;
                        case 2:
                            if ( stid == 1025 ) {
                                s1.selectCourse(HumanCivilization);
                            } else if ( stid == 1001 ) {
                                s2.selectCourse(HumanCivilization);
                            }
                            break;
                        case 3:
                            if ( stid == 1025 ) {
                                s1.selectCourse(English);
                            } else if ( stid == 1001 ) {
                                s2.selectCourse(English);
                            }
                            break;
                        case 4:
                            if ( stid == 1025 ) {
                                s1.selectCourse(Programming);
                            } else if ( stid == 1001 ) {
                                s2.selectCourse(Programming);
                            }
                            break;
                        case 5:
                            if ( stid == 1025 ) {
                                s1.selectCourse(MilitaryTheory);
                            } else if ( stid == 1001 ) {
                                s2.selectCourse(MilitaryTheory);
                            }
                            break;
                        default:
                            cout << "��Ч�Ŀγ̱��" << endl;
                            break;
                    }
                    cout << "���Ժ�... ";
                    for ( int i = 0; i < 3; i++ ) {
                        cout << "... ";
                        Sleep(500);
                    }
                    cout << endl;
                    cout << "�Ƿ����ѡ��" << endl;
                    cout << "1.����" << endl;
                    cout << "2.������" << endl;
                    cin >> cnt;
                    cnt--;
                } while ( !cnt );
                break;
            }
            case 2: {
                // �ж�ѧ���Ƿ�����ɸ�ѧ�ڵĿγ�
                if ( stid == 1025 ) {
                    cout << "Can " << stName << " finish this semester?" << endl;
                    Sleep(500);
                    cout << ( s1.judge() ? "Yes" : "No" ) << endl;
                } else if ( stid == 1001 ) {
                    cout << "Can " << stName << " finish this semester?" << endl;
                    Sleep(500);
                    cout << ( s2.judge() ? "Yes" : "No" ) << endl;
                }
                Sleep(500);
                break;
            }
            case 3: {
                // �γ�����
                TeachingAssistant ta("TA", 20, 1001, 2, 1025, 3);
                cout << "�γ����̽��εķ���: "; 
                Sleep(500);
                ta.teach();
                Sleep(500);
                cout << "��ѡ����: " << endl;
                cout << "1.ѡ���Ϊ�γ�����" << endl << "2.�˳���Ϊ�γ�����" << endl;
                int taNum, tNum;
                cin >> taNum;
                cout << "���Ժ�... ";
                for ( int i = 0; i < 3; i++ ) {
                    cout << "... ";
                    Sleep(500);
                }
                cout << endl;
                switch (taNum) {
                    case 1: 
                        cout << "�������ʦ�����ѡ������: " << endl;
                        cout << "1.Mr.Tang" << endl;
                        cout << "2.Mr.Chen" << endl;
                        cout << "3.Ms.Wei" << endl;
                        cout << "4.Mr.Su" << endl;
                        cin >> tNum;
                        cout << "���Ժ�... ";
                        for ( int i = 0; i < 3; i++ ) {
                            cout << "... ";
                            Sleep(500);
                        }
                        cout << endl;
                        switch (tNum) {
                            case 1:
                                ta.selectCourse(t1);
                                break;
                            case 2:
                                ta.selectCourse(t2);
                                break;
                            case 3:
                                ta.selectCourse(t3);
                                break;
                            case 4:
                                ta.selectCourse(t4);
                                break;
                            default:
                                cout << "��Ч�Ľ�ʦ���" << endl;
                                break;
                        }
                        Sleep(500);
                        break;
                    case 2: 
                        cout << "��ѡ���ʦ������˳�ѡ������: " << endl;
                        cout << "1.Mr.Tang" << endl;
                        cout << "2.Mr.Chen" << endl;
                        cout << "3.Ms.Wei" << endl;
                        cout << "4.Mr.Su" << endl;
                        cin >> tNum;
                        cout << "���Ժ�... ";
                        for ( int i = 0; i < 3; i++ ) {
                            cout << "... ";
                            Sleep(500);
                        }
                        switch (tNum) {
                            case 1:
                                ta.deleteCourse(t1);
                                break;
                            case 2:
                                ta.deleteCourse(t2);
                                break;
                            case 3:
                                ta.deleteCourse(t3);
                                break;
                            case 4:
                                ta.deleteCourse(t4);
                                break;
                            default:
                                cout << "��Ч�Ľ�ʦ���" << endl;
                                break;
                        }
                        Sleep(500);
                        break;
                }
                break;
            }
            case 4: {
                running = false;
                cout << "���˳�ϵͳ��ллʹ�ã�" << endl;
                break;
            }
            default:
                cout << "��Ч�Ĺ��ܱ��" << endl;
                break;
        }
    }

    return 0;
}