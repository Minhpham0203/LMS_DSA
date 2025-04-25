#include <bits/stdc++.h> // Thư viện bao gồm hầu hết các thư viện chuẩn của C++
#include <chrono>       // Thư viện hỗ trợ các chức năng liên quan đến thời gian
using namespace std;    // Sử dụng không gian tên std để tránh việc gõ std:: trước các thành phần của thư viện chuẩn

// Khai báo biến toàn cục (nên hạn chế sử dụng biến toàn cục trong các dự án lớn)
vector<vector<string>> content; // Một vector 2D chứa các chuỗi, có thể dùng để lưu trữ dữ liệu đọc từ file CSV
vector<string> toupdate;       // Một vector chứa các chuỗi, có thể dùng để lưu trữ dữ liệu tạm thời để ghi vào file

// Hàm đọc dữ liệu từ một file CSV
void readfile(string fname){ // fname là tên của file cần đọc
    vector<string> row;    // Vector tạm thời để lưu trữ một dòng dữ liệu
    string line, word;    // line: chuỗi lưu trữ một dòng đọc từ file, word: chuỗi lưu trữ một từ (giữa các dấu phẩy)

    fstream file (fname,ios::in); // Mở file ở chế độ đọc (input)
    if(file.is_open()){         // Kiểm tra xem file có được mở thành công không
        while(getline(file, line)){ // Đọc từng dòng từ file vào biến line
            row.clear();            // Xóa dữ liệu của vector row từ lần đọc trước
            stringstream str(line); // Tạo một stringstream từ dòng vừa đọc để phân tách các từ
            while(getline(str, word, ',')) // Đọc từng từ từ stringstream, phân tách bởi dấu phẩy, và lưu vào word
                row.push_back(word);    // Thêm từ vừa đọc vào vector row
            content.push_back(row);     // Thêm vector row (đại diện cho một dòng) vào vector 2D content
        }
    }
    else cout<<"Could not open the file\n"; // In ra thông báo lỗi nếu không mở được file
}

// Hàm ghi dữ liệu (vector 2D các chuỗi) vào một file CSV, ghi đè nội dung cũ
void writefile(vector<vector<string>> par, string fname){ // par: vector 2D chứa dữ liệu cần ghi, fname: tên file để ghi
    fstream fout(fname,ios::out); // Mở file ở chế độ ghi (output), nếu file tồn tại sẽ bị ghi đè
    for(auto x:par){             // Duyệt qua từng vector (dòng) trong vector 2D par
        for(auto y:x){         // Duyệt qua từng chuỗi (từ) trong vector (dòng) x
            fout<<y;             // Ghi chuỗi y vào file
            if(y!=x.back()) fout<<","; // Nếu không phải là phần tử cuối cùng của dòng, thì ghi thêm dấu phẩy
        }
        fout<<"\n";             // Ghi dấu xuống dòng sau khi ghi xong một dòng
    }
}

// Hàm ghi dữ liệu (vector các chuỗi) vào một file CSV, thêm vào cuối file (append)
void writefileappend(vector<string> par, string fname){ // par: vector chứa dữ liệu cần ghi (một dòng), fname: tên file để ghi
    fstream fout(fname,ios::out | ios::app); // Mở file ở chế độ ghi (output) và thêm vào cuối file (append)
    for(auto x:par){                         // Duyệt qua từng chuỗi trong vector par
        fout<<x;                             // Ghi chuỗi x vào file
        if(x!=par.back()) fout<<",";         // Nếu không phải là phần tử cuối cùng, thì ghi thêm dấu phẩy
    }
    fout<<"\n";                             // Ghi dấu xuống dòng sau khi ghi xong
}

// Hàm in dữ liệu (vector 2D các chuỗi) ra màn hình, có đánh số thứ tự
void printdata(vector<vector<string>> par){ // par: vector 2D chứa dữ liệu cần in
    int c=1;                                // Biến đếm thứ tự dòng
    for(auto x:par){                        // Duyệt qua từng vector (dòng) trong vector 2D par
        cout<<c<<". ";                     // In ra số thứ tự của dòng
        for(auto y:x){                    // Duyệt qua từng chuỗi (từ) trong vector (dòng) x
            cout<<y;                         // In ra chuỗi y
            if(y!=x.back()) cout<<" | ";    // Nếu không phải là phần tử cuối cùng, thì in thêm " | " để phân tách
        }
        c++;                                // Tăng biến đếm thứ tự
        cout<<"\n";                         // In dấu xuống dòng sau khi in xong một dòng
    }
}

// Hàm in dữ liệu (vector 2D các chuỗi) ra màn hình, nhưng bỏ qua cột mật khẩu (giả sử mật khẩu ở cột thứ 3, index 2)
void printdata_notpassword(vector<vector<string>> par){ // par: vector 2D chứa dữ liệu cần in
    int c=1;                                            // Biến đếm thứ tự dòng
    for(auto x:par){                                    // Duyệt qua từng vector (dòng) trong vector 2D par
        cout<<c<<". ";                                 // In ra số thứ tự của dòng
        cout<<x[0]<<" | "<<x[1]<<" | "<<x[3]<<'\n';    // In ra các cột dữ liệu, bỏ qua cột index 2 (mật khẩu)
        c++;                                            // Tăng biến đếm thứ tự
    }
}

