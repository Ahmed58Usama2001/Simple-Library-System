#include<iostream>
#include<algorithm>
using namespace std;
int addb = 0, addu = 0;
const int MAX{ 100 };
struct book {
	int id, quantity,total_borrowed=0;
	string name;

	string borrowed_books_users[MAX];
	
	void add_book()
	{
		cout << "Enter Book info: ID , Name , Total Quantity:\t";
		cin >> id>>name>> quantity;
	}

};


struct user {
	int id,borrowed=0;
	string name;

	int borrowed_books_ids[MAX];

	void add_user()
	{
		cout << "Enter user name & national ID: ";
		cin >> name >> id;
	}

};

void search_books(book books[])
{
	string prefix;
	cout << "Enter Book name prefix: ";
	cin >> prefix;
	
	bool exist = true;
	int nexist = 0;
	for (int i = 0; i < addb; i++)
	{
		exist = true;

		for (int j = 0; j < prefix.length(); j++)
		{
			if (books[i].name[j] != prefix[j])
			{
				exist = false;
				break;
			}
		}

		if (exist == true)
		{
			cout << books[i].name << endl;
			nexist++;
		}

	}
	if (nexist == 0)
		cout << "No Books With such Prefix\n";
}

bool sortid(book& a, book& b)
{
	if (a.id < b.id)
		return true;
	return false;

}

bool sortname(book& a, book& b)
{
	if (a.name < b.name)
		return true;

		return false;
}

void print_library_by_id(book books[])
{
	sort(books, books + addb, sortid);
	for (int i = 0; i < addb; i++)
		cout << "ID = " << books[i].id << " name is " << books[i].name << " Total_quantity = " << books[i].quantity << " total_borrowed = " << books[i].total_borrowed << endl;;

}

void print_library_by_name(book books[])
{
	sort(books, books + addb, sortname);
	for (int i = 0; i < addb; i++)
		cout << "ID = " << books[i].id << " name is " << books[i].name << " Total_quantity = " << books[i].quantity << " total_borrowed = " << books[i].total_borrowed << endl;;

}

void print_users(user users[])
{
	for (int i = 0; i < addu; i++)
	{
		cout << "user " << users[i].name << " ID " << users[i].id << " borrowed books ids:";
		for (int j = 0; j < MAX; j++)
		{
			if (users[i].borrowed_books_ids[j] >0)
			{
				cout << users[i].borrowed_books_ids[j] << " ";
			}
		}

		cout << endl;
	}
}

void borrow_book(user users[], book books[])
{
	cout << "Enter user name and book name: ";
		string borrowed_book, borrowing_user;
		cin >> borrowing_user >> borrowed_book;
		bool exist = false;

		for (int i = 0; i < addb; i++)
		{
			if (books[i].name == borrowed_book )
			{
				
				if ((books[i].quantity - books[i].total_borrowed) > 0)
				{
					

					for (int j = 0; j < addu; j++)
					{
						if (borrowing_user == users[j].name)
						{
							exist = true;
							books[i].borrowed_books_users[books[i].total_borrowed] = users[j].name;
							users[j].borrowed_books_ids[users[j].borrowed++] = books[i].id;
							books[i].total_borrowed++;
					    }

					}
					
				}


				break;
			}
		}
		if (!exist)
			cout << "Invalid book or invalid user.\n";
}

void return_book(user users[], book books[])
{
	cout << "Enter user name and book name: ";
	string borrowed_book, borrowing_user;
	cin >> borrowing_user >> borrowed_book;
	bool exist = false;

	for (int i = 0; i < addb; i++)
	{
		if (books[i].name == borrowed_book && books[i].total_borrowed>0)
		{
			exist = true;
			

			for (int j = 0; j < addu; j++)
			{
				if (borrowing_user == users[j].name)
				{

					for (int k = 0; k < users[j].borrowed; k++)
					{
						if (users[j].borrowed_books_ids[k] == books[i].id)
						{
							users[j].borrowed_books_ids[k] = -1;
							users[j].borrowed--;

						}
					}

					for (int l = 0; l < books[i].total_borrowed; l++)
					{
						if (books[i].borrowed_books_users[l] == users[j].name)
							books[i].borrowed_books_users[l] = "";

					}

				}

			}
			books[i].total_borrowed--;
			break;
		}
	}

	if (!exist)
		cout << "Either this book does not exist in the library or not borrowed by this user.\n";
}

void print_who_borrowed_book_by_name(user users[], book books[])
{
	cout << "Enter book name: ";
		string book_name;
	cin >> book_name;
	bool exist = false;
	for (int i = 0; i < addb; i++)
	{
		if (book_name == books[i].name)
		{
			exist = true;

			for (int j = 0; j < MAX; j++)
			{
				if (books[i].borrowed_books_users[j]!="")
				{
					cout << books[i].borrowed_books_users[j] << endl;
				}
			}
		}
	}

	if(!exist)
		cout<< "This book does not exist in the library.\n";

}


book books[MAX];
user users[MAX];

int menu()
{
	cout << "Library menu:\n1) Add Book\n2) Search Books by prefix\n3) Print who borrowed book by name\n4) Print Books list by ID\n5) Print library by name\n6)Add user\n7) User borrow book\n8) User return book\n9) Print users\n10) Exit\n";

	string choice;
	
		cin >> choice;

		if (choice == "1")
		{
			book b;
			b.add_book();
			books[addb] = b;
			addb++;
		}

		else if (choice == "2")
			search_books(books);

		else if (choice =="3")
			print_who_borrowed_book_by_name(users, books);

		else if (choice == "4")
			print_library_by_id(books);

		else if (choice == "5")
			print_library_by_name(books);

		else if (choice == "6")
		{
			user u;
			u.add_user();
			users[addu] = u;
			addu++;
		}

		else if (choice == "7")
			borrow_book(users, books);

		else if (choice == "8")
			return_book(users, books);

		else if (choice == "9")
			print_users(users);

		else if (choice == "10")
		{
			cout << "Thanks for using our library system.";
			return 0;
		}

		else
			cout << "Invalid choice..Please read the menu carfully and chose an valid option.\n";
		
		
		cout << endl;
		menu();

}


int main()
{
	menu();
	return 0;
}