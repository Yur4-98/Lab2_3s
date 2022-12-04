#pragma once
#include "Tree.h"
//#include "People.h"
#include "Person.h"
#include "B_Tree.h"
#include "IDictionary.h"
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>



void print_menu0() {
	system("cls");
	cout << "What need to check?" << endl;
	cout << "1. BTree" << endl;
	cout << "2. IDictianary" << endl;
	cout << "3. Index" << endl;
	cout << "4. Cash" << endl;
	cout << "5. Exit" << endl;
	cout << ">";
}
void print_menu_tree() {
	system("cls");
	cout << "1. Insert element in tree" << endl;
	cout << "2. remove element from tree" << endl;
	cout << "3. see elements in tree" << endl;
	cout << "4. Exit" << endl;
	cout << ">";
}
void print_menu_dictionary() {
	system("cls");
	cout << "1. Get count" << endl;
	cout << "2. Get capacity" << endl;
	cout << "3. Is key contain?" << endl;
	cout << "4. Get element by key" << endl;
	cout << "5. Add" << endl;
	cout << "6. Remove" << endl;
	cout << "7. Exit" << endl;
	cout << ">";
}
void print_menu_index() {
	system("cls");
	cout << "I create index for class Person" << endl << "Atributes:" << endl
		<< "Fio\nFirstName\nMiddleName\nLastName\nFullName\nBirthYear\nAge" << endl;
	cout << "1. Index by one atribute" << endl;
	cout << "2. Index by some atributes(later)" << endl;
	cout << "3. Check answer" << endl;
	cout << "4. Check sequence of Persons" << endl;
	cout << "5. Get element by key" << endl;
	cout << "6. Add Person" << endl;
	cout << "7. Exit" << endl;
	cout << ">";
}
void print_choose_atribute() {
	cout << "What atribute use?" <<endl;
	cout << "1 FIO" << endl;
	cout << "2 FirstName" << endl;
	cout << "3 MiddleName" << endl;
	cout << "4 LastName" << endl;
	cout << "5 FullName" << endl;
	cout << "6 BirthYear" << endl;
	cout << "7 Age" << endl;
	cout << ">";
}
void print_menu_cash() {
	system("cls");
	cout << "1. Get count" << endl;
	cout << "2. Get capacity" << endl;
	cout << "3. Is key contain?" << endl;
	cout << "4. Get element by key" << endl;
	cout << "5. Add" << endl;
	cout << "6. Remove" << endl;
	cout << "7. See cash" << endl;
	cout << "8. See dictionary" << endl;
	cout << "9. Exit" << endl;
	cout << ">";
}


int get_variant(int count) {
	int variant = 0;
	//string s;
	//getline(cin, s);

	do
	{
		cin >> variant;
		if (variant < 1 || variant > count)
		{
			cout << "Incorrec input. Try again: ";
		}
	} while (variant < 1 || variant > count);

	
	/*
	while (sscanf_s(s.c_str(), "%d", &variant) != 1 || variant < 1 || variant > count) {
		cout << "Incorrec input. Try again: ";
		getline(cin, s);
	}
	*/
	return variant;
}