// Lớp User (người dùng hệ thống)
class User{
private:
    string password;               // Thuộc tính private: mật khẩu của người dùng (chỉ có thể truy cập từ bên trong lớp)
public:
    string name;                   // Thuộc tính public: tên của người dùng
    string id;                     // Thuộc tính public: ID của người dùng
    vector<string> isbns_issued;   // Thuộc tính public: vector chứa các mã ISBN của sách đã mượn
    void display_menu();           // Phương thức hiển thị menu chính của người dùng
    void login();                  // Phương thức đăng nhập
    void see_all_books(string id);  // Phương thức xem tất cả sách
    void see_issued_books(string id);// Phương thức xem sách đã mượn
    void logout();                 // Phương thức đăng xuất
    void issue_book(string id, string bookname,string type_user); // Phương thức mượn sách
    void return_book(string id,string isbncode);                 // Phương thức trả sách
    void check_available(string id, string bookname);           // Phương thức kiểm tra sách còn không
    int calc_fine(string id,string type_user);                  // Phương thức tính tiền phạt
    void clear_fine_amount(string id,string type_user);         // Phương thức xóa tiền phạt
    void User_add(string id);                                   // Phương thức thêm người dùng (chỉ librarian có quyền)
    void User_update(string id);                                // Phương thức cập nhật thông tin người dùng (chỉ librarian có quyền)
    void User_delete(string id);                                // Phương thức xóa người dùng (chỉ librarian có quyền)
    void User_search(string id);                                // Phương thức tìm kiếm người dùng (chưa triển khai)
};

// Lớp Book (sách)
class Book{
public:
    string title;       // Thuộc tính public: tiêu đề sách
    string author;      // Thuộc tính public: tác giả
    string isbn;        // Thuộc tính public: mã ISBN
    string publication; // Thuộc tính public: nhà xuất bản
    int is_issued;      // Thuộc tính public: trạng thái sách (0: chưa mượn, 1: đã mượn)
    void Book_request(string id,string bookname,string type_user); // Phương thức yêu cầu mượn sách
    void Show_duedate(string isbn_no);                             // Phương thức hiển thị ngày hết hạn mượn
    void Book_add(string id);                                      // Phương thức thêm sách (chỉ librarian có quyền)
    void Book_update(string id);                                   // Phương thức cập nhật thông tin sách (chỉ librarian có quyền)
    void Book_delete(string id);                                   // Phương thức xóa sách (chỉ librarian có quyền)
    void Book_search(string id);                                   // Phương thức tìm kiếm sách (chưa triển khai)
};

// Lớp Student (sinh viên), kế thừa từ lớp User
class Student : public User{
public:
    int Fine_amount; // Thuộc tính public: số tiền phạt của sinh viên
    void display_student_menu(string id); // Phương thức hiển thị menu dành cho sinh viên
};

// Lớp Professor (giảng viên), kế thừa từ lớp User
class Professor : public User{
public:
    int Fine_amount; // Thuộc tính public: số tiền phạt của giảng viên
public:
    void display_prof_menu(string id); // Phương thức hiển thị menu dành cho giảng viên
};

// Lớp Librarian (thủ thư), kế thừa từ lớp User
class Librarian : public User{
public:
    void display_lib_menu(string id);    // Phương thức hiển thị menu dành cho thủ thư
    void see_all_users(string id);       // Phương thức xem tất cả người dùng
    void see_all_books(string id);       // Phương thức xem tất cả sách
    void add_user(string id);            // Phương thức thêm người dùng
    void update_user(string id);         // Phương thức cập nhật thông tin người dùng
    void delete_user(string id);         // Phương thức xóa người dùng
    void add_book(string id);            // Phương thức thêm sách
    void update_book(string id);         // Phương thức cập nhật thông tin sách
    void delete_book(string id);         // Phương thức xóa sách
    void see_issued_to_user(string id,string uid); // Phương thức xem sách đã mượn của một người dùng cụ thể
    void see_issued_book(string id,string isbn);   // Phương thức xem thông tin người mượn của một cuốn sách cụ thể
};

// Phương thức hiển thị menu cho sinh viên
void Student :: display_student_menu(string id){ // id: ID của sinh viên đã đăng nhập
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged in as Student\n";
    cout<<"Press 1 to see all the books\n";
    cout<<"Press 2 to view books issued by you\n";
    cout<<"Press 3 to check if a book is available for issue or not\n";
    cout<<"Press 4 to view the fine\n";
    cout<<"Press 5 to issue a book\n";
    cout<<"Press 6 to return a book\n";
    cout<<"Press 7 to clear your fine\n";
    cout<<"Press 8 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    string book_name,isbncode;
    Student s; // Tạo một đối tượng Student cục bộ (có thể không cần thiết)
    Book b;    // Tạo một đối tượng Book cục bộ (có thể không cần thiết)
    switch(c){ // Dựa vào lựa chọn của người dùng để thực hiện các hành động khác nhau
        case '1':
            s.see_all_books(id);       // Xem tất cả sách
            s.display_student_menu(id); // Hiển thị lại menu sinh viên sau khi thực hiện hành động
            break;
        case '2':
            s.see_issued_books(id);    // Xem sách đã mượn
            s.display_student_menu(id); // Hiển thị lại menu sinh viên
            break;
        case '3':
            cout<<"Enter the name of the book you want to check : ";
            cin.ignore(); // Xóa bộ đệm bàn phím trước khi đọc dòng
            getline(cin,book_name); // Đọc tên sách muốn kiểm tra
            s.check_available(id,book_name); // Kiểm tra tình trạng sách
            s.display_student_menu(id);     // Hiển thị lại menu sinh viên
            break;
        case '4':
            s.calc_fine(id,"1");        // Tính tiền phạt (type_user "1" cho sinh viên)
            s.display_student_menu(id); // Hiển thị lại menu sinh viên
            break;
        case '5':
            cout<<"Enter the name of the book you want to issue : ";
            cin.ignore();
            getline(cin,book_name); // Đọc tên sách muốn mượn
            b.Book_request(id,book_name,"1"); // Yêu cầu mượn sách
            s.display_student_menu(id);     // Hiển thị lại menu sinh viên
            break;
        case '6':
            cout<<"Enter the isbn code of the book you want to return : ";
            cin>>isbncode; // Đọc mã ISBN của sách muốn trả
            s.return_book(id,isbncode); // Trả sách
            s.display_student_menu(id); // Hiển thị lại menu sinh viên
            break;
        case '7':
            s.clear_fine_amount(id,"1"); // Xóa tiền phạt
            s.display_student_menu(id); // Hiển thị lại menu sinh viên
            break;
        case '8':
            logout();                   // Đăng xuất
            break;
    }
}

