#include <bits/stdc++.h>
using namespace std;


// Function to return the current time and date as a string
string return_current_time_and_date()
{
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}


// Forward declaration of the User class

class User;


class Book{

private:

    string Title;
    int TotalPages;
    string Author;

public:
    void PrintBookDetails(){

        cout << "Title: " << Title << '\n';
        cout << "Author: " << Author << '\n';
        cout << "Total pages: " << TotalPages << '\n';


    }

    // Read book details from admin input
    void ReadBook(const string &book_name) {
        SetBookName(book_name);

        string str;
        int total_pages;

        cout << "Enter book's Author name: \n";
        cin >> str;
        SetAuthor(str);

        cout << "Enter number of book pages: \n";
        cin >> total_pages;
        SetTotalPages(total_pages);


    }


    // Getter and setter for book title
    const string& GetBookName() const {
        return Title;
    }
    void SetBookName(const string& name) {
        this->Title = name;
    }

    // Getter and setter for total pages
    const int& GetTotalPages() const {
        return TotalPages;
    }
    void SetTotalPages(const int& total_pages) {
        this->TotalPages = total_pages;
    }


    // Getter and setter for author
    const string& GetAuthor() const {
        return Author;
    }
    const void SetAuthor(const string& author_name) {
        this->Author = author_name;
    }


};

class BooksManager{

private:

    Book *current_book;// Pointer to the current book being added
    map<string, Book*> book_name_book_object_map;// Map to store books by their titles
    static int num_of_books;// Static variable to track the number of books

public:

    // Destructor to free memory
    ~BooksManager() {
        // Iterate through the map and delete all dynamically allocated Book objects
        for (auto& pair : book_name_book_object_map) {
            delete pair.second;  // Free the memory for each book
        }
        cout << "All books deleted.\n";
    }

    // Add a new book to the system

    void AddBook() {
        // Allocate memory for a new book
        current_book = new Book();

        string title;

        // Prompt admin to fill in book details
        cout << "Enter book title: ";
        cin.ignore(); // To clear any newline character left in input buffer
        getline(cin, title);

        current_book->ReadBook(title);
        // Store the book in the map using the title as the key
        book_name_book_object_map[title] = current_book;

        num_of_books++;
        cout << "Book added successfully!\n";
    }

    // List all books stored in the system
    void ListAllBooks() const {
        int cnt = 1;
        for (const auto &pair : book_name_book_object_map) {
            cout << "Book (" << cnt << ") :\n";
            pair.second->PrintBookDetails();
            cout<<"\n\n";
            cnt++;
        }
    }

    // Check if there are any books in the system
    const bool CheckEmpty() const{
        if(!num_of_books)
            return false;

        return true;
    }

    // Return the number of books
    const int NumberOfBooks() const {
        return num_of_books;
    }

    // Retrieve a book based on its index
     Book* GetBook(int place) const{
        int cnt = 0;
        place--;
        for(auto it :book_name_book_object_map){
            if(cnt == place){
                return it.second;
            }
            cnt++;
        }
        return nullptr;  // Return null if the index is invalid
    }

};
int BooksManager::num_of_books = 0;// Initialize static member variable






class User {
private:

    string user_name;
    string password;
    string name;
    string email;
    bool admin_or_not;
    int num_of_books; // Tracks the number of books a user has read
    map<Book*,pair<int,string>> books_i_read;// Stores books read by the user, with last page read and last access time

public:
    User(){
            num_of_books = 0;
    }


    // Print user details
    void Print() const {
        cout << "User_name: "<< user_name << "\nPassword: " << password << "\nReal name: " << name << "\nEmail: " << email << "\n";
    }


    // Read user details during signup
    void ReadUser(const string &user_name) {
        SetUserName(user_name);

        string str;
        int admin;
        cout << "Enter password: \n";
        cin >> str;
        SetPassword(str);

        cout << "Enter name: \n";
        cin >> str;
        SetName(str);

        cout << "Enter email: \n";
        cin >> str;
        SetEmail(str);


        cout << "Are you an admin ? (1-Yes 0-No)\n ";
        cin >> admin;
        SetAdmin(admin);

    }


    // Increment the number of books read by the user
    void IncrementNumberOfBooks(){
        num_of_books++;
    }


    // Get and set user details (getter/setter methods)
    const string& GetEmail() const {
        return email;
    }

    void SetEmail(const string& email) {
        this->email = email;
    }

    const string& GetName() const {
        return name;
    }
    const void SetName(const string& name) {
        this->name = name;
    }

