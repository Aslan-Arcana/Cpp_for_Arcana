#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// Course类
class Course{
    public:
        int CourseId;   //表示课程编号
        string courseName;  //表示课程名称
        int credit; //表示课程的学分
        Course(int CourseId, string courseName, int credit){
            this -> CourseId = CourseId;
            this -> courseName = courseName;
            this -> credit = credit;
        }   //构造函数创建课程
};

// Person类
class Person{
    public:
        string name;    //人名
        int age;    //年龄
        Person(string name, int age){
            this -> name = name;
            this -> age = age;
        }   //构造函数创建个人信息
};

// Teacher类
class Teacher : virtual public Person{
    public:    
        int teacherId;  //表示教师ID
        int *TeachCourse;   //教师所教授课程ID的集合
        int TeachCourseNum; //教师所教授课程的数量
        Teacher(string name, int age, int teacherId, int n) : Person(name, age){
            this -> teacherId = teacherId;
            this -> TeachCourse = new int[n];
            this -> TeachCourseNum = n;
        }   //创建教师信息
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
        }   //创建老师所讲课程
};

// Student类
class Student : virtual public Person{
    public:
        int number; //学生学号
        static int courseCount; //已选课程的数目
        static int courseCredit;    //已选课程的学分
        int *myCourses; //存放已选课程的id的数组
        int minCourseNum;   //每学期至少选课的课程数量
        Student(string name, int age, int number, int n) : Person(name, age){
            this -> number = number;
            this -> myCourses = new int[n];
            this -> minCourseNum = n;
        }   //创建学生信息
        void selectCourse(Course course){
            if ( courseCount < this -> minCourseNum ) {
                this -> myCourses[courseCount] = course.CourseId;
                courseCount++;
                courseCredit += course.credit;
            }
        }   //选课
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
        }   //退课
        bool judge(){
            return courseCount >= 5;
        }   //判断学生该学期是否可完成课程
        int creditSum(){
            return courseCredit;
        }
};

int Student::courseCount = 0, Student::courseCredit = 0;   //定义学生初始选课数量与学分为0

// TeachingAssistant类
class TeachingAssistant : public Teacher, public Student{
    public:
        TeachingAssistant(string name, int age, int teacherId, int n, int number, int m) : 
            Person(name, age), Teacher(name, age, teacherId, n), Student(name, age, number, m){}
        void teach(){
            cout << "I am a teaching assistant, I help my teacher teach his students." << endl;
        }
        void selectCourse(Teacher t){
            cout << "你已经选择了做" << t.name << "老师的课程助教。" << endl;
        }
        void deleteCourse(Teacher t){
            cout << "你已经退出了做" << t.name << "老师的课程助教。" << endl;
        }
};

int main(){
    // 创建微积分，人类文明，英语，程序设计，军事理论五门课程(序号，课程名称，学分)
    Course Calculus(1, "Calculus", 6);
    Course HumanCivilization(2, "HumanCivilization", 1);
    Course English(3, "English", 4);
    Course Programming(4, "Programming", 4);
    Course MilitaryTheory(5,"MilitaryTheory", 2);

    // 创建老师资料(姓名，年龄，教工号，教授课程数量)
    Teacher t1("Mr.Tang", 35, 101, 3);
    Teacher t2("Mr.Chen", 29, 102, 2);
    Teacher t3("Ms.Wei", 30, 103, 2);
    Teacher t4("Mr.Su", 29, 104, 2);

    // 创建课程id
    t1.setCourseId(Calculus);
    t1.setCourseId(English);
    t1.setCourseId(Programming);
    t2.setCourseId(MilitaryTheory);
    t2.setCourseId(Programming);
    t3.setCourseId(HumanCivilization);
    t3.setCourseId(MilitaryTheory);
    t4.setCourseId(HumanCivilization);
    t4.setCourseId(English);

    // 创建学生资料(姓名，年龄，学号，每学期选课数目)
    Student s1("JKwang", 18, 1025, 5);
    Student s2("ZTcheng", 22, 1001, 5);

    cout << "欢迎来到选课系统, 请开始你的选课" << endl;
    Sleep(500);
    cout << "请输入学号: ";
    int stid;
    string stName;
    cin >> stid;
    Sleep(500);
    while ( stid <= 1000 || stid >= 1100 ) {
        cout << "无效的学号, 请重新输入你的学号: ";
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

    cout << "正在进行人脸识别, 请稍后" << endl;
    for ( int i = 0; i < 4; i++ ) {
        cout << "... ";
        Sleep(500);
    }
    cout << endl << "识别成功, 欢迎你, " << stName << endl;
    Sleep(500);
    bool running = true;
    while (running) {
        cout << "请选择功能编号:" << endl;
        cout << "1.开始选课" << endl;
        cout << "2.查看该学期是否可完成课程" << endl;
        cout << "3.课程助教" << endl;
        cout << "4.退出系统" << endl;
        int opt, cnt = 0;
        cin >> opt;
        cout << "请稍后... ";
        for ( int i = 0; i < 3; i++ ) {
            cout << "... ";
            Sleep(500);
        }
        cout << endl;
        switch (opt) {
            case 1: {
                do {
                    // 选课
                    cout << "请输入课程编号来选择课程: " << endl;
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
                            cout << "无效的课程编号" << endl;
                            break;
                    }
                    cout << "请稍后... ";
                    for ( int i = 0; i < 3; i++ ) {
                        cout << "... ";
                        Sleep(500);
                    }
                    cout << endl;
                    cout << "是否继续选课" << endl;
                    cout << "1.继续" << endl;
                    cout << "2.不继续" << endl;
                    cin >> cnt;
                    cnt--;
                } while ( !cnt );
                break;
            }
            case 2: {
                // 判断学生是否能完成该学期的课程
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
                // 课程助教
                TeachingAssistant ta("TA", 20, 1001, 2, 1025, 3);
                cout << "课程助教讲课的方法: "; 
                Sleep(500);
                ta.teach();
                Sleep(500);
                cout << "请选择功能: " << endl;
                cout << "1.选择成为课程助教" << endl << "2.退出成为课程助教" << endl;
                int taNum, tNum;
                cin >> taNum;
                cout << "请稍后... ";
                for ( int i = 0; i < 3; i++ ) {
                    cout << "... ";
                    Sleep(500);
                }
                cout << endl;
                switch (taNum) {
                    case 1: 
                        cout << "请输入教师编号来选择助教: " << endl;
                        cout << "1.Mr.Tang" << endl;
                        cout << "2.Mr.Chen" << endl;
                        cout << "3.Ms.Wei" << endl;
                        cout << "4.Mr.Su" << endl;
                        cin >> tNum;
                        cout << "请稍后... ";
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
                                cout << "无效的教师编号" << endl;
                                break;
                        }
                        Sleep(500);
                        break;
                    case 2: 
                        cout << "请选择教师编号来退出选择助教: " << endl;
                        cout << "1.Mr.Tang" << endl;
                        cout << "2.Mr.Chen" << endl;
                        cout << "3.Ms.Wei" << endl;
                        cout << "4.Mr.Su" << endl;
                        cin >> tNum;
                        cout << "请稍后... ";
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
                                cout << "无效的教师编号" << endl;
                                break;
                        }
                        Sleep(500);
                        break;
                }
                break;
            }
            case 4: {
                running = false;
                cout << "已退出系统，谢谢使用！" << endl;
                break;
            }
            default:
                cout << "无效的功能编号" << endl;
                break;
        }
    }

    return 0;
}