// Phương thức hiển thị menu cho giảng viên (tương tự như sinh viên)
void Professor :: display_prof_menu(string id){ // id: ID của giảng viên đã đăng nhập
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged in as Student\n"; // Lỗi in, nên là "Professor"
    cout<<"Press 1 to see all the books\n";
    cout<<"Press 2 to view books issued by you\n";
    cout<<"Press 3 to check if a book is available for issue or not\n";
    cout<<"Press 4 to view the fine\n";
    cout<<"Press 5 to issue a book\n";
    cout<<"Press 6 to return a book\n";
    cout<<"Press 7 to clear your fine\n";
    cout<<"Press 8 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    string book_name,isbncode;
    Professor s; // Tạo một đối tượng Professor cục bộ (có thể không cần thiết)
    switch(c){
        case '1':
            s.see_all_books(id);
            s.display_prof_menu(id);
            break;
        case '2':
            s.see_issued_books(id);
            s.display_prof_menu(id);
            break;
        case '3':
            cout<<"Enter the name of the book you want to check : ";
            cin>>book_name;
            s.check_available(id,book_name);
            s.display_prof_menu(id);
            break;
        case '4':
            s.calc_fine(id,"2"); // Tính tiền phạt (type_user "2" cho giảng viên)
            s.display_prof_menu(id);
            break;
        case '5':
            cout<<"Enter the name of the book you want to issue : ";
            cin>>book_name;
            s.issue_book(id,book_name,"2"); // Mượn sách
            s.display_prof_menu(id);
            break;
        case '6':
            cout<<"Enter the isbn code of the book you want to return : ";
            cin>>isbncode;
            s.return_book(id,isbncode); // Trả sách
            s.display_prof_menu(id);
            break;
        case '7':
            s.clear_fine_amount(id,"2"); // Xóa tiền phạt
            s.display_prof_menu(id);
            break;
        case '8':
            logout();
            break;
    }
}

// Phương thức hiển thị menu đăng nhập cho người dùng
void User :: display_menu(){
    char c;
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\n\nWelcome to the library management system!\n\n";
    cout<<"1. Press 1 to log in : \n";
    cout<<"2. Press 2 to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cin>>c;
    if(c=='1'){ // Nếu người dùng chọn 1, thực hiện đăng nhập
        User u; // Tạo một đối tượng User cục bộ để gọi phương thức login
        u.login();
    }
    else{       // Nếu người dùng chọn
        cout<<"Thanks for using the system !";
        exit(1); // Thoát chương trình với mã lỗi 1
    }
}

// Phương thức đăng nhập của người dùng
void User :: login(){
    string id,password; // Biến để lưu ID và mật khẩu người dùng nhập
    cout<<"Enter your id : ";
    cin>>id;           // Nhập ID người dùng
    cout<<"Enter the password : ";
    cin>>password;     // Nhập mật khẩu người dùng
    vector<string> words_in_a_row; // Vector để lưu trữ các từ trong một dòng đọc từ file
    string line_in_csv,word;      // line_in_csv: chuỗi lưu trữ một dòng từ file, word: chuỗi lưu trữ một từ
    fstream file("all_users_data.csv",ios::in); // Mở file chứa thông tin người dùng ở chế độ đọc
    int count=0; // Biến đếm để kiểm tra trạng thái đăng nhập (0: chưa tìm thấy, 1: tìm thấy ID, 2: tìm thấy ID và mật khẩu đúng)
    if(file.is_open()){ // Kiểm tra nếu file được mở thành công
        while(getline(file,line_in_csv)){ // Đọc từng dòng từ file
            words_in_a_row.clear();     // Xóa dữ liệu của vector từ lần đọc trước
            stringstream str(line_in_csv); // Tạo stringstream từ dòng vừa đọc
            while(getline(str,word,',')) // Đọc từng từ, phân tách bởi dấu phẩy
                words_in_a_row.push_back(word); // Thêm từ vào vector
            if(words_in_a_row[1]==id){ // Kiểm tra nếu ID trong file trùng với ID người dùng nhập (giả sử ID ở cột thứ 2, index 1)
                count=1; // Đánh dấu đã tìm thấy ID
                if(words_in_a_row[2]==password){ // Kiểm tra nếu mật khẩu trong file trùng với mật khẩu người dùng nhập (giả sử mật khẩu ở cột thứ 3, index 2)
                    count++; // Đánh dấu đã tìm thấy mật khẩu đúng
                    break;   // Thoát khỏi vòng lặp while vì đã tìm thấy thông tin đăng nhập
                }
                else{ // Nếu mật khẩu sai
                    while(password!=words_in_a_row[2]){ // Tiếp tục hỏi lại mật khẩu cho đến khi đúng hoặc người dùng chọn thoát
                        cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                        char c;
                        cin>>c;
                        if(c=='1'){ // Nếu người dùng chọn nhập lại mật khẩu
                            cout<<"Enter the password : ";
                            cin>>password; // Nhập lại mật khẩu
                            if(password==words_in_a_row[2]) count++; // Kiểm tra lại mật khẩu
                        }
                        else if(c=='2'){ // Nếu người dùng chọn thoát
                            cout<<"Exiting...";
                            return;      // Kết thúc hàm login
                        }
                        else{ // Nếu người dùng nhập lựa chọn không hợp lệ
                            cout<<"Please enter a valid input.\n";
                        }
                    }
                    if(count==2) break; // Nếu sau khi nhập lại mật khẩu đúng, thoát khỏi vòng lặp while ngoài
                }
            }
            if(count==2) break; // Nếu đã tìm thấy ID và mật khẩu đúng, thoát khỏi vòng lặp while đọc file
        }
        if(count==0){ // Nếu không tìm thấy người dùng
            cout<<"User not found\n";
            User u;    // Tạo đối tượng User cục bộ
            u.display_menu(); // Hiển thị lại menu đăng nhập
        }
        if(count==2){ // Nếu đăng nhập thành công
            Student s;   // Tạo đối tượng Student
            Professor p; // Tạo đối tượng Professor
            Librarian l; // Tạo đối tượng Librarian

            if(words_in_a_row[3]=="1"){ // Kiểm tra loại người dùng (giả sử loại người dùng ở cột thứ 4, index 3; "1" là sinh viên)
                s.display_student_menu(words_in_a_row[1]); // Hiển thị menu sinh viên với ID đã đăng nhập
            }
            else if(words_in_a_row[3]=="2"){ // "2" là giảng viên
                p.display_prof_menu(words_in_a_row[1]);   // Hiển thị menu giảng viên
            }
            else{ // Các trường hợp khác (giả sử "3" là thủ thư)
                l.display_lib_menu(words_in_a_row[1]);   // Hiển thị menu thủ thư
            }
        }
    }
}