void menuBTree(){
	int var = 1;
	int tmp;
	BTree<int> tree(3);
	do
	{

		print_menu_tree();
		var = get_variant(4);
		switch (var)
		{
		case 1:
			cout << "Enter a number" << endl <<">";
			
			cin >> tmp;
			tree.insert(tmp);
			break;
		case 2:
			cout << "Enter a number" << endl << ">";

			cin >> tmp;
			if (!tree.search(tmp))
			{
				cout << "This number isn't in tree" << endl;
				break;
			}
			tree.remove(tmp);
			break;
		case 3:
			cout << "Tree:" << endl;
			ArraySequence<int> s = tree.traverse();
			for (int i = 0; i < s.GetSize(); i++)
			{
				cout << s[i] <<" ";
			}
			cout << endl;
			break;

		}
			if (var != 4)
				system("pause");
	} while (var != 4);
	
}
//template <typename TKey, typename TElement>
void menuIDictionary() {
	int tmp;
	int tmp1;
	int var = 6;
	IDictionary<int, int> dict(20);
	do
	{
		print_menu_dictionary();
		var = get_variant(7);
		switch (var)
		{
		case 1:
			cout << "Count: " << dict.GetCount() << endl;
			break;
		case 2:
			cout << "Capacity: " << dict.GetCapacity() << endl;
			break;
		case 3:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			if (dict.ContainsKey(tmp))
			{
				cout << "true" << endl;
			}
			else {
				cout << "false" << endl;
			}
			break;
		case 4:
			cout << "Enter a key" << endl << ">";

			cin >> tmp;
			cout << "Element: " << dict.Get(tmp) << endl;
			break;
		case 5:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			cout << "Enter an element" << endl << ">";
			cin >> tmp1;
			dict.Add(tmp, tmp1);
			break;
		case 6:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			if (!dict.ContainsKey(tmp))
			{
				cout << "This key isn't in dictionary" << endl;
				break;
			}
			dict.Remove(tmp);
			break;
		}

		if (var != 7)
			system("pause");
	} while (var != 7);

}

void menuIndex() {
	int var = 4;
	int var2 = 0;
	string str;
	ArraySequence<Pair<string, Person>> seqs;
	ArraySequence<Pair<int, Person>> seqi;
	ArraySequence<Person> inf;
	int cur = 0;
	IDictionary<string, Person> dicts(100);
	IDictionary<int, Person> dicti(100);
	
	do
	{
		
		
		print_menu_index();
		var = get_variant(7);
		switch (var)
		{
		case 1://///???
			int tmp;
			cout << "Enter a key" << endl << ">";
			print_choose_atribute();
			tmp = get_variant(8);
			//cin >> tmp;
			switch (tmp)
			{
			case 1:
				IndexOfDataFIO<string>(inf, &dicts);
				cur = 1;
				break;
			case 2:
				IndexOfDataFN<string>(inf, &dicts);
				cur = 1;
				break;
			case 3:
				IndexOfDataMN<string>(inf, &dicts);
				cur = 1;
				break;
			case 4:
				IndexOfDataLN<string>(inf, &dicts);
				cur = 1;
				break;
			case 5:
				IndexOfDataFullN<string>(inf, &dicts);
				cur = 1;
				break;
			case 6:
				IndexOfDataBD<int>(inf, &dicti);
				cur = 2;
				break;
			case 7:
				IndexOfDataAge<int>(inf, &dicti);
				cur = 2;
				break;
			default:
				break;
			}
			break;
		case 2:
			//
			break;
		case 3:

			switch (cur)
			{
			case 1:
				seqs = dicts.GetBTree().traverse();
				for (int i = 0; i < seqs.GetSize(); i++)
				{
					cout << "[" << seqs[i].GetElement().GetFirstName() << " " << seqs[i].GetElement().GetMiddleName() << " " << seqs[i].GetElement().GetLastName() << " Birth year:" << seqs[i].GetElement().GetBirthYear() << "]" << endl;

				}
				cout << endl;
				break;
			case 2:
				seqi = dicti.GetBTree().traverse();
				for (int i = 0; i < seqi.GetSize(); i++)
				{
					cout << "[" << seqi[i].GetElement().GetFirstName() << " " << seqi[i].GetElement().GetMiddleName() << " " << seqi[i].GetElement().GetLastName() << " Birth year:" << seqi[i].GetElement().GetBirthYear() << "]" << endl;

				}
				cout << endl;
				break;
			}

			break;
		case 4:
			for (int i = 0; i < inf.GetSize(); i++)
			{
				cout << "[" << inf[i].GetFirstName() << " " << inf[i].GetMiddleName() << " " << inf[i].GetLastName() << " Birth year:" << inf[i].GetBirthYear() << "]" <<endl;
			}
			cout << endl;
			break;
		case 5:
			cout << "1 ~ int | 2 ~ string"<<endl;
			var2 = get_variant(2);
			if (var2 == 1)
			{
				cout << "Enter a key" << endl << ">";
				cin >> tmp;
			
				cout << "Element: " << "[" << dicti.Get(tmp).GetFirstName() << " " << dicti.Get(tmp).GetMiddleName() << " " << dicti.Get(tmp).GetLastName() << " Birth year:" << dicti.Get(tmp).GetBirthYear() << "]" << endl;
			}
			else
			{
				cout << "Enter a key" << endl << ">";
				cin >> str;
				cout << "Element: " << "[" << dicts.Get(str).GetFirstName() << " " << dicts.Get(str).GetMiddleName() << " " << dicts.Get(str).GetLastName() << " Birth year:" << dicts.Get(str).GetBirthYear() << "]" << endl;
			}
			
			break;
			
		case 6:
			string FN;
			cout << "Enter first name" << endl << ">";
			cin >> FN;
			string MN; 
			cout << "Enter middle name" << endl << ">";
			cin >> MN;
			string LN; 
			cout << "Enter last name" << endl << ">";
			cin >> LN;
			int BD; 
			cout << "Enter birth year" << endl << ">";
			cin >> BD;
			Person tmpp(FN,MN,LN,BD);
			inf.Append(tmpp);
			break;
		
		}

		if (var != 7)
			system("pause");
	} while (var != 7);

}