    const bool& GetAdmin() const {
        return admin_or_not;
    }
    const void SetAdmin(const int& admin) {
        this->admin_or_not = admin;
    }

    const string& GetPassword() const {
        return password;
    }

    const void SetPassword(const string& password) {
        this->password = password;
    }


    const string& GetUserName() const {
        return user_name;
    }

    const void SetUserName(const string& userName) {
        this->user_name = userName;
    }

    // Check if the user has read any book
    bool CheckUserBook(){

        return num_of_books;
    }

    // Get the last page read for a particular book
    int GetLastPage(Book* cur_book){
       string name = cur_book->GetBookName();
       for(auto it: books_i_read){
           if(it.first->GetBookName() == name){
               return it.second.first;
           }
       }

        return 0;
    }

    // Set the last page read for a book and record the time
    void SetLastPage(int num,Book* cur_book, string last_time){
        books_i_read[cur_book].first = num;
        books_i_read[cur_book].second = last_time;
    }

    // Check if a user has already read the book
    bool BookFound(Book* cur_book){
        string name = cur_book->GetBookName();
        for(auto it: books_i_read){
            if(it.first->GetBookName() == name){
                return true;
            }
        }
        books_i_read[cur_book].first = 0; // If not found, initialize book progress
        return false;
    }

    // List all books read by the user with progress
    void ListAllBook_I_Read(){
        for(auto it: books_i_read){
            cout << "Name of the book: " << it.first->GetBookName() << "  Number of pages you read: (" << it.second.first << ") out of (" << it.first->GetTotalPages() << ")\n";
            cout << "Last time opened the book: " << it.second.second << "\n";
            if(it.second.first == it.first->GetTotalPages()){
                cout << "You finished this book (" << it.first->GetBookName() << ")\n\n";
            }
        }
    }

};



class UsersManager {
private:
    User *current_user{}; // Pointer to the current logged-in user
    map<string, User*> userame_userobject_map; // Map to store users by their usernames


public:
    UsersManager() {

    }


    // Destructor to free memory
    ~UsersManager() {
        // Iterate through the map and delete all dynamically allocated Book objects
        for (auto& pair : userame_userobject_map) {
            delete pair.second;  // Free the memory for each user
        }
        cout << "All users deleted.\n";
    }

    // Function to login or sign up
    void AccessSystem() {
        int choice;
        cout << "1- login\n2- signup\n3- exit\n ";
        cin >> choice;
        if (choice == 1)
            DoLogin();
        else if(choice == 2)
            DoSignUp();
        else
            exit(0);
    }

    // Show the appropriate menu based on user role
    const void ShowMenu(BooksManager& booksManager){
        if(current_user->GetAdmin()){
             ShowAdminMenu(booksManager);
        }
        else{
            ShowCustomerMenu(booksManager);
        }


    }

    // Show menu options for admin users
    const void ShowAdminMenu( BooksManager& booksManager){
        int choice;
        while(true) {
            cout << "1- Add a new book\n";
            cout << "2- View all users\n";
            cout << "3- Exit\n";
            cin >> choice;
            if (choice == 1) {

                booksManager.AddBook();
            }
            else if(choice == 2){
                for(const auto it : userame_userobject_map){
                    it.second->Print();
                    cout <<"\n\n";
                }
            }
            else if (choice == 3){
                cout << "\n\n";
                break;
            }
            else{
                cout << "Enter a correct choice please\n\n";
            }


        }
    }


    // Show menu options for customer users
    void ShowCustomerMenu(const BooksManager& booksManager){
        while(true){

            cout << "1- list all available books\n";
            cout << "2- see my progress\n";
            cout << "3- continue reading\n";
            cout << "4- exit";
            int choice;
            cin >> choice;

            if(choice == 1){
                if(!booksManager.CheckEmpty()){
                    cout << "There are no books available at the moment. Come back soon when books are available\n ";
                }
                else{
                    booksManager.ListAllBooks();
                }
            }
            else if(choice == 2){
                if(!current_user->CheckUserBook()){
                    cout << "You haven't read any book yet. Start reading a book now\n";
                }
                else{
                    current_user->ListAllBook_I_Read();
                }
            }
            else if(choice == 3){
                if(!booksManager.CheckEmpty()){
                    cout << "There are no books available at the moment. Come back soon when books are available\n ";
                    continue;
                }
                if(!current_user->CheckUserBook()){
                    cout << "You haven't read any book yet. do you want to choose a book now ? (1-Yes 0-No)\n";
                    int option;
                    cin >> option;
                    if(!option){
                        continue;
                    }
                }
                booksManager.ListAllBooks();
                int option;
                cout << "\nChoose the book you want to read: \n";
                while(true) {
                    cin >> option;
                    if (option < 0 || option > booksManager.NumberOfBooks()) {
                        cout << "Please,choose a correct option\n";
                    }
                    else{
                        break;
                    }
                }
                Book* cur_book = booksManager.GetBook(option);
                reading(cur_book);

            }
            else if(choice == 4){
                cout <<"\n\n";
                break;
            }
            else{
                cout << "Choose a correct choice please\n\n";
            }

        }

    }