// Phương thức xem tất cả sách có trong thư viện
void User :: see_all_books(string id){ // id: ID của người dùng đang xem (có thể dùng cho mục đích logging hoặc kiểm tra quyền)
    content.clear(); // Xóa nội dung vector content từ lần đọc file trước
    cout<<"In the data below, 0 signifies that the book is not issued and 1 means that the book is issued.\n";
    readfile("all_books_data.csv"); // Đọc dữ liệu sách từ file "all_books_data.csv" vào vector content
    printdata(content);            // In dữ liệu sách ra màn hình
    content.clear();             // Xóa lại vector content sau khi đã in
}

// Phương thức mượn sách
void User :: issue_book(string id,string bookname,string type_user){ // id: ID người mượn, bookname: tên sách muốn mượn, type_user: loại người dùng ("1" student, "2" professor)
    content.clear(); // Xóa nội dung vector content
    int fl=0;      // Biến flag để kiểm tra xem sách có tồn tại và còn không
    if(type_user=="1"){ // Nếu là sinh viên
        int count=0;   // Biến đếm số sách đã mượn của sinh viên
        content.clear();
        readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn từ file
        for(int i=0;i<content.size();i++){ // Duyệt qua danh sách sách đã mượn
            if(content[i][0]==id){ // Nếu ID người mượn trùng với ID hiện tại
                count++;           // Tăng số sách đã mượn
            }
        }
        content.clear();
        if(count>4){ // Giả sử sinh viên chỉ được mượn tối đa 5 cuốn
            cout<<"You cant issue more than 5 books !\n\n";
        }
        else{ // Nếu số sách đã mượn chưa đạt giới hạn
            readfile("all_books_data.csv"); // Đọc dữ liệu tất cả sách
            for(int i=0;i<content.size();i++){ // Duyệt qua danh sách tất cả sách
                if(content[i][0]==bookname && content[i][4]=="0"){ // Nếu tên sách trùng khớp và trạng thái là chưa mượn (giả sử trạng thái ở cột thứ 5, index 4)
                    fl=1; // Đánh dấu là sách có sẵn
                    cout<<"Book is available!\n";
                    content[i][4]="1"; // Cập nhật trạng thái sách thành đã mượn
                    toupdate.clear();  // Xóa vector toupdate
                    toupdate.push_back(id);       // Thêm ID người mượn
                    toupdate.push_back(bookname); // Thêm tên sách
                    toupdate.push_back(content[i][3]); // Thêm ISBN (giả sử ISBN ở cột thứ 4, index 3)
                    toupdate.push_back(to_string(time(0))); // Thêm thời gian mượn (timestamp)
                    writefileappend(toupdate,"issued_books_data.csv"); // Ghi thông tin mượn vào file "issued_books_data.csv"
                    cout<<"Book succesfully issued\n";
                    break; // Thoát khỏi vòng lặp vì đã tìm thấy sách và mượn thành công
                }
            }
            if(fl==0) cout<<"Book not available\n"; // Nếu không tìm thấy sách hoặc sách đã được mượn
            writefile(content,"all_books_data.csv"); // Cập nhật lại file "all_books_data.csv" với trạng thái mới của sách
            content.clear();
        }
    }
    if(type_user=="2"){ // Nếu là giảng viên (tương tự như sinh viên nhưng có thể không có giới hạn số lượng sách mượn hoặc giới hạn khác)
        readfile("all_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==bookname && content[i][4]=="0"){
                fl=1;
                cout<<"Book is available!\n";
                content[i][4]="1";
                toupdate.clear();
                toupdate.push_back(id);
                toupdate.push_back(bookname);
                toupdate.push_back(content[i][3]);
                toupdate.push_back(to_string(time(0)));
                writefileappend(toupdate,"issued_books_data.csv");
                cout<<"Book succesfully issued\n";
                break;
            }
        }
        if(fl==0) cout<<"Book not available\n";
        writefile(content,"all_books_data.csv");
        content.clear();
    }
}

// Phương thức trả sách
void User :: return_book(string id,string isbncode){ // id: ID người trả, isbncode: mã ISBN của sách trả
    content.clear();
    int fl=0; // Flag để kiểm tra xem thông tin mượn có hợp lệ không
    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn
    for(int i=0;i<content.size();i++){ // Duyệt qua danh sách sách đã mượn
        if(content[i][2]==isbncode && content[i][0]==id){ // Nếu ISBN và ID người mượn trùng khớp
            fl=1;
            content.erase(content.begin()+i,content.begin()+i+1); // Xóa thông tin mượn khỏi vector
            cout<<"Book was issued by you and is now being returned\n";
            writefile(content,"issued_books_data.csv"); // Cập nhật file "issued_books_data.csv"
            content.clear();
            readfile("all_books_data.csv"); // Đọc lại dữ liệu tất cả sách
            for(int i=0;i<content.size();i++){
                if(content[i][3]==isbncode) content[i][4]="0"; // Cập nhật trạng thái sách thành chưa mượn trong file "all_books_data.csv"
            }
            writefile(content,"all_books_data.csv");
            break; // Thoát khỏi vòng lặp vì đã trả sách thành công
        }
    }
    if(fl==0) cout<<"Invalid details!\n"; // Nếu không tìm thấy thông tin mượn hợp lệ

    content.clear();
}

// Phương thức xem sách đã mượn của một người dùng
void User :: see_issued_books(string id){ // id: ID của người dùng muốn xem sách đã mượn
    int count=1;
    content.clear();
    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn
    for(int i=0;i<content.size();i++){ // Duyệt qua danh sách
        if(content[i][0]==id){ // Nếu ID người mượn trùng với ID hiện tại
            cout<<count<<". ";
            count++;
            for(int k=0;k<content[i].size()-1;k++) // In thông tin sách đã mượn (trừ cột cuối cùng, có thể là timestamp)
                cout<<content[i][k]<<" | ";
            time_t stamp = stoi(content[i][3]); // Lấy timestamp mượn sách (giả sử ở cột thứ 4, index 3) và chuyển thành kiểu time_t
            tm *dateformat = localtime(&stamp); // Chuyển timestamp thành định dạng thời gian địa phương
            cout<< dateformat->tm_mday<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<"\n"; // In ngày mượn
        }
    }
    if(count==0) cout<<"You haven't issued any books as of now\n\n"; // Nếu chưa mượn cuốn nào
    content.clear();
}

// Phương thức kiểm tra xem một cuốn sách có còn không
void User :: check_available(string id,string bookname){ // id: ID người kiểm tra, bookname: tên sách muốn kiểm tra
    content.clear();
    int fl=0;
    readfile("all_books_data.csv"); // Đọc dữ liệu tất cả sách
    int count=1;
    for(int i=0;i<content.size();i++){
        if(content[i][0]==bookname && content[i][4]=="0"){ // Nếu tên sách trùng khớp và trạng thái là chưa mượn
            fl=1;
            cout<<count<<". ";
            count++;
            cout<<"Book is available!\n";
            for(auto j:content[i]) // In thông tin chi tiết của sách
                cout<<j<<" | ";
            cout<<"\n";
            break; // Thoát sau khi tìm thấy sách
        }
    }
    if(fl==0) cout<<"Book not available\n"; // Nếu không tìm thấy hoặc đã mượn
    content.clear();
}

// Phương thức tính tiền phạt
int User :: calc_fine(string id, string type_user){ // id: ID người dùng, type_user: loại người dùng ("1" student, "2" professor)
    int fine=0;
    if(type_user=="1"){ // Tính phạt cho sinh viên (giả sử quá 30 ngày bị phạt 2 đồng/ngày)
        content.clear();
        readfile("issued_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==id){
                int curtime = time(0);                      // Thời gian hiện tại (timestamp)
                int isstime = stoi(content[i][3]);          // Thời gian mượn sách (timestamp)
                if((curtime-isstime)/86400>30) // 86400 là số giây trong một ngày
                    fine+=2*((curtime-isstime)/86400 - 30); // Tính tiền phạt nếu quá hạn 30 ngày
            }
        }
        cout<<"Your fine is : "<<fine<<"\n";
        return fine;
        content.clear();
    }
    if(type_user=="2"){ // Tính phạt cho giảng viên (giả sử quá 60 ngày bị phạt 5 đồng/ngày)
        content.clear();
        readfile("issued_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==id){
                int curtime = time(0);
                int isstime = stoi(content[i][3]);
                if((curtime-isstime)/86400>60)
                    fine+=5*((curtime-isstime)/86400 - 60);
            }
        }
        cout<<"Your fine is : "<<fine<<"\n";
        content.clear();
    }
    return fine;
}

// Phương thức đăng xuất
void User :: logout(){
    cout<<"Logging out...\n";
    User u; // Tạo đối tượng User cục bộ
    u.display_menu(); // Hiển thị lại menu đăng nhập
}

// Phương thức xóa tiền phạt
void User :: clear_fine_amount(string id,string type_user){
    int a = calc_fine(id,type_user); // Tính số tiền phạt hiện tại
    if(a==0) cout<<"You have no pending dues\n";
    else cout<<"Your fine of Rupees "<<a<<" is being cleared.\n";
}

// Các phương thức gọi các phương thức tương ứng của lớp Librarian (để thực hiện các chức năng quản trị người dùng)
void User :: User_add(string id){
    Librarian l;
    l.add_user(id);
}
void User :: User_delete(string id){
    Librarian l;
    l.delete_user(id);
}
void User :: User_update(string id){
    Librarian l;
    l.update_user(id);
}
void User :: User_search(string id){
    // Chưa triển khai
}