void menuCash() {
	int tmp = 0;
	int tmp1 = 1;
	int var = 7;
	Cash<int, int> c(5);
	IDictionary<int, int> dict(20);
	ArraySequence<Pair<int, int>> seqc;
	ArraySequence<Pair<int, int>> seqd;
	do
	{
		print_menu_cash();
		var = get_variant(9);
		switch (var)
		{
		case 1:
			cout << "Dictianry's count: " << dict.GetCount() << endl;
			cout << "Cash's count: " << c.GetCount() << endl;
			break;
		case 2:
			cout << "Dictianry's capacity: " << dict.GetCapacity() << endl;
			cout << "Cash's capacity: " << c.GetCapacity() << endl;
			break;
		case 3:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			if (c.ContainsKey(tmp))
			{
				cout << "true" << endl;
			}
			else {
				if (dict.ContainsKey(tmp))
				{
					cout << "true" << endl;
				}
				else
				{
					cout << "false" << endl;
				}
			}
			break;
		case 4:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			if (c.ContainsKey(tmp))
			{
				cout << "Element: " << c.Get(tmp) << endl;
			}
			else
			{
				if (dict.ContainsKey(tmp))
				{
					cout << "Element: " << dict.Get(tmp) << endl;
					c.Add(tmp, dict.Get(tmp));
				}
				else
				{
					cout << "There is not this key in dictionary" << endl;
				}
			}
			break;
		case 5:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			cout << "Enter an element" << endl << ">";
			cin >> tmp1;
			dict.Add(tmp,tmp1);
			c.Add(tmp, tmp1);
			break;
		case 6:
			cout << "Enter a key" << endl << ">";
			cin >> tmp;
			if (!dict.ContainsKey(tmp))
			{
				cout << "This key isn't in dictionary" << endl;
				break;
			}
			dict.Remove(tmp);
			break;
		case 7:
			seqc = c.GetCash().GetBTree().traverse();
			for (int i = 0; i < seqc.GetSize(); i++)
			{
				cout << seqc[i] << endl;
			}
			cout << endl;
			break;
		case 8:
			seqd = dict.GetBTree().traverse();
			for (int i = 0; i < seqd.GetSize(); i++)
			{
				cout << seqd[i] << endl;
			}
			cout << endl;
			break;
		}
		if (var != 9)
			system("pause");
	} while (var != 9);
	
}


void menu() {
	int var = 0;
	
	
	do
	{
		print_menu0();
		var = get_variant(5);
		switch (var)
		{
		case 1:
			menuBTree();//int
			break;
		case 2:
			menuIDictionary();//int | int
			break;
		case 3:
			menuIndex();
			break;
		case 4:
			menuCash();
			break;
		}
	} while (var!=5);
}