    // login menu
    void DoLogin() {


        while (true) {
            string name, pass;
            cout << "Enter user name & password: ";
            cin >> name >> pass;

            // First, check if the username exists
            if (!userame_userobject_map.count(name)) {
                cout << "\nInvalid user name or password. Try again\n\n";
                continue;
            }

            // Retrieve the user object from the map
            User* user_exist = userame_userobject_map[name];

            // Now check if the password is correct
            if (pass != user_exist->GetPassword()) {
                cout << "\nInvalid user name or password. Try again\n\n";
                continue;
            }

            // If both username and password are correct, assign the user to current_user
            current_user = user_exist;
            break;
        }

    }

    // sign up menu
    void DoSignUp() {
        string user_name;

        while (true) {
            cout << "Enter user name. (No spaces): ";
            cin >> user_name;
            if (userame_userobject_map.count(user_name)) {
                cout << "\nuser name is already taken\n\n";
                continue;
            }
            else{
                break;
            }

        }

        current_user = new User();  // Allocate memory for the new user
        current_user->ReadUser(user_name);

        userame_userobject_map[current_user->GetUserName()] = current_user;

    }

    // Read a book, save progress, and update user's reading list
    void reading(Book* cur_book){

        int last_page = current_user->GetLastPage(cur_book);
        if(last_page == 0 && !current_user->BookFound(cur_book)){
           current_user->IncrementNumberOfBooks();
        }
        bool finished_book = false;
        while(true){
            int choice;
            if(last_page == 0){
                cout << "1- next page\n2- exit";
                cin >> choice;
                if(choice == 1){
                    cout << "You are now reading page (" << ++last_page << ")\n";
                }
                else if (choice == 2){
                    break;
                }
                else{
                    cout << "Choose a correct choice please\n\n";
                }
            }
            else if(last_page < cur_book->GetTotalPages()){
                cout << "1- next page\n2- previous page\n 3- exit";
                cin >> choice;
                if(choice == 1){
                    cout << "You are now reading page (" << ++last_page << ")\n";
                }
                else if (choice == 2){
                    if(last_page == 1){
                        cout << "You can't go back further\n ";
                        continue;
                    }
                    else {
                        cout << "You are now reading page (" << --last_page << ")\n";
                    }
                }
                else if (choice == 3){
                    break;
                }
                else{
                    cout << "Choose a correct choice please\n\n";
                }

            }
            else{
                if(!finished_book){
                    cout << "congrats you just finished reading (" << cur_book->GetBookName() << ") \n";
                    finished_book = true;
                }
                cout << "1- previous\n2- exit";
                cin >> choice;
                if(choice == 1){
                    cout << "You are now reading page (" << --last_page << ")\n";
                }
                else if (choice == 2){
                    break;
                }
                else{
                    cout << "Choose a correct choice please\n\n";
                }
            }
        }
        current_user->SetLastPage(last_page,cur_book,return_current_time_and_date());
        cout << "\n\n";

    }


    void ListUsersNamesIds() const {
        for (const auto &pair : userame_userobject_map)
            cout << "\t\tName: " << pair.second->GetName() << "\n";
    }

    const User& GetCurrentUser() const {
        return *current_user;
    }
};


class OnlineBookReader{

private:

    UsersManager* usersManager; // pointer for a current users manager
    BooksManager* booksManager;  // pointer for a current books manager
public:

    OnlineBookReader() {
        usersManager = new UsersManager();  // Allocate UsersManager
        booksManager = new BooksManager();  // Allocate BooksManager
    }

    ~OnlineBookReader() {
        delete usersManager;  // Free allocated memory
        delete booksManager;  // Free allocated memory
    }
    void Run_app(){
        while(true) {
            usersManager->AccessSystem();
            usersManager->ShowMenu(*booksManager);
        }


    }

};

int main() {

    // start app
    OnlineBookReader app;
    app.Run_app();



    return 0;
}