// Phương thức hiển thị ngày hết hạn mượn của sách
void Book :: Show_duedate(string isbn){ // isbn: mã ISBN của sách cần xem ngày hết hạn
    content.clear();
    string uid;    // ID của người mượn
    time_t stamp;  // Timestamp mượn sách
    readfile("issued_books_data.csv");
    int fl=0;
    for(int i=0;i<content.size();i++){
        if(content[i][2]==isbn){ // Tìm dòng tương ứng với ISBN
            fl=1;
            uid = content[i][0];     // Lấy ID người mượn (giả sử ở cột đầu tiên, index 0)
            stamp = stoi(content[i][3]); // Lấy timestamp mượn (giả sử ở cột thứ tư, index 3)
            break;
        }
    }
    content.clear();
    int days=30; // Số ngày mượn mặc định cho sinh viên
    readfile("all_users_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][1]==uid){ // Tìm người dùng theo ID (giả sử ID ở cột thứ hai, index 1)
            if(content[i][3]=="1") // Kiểm tra loại người dùng (giả sử ở cột thứ tư, index 3; "1" là sinh viên)
                days=30;
            else
                days=60; // Giả sử giảng viên được mượn 60 ngày
            break;
        }
    }
    stamp+=days*86400; // Cộng thêm số giây tương ứng với số ngày mượn vào timestamp
    tm *due_time = localtime(&stamp); // Chuyển timestamp hết hạn thành định dạng thời gian địa phương
    if(fl==0) cout<<"Book was not issued!\n";
    else{
        cout<<"Due date of the book is : ";
        cout<< due_time->tm_mday<<"/"<<1 + due_time->tm_mon<<"/"<<1900 + due_time->tm_year<<"\n"; // In ngày hết hạn
    }
}

// Phương thức yêu cầu mượn sách (gọi phương thức issue_book của lớp User)
void Book :: Book_request(string id,string bookname,string type_user){
    User u;
    u.issue_book(id,bookname,type_user);
}

// Các phương thức gọi các phương thức tương ứng của lớp Librarian (để thực hiện các chức năng quản trị sách)
void Book :: Book_add(string id){
    Librarian l;
    l.add_book(id);
}
void Book :: Book_delete(string id){
    Librarian l;
    l.delete_book(id);
}
void Book :: Book_update(string id){
    Librarian l;
    l.update_book(id);
}
void Book :: Book_search(string id){
    // Chưa triển khai
}

// Phương thức hiển thị menu cho thủ thư
void Librarian :: display_lib_menu(string id){ // id: ID của thủ thư đã đăng nhập
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nWelcome "<<id<<"! You are logged in as librarian.\n\n";
    cout<<"Press 1 to add a user\n";
    cout<<"Press 2 to update a user\n";
    cout<<"Press 3 to delete a user\n";
    cout<<"Press 4 to add a book\n";
    cout<<"Press 5 to update a book\n";
    cout<<"Press 6 to delete a book\n";
    cout<<"Press 7 to see all books issued to a particular user\n";
    cout<<"Press 8 to see which book is issued to which user\n";
    cout<<"Press 9 to view all users\n";
    cout<<"Press 0 to view all books\n";
    cout<<"Press d to show due date of a book\n";
    cout<<"Press l to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    Librarian l; // Tạo đối tượng Librarian cục bộ
    Book b;      // Tạo đối tượng Book cục bộ
    User u;      // Tạo đối tượng User cục bộ
    string isbn,uid;
    switch(c){ // Dựa vào lựa chọn của thủ thư để thực hiện các hành động quản trị
        case '1':
            u.User_add(id);          // Thêm người dùng
            l.display_lib_menu(id); // Hiển thị lại menu thủ thư
            break;
        case '2':
            u.User_update(id);       // Cập nhật thông tin người dùng
            l.display_lib_menu(id);
            break;
        case '3':
            u.User_delete(id);       // Xóa người dùng
            l.display_lib_menu(id);
            break;
        case '4':
            b.Book_add(id);          // Thêm sách
            l.display_lib_menu(id);
            break;
        case '5':
            b.Book_update(id);       // Cập nhật thông tin sách
            l.display_lib_menu(id);
            break;
        case '6':
            b.Book_delete(id);       // Xóa sách
            l.display_lib_menu(id);
            break;
        case '7':
            cout<<"Enter the id of the user : ";
            cin>>uid;
            l.see_issued_to_user(id,uid); // Xem sách đã mượn của một người dùng
            l.display_lib_menu(id);
            break;
        case '8':
            cout<<"Enter the isbn number of the book : ";
            cin>>isbn;
            l.see_issued_book(id,isbn);   // Xem thông tin người mượn của một cuốn sách
            l.display_lib_menu(id);
            break;
        case '9':
            l.see_all_users(id);      // Xem tất cả người dùng
            l.display_lib_menu(id);
            break;
        case '0':
            l.see_all_books(id);      // Xem tất cả sách
            l.display_lib_menu(id);
            break;
        case 'd':
            cout<<"Enter the isbn number of the book : ";
            cin>>isbn;
            b.Show_duedate(isbn);     // Hiển thị ngày hết hạn của sách
            l.display_lib_menu(id);
            break;
        case 'l':
            logout();                 // Đăng xuất
            l.display_lib_menu(id); // Hiển thị lại menu thủ thư (có thể không cần thiết sau khi đăng xuất)
            break;
    }
}

// Phương thức xem tất cả người dùng
void Librarian :: see_all_users(string id){ // id: ID của thủ thư đang xem
    content.clear();
    readfile("all_users_data.csv"); // Đọc dữ liệu người dùng từ file
    cout<<"Below are all the users. 1 at the end signifies a student, 2 means a professor and 3 means a librarian \n\n";
    cout<<"The data is given in the form of student,username,type of user.\n\n";
    printdata_notpassword(content); // In thông tin người dùng (bỏ qua mật khẩu)
    content.clear();
}

// Phương thức xem tất cả sách
void Librarian :: see_all_books(string id){ // id: ID của thủ thư đang xem
    content.clear();
    readfile("all_books_data.csv"); // Đọc dữ liệu sách từ file
    cout<<"Below are all the books. 1 at the end signifies a student, 2 means a professor and 3 means a librarian \n\n"; // Lỗi in, không liên quan đến loại người dùng
    cout<<"The data is given in the form of book name,author,pubisher,isbn number,and is_issued(1 if book is issued).\n\n";
    printdata(content); // In thông tin sách
    content.clear();
}

// Phương thức thêm người dùng mới
void Librarian :: add_user(string id){ // id: ID của thủ thư đang thực hiện thao tác
    cout<<"Please enter the details of the new user : \n";
    string _name,_id,_password,_type;
    cout<<"Enter name: ";
    cin.ignore(); // Xóa bộ đệm bàn phím
    getline(cin,name); // Nhập tên người dùng
    cout<<"Enter id : ";
    cin>>_id;       // Nhập ID người dùng
    cout<<"Enter password : ";
    cin>>_password; // Nhập mật khẩu
    cout<<"Enter type of the user : 1 if student, 2 if professor, 3 if librarian : ";
    cin>>_type;     // Nhập loại người dùng
    fstream fout("all_users_data.csv",ios::out | ios::app); // Mở file ở chế độ ghi và thêm vào cuối
    fout<<name<<","<<_id<<","<<_password<<","<<_type<<'\n'; // Ghi thông tin người dùng mới vào file
    cout<<"New user has been added.\n";
}

// Phương thức thêm sách mới
void Librarian :: add_book(string id){ // id: ID của thủ thư đang thực hiện thao tác
    cout<<"Please enter the details of the new book : \n";
    string title,author,isbn,publisher;
    cout<<"Enter title: ";
    cin.ignore();
    getline(cin,title); // Nhập tiêu đề sách
    cout<<"Enter author : ";
    cin>>author;       // Nhập tên tác giả
    cout<<"Enter isbn : ";
    cin>>isbn;         // Nhập mã ISBN
    cout<<"Enter name of publisher : ";
    cin>>publisher;    // Nhập tên nhà xuất bản
    fstream fout("all_books_data.csv",ios::out | ios::app); // Mở file ở chế độ ghi và thêm vào cuối
    fout<<title<<","<<author<<","<<isbn<<","<<publisher<<",0"<<'\n'; // Ghi thông tin sách mới vào file (trạng thái ban đầu là chưa mượn - 0)
    cout<<"New book has been added.\n";
}

// Phương thức xóa sách
void Librarian :: delete_book(string id){ // id: ID của thủ thư đang thực hiện thao tác
    string isbnno;
    cout<<"Enter the isbn number of the book : ";
    cin>>isbnno; // Nhập ISBN của sách cần xóa
    content.clear();
    int found=0;
    readfile("all_books_data.csv"); // Đọc dữ liệu tất cả sách
    for(int i=0;i<content.size();i++){
        if(content[i][3]==isbnno){ // Tìm sách theo ISBN
            found=1;
            content.erase(content.begin()+i,content.begin()+i+1); // Xóa sách khỏi vector
            break;
        }
    }
    writefile(content,"all_books_data.csv"); // Cập nhật file "all_books_data.csv"
    content.clear();
    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn
    for(int i=0;i<content.size();i++){
        if(content[i][2]==isbnno){ // Tìm thông tin mượn của sách cần xóa (nếu có)
            content.erase(content.begin()+i,content.begin()+i+1); // Xóa thông tin mượn
            break;
        }
    }
    writefile(content,"issued_books_data.csv"); // Cập nhật file "issued_books_data.csv"
    content.clear();
    if(found==0) cout<<"Book not found.\n";
}

// Phương thức xóa người dùng
void Librarian :: delete_user(string id){ // id: ID của thủ thư đang thực hiện thao tác
    string uid;
    cout<<"Enter the user id of the user : ";
    cin>>uid; // Nhập ID của người dùng cần xóa
    content.clear();
    int found=0;
    readfile("all_users_data.csv"); // Đọc dữ liệu tất cả người dùng
    for(int i=0;i<content.size();i++){
        if(content[i][1]==uid){ // Tìm người dùng theo ID
            found=1;
            content.erase(content.begin()+i,content.begin()+i+1); // Xóa người dùng khỏi vector
            break;
        }
    }
    writefile(content,"all_users_data.csv"); // Cập nhật file "all_users_data.csv"
    content.clear();
    vector<string> isbns;
    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn
    for(int i=0;i<content.size();i++){
        if(content[i][0]==uid){ // Tìm tất cả sách mà người dùng này đã mượn
            isbns.push_back(content[i][2]); // Lưu lại ISBN
            content.erase(content.begin()+i,content.begin()+i+1); // Xóa thông tin mượn
            break; // Có thể có nhiều sách đã mượn, nên cần duyệt hết
        }
    }
    writefile(content,"issued_books_data.csv"); // Cập nhật file "issued_books_data.csv"
    content.clear();

    readfile("all_books_data.csv"); // Đọc dữ liệu tất cả sách để cập nhật trạng thái
    for(int i=0;i<content.size();i++){
        for(int j=0;j<isbns.size();j++){
            if(isbns[j]==content[i][3]){ // Nếu ISBN của sách đã mượn trùng với ISBN trong danh sách tất cả sách
                content[i][4]="0"; // Cập nhật trạng thái sách thành chưa mượn
            }
        }
    }
    writefile(content,"all_books_data.csv"); // Cập nhật file "all_books_data.csv"
    if(found==0) cout<<"User not found.\n";
}

// Phương thức cập nhật thông tin người dùng
void Librarian :: update_user(string id){ // id: ID của thủ thư đang thực hiện thao tác
    string upid;
    cout<<"Enter the id of the user you want to update : ";
    cin>>upid; // Nhập ID của người dùng cần cập nhật
    cout<<"Enter the serial number of the field you want to update : \n";
    cout<<"1. Password\n";
    cout<<"2. Name of the User\n";
    char c;
    cin>>c;
    content.clear();
    int fl=0;
    readfile("all_users_data.csv"); // Đọc dữ liệu tất cả người dùng
    for(int i=0;i<content.size();i++){
        if(content[i][1]==upid){ // Tìm người dùng theo ID
            fl=1;
            string new_field;
            cout<<"Enter the new value of the field : ";
            cin.ignore();
            getline(cin,new_field); // Nhập giá trị mới
            if(c=='1'){
                content[i][2]=new_field; // Cập nhật mật khẩu (giả sử ở cột thứ 3, index 2)
            }
            else if(c=='2'){
                content[i][0]=new_field; // Cập nhật tên (giả sử ở cột đầu tiên, index 0)
            }
            else{
                cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    cout<<"User updated\n";
    writefile(content,"all_users_data.csv"); // Cập nhật file "all_users_data.csv"
    content.clear();
    if(fl==0) cout<<"User was not found.\n\n";
}

// Phương thức cập nhật thông tin sách
void Librarian :: update_book(string id){ // id: ID của thủ thư đang thực hiện thao tác
    string isbn_no;
    cout<<"Enter the isbn number of the book you want to update : ";
    cin>>isbn_no; // Nhập ISBN của sách cần cập nhật
    cout<<"Enter the serial number of the field you want to update : \n";
    cout<<"1. Name of the Book\n";
    cout<<"2. Name of the Author\n";
    cout<<"3. Name of the Publisher\n";
    char c;
    cin>>c;
    content.clear();
    int fl=0;
    string new_field;
    readfile("all_books_data.csv"); // Đọc dữ liệu tất cả sách
    for(int i=0;i<content.size();i++){
        if(content[i][3]==isbn_no){ // Tìm sách theo ISBN
            fl=1;
            cout<<"Enter the new value of the field : ";
            cin.ignore();
            getline(cin,new_field); // Nhập giá trị mới
            if(c=='1'){
                content[i][0]=new_field; // Cập nhật tên sách (giả sử ở cột đầu tiên, index 0)
            }
            else if(c=='2'){
                content[i][1]=new_field; // Cập nhật tên tác giả (giả sử ở cột thứ hai, index 1)
            }
            else if(c=='3'){
                content[i][2]=new_field; //
                content[i][2]=new_field; // Cập nhật tên nhà xuất bản (giả sử ở cột thứ ba, index 2)
            }
            else{
                cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    writefile(content,"all_books_data.csv"); // Cập nhật file "all_books_data.csv"
    content.clear();

    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn để cập nhật tên sách (nếu có)
    for(int i=0;i<content.size();i++){
        if(content[i][2]==isbn_no){ // Tìm thông tin mượn theo ISBN
            fl=1;
            if(c=='1'){
                content[i][1]=new_field; // Cập nhật tên sách (giả sử ở cột thứ hai, index 1 trong file issued_books_data.csv)
            }
            break;
        }
    }
    cout<<"Book updated\n";
    writefile(content,"issued_books_data.csv"); // Cập nhật file "issued_books_data.csv"

    if(fl==0) cout<<"Book was not found.\n\n";
}

// Phương thức xem tất cả sách đã mượn của một người dùng cụ thể
void Librarian :: see_issued_to_user(string id,string uid){ // id: ID của thủ thư, uid: ID của người dùng cần xem
    vector <string> isbns;
    content.clear();
    int count=1;
    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn
    for(int i=0;i<content.size();i++){
        if(content[i][0]==uid){ // Tìm các bản ghi mượn theo ID người dùng
            isbns.push_back(content[i][2]); // Lưu lại ISBN của sách đã mượn
        }
    }
    content.clear();
    if(isbns.size()==0) cout<<"No book is issued to this user.\n\n";
    else{
        readfile("all_books_data.csv"); // Đọc dữ liệu tất cả sách để lấy thông tin chi tiết
        for(int d=0;d<isbns.size();d++){
            for(int i=0;i<content.size();i++){
                if(content[i][3]==isbns[d]){ // Tìm sách theo ISBN
                    cout<<count<<". ";
                    count++;
                    for(auto y:content[i]){
                        if(y!=content[i].back())
                            cout<<y<<" | ";
                        else
                            cout<<y<<"\n";
                    }
                }
            }
        }
        content.clear();
    }
}

// Phương thức xem thông tin người mượn của một cuốn sách cụ thể
void Librarian :: see_issued_book(string id,string isbn){ // id: ID của thủ thư, isbn: ISBN của sách cần xem
    content.clear();
    int coun=0;
    readfile("issued_books_data.csv"); // Đọc dữ liệu sách đã mượn
    for(int i=0;i<content.size();i++){
        coun=1;
        if(content[i][2]==isbn){ // Tìm bản ghi mượn theo ISBN
            cout<<"Book with id "<<isbn<<" and name "<<content[i][1]<<" is issued to user with id : "<<content[i][0]<<"\n";
            // Giả sử tên sách cũng được lưu trong file issued_books_data.csv ở cột thứ hai (index 1)
            break; // Có thể chỉ có một bản ghi mượn cho mỗi ISBN
        }
    }
    if(coun==0) cout<<"Book has not been issued to anyone.\n\n";
}

// Hàm main, điểm bắt đầu của chương trình
int main(){
    User temp; // Tạo một đối tượng User tạm thời
    temp.display_menu(); // Hiển thị menu đăng nhập ban đầu
    return 0; // Kết thúc chương trình